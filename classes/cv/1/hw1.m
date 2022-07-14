%% HW1.m
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/17/2022
% Version tested: R2020b
% Answers written automatically using helper function
% Run in folder with helpers

clear;
close all;
clc;

ANSWERS_FILE = 'answers.txt';
f = fopen(ANSWERS_FILE, 'w');
writeans(f, 'answers.txt\n');
writeans(f, 'Author: Shane Riley\n');
writeans(f, 'Course: Course Name Removed\n');
writeans(f, 'Homework 1\n');
writeans(f, '\n');



%% Problem 1
% Make a million-row vector of random numbers
average = 0;
std = 5;
distribution = std .* randn(1000000, 1) + average;


%% Problem 2
% Add one to each element; time the operation and add to answers
tic;
for i = 1:size(distribution)
   distribution(i) = distribution(i) + 1;
end
t = toc;
writeans(f, 'Problem 2:\n');
writeans(f, ['Add time using loop: ', num2str(t), ' s\n']);
writeans(f, '\n');


%% Problem 3
% Add one to each element without a loop; time the operation and add to
% answers and use a different print format
tic;
distribution = distribution + 1;
t = toc;
writeans(f, 'Problem 3:\n');
writeans(f, sprintf('Add time vectorized: %.5f s\n', t));
writeans(f, '\n');


%% Problem 4
% Plot 2.^x for non-negative even values of x such that x < 100 (noloop)
exponential = @(x) 2.^x;
x = 2:2:99;
y = exponential(x);
figure(1);
plot(x, y, 'bo');
title('Exponential plot');
xlabel('x');
ylabel('y');

%% Problem 5
% Make A and B such that C is 10x10 and contains all numbers 1 to 100
% (noloop)

% A is tens-by-row, B is ones-by-column, meaning A is ten times the
% transponse of B-1
B = repmat(1:10, [10,1]);
A = (B-1)'.*10;
C = A + B;


%% Problem 6
% Create a script that prints all the integers between 1 and 10 in random
% order with pauses between each pair of prints

% Get random permutation
n = randperm(10);

disp('Printing permutations: ');
for i = 1:2:10
    % Print 2 integers
    disp(n(i));
    disp(n(i+1));
    % Wait 1 second
    pause(1)
end

%% Problem 7
% Generate A [5,3] and B [3,5] randomly, compare stock multiply and a
% by-hand multiply
A = rand(5,3);
B = rand(3,5);
C_1 = A*B;

C_2 = zeros(5);
for i = 1:5
    for j = 1:5
        % Row of A, Column of B
        C_2(i,j) = sum(A(i,:) .* B(:,j)');
        assert(C_1(i,j) == C_2(i,j));
    end
end

%% Problem 8
% Make [B] = normalize_rows(A) that makes the sum of each row 1, using
% repmat (positive sum and non-negative)
A = [1 2 3; 4 5 6; 7 8 9];
B = normalize_rows(A);

%% Problem 9
% Make [B] = normalize_columns(A)
A = [1 2 3; 4 5 6; 7 8 9];
B = normalize_columns(A);

%% Problem 10
% Make [val] = fib(n) that returns the n-th number in the fibonacci
% sequence
val = fib(6);


%% Problem 11
% Make [N] = my_unique(M) that removes duplicate rows from a matrix
% (nounique)
M = [1 2 3; 1 2 3; 1 2 4; 1 2 3; 1 2 5; 1 2 3];
N = my_unique(M);

%% Problem 12
% Import PITTSBURGH_IMAGE and write the dimensions
PITTSBURGH_IMAGE = 'pittsburgh.png';
im = imread(PITTSBURGH_IMAGE);
writeans(f, 'Problem 12:\n');
writeans(f, sprintf('Num rows: %d \n', size(im,1)));
writeans(f, sprintf('Num columns: %d \n', size(im,2)));
writeans(f, sprintf('Num channels: %d \n', size(im,3)));
writeans(f, '\n');

%% Problem 13
% Convert PITTSBURGH_IMAGE to grayscale
im_gray = rgb2gray(im);

%% Problem 14
% Determine how many pixels in PITTSBURGH_IMAGE are equal to 6 (noloop)
num_6 = sum(im_gray(:) == 6);
writeans(f, 'Problem 14:\n');
writeans(f, sprintf('Number of pixels with value 6: %d \n', num_6));
writeans(f, '\n');

%% Problem 15
% Determine the row and column of the darkest pixel (use ind2sub) (noloop)
[min_val, min_i] = min(im_gray(:));
[min_r, min_c] = ind2sub(size(im_gray), min_i);
writeans(f, 'Problem 15:\n');
writeans(f, sprintf('(r,c) of darkest pixel: (%d,%d) \n', min_r, min_c));
writeans(f, '\n');

%% Problem 16
% Select a 31x31 region of pixels centered about the darkest pixel, and
% make the region white (loop)
for i = min_r-15:min_r+15
    for j = min_c-15:min_c+15
        if i > 0 && i <= size(im_gray,1) && j > 0 && j <= size(im_gray,2)
            im_gray(i,j) = 255;
        end
    end
end

%% Problem 17
% Select a 121x121 region of pixels centered in the image, and
% make the region gray (150) (noloop)
mid_r = size(im_gray,1)/2;
mid_c = size(im_gray,2)/2;
im_gray(mid_r - 60:mid_r + 60, mid_c - 60:mid_c + 60) = 150;

%% Problem 18
% Display and save the modified image as NEW_IMAGE
NEW_IMAGE = 'new_image.png';
figure(2);
imshow(im_gray);
imwrite(im_gray, NEW_IMAGE);

%% Problem 19
% Using the original image, subtract the average per-channel value from the
% image. Display and show
ch_avg = cast(mean(im, 1:2), 'uint8');
im_sub = im - repmat(ch_avg, size(im, 1:2));
SUB_IMAGE = 'mean_sub.png';
figure(3);
imshow(im_sub);
imwrite(im_sub, SUB_IMAGE);

%% END
writeans(f, 'Completed run.\n');
fclose(f);
