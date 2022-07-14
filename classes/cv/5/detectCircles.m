function [centers] = detectCircles(im, edges, radius, top_k)
%% DETECTCIRCLES Using Hough Transform, Find circles from edges
%
% INPUTS:
%
% im:        uint8 image
% edges:     edges return from detectEdges N-by-(x,y,|g|,theta degrees)
% radius:    Circle size to detect
% top_k:     Number of circles to output
%
% OUTPUTS:
% 
% centers:   Matrix containing circle centers (N-by-2)
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/16/2022
% Version tested: R2020b

    % Constants
    QUANTIZATION = 5;
    n_e = size(edges, 1);
    [n_r, n_c, ~] = size(im);
    
    % Only going to detect circles contained completely within the image
    hough = zeros(ceil(n_r/QUANTIZATION),ceil(n_c/QUANTIZATION));
    
    % Loop through edges to populate votes
    for i = 1:n_e
       edge = edges(i,:);
       vote_x = edge(1) + radius * cosd(edge(4));
       vote_y = edge(2) + radius * sind(edge(4));
       hough_vote_i = ceil(vote_x / QUANTIZATION);
       hough_vote_j = ceil(vote_y / QUANTIZATION);
       if (hough_vote_i > 0 && hough_vote_i <= size(hough,1) && ...
               hough_vote_j > 0 && hough_vote_j <= size(hough,2))
            hough(hough_vote_i, hough_vote_j) = hough(hough_vote_i, hough_vote_j) + 1;
       end
    end
    
    % Debug: show hough space
    figure;
    imagesc(hough);
    
    % Pull indeces in hough space
    [~, indeces] = maxk(hough(:), top_k);
    
    % Get coordinates in hough space
    [hough_center_y, hough_center_x] = ind2sub(size(hough), indeces);
    
    % Translate coordinates back to image space
    centers = [hough_center_x * QUANTIZATION - QUANTIZATION/2, hough_center_y * QUANTIZATION - QUANTIZATION/2];
    
    % Plot
    figure;
    imshow(im);
    viscircles([centers(:,2), centers(:,1)], radius * ones(size(centers,1),1));
end