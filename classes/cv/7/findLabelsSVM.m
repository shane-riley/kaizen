function [predicted_labels_test] = findLabelsSVM(pyramids_train, labels_train, pyramids_test)
%% FINDLABELSSVM Predict test labels using support vector machines
%
% INPUTS:
%
% pyramids_train:   Training features (MxD)
% labels_train:     Training labels (MxD)
% pyramids_test:    Test features (NxD)
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
    
    % Train the model
    model = fitcecoc(pyramids_train, labels_train);
    
    % Perform the predictions
    for i=1:N
        predicted_labels_test(i) = predict(model, pyramids_test(i,:));
    end