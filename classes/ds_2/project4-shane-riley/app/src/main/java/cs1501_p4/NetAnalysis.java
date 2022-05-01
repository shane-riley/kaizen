/**
 * Network Analysis class for CS1501 Project 4
 * @author	Shane Riley
 */

package cs1501_p4;

import java.util.ArrayList;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class NetAnalysis implements NetAnalysis_Inter {

    // Instance variables
    myLL[] adj;
    int numEdges;


    public NetAnalysis(String filename)  {

        try {
            // Open file
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line;
            String arr[];
            int from, to, bandwidth, length;
            boolean isCopper;
            Link link1, link2;

            // Get number of vertices
            line = br.readLine();
            int numVertices = Integer.parseInt(line);
            adj = new myLL[numVertices];

            // Initialize lists
            for (int i = 0; i < numVertices; i++) {
                adj[i] = new myLL();
            }
            numEdges = 0;
            // Read links
            while ((line = br.readLine()) != null) {
                arr = line.split(" ");
                assert (arr.length == 5);

                from = Integer.parseInt(arr[0]);

                to = Integer.parseInt(arr[1]);
                isCopper = (arr[2].equals("copper"));
                bandwidth = Integer.parseInt(arr[3]);
                length = Integer.parseInt(arr[4]);

                link1 = new Link(from, to, isCopper, bandwidth, length);
                link2 = new Link(to, from, isCopper, bandwidth, length);

                // Add to from and to
                adj[from].addHead(link1);
                adj[to].addHead(link2);
                numEdges++;
            }
            br.close();
        } catch (IOException e) {
            System.out.println("Bad state!");
        }
    }
    
    public ArrayList<Integer> lowestLatencyPath(int u, int w) {

        // Use Dijkstra, featuring a PQ
        
        // Declare and init
        int[] via = new int[adj.length];
        double[] distTo = new double[adj.length];
        boolean[] visited = new boolean[adj.length];
        for (int i = 0; i < adj.length; i++) {
            via[i] = -1;
            distTo[i] = Double.POSITIVE_INFINITY;
        }
        
        // index is node, key is distance to node from U
        IndexMinPQ<Double> toVisit = new IndexMinPQ<>(adj.length);

        Link l;
        myLL ll;

        int thisNode = u;

        // Visit thisNode
        distTo[thisNode] = 0.0;
        visited[thisNode] = true;

        // Add thisNode's neighbors
        ll = adj[thisNode];
        ll.reset();
        while (ll.hasThis()) {
            l = ll.getThis();
            ll.getNext();
            distTo[l.getTo()] = l.getLatency() + distTo[thisNode];
            toVisit.insert(l.getTo(), distTo[l.getTo()]);
            via[l.getTo()] = thisNode;
        }

        // While the next node to visit is not w
        while (toVisit.minIndex() != w) {

            // Visited nodes are excluded from the PQ
            int nextNode = toVisit.minIndex();

            // Visit nextNode
            toVisit.delete(nextNode);
            
            visited[nextNode] = true;
            thisNode = nextNode;

            // Add all neighbors to PQ that are not already visited
            ll = adj[thisNode];
            ll.reset();
            while (ll.hasThis()) {
                l = ll.getThis();
                ll.getNext();

                // Skip if visited
                if (visited[l.getTo()]) continue;

                double dist = l.getLatency() + distTo[thisNode];

                if (dist < distTo[l.getTo()]) {
                    // This path is better
                    distTo[l.getTo()] = dist;
                    via[l.getTo()] = thisNode;

                    if (toVisit.contains(l.getTo())) {
                        toVisit.changeKey(l.getTo(), dist);
                    } else {
                        toVisit.insert(l.getTo(), dist);
                    }
                } else {
                    // This path is not better
                    // PQ does not change, neither does via or distTo
                }
            }

            if (toVisit.isEmpty()) break;
        }

        if (distTo[w] == Double.POSITIVE_INFINITY) return null;

        // Backprop to find the list
        ArrayList<Integer> al = new ArrayList<>();
        al.add(0, w);
        int n = w;
        while (true) {
            n = via[n];
            al.add(0, n);
            if (n == u) break;
        }
        
        return al;
    }


    public int bandwidthAlongPath(ArrayList<Integer> p) throws IllegalArgumentException {
        // Move from first to last element, using adj to find the minimum bandwidth and throwing if now there
        
        int minBandwidth = Integer.MAX_VALUE;
        Link link;
        int from, to;

        for (int i = 0; i < p.size()-1; i++) {
            // check link from i to i+1

            from = p.get(i);
            to = p.get(i+1);

            link = adj[from].get(to);
            
            // Check for nonexistent link
            if (link == null) throw new IllegalArgumentException();

            minBandwidth = Math.min(minBandwidth, link.getBandwidth());
        }
        return minBandwidth;
    }

    public boolean copperOnlyConnected() {
        // Conduct a DFS, ignoring fiber optic lines
        // If there is an unvisited node return false. Else, true.
        
        boolean[] visited = new boolean[adj.length];
        int node = 0;
        boolean onlyCopper = true;

        dfs(node, visited, onlyCopper);

        // Check for any false visiteds
        for (boolean y : visited) {
            if (!y) return false;
        }
        return true;
    }

    private void dfs(int node, boolean[] visited, boolean onlyCopper) {

        // Add node to visited
        visited[node] = true;

        // Recurse through each edge
        myLL thisAdj = adj[node];
        Link link;

        while (thisAdj.hasThis()) {
            link = thisAdj.getThis();
            thisAdj.getNext();

            // If optical and onlyCopper, skip
            if (!link.getIsCopper() && onlyCopper) continue;

            // If visited, skip
            if (visited[link.getTo()]) continue;

            // Else, recurse
            dfs(link.getTo(), visited, onlyCopper);
        }
    }

    public boolean connectedTwoVertFail() {
        // is the graph triconnected?
        // For each node, remove and ensure graph remains biconnected.
        
        // Check connection
        boolean[] nodes = new boolean[adj.length];
        dfs(0, nodes, false);
        for (int i = 0; i < nodes.length; i++) {
            if (!nodes[i]) return false;
        }

        for (int i = 0; i < adj.length; i++) {

            // Exclude i, check for articulartion points
            // If there is one, return false
            int[] cnt = new int[1];
            int[] low = new int[adj.length];
            int[] pre = new int[adj.length];
            int v;
            for (v = 0; v < adj.length; v++) {
                low[v] = -1;
                pre[v] = -1;
            }

            for (v = 0; v < adj.length; v++) {
                if (pre[v] == -1 && v != i) {
                    if (bidfs(i,v,v, pre, low, cnt)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private boolean bidfs(int exclude, int u, int v, int[] pre, int[] low, int[] cnt) {
        int children = 0;
        pre[v] = cnt[0]++;
        low[v] = pre[v];
        
        int w;
        myLL ll = adj[v];
        Link l;
        ll.reset();
        while (ll.hasThis()) {
            l = ll.getThis();
            ll.getNext();
            w = l.getTo();
            if (w == exclude) continue;

            if (pre[w] == -1) {
                children++;
                if (bidfs(exclude, v, w, pre, low, cnt))
                    return true;
                
                low[v] = Math.min(low[v], low[w]);

                if (low[w] >= pre[v] && u != v)
                    return true;
            }
            else if (w != u) {
                low[v] = Math.min(low[v], pre[w]);
            }
        }

        if (u == v && children > 1) {
            return true;
        }
        return false;
    }

    public ArrayList<STE> lowestAvgLatST() {
        // Use Kruskals algorithm

        // Check connection
        boolean[] nodes = new boolean[adj.length];
        dfs(0, nodes, false);
        for (int i = 0; i < nodes.length; i++) {
            if (!nodes[i]) return null;
        }

        // Make an array and corresponding IndexPQ for links
        Link[] links = new Link[numEdges];
        IndexMinPQ<Double> latencies = new IndexMinPQ<>(numEdges);

        int n = 0;
        myLL ll;
        Link l;
        for (int i = 0; i < adj.length; i++) {
            ll = adj[i];
            ll.reset();
            while (ll.hasThis()) {
                l = ll.getThis();
                ll.getNext();
                if (l.getFrom() > l.getTo()) continue;
                links[n] = l;
                latencies.insert(n, l.getLatency());
                n++;
                if (n == numEdges) break;
                
            }
            if (n == numEdges) break;
        }

        // Make the arraylist
        ArrayList<STE> al = new ArrayList<>();
        boolean[] visited = new boolean[adj.length];

        // A list and PQ of links is made
        int nPlaced = 0;
        while (nPlaced < adj.length - 1) {
            // Get lowest weight link
            l = links[latencies.minIndex()];
            latencies.delMin();

            if (visited[l.getTo()] && visited[l.getFrom()]) {
                // Will introduce a cycle, skip
                continue;
            } else {
                // Make STE from link
                visited[l.getFrom()] = true;
                visited[l.getTo()] = true;
                STE ste = new STE(l.getFrom(), l.getTo());
                al.add(ste);
                nPlaced++;
            }   
        }
        return al;
    }

    // Debug
    public void printGraph() {
        myLL ll;
        Link link;

        for (int i = 0; i < adj.length; i++) {
            ll = adj[i];

            while (ll.hasThis()) {
                link = ll.getThis();
                System.out.println(i + " " + link.getTo() + " " + (link.getIsCopper() ? "copper" : "optical") + " " + link.getBandwidth() + " " + link.getLength() + " " + link.getLatency() * 1000000.0);
                ll.getNext();
            }
            
        }
    }


}
