function [predicted_labels_test] = findLabelsKNN(pyramids_train, labels_train, pyramids_test, k)
%% FINDLABELSKNN Predict test labels using K-nearest neighbors
%
% INPUTS:
%
% pyramids_train:   Training features (MxD)
% labels_train:     Training labels (MxD)
% pyramids_test:    Test features (NxD)
% k:                Number of nearest neighbors
%
% OUTPUTS:
% 
% predicted_labels_test:    Testing labels (NxD)
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/21/2022
% Version tested: R2020b

    N = size(pyramids_test,1);
    predicted_labels_test = zeros(N,1);
    
    % Loop through test images
    for i = 1:N
        
        % Compute the distances
        distances = pdist2(pyramids_train, pyramids_test(i,:));
        
        % Get closest neighbor indeces
        [~, I] = mink(distances, k);
        
        % Get the labels from the indeces
        labels = labels_train(I);
        
        % Find the mode
        predicted_labels_test(i) = mode(labels);
    end