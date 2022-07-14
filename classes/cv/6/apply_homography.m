function p2 = apply_homography(p1, H)
%% APPLY_HOMOGRAPHY 
%
% INPUTS:
%
% p1:       Matrix of points from first image 4x2
% H:        Projective transformation matrix 3x3
%
% OUTPUTS:
% 
% p2:       Post-homography points
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/24/2022
% Version tested: R2020b

    % Allocate size
    p2 = zeros(size(p1));

    % Loop through points
    for i = 1:size(p1, 1)
        
        % Unpack points
        in_p = [p1(i,1); p1(i,2); 1];
        
        % Perform transformation
        out_p = H * in_p;
        
        % pack
        p2(i,1) = out_p(1)/out_p(3);
        p2(i,2) = out_p(2)/out_p(3);
    end
end