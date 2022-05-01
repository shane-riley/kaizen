%% HYBRID_IMAGES.m
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/26/2022
% Version tested: R2020b

clear;
close all;
clc;

%% CONSTANTS
FILE1 = 'baby_happy.jpg';
FILE2 = 'baby_weird.jpg';
IMG_SIZE = 512;

%% IMPORT IMAGES
im1 = imresize(rgb2gray(imread(FILE1)), [IMG_SIZE, IMG_SIZE]);
im2 = imresize(rgb2gray(imread(FILE2)), [IMG_SIZE, IMG_SIZE]);

%% FILTER IMAGE
im1_blur = imgaussfilt(im1, 10, 'FilterSize', 31);
im2_blur = imgaussfilt(im2, 10, 'FilterSize', 31);

%% OBTAIN DETAIL
im2_detail = im2 - im2_blur;

%% HYBRIDIZE
hybrid = im1_blur + im2_detail;

%% PRINT AND SAVE
imshow(hybrid);
print('hybrid', '-dpng');
