%% COMPARE_REPRESENTATIONS Driver script
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/21/2022
% Version tested: R2020b

% Get pyramids for all the training and test images

% Allocate space
train_pyramids = zeros(length(train_sift), size(means,1)*5);  % mult by 5 for pyramid
test_pyramids = zeros(length(test_sift), size(means,1)*5);  % mult by 5 for pyramid
train_levels_0 = zeros(length(train_sift), size(means,1));  % mult by 1 for level 0
test_levels_0 = zeros(length(test_sift), size(means,1));  % mult by 1 for level 0
train_levels_1 = zeros(length(train_sift), size(means,1)*4);  % mult by 4 for level 1
test_levels_1 = zeros(length(test_sift), size(means,1)*4);  % mult by 4 for level 1

% Populate representations
for i = 1:length(train_sift)
   [train_pyramids(i,:), train_levels_0(i,:), train_levels_1(i,:)] = computeSPMRepr(train_images(i,:), train_sift{i}, means);
end
for i = 1:length(test_sift)
   [test_pyramids(i,:), test_levels_0(i,:), test_levels_1(i,:)] = computeSPMRepr(test_images(i,:), test_sift{i}, means);
end

% Get the accuracies
disp('Level 0');
a_level_0_train = mean(train_labels == findLabelsSVM(train_levels_0, train_labels, train_levels_0));
a_level_0_test = mean(test_labels == findLabelsSVM(train_levels_0, train_labels, test_levels_0));
disp('Level 1');
a_level_1_train = mean(train_labels == findLabelsSVM(train_levels_1, train_labels, train_levels_1));
a_level_1_test = mean(test_labels == findLabelsSVM(train_levels_1, train_labels, test_levels_1));
disp('Pyramid');
a_pyramids_train = mean(train_labels == findLabelsSVM(train_pyramids, train_labels, train_pyramids));
a_pyramids_test = mean(test_labels == findLabelsSVM(train_pyramids, train_labels, test_pyramids));

fprintf("Train Accuracies:\n");
fprintf("Level 0\t\tLevel 1\t\tPyramid\n");
fprintf("%.4f\t\t%.4f\t\t%.4f\n", a_level_0_train, a_level_1_train, a_pyramids_train);
fprintf("\n");
fprintf("Test Accuracies:\n");
fprintf("Level 0\t\tLevel 1\t\tPyramid\n");
fprintf("%.4f\t\t%.4f\t\t%.4f\n", a_level_0_test, a_level_1_test, a_pyramids_test);
