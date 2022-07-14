function [reducedColorImage] = reduceWidth(im, display_flag)
%% REDUCEWIDTH Determine the energy of each pixel in an image
%
% INPUTS:
%
% im:               image
% display_flag:     whether to display the subplots
%
% OUTPUTS:
% 
% reducedColorImage: output image
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/26/2022
% Version tested: R2020b
    
    % Get energy
    energyImage = energy_image(im);
    M = cumulative_minimum_energy_map(energyImage, 'VERTICAL');
    vs = find_optimal_vertical_seam(M);
    
    % Check size
    [n_r, n_c, n_ch] = size(im);
    assert(length(vs) == n_r);
    
    % Allocate
    reducedColorImage = zeros([n_r n_c-1 n_ch]);
    
    % Cut seam
    for i = 1:n_r
        for j = 1:n_ch
            col = im(i, :, j);
            col(vs(i)) = [];
            reducedColorImage(i, :, j) = col;
        end
    end
    
    % Cast
    reducedColorImage = uint8(reducedColorImage);
    
    % Display
    if (display_flag)
        figure;
        subplot(1, 3, 1); imagesc(energyImage);
        subplot(1, 3, 2); imagesc(M);
        subplot(1, 3, 3); imshow(im); displaySeam(im, vs, 'VERTICAL');
    end
end