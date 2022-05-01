function [x,y, scores, Ih, Iv] = extract_keypoints(image)
%% EXTRACT_KEYPOINTS Using Harris, determine the location of keypoints
%
% INPUTS:
%
% image:        uint8 image
%
% OUTPUTS:
% 
% x:            X-locations (colomns)
% y:            Y-locations (rows)
% scores:       R-score per keypoint
% Ih:           Horizontal gradient
% Iv:           Vertical gradient
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/5/2022
% Version tested: R2020b

    % Constants
    NUM_KEYS = 3000;
    k = 0.05;
    window_size = 5;  % must be odd
    [n_r, n_c, ~] = size(image);
    half_window_size = floor(window_size / 2);
    
    % Setup
    img_gray = im2double(rgb2gray(image));
    fil_x = [2 0 -2; 1 0 -1; 2 0 -2];
    fil_y = fil_x';
    Ih = imfilter(img_gray, fil_x);
    Iv = imfilter(img_gray, fil_y);
    R = zeros(n_r, n_c);
    
    
    % Compute R
    for i = 1:n_r
        for j = 1:n_c
            % Find R(i,j)
            
            % Check window in bounds
            if (i - half_window_size > 0) && ...
               (j - half_window_size > 0) && ...
               (i + half_window_size <= n_r) && ...
               (j + half_window_size <= n_c)
                
                % Calculate M
                M = zeros(2,2);
                for u = -half_window_size:half_window_size
                    for v = -half_window_size:half_window_size
                        M = M + [...
                            Ih(i+u,j+v).^2          Ih(i+u,j+v).*Iv(i+u,j+v)
                            Ih(i+u,j+v).*Iv(i+u,j+v)    Iv(i+u,j+v).^2      ];
                    end
                end
                R(i,j) = det(M) - k .* (trace(M)).^2;
            else
                R(i,j) = -Inf;
            end
        end
    end
    
    % Use maxk
    [~, indeces] = maxk(R(:), NUM_KEYS);
    sorted_R = sort(R, 'descend');
    
    % Perform non-max suppression
    indeces_to_keep = [];
    for i = 1:length(indeces)
        j = indeces(i);
        if (R(j) > R(j + 1)) && ...
           (R(j) > R(j - 1)) && ...
           (R(j) > R(j + n_r)) && ...
           (R(j) > R(j + n_r + 1)) && ...
           (R(j) > R(j + n_r - 1)) && ...
           (R(j) > R(j - n_r)) && ...
           (R(j) > R(j - n_r + 1)) && ...
           (R(j) > R(j - n_r - 1))
            
            indeces_to_keep = [indeces_to_keep; i];
        end
    end
    
    indeces = indeces(indeces_to_keep);
    
    % Unpack indeces
    [y,x] = ind2sub([n_r, n_c], indeces);
    scores = R(indeces);
    
    % Perform plot
%     figure;
%     imshow(image);
%     hold on
%     for i = 1:length(indeces)
%         plot(x(i), y(i), 'mo', 'MarkerSize', scores(i) / 1000000000);
%     end
%     hold off
end