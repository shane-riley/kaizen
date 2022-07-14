%% nm Homework 1
% Author: Shane Riley
% Date: 2/4/2021
format long
%% Problem 1
% Plot the given function for the given span of x

x_min = -299.25;
x_max = 299.25;
y = @(x) 693.8 - 68.8 * cosh(x/99.7);
xspan = [x_min, x_max];

disp(" ");
disp("Problem 1")
fplot(y, xspan);
title("Gateway Arch Shape");
xlabel("Distance (ft)");
ylabel("Height (ft)");


%% Problem 2
% Write a 3x3 determinant function that employs a 2x2 determinant
% subfunction

test_1 = [...
    1 3 2
    6 5 4
    7 8 9];
test_2 = [...
    -2 1 3
    5 2 -1
    6 -3 4];

disp(" ");
disp("Problem 2");
disp("Problem 2 matrix (a): " + det3by3(test_1));
disp("Problem 2 matrix (b): " + det3by3(test_2));

%% Problem 3
% For the given function and x value, use calculator vs format long MATLAB
% to determine relative round-off error

x_3 = 0.005;
f_3 = @(x) (exp(x) - 1)/x;

% Calculator value evaluated using TI-84 using function and table 
y_3_calculator = 1.0025;
y_3_matlab = f_3(x_3);

disp(" ");
disp("Problem 3");
disp("True value of function: " + sprintf('%1.15f', y_3_matlab));
disp("Calculator value of function: " + sprintf('%1.15f', y_3_calculator));
disp("Relative error: " + relError(y_3_matlab, y_3_calculator));



%% Problem 4
% Estimate sin(pi/4) using taylor series rounded to 6 decimal places each
% term. Compare to true value (format long evaluation)

x_4 = pi/4;
true_value = sin(x_4);
tries = [2, 4, 6];
roundoff = 6;

disp(" ");
disp("Problem 4");
disp("Taylor series centered around 0; rounded at 6 decimal places for each term");
disp("True value: " + sprintf('%1.15f', true_value))
for n = tries
    disp("First " + n + " terms:");
    value = sinTaylor(x_4, n, roundoff);
    err = relError(true_value, value);
    disp("Value: " + sprintf('%1.15f', value))
    disp("Relative error vs true: " + err)
end


%% Supporting functions

function d3 = det3by3(A)
% DET3BY3 Local function to evalute 3x3 matrix determinants
    
    function d2 = det2by2(B)
    % DET2BY2 subfunction
       d2 = (B(1,1)*B(2,2)) - (B(1,2)*B(2,1));
    end

    % Check size
    [x, y] = size(A);
    if (x ~= 3) 
    or (y ~= 3)
        throw MException("Not 3x3 matrix");
    end
    
    % Else
    comp1 = A(1,1) * det2by2(A(2:3,2:3));
    comp2 = A(1,2) * det2by2(A(2:3,1:2:3));
    comp3 = A(1,3) * det2by2(A(2:3,1:2));
    
    d3 = comp1 - comp2 + comp3;  
end

function relative_error = relError(true_value, calc_value)
% RELERROR Local function to evaluate relative error
    absolute_error = abs(calc_value - true_value);
    relative_error = absolute_error / abs(true_value);
end

function value_out = sinTaylor(value_in, n, roundoff)
% SINTAYLOR evaluate n terms of sin taylor series centered at 0
    value_out = 0;
    taylor_term = @(x, term) round((-1)^(term-1) * x^(2*term - 1) / factorial(2*term - 1), roundoff);
    for i = 1:n
        value_out = value_out + taylor_term(value_in, i);
    end
        
end
    
    
    
    
