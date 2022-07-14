#!/usr/bin/env python

"""
vmsim -- Virtual memory simulator

Author: Shane Riley
Course: os
Date:   4/5/2022

Usage: vmsim [OPTION] [TRACEFILE]

-a      Algorithm (opt or lru)
-n      Number of frames
-p      pagesize in KB
-s      Memory split (x:y) form

"""

import argparse
import sys
import os
import math

N_BITS = 32

def parse_line(line):
    """Parse a line"""
    entries = line.split(' ')
    return (entries[0], entries[1], int(entries[2]))

def get_page_number(address, n_offset_bits):

    # Go to int
    int_address = int(address, 16)

    #import pdb; pdb.set_trace()
    # Drop offset bits
    return (int_address >> n_offset_bits)


def run_sim(tracefile, algorithm, n_frames, pagesize, mem_1, mem_2, d):
    """Run the simulation."""

    # Initialize current_timeers
    n_accesses = 0
    n_faults = 0
    n_writes = 0
    current_time = 0

    # Initialize structure
    n_offset_bits = int(math.ceil(math.log(pagesize)/math.log(2)) + 10)  # bits per page
    n_page_bits = N_BITS - n_offset_bits
    n_frames_proc = (
        int(n_frames * (mem_1)/(mem_1 + mem_2)),
        int(n_frames * (mem_2)/(mem_1 + mem_2))
    )

    if (d): assert(n_frames_proc[0] + n_frames_proc[1] == n_frames)

    # Init tables
    # Maps decimal page number to page
    # Page is a list with dirty bit and age
    tables = ({}, {})
    # Open trace
    with open(tracefile, 'r') as f:
        # Loop through trace lines
        lines = f.readlines()


    future = {}
    if algorithm == 'opt':
        # Populate lists of futures
        for i in range(len(lines)):
            line = lines[i]
            _, address, _ = parse_line(line)
            page = get_page_number(address, n_offset_bits)
            future.setdefault(page, [0, []])
            future[page][1].append(i)



    # Loop through lines
    for line_i, line in enumerate(lines):

        if d and line_i%10000==0:
            print("Prog: {:2.2f}\t%".format(100*(line_i)/len(lines)))

        # Parse trace line
        op, address, proc = parse_line(line)
        page = get_page_number(address, n_offset_bits)

        # Check page not in table
        if page not in tables[proc]:

            # Fault!
            n_faults += 1

            # Is eviction necessary
            if (d): assert (len(tables[proc]) <= n_frames_proc[proc])
            if len(tables[proc]) >= n_frames_proc[proc]:
                # Yes!

                # Make a list containing the page numbers
                page_list = list(tables[proc].keys())

                # Find page_to_remove
                if algorithm == 'opt' and len(page_list) > 1:
                    # RUN OPT

                    frame_earliest_lines = [-1]*len(page_list)
                    missing_pages = []
                    for page_i, c_page in enumerate(page_list):
                        future_list = future[c_page][1]
                        for j in range(future[c_page][0], len(future_list)):
                            if future_list[j] > line_i:
                                #if (d): print("Found in {} lines".format(j - future[c_page][0]))
                                future[c_page][0] = j
                                frame_earliest_lines[page_i] = future_list[j]
                                break
                            if j == len(future_list) - 1:
                                missing_pages.append(c_page)
                    
                    if len(missing_pages) == 0:
                        page_to_remove = page_list[frame_earliest_lines.index(max(frame_earliest_lines))]
                    else:
                        frame_times = list(map(lambda x: tables[proc][x][1], missing_pages))
                        page_to_remove = page_list[frame_times.index(min(frame_times))]
                    
                    
                    
                else:
                    # Run LRU
                    frame_times = list(map(lambda x: tables[proc][x][1], page_list))
                    page_to_remove = page_list[frame_times.index(min(frame_times))]

        
                
                # Page to remove is found
                # Check whether page to remove is dirty
                if tables[proc][page_to_remove][0]:
                    # Dirty, must write back
                    n_writes += 1

                # Remove the page
                tables[proc].pop(page_to_remove)
            
            # Space guaranteed
            # Bring in new page
            tables[proc][page] = [0, -1]
            current_time += 1
        
        # Page now in table
        # If store, set dirty bit
        if op == 's':
            tables[proc][page][0] = 1

        # Increment age
        tables[proc][page][1] = current_time
        # Access
        n_accesses += 1

    # Done
    return (n_accesses, n_faults, n_writes)


def main():
    """Main function"""

    ## Parse arguments
    parser = argparse.ArgumentParser(description="Virtual memory simulator.")
    parser.add_argument('-a', dest='algorithm', nargs='?', type=str, default='opt', help="Choice of algorithm (opt/lru)")
    parser.add_argument('-n', dest='n_frames', nargs='?', type=int, default=2, help="Number of frames")
    parser.add_argument('-p', dest='pagesize', nargs='?', type=int, default=4, help="Pagesize in KB")
    parser.add_argument('-s', dest='mem_split', nargs='?', type=str, default='1:1', help="Memory split (x:y)")
    parser.add_argument('--debug', dest='debug', action='store_true', help="Debug mode")
    parser.add_argument('tracefile', metavar='trace', type=str, nargs=1, help="File to step through")

    # Parse args
    args = parser.parse_args()
    algorithm = 'lru' if args.algorithm.lower() == 'lru' else 'opt'
    n_frames = args.n_frames
    pagesize = args.pagesize
    tracefile = args.tracefile[0]
    mem_split = args.mem_split
    debug = args.debug
    

    # Make some assertions
    if n_frames < 1:
        print("Invalid number of frames.")
        sys.exit(-1)
    if pagesize <= 0:
        print("Invalid pagesize.")
        sys.exit(-1)
    if not os.path.exists(tracefile):
        print("Tracefile \"{}\" not found.".format(tracefile))
        sys.exit(-1)

    # Get mem
    try:
        mem_a, mem_b = list(map(lambda x: int(x), mem_split.split(':')))
    except e:
        print("Invalid memsplit")
        sys.exit(-1)

    # Call the solver
    n_accesses, n_faults, n_writes = run_sim(tracefile, algorithm, n_frames, pagesize, mem_a, mem_b, debug)

    # Print results
    print('''\
Algorithm: {}
Number of frames: {}
Page size: {} KB
Total memory accesses: {}
Total page faults: {}
Total writes to disk: {}\
'''.format(algorithm.upper(),
           n_frames,
           pagesize,
           n_accesses,
           n_faults,
           n_writes))
    

if __name__ == "__main__":
    main()