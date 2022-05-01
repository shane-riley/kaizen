function [features] = compute_features(x, y, scores, Ix, Iy)
%% COMPUTE_FEATURES Using harris results, find SIFT features
%
% INPUTS:
%
% x:            x-locations of keypoints
% y:            y-locations of keypoints
% scores:       scores of keypoints
% Ix:           Horizontal gradient
% Iy:           Vertical gradient
%
% OUTPUTS:
% 
% features:     Nxd matrix (N is num features and d is num dimensions)
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/5/2022
% Version tested: R2020b
    
    % CONSTANTS
    w = 11;                 % window size
    [n_r, n_c] = size(Ix);  % Img dimensions
    h_w = floor(w / 2);     % Half window size
    D = 8;                  % Num dimensions
    CLIP = .2;
    
    % Drop keypoints without full window in bounds
    r_min = 1 + h_w;
    c_min = 1 + h_w;
    r_max = n_r;
    c_max = n_c;
    
    % Identify to drop
    indeces_to_keep = [];
    for i = 1:length(x)
        if ((x(i) + h_w <= c_max && x(i) - h_w > 0) && ...
            (y(i) + h_w <= r_max && y(i) - h_w > 0))
            
            indeces_to_keep = [indeces_to_keep, i];
        end
    end
    
    % Drop
    x = x(indeces_to_keep);
    y = y(indeces_to_keep);
    scores = scores(indeces_to_keep);
    
    n_p = length(x);  % num remaining points
    % Loop through keypoints
    features = zeros(n_p, D);
    for i = 1:n_p
        x_p = x(i);
        y_p = y(i);
        % Init matrices for window
        m = zeros(w,w);
        theta = zeros(w,w);
        dimensions = zeros(1, D);
        
        % Loop through windows
        for j = -h_w:h_w
            for k = -h_w:h_w
                
                % Compute m
                m(j + h_w + 1, k + h_w + 1) = ...
                    sqrt(Ix(y_p + j, x_p + k).^2 + Iy(y_p + j, x_p + k).^2);
                
                % Compute theta
                theta(j + h_w + 1, k + h_w + 1) = ...
                    atand(Iy(y_p + j, x_p + k)/Ix(y_p + j, x_p + k));
            end
        end
        
        % Bin
        bin = discretize(theta, linspace(-90, 90, D + 1));
        
        % Populate dimensions
        for d_i = 1:D
            dimensions(d_i) = sum(m(bin == d_i));
        end
        
        % Normalize and clip values
        dimensions = dimensions ./ sum(dimensions);
        dimensions = min(dimensions, CLIP);
        
        % Normalize
        features(i,:) = dimensions ./ sum(dimensions);
    end  
end