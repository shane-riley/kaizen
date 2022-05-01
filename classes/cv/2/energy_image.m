function [energyImage, Ix, Iy] = energy_image(im)
%% ENERGY_IMAGE Determine the energy of each pixel in an image
%
% INPUTS:
%
% im:           image
%
% OUTPUTS:
%
% energyImage:  the L2 norm of the image
% Ix:           gradient w.r.t x
% Iy:           gradient w.r.t y
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/26/2022
% Version tested: R2020b

    % Create filters
    % Sobel filter
    filter_x = [...
        1 0 -1
        ];
    
    filter_y = filter_x';
    
    im = rgb2gray(im);
    
    % Apply filters
    Ix = double(imfilter(im, filter_x));
    Iy = double(imfilter(im, filter_y));
    
    % Compute energy
    energyImage = sqrt(Ix.^2 + Iy.^2);
end