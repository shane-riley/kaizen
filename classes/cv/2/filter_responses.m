%% FILTER_RESPONSES.m
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/26/2022
% Version tested: R2020b

clear;
close all;
clc;

%% CONSTANTS
IMG_SIZE = 100;
FILENAMES = {...
    'cardinal1.jpg'
    'cardinal2.jpg'
    'leopard1.jpg'
    'leopard2.jpg'
    'panda1.jpg'
    'panda2.jpg'
};

%% LOAD
% Grab filters
F = makeLMfilters();

% Load in images
ims = cellmat(length(FILENAMES), 1, IMG_SIZE, IMG_SIZE);
for i = 1:length(FILENAMES)
    ims{i} = imresize(rgb2gray(imread(FILENAMES{i})), [IMG_SIZE, IMG_SIZE]);
end

%% APPLY FILTERS
% For each filter
for i = 1:size(F,3)
    
    % Make a figure
    figure(i)
    
    % Show the plain filter
    subplot(2,4,1)
    imagesc(F(:,:,i));
    
    for j = 1:length(FILENAMES)
        im_filtered = imfilter(ims{j},F(:,:,i));
        subplot(2, 4, j + 2);
        imagesc(im_filtered);
        title(FILENAMES{j});
    end
end

%% PICK TO SAVE
ANIMALS_DIFFERENT = 41;
ANIMALS_SIMILAR = 36;
figure(ANIMALS_DIFFERENT);
print('different_animals_similar', '-dpng');
figure(ANIMALS_SIMILAR);
print('same_animal_similar', '-dpng');