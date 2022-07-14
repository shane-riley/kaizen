function [num] = fib(n)
%FIB return n-th number of the fibonacci sequence
    if n == 1
        num = 0;
    elseif n == 2
        num = 1;
    elseif n < 1
        num = -1;
    else
        % Store results in vector dynamic-programming style
        ns = zeros(n,1);
        ns(2) = 1;
        for i = 3:size(ns)
            ns(i) = ns(i - 1) + ns(i - 2);
        end
        num = ns(end);
    end
end

