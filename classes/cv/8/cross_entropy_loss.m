function [loss] = cross_entropy_loss(scores, correct_class)
%% CROSS_ENTROPY_LOSS compute the Li loss for an individual sample
%
% INPUTS:
%
% scores: 4x1 set of predicted scores, one per class, for a sample
% correct_class: the correct class index
%
% OUTPUTS:
% 
% loss: scalar measuring cross-entropy loss given scores and true class
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/31/2022
% Version tested: R2020b

    % Get wrong & right scores
    P = exp(scores(correct_class)) / sum(exp(scores));
    loss = -log(P);