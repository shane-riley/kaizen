function generate_results(filename, reduceAmt, reduceWhat)
%% GENERATE_RESULTS Show the seam in the image
%
% INPUTS:
%
% filename:     image file
% reduceAmt:    number of pixels to remove
% reduceWhat:   'WIDTH' or 'HEIGHT'
%
% OUTPUTS:
% None
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 1/26/2022
% Version tested: R2020b

    im_orig = imread(filename);
    [n_r, n_c, ~] = size(im_orig);
    
    if (strcmp(reduceWhat, 'WIDTH'))
        assert(reduceAmt < n_c)
        im_content_aware = im_orig;
        for i = 1:reduceAmt
            im_content_aware = reduceWidth(im_content_aware, (i == 1));
        end
        im_standard = imresize(im_orig, [n_r, n_c - reduceAmt]);
        
    else
        assert(strcmp(reduceWhat, 'HEIGHT'))
        assert(reduceAmt < n_r)
        im_content_aware = im_orig;
        for i = 1:reduceAmt
            im_content_aware = reduceHeight(im_content_aware, (i == 1));
        end
        im_standard = imresize(im_orig, [n_r - reduceAmt, n_c]);
    end
    
    
    figure;
    subplot(1, 3, 1); imshow(im_orig);
    title('original');
    subplot(1, 3, 2); imshow(im_content_aware);
    title('content-aware');
    subplot(1, 3, 3); imshow(im_standard);
    title('standard');
end