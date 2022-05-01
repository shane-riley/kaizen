%% ACTIVATIONS Demonstrate NN math
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/31/2022
% Version tested: R2020b
format long
% Encode values
D = 4;
M = 3;
K = 2;

x = [10; 1; 2; 3];
w_1 = [...
    0.5 0.6 0.4 0.3
    0.02 0.25 0.4 0.3
    0.82 0.1 0.35 0.3];
w_2 = [...
    0.7 0.45 0.5
    0.17 0.9 0.8];

% Express activation functions
h_tanh = @(x) tanh(x);
h_relu = @(x) max(0,x);
h_sigmoid = @(x) 1 ./ (1 + exp(-x));

% Find z2 given tanh activation
z = h_tanh(w_1*x);
disp(z(2));

% Find y1 given RELU and then sigmoid activation
z = h_relu(w_1*x);
y = h_sigmoid(w_2*z);
disp(y(1));





    