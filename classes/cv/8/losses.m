%% LOSSES Demonstrate differences between hinge & cross-entropy on some
% weight matrices
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 3/31/2022
% Version tested: R2020b

% Load weights
load('weights_samples');

% Allocate space
N_W = 3;
N_x = 4;
hinge_losses_per_sample = zeros(N_x, N_W);
c_e_losses_per_sample = zeros(N_x, N_W);

% Loop through weight/sample permutations
for i = 1:N_x
    x = eval(['x', num2str(i)]);
    for j = 1:N_W
        W = eval(['W', num2str(j)]);
        
        hinge_losses_per_sample(i,j) = hinge_loss(W*x, i);
        c_e_losses_per_sample(i,j) = cross_entropy_loss(W*x, i);
    end
end

% Sum across
hinge_losses = sum(hinge_losses_per_sample);
c_e_losses = sum(c_e_losses_per_sample);

disp('Hinge losses:');
disp(hinge_losses);
disp('Cross-Entropy losses:');
disp(c_e_losses);








    