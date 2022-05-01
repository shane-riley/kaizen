function [Output] = my_conv(Image, Filter, Padding, Stride)
%% MY_CONV computes the output of applying a filter over an image with padding
% and stride
%
% INPUTS:
%
% Image: greyscale single-channel image
% Filter: Single-channel filter
% Padding: Padding to apply
% Stride: Stride for convolution
%
% OUTPUTS:
% 
% Output: results matrix
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 4/3/2022
% Version tested: R2020b

    % Get size
    [n_r, n_c] = size(Image);
    
    n_f = size(Filter, 1);
    % NOTE: assuming filter is square
    
    % Find the number of applications in each direction
    n_strides_r = (n_r + 2*Padding - n_f)/Stride + 1;
    n_strides_c = (n_c + 2*Padding - n_f)/Stride + 1;
    
    
    % Allocate space for output
    Output = zeros(n_strides_r, n_strides_c);
    
    % Loop through output cells
    for i = 1:n_strides_r
        for j = 1:n_strides_c
               
            % Find corresponding domain in image
            r_min = (i-1)*Stride + 1 - Padding;
            c_min = (j-1)*Stride + 1 - Padding;
            
            
            % Perform the convolution op
            my_sum = 0;
            for r = 1:n_f
                for c = 1:n_f
                    im_r = r + r_min - 1;
                    im_c = c + c_min - 1;
                    % Range check
                    if (im_r > 0 && im_r <= n_r && im_c > 0 && im_c <= n_c)
                        im_val = Image(im_r, im_c);
                    else
                        % In padding
                        im_val = 0;
                    end
                    filter_val = Filter(r,c);
                    my_sum = my_sum + ...
                        (im_val * filter_val);
                end
            end
            % Place the sum
            Output(i, j) = my_sum;
        end
    end
    
    

end