function [pyramid, level_0, level_1] = computeSPMRepr(im_size, sift, means)
%% COMPUTESPMREPR Make the pyramid SIFT representation 
%
% INPUTS:
%
% im_size:  Size of image
% sift:     Sift features for one image
% means:    Sift cluster means
%
% OUTPUTS:
% 
% num_samples x feature dimensions
% pyramid: 1xD feature descriptor for the image combining both levels
% level_0: standard bag-of-words histogram
% level_1: bag-of-words histogram (one for each quadrant)
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/21/2022
% Version tested: R2020b

    % Get the BOW Representation (which is level zero)
    % Transpose to get descriptors per row
    descriptors = double(sift.d');
    level_0 = computeBOWRepr(descriptors, means);
    
    % Get level one representation
    r_chunk = im_size(1) / 2;
    c_chunk = im_size(2) / 2;
    n_values = size(means,1);
    
    level_1 = zeros(1, 4 * n_values);
    y = sift.f(1,:);
    x = sift.f(2,:);
    for r = 0:1
        for c = 0:1
            filter_mask = (y > r*r_chunk) & ...
                          (y <= (r+1)*r_chunk) & ...
                          (x > c*c_chunk) & ...
                          (x <= (c+1)*c_chunk);
            filtered_desc = descriptors(filter_mask, :);
            start_loc = r*(size(level_1,2)/2) + c*(size(level_1,2))/4 + 1;
            end_loc = start_loc + (size(level_1,2))/4 - 1;
            histogram_piece = computeBOWRepr(filtered_desc, means);
            level_1(1,start_loc:end_loc) = histogram_piece;
        end
    end
    
    % Concatenate for pyramid
    pyramid = [level_0, level_1];

end
