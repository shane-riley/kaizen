function [B] = normalize_rows(A)
%NORMALIZE_ROWS Normalize rows so sum is 1 for each row
    B = A ./ repmat(sum(A, 2), [1, size(A, 2)]);
end