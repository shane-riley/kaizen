%% nm Homework 3
% Author: Shane Riley
% Date: 2/21/2021
format long
%% Problem 1
% Given the following linear system, solve using GJ and Crout's method
disp(" ");
disp("Problem 1");

A = [...
    1   2  -2
    2   3   1
    3   2  -4];

b = [...
    9
    23
    11];

x_true = A\b;
% disp("x = " + x);

% Get L,U
[L, U] = myCrout3x3(A);
disp(L);
disp(U);

% Find y
y = myForward(L,b);

% Find x
x = myBackward(U,y);
disp(x);


    
%% Problem 2
% Use Jacobi iterative method to solve using 0,0,0 and epsilon = 0.001 and
% 0.0001
disp(" ");
disp("Problem 2");

A = [...
    8   2   3
    2   5   1
    -3  -1  6];

b = [...
    51
    23
    20];

[x_e_001, i_001] = myJacobi3x3(A,b,[0;0;0],0.001,100);
[x_e_0001, i_0001] = myJacobi3x3(A,b,[0;0;0],0.0001,100);
disp(x_e_001);
disp(i_001);
disp(x_e_0001);
disp(i_0001);

x_true=A\b;

%% Problem 3
% Find the condition number of the matrix using the infinity norm
disp(" ");
disp("Problem 3");

A = [...
    6   3   11
    3   2   7
    3   2   6];

norm = norm(A,inf);
disp(norm);


%% Supporting functions

function [L, U] = myCrout3x3(A)
% MYCROUT3x3 performs LU decomp using Crout's Method for 3x3
% A - Coefficients
% L - Lower Triangular
% U - Upper Triangular

[rows, columns] = size(A);
U = zeros(rows,columns);
L = zeros(rows,columns);

for i=1:rows
    % First column of L matches A
    L(i,1)=A(i,1);
    
    % Diagonals for U are 1
    U(i,i) = 1;
end

% First row of U
for j=2:columns
    U(1,j) = A(1,j)/L(1,1);
end


for i=2:rows
    % Fill in L in triangular iteration
    for j=2:i
        L(i,j) = A(i,j) - L(i,1:j-1) * U(1:j-1,j);  % The product will be a scalar
    end
    % Fill in U in triangular iteration
    for j=i + 1:rows
        U(i,j) = (A(i,j) - L(i, 1:i-1) * U(1:i-1, j))/L(i,i);
    end
end
end

function y = myForward(L,b)
% MYFORWARD finds y using lower triangular L and b
% L - Lower Triangular
% b - Constants
% y - mid-solution

n = length(b);
y = zeros(n,1);
% Get 1,1
y(1) = b(1)/L(1,1);
for i=2:n
    y(i) = (b(i) - L(i,1:i-1)*y(1:i-1,1))./L(i,i);
end
end

function x = myBackward(U,y)
% MYFORWARD finds y using upper triangular U and y
% U - Upper Triangular
% y - mid-solution
% x - Solution

n = length(y);
x = zeros(n,1);
% Get last component
x(n) = y(n)/U(n,n);
for i=n-1:-1:1  % iterate backwards
    x(i) = (y(i) - U(i,i+1:n)*x(i+1:n,1))./U(i,i);
end
end

function [x, i] = myJacobi3x3(A,b,x0,epsilon,max_i)
% MYJACOBI3x3 finds y using upper triangular U and y
% Assumes proper sizing
% A - Coefficients
% b - constants
% x0 - Initial condition
% epsilon - convergence condition
% max_i - max iterations
% x - solution
% i - number of taken iterations

% n = 3
x_old = x0;
x = zeros(length(b),1);

% First iteration
x(1) = (b(1) - A(1,2).*x(2) - A(1,3).*x(3))./A(1,1);
x(2) = (b(2) - A(2,1).*x(1) - A(2,3).*x(3))./A(2,2);
x(3) = (b(3) - A(3,1).*x(1) - A(3,2).*x(2))./A(3,3);
i = 1;

while ~isConverged(x,x_old,epsilon)

    if (i > max_i)
        disp("Jacobi not converged");
        break;
    end
    x_old = x;
    x(1) = (b(1) - A(1,2).*x(2) - A(1,3).*x(3))./A(1,1);
    x(2) = (b(2) - A(2,1).*x(1) - A(2,3).*x(3))./A(2,2);
    x(3) = (b(3) - A(3,1).*x(1) - A(3,2).*x(2))./A(3,3);
    i = i + 1;

end

end

function b = isConverged(x, x_old, e)
% ISCONVERGED checks for convergence
% x - current iteration
% x_old - old iteration
% e - threshold

n = length(x);
b = true;

for i=1:n
    if (abs((x(i) - x_old(i))/x_old(i)) > e)
        b = false;
    end
end
end



    
    
    
    
