function [N] = my_unique(M)
%MY_UNIQUE return a copy of M with no duplicate rows
    
    % Write first row
    N(1, :) = M(1, :);
    
    % Iterate through other rows
    for i = 2:size(M)
        row_found = false;
        row = M(i, :);
        for j = 1:size(N)
            if row == N(j, :)
                row_found = true;
                break;
            end
        end
        if ~row_found
            N(size(N, 1) + 1, :) = M(i, :);
        end
    end
end

