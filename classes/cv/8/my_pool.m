function [Output] = my_pool(Input, Pool_Size)
%% MY_POOL computes the output of non-overlapping max-pooling
%
% INPUTS:
%
% Input: a square matrix which comes from RELU on a convolution output
% Pool_Size: a scalar for pooling size
%
% OUTPUTS:
% 
% Output: A single-channel matrix result
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 4/3/2022
% Version tested: R2020b

    % Get input size
    [n_r, n_c] = size(Input);
    
    % Get output size
    n_o_r = n_r / Pool_Size;
    n_o_c = n_c / Pool_Size;
    Output = zeros(n_o_r, n_o_c);
    
    % Loop through outputs
    for i = 1:n_o_r
        for j = 1:n_o_c
            
            % Get range from input
            r_min = (i-1)*Pool_Size + 1;
            c_min = (j-1)*Pool_Size + 1;
            r_max = r_min + Pool_Size - 1;
            c_max = c_min + Pool_Size - 1;
            
            % Get subset
            subset = Input(r_min:r_max, c_min:c_max);
            
            % Place result
            Output(i,j) = max(subset(:));
        end
    end
end