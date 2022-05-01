%% GRADIENT Compute numerical gradient of W1
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/31/2022
% Version tested: R2020b

% Get W1
load('weights_samples');
s = {x1, x2, x3, x4};
c = [1 2 3 4];

% Infinitesimal
h = 0.0001;

% Vector representation
W1_v = W1(:);

% Make room for dW
dW_v = zeros(length(W1_v), 1);

% Compute original loss
loss = total_loss(W1, s, c);

% Loop through weights
for w = 1:length(W1_v)
    W1_v_mod = W1_v;
    
    % Add the delta
    W1_v_mod(w) = W1_v_mod(w) + h;
    
    W1_mod = reshape(W1_v_mod, [4 25]);
 
    new_loss = total_loss(reshape(W1_mod, [4 25]), s, c);
    dW_v(w) = (new_loss - loss) / h;
end

% Perform timestep
rate = 0.001;
new_W_v = W1_v - rate .* (dW_v' * W1_v);

% Show result
disp('Delta:');
disp(dW_v)

% Show result
disp('New weights:');
disp(new_W_v);


%% HELPER FUNCTIONS
function [total_loss] = total_loss(matrix, samples, corrects)
% TOTAL_LOSS compute total hinge loss of multiple samples
% matrix: weights
% samples: cell array of samples  
% corrects: correct classes



    total_loss = 0;
    
    for i = 1:length(samples)
       total_loss = total_loss + hinge_loss(matrix*samples{i}, corrects(i));
    end
end

