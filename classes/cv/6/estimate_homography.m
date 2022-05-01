function H = estimate_homography(PA, PB)
%% ESTIMATE_HOMOGRAPHY 
%
% INPUTS:
%
% PA:       Matrix of points from first image 4x2
% PB:       Matrix of points from second image 4x2
%
% OUTPUTS:
% 
% H:        Projective transformation matrix 3x3
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 2/24/2022
% Version tested: R2020b

    % Build matrix
    A = [];
    
    for i = 1:size(PA,1)
        % Unpack points
        x = PA(i,1);
        x2 = PB(i,1);
        y = PA(i,2);
        y2 = PB(i,2);
        
        % Build matrix piece
        A_p = [-x -y -1 0 0 0 x*x2 y*x2 x2; 0 0 0 -x -y -1 x*y2 y*y2 y2];
        A = [A;A_p];
    end
    % Append final row with a 1
    A = [A; 0 0 0 0 0 0 0 0 1];
    z_v = [zeros(size(PA,1)*2, 1); 1];
    H = A\z_v;
    H = reshape(H, [3 3])';
end