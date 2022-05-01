function [bow_repr] = computeBOWRepr(features, means)
%% COMPUTEBOWREPR compute Bag Of Words representation
%
% INPUTS:
%
% features:     NxD matrix of weights
% means:        kxD Cluster means
%
% OUTPUTS:
% 
% bow_repr:     Normalized bag-of-words histogram
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/5/2022
% Version tested: R2020b

    % Find distances to means
    [k,D] = size(means);
    bow = zeros(1,k);
    for f_i = 1:size(features,1)
       feature = features(f_i, :);
       distances = pdist2(feature, means);
       [nearest_dist, nearest_neighbor_i] = min(distances);
       bow(nearest_neighbor_i) = bow(nearest_neighbor_i) + 1; 
    end
    bow_repr = bow / sum(bow);
end