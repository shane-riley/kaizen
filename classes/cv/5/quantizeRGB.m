function [outputImg, meanColors, clusterIds] = quantizeRGB(origImg, k)
%% QUANTIZERGB clusters an image in 3-D RGB space and quantizes it
%
% INPUTS:
%
% origImg:      Original uint8 images
% k:            Number of clusters (colors)
%
% OUTPUTS:
% 
% outputImg:    Clustered image
% meanColors:   k-by-3 array of average colors
% clusterIds:   n_r x n_c-by-1 vector identifying clusters
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/16/2022
% Version tested: R2020b

    % Setup
    [n_r, n_c, n_ch] = size(origImg);
    n_p = n_r * n_c;
    
    % Reshape per pixel
    per_pixel = reshape(double(origImg), [n_p, n_ch]);
    
    % Run kmeans to get ids and means
    [clusterIds, meanColors] = kmeans(per_pixel, k);
    
    % Write output image
    outputImg = uint8(zeros(size(origImg)));
    for p = 1:prod(size(outputImg,[1 2]))
        [i,j] = ind2sub(size(outputImg, [1 2]), p);
        outputImg(i,j,:) = meanColors(clusterIds(p), :);
    end
    
    % Print
    figure;
    imshow(outputImg);
    
end