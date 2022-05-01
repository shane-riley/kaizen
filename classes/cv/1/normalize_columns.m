function [B] = normalize_columns(A)
%NORMALIZE_COLUMNS Normalize columns so sum is 1 for each column
    B = A ./ repmat(sum(A, 1), [size(A, 1), 1]);
end