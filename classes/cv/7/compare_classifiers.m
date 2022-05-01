%% COMPARE_CLASSIFIERS Driver script
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/21/2022
% Version tested: R2020b

% Get pyramids for all the training and test images

% Allocate space
train_pyramids = zeros(length(train_sift), size(means,1)*5);  % mult by 5 for pyramid
test_pyramids = zeros(length(test_sift), size(means,1)*5);  % mult by 5 for pyramid

% Populate the pyramids
for i = 1:length(train_sift)
   train_pyramids(i,:) = computeSPMRepr(train_images(i,:), train_sift{i}, means);
end
for i = 1:length(test_sift)
   test_pyramids(i,:) = computeSPMRepr(test_images(i,:), test_sift{i}, means);
end

% Try k values
k_vector = 1:2:21;
num_k = length(k_vector);

% Allocate
accuracy_knn_train = zeros(num_k,1);
accuracy_knn_test = zeros(num_k,1);
accuracy_svm_train = zeros(num_k,1);
accuracy_svm_test = zeros(num_k,1);

% Loop through k
for i = 1:num_k
    
    k = k_vector(i);
    disp(k);
    
    % Test knn on train
    train_knn = findLabelsKNN(train_pyramids, train_labels, train_pyramids, k);
    accuracy_knn_train(i) = mean(train_knn == train_labels);
    
    % Test knn on test
    test_knn = findLabelsKNN(train_pyramids, train_labels, test_pyramids, k);
    accuracy_knn_test(i) = mean(test_knn == test_labels);
    
    % Test knn on train
    if i == 1
        train_svm = findLabelsSVM(train_pyramids, train_labels, train_pyramids);
        accuracy_svm_train(i) = mean(train_svm == train_labels);

        % Test svm on test
        test_svm = findLabelsSVM(train_pyramids, train_labels, test_pyramids);
        accuracy_svm_test(i) = mean(test_svm == test_labels);
    else
        accuracy_svm_train(i) = accuracy_svm_train(1);
        accuracy_svm_test(i) = accuracy_svm_test(1);
    end
end

% Make the plot
figure;
hold on
plot(k_vector, accuracy_knn_train, 'bo');
plot(k_vector, accuracy_knn_test, 'co');
plot(k_vector, accuracy_svm_train, 'ro');
plot(k_vector, accuracy_svm_test, 'mo');
plot(k_vector, accuracy_knn_train, 'b-');
plot(k_vector, accuracy_knn_test, 'c-');
plot(k_vector, accuracy_svm_train, 'r-');
plot(k_vector, accuracy_svm_test, 'm-');
title('Performance Comparison');
ylabel('Accuracy');
xlabel('K');
legend('KNN -- Train', 'KNN -- Test', 'SVM -- Train', 'SVM -- Test');
print('results.png', '-dpng');
