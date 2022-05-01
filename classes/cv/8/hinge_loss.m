function [loss] = hinge_loss(scores, correct_class)
%% HINGE_LOSS compute the Li loss for an individual sample
%
% INPUTS:
%
% scores: 4x1 set of predicted scores, one per class, for a sample
% correct_class: the correct class index
%
% OUTPUTS:
% 
% loss: scalar measuring hinge loss given scores and true class
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/31/2022
% Version tested: R2020b

    % Get wrong & right scores
    wrong_scores = scores;
    wrong_scores(correct_class) = [];
    right_score = scores(correct_class);
    
    % Compute loss using formula
    loss = sum(max(0,wrong_scores - right_score + 1));