function displaySeam(im, seam, seamDirection)
%% DISPLAYSEAM Show the seam in the image
%
% INPUTS:
%
% im:               image
% seam:             complementary seam indeces as vector
% seamDirection:    'HORIZONTAL' or 'VERTICAL'
%
% OUTPUTS:
% None
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/26/2022
% Version tested: R2020b

    [n_r, n_c, ~] = size(im);
    
    if(strcmp(seamDirection, 'VERTICAL'))
        x = seam;  % columns
        assert(length(seam) == n_r);
        y = 1:n_r; % rows
    else
        assert(strcmp(seamDirection, 'HORIZONTAL'))
        x = 1:n_c;  % columns
        assert(length(seam) == n_c);
        y = seam; % rows
    end
    
    hold on
    plot(x,y, '-r');
    hold off
end