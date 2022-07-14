function run_circle(filename, threshold, radius, top_k)
%% RUN_CIRCLE Using Hough Transform, Find circles from edgges

% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/16/2022
% Version tested: R2020b
    clc
    close all
    im = imread(filename);
    edges = detectEdges(im, threshold);
    centers = detectCircles(im, edges, radius, top_k);
end