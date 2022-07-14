%% MOSAIC 
%
% INPUTS:
%
% p1:       Matrix of points from first image 4x2
% H:        Projective transformation matrix 3x3
%
% OUTPUTS:
% 
% p2:       Post-homography points
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/24/2022
% Version tested: R2020b

clear;
clc;
close all;

img1_n = "keble1.png";
img2_n = "keble2.png";

% RESULT POINTS (MANUAL)
P1 = [...
  254, 101
  259, 21
  338, 15
  352, 123
];

P2 = [...
  160, 117
  166, 38
  242, 35
  251, 141
];

P1_sample = [244, 159];

% Read and display images
im1 = imread(img1_n);
im2 = imread(img2_n);

% Determine the homography
H = estimate_homography(P1, P2);

% Estimate point
P2_sample = apply_homography(P1_sample, H);

% Replot in subplots for assignment
f = figure;
subplot(1,2,1);
imshow(im1);
hold on;
impixelinfo();
plot(P1_sample(:,1), P1_sample(:,2), 'go');
plot(P1(:,1), P1(:,2), 'ro');
title('Homography input');
subplot(1,2,2);
imshow(im2);
hold on;
impixelinfo();
plot(P2_sample(:,1), P2_sample(:,2), 'yo');
plot(P2(:,1), P2(:,2), 'ro');
title('Homography output');
f.Position = [100 100 1080 800];
print('keble_onept', '-dpng');

% Make the new canvas
canvas = uint8(ones(3*size(im2,1), 3*size(im2,2), 3) .* 120);
im2_center = [size(im2,1)/2, size(im2,2)/2];
canvas_center = [size(canvas,1)/2, size(canvas,2)/2];
im2_offset = canvas_center - im2_center;
canvas(im2_offset(1)+1:im2_offset(1) + size(im2,1), ...
       im2_offset(2)+1:im2_offset(2) + size(im2,2), :) = im2;
   
% Translate the points from p1 to p2 space
for i = 1:(size(im1,1)*size(im1,2))
    [x,y] = ind2sub([size(im1,1), size(im1,2)], i);
    p1_point = [x,y];
    p2_point = apply_homography(p1_point, H);
    c = im1(x, y, :);
    canvas(im2_offset(2)+ceil(p2_point(1)), im2_offset(1)+ceil(p2_point(2)), :) = c;
end
figure;
imshow(canvas);
print('keble_mosaic', '-dpng');


% Sample workflow for uttower

img1_n = "uttower1.JPG";
img2_n = "uttower2.JPG";

P1 = [...
    325 505
    371 292
    561 319
    445 508
];

P2 = [...
    782 541
    815 321
    1018 334
    909 542
];
   
P1_sample = [106 572];
% Read and display images
im1 = imread(img1_n);
im2 = imread(img2_n);

% Determine the homography
H = estimate_homography(P1, P2);

% Estimate point
P2_sample = apply_homography(P1_sample, H);

f = figure;
subplot(1,2,1);
imshow(im1);
hold on;
impixelinfo();
plot(P1_sample(:,1), P1_sample(:,2), 'go');
plot(P1(:,1), P1(:,2), 'ro');
title('Homography input');
subplot(1,2,2);
imshow(im2);
hold on;
impixelinfo();
plot(P2_sample(:,1), P2_sample(:,2), 'yo');
plot(P2(:,1), P2(:,2), 'ro');
title('Homography output');
f.Position = [100 100 1080 800];
print('uttower_onept', '-dpng');

% Make the new canvas
canvas = uint8(ones(3*size(im2,1), 3*size(im2,2), 3) .* 120);
im2_center = [size(im2,1)/2, size(im2,2)/2];
canvas_center = [size(canvas,1)/2, size(canvas,2)/2];
im2_offset = canvas_center - im2_center;
canvas(im2_offset(1)+1:im2_offset(1) + size(im2,1), ...
       im2_offset(2)+1:im2_offset(2) + size(im2,2), :) = im2;
   
% Translate the points from p1 to p2 space
for i = 1:(size(im1,1)*size(im1,2))
    [x,y] = ind2sub([size(im1,1), size(im1,2)], i);
    p1_point = [y,x];
    p2_point = apply_homography(p1_point, H);
    c = im1(x, y, :);
    x_c = im2_offset(1)+ceil(p2_point(2));
    y_c = im2_offset(2)+ceil(p2_point(1));
    canvas(x_c, y_c, :) = c;
end
figure;
imshow(canvas);
print('uttower_mosaic', '-dpng');




