%% MEMS 1060 Homework 5
% Author: Shane Riley
% Date: 3/4/2021
format long
%% Problem 1
% Given population/year data, find an eponential curve of best fit by
% linearizing and using linear least-squares regression. Estimate the
% population in 1970 and plot the regression with the points.
disp(" ");
disp("Problem 1");

years = [...
    1850
    1900
    1950
    1980
    2000];  % [years]
populations = [...
    1.3
    1.6
    3
    4.4
    6];  % [billions]

% p = b*exp(m x)
% ln both sides
% ln(p) = ln(b) + (m x)

ln_populations = log(populations);
a_p1 = myPolyReg(years, ln_populations, 1);

% Post process, get the estimate
m = a_p1(2);
b = exp(a_p1(1));
model = @(x) b*exp(m .* x);
pop_1970 = model(1970);

% Prints
disp("m:");
disp(m);
disp("b:");
disp(b);
disp("Population in 1970:");
disp(pop_1970);

% Plot
linyears = linspace(min(years) - 5, max(years) + 5, 100);
hold on
figure(1)
plot(years, populations, 'k*');  % plot input points
plot(linyears, model(linyears), 'b-');  % Plot fit
title("Problem 1: Earth population per year");
xlabel("Year");
ylabel("Population [billions]");
print("images/figure1",'-dpng');
hold off


%% Problem 2
% Given v(x) data points, find g using linear regression
disp(" ");
disp("Problem 2");

height = [...
    0
    5
    10
    15
    20
    25];  % [m]

fall_speed = [...
    0
    9.85
    14.32
    17.63
    19.34
    22.41];  % [m/s]

% v^2 = 2 g x

fall_speed_squared = fall_speed .^ 2;

a_p2 = myPolyReg(height, fall_speed_squared, 1);  % first order fit

g_p2 = a_p2(2)/2;

% Prints
disp("Experimental value for g: ");
disp(g_p2);


%% Problem 3
% Given y(x) data points, find a second-order polynomial fit
disp(" ");
disp("Problem 3");

x = [...
    1
    3
    5
    7
    10];  % [-]

y = [...
    2.2
    5.0
    5.4
    6.2
    6.7];

% find a, where a(1) is lowest-order coefficient
a_p3 = myPolyReg(x,y,2);

% Print coefficients
for i=1:length(a_p3)
   disp("a" + num2str(i-1) + ":");
   disp(a_p3(i));
end

polynomial_fit = @(x) a_p3(1) + (a_p3(2) .* x) + (a_p3(3) .* (x .^2));

% Plot
linx_p3 = linspace(min(x) - 1, max(x) + 1, 100);
figure(2)
hold on
plot(x, y, 'k*');  % plot input points
plot(linx_p3, polynomial_fit(linx_p3), 'b-');  % Plot fit
title("Problem 3: second order fit");
xlabel("Unitless");
ylabel("Unitless");
print("images/figure2",'-dpng');
hold off
    


%% Problem 4
% Use quadratic splines interpolation to find mpg(30 mph), mpg(65 mph),
% given mpg(mph) data points
disp(" ");
disp("Problem 4");

drive_speed = [...
    11
    25
    40
    55
    70];  % [mph]

fuel_economy = [...
    13
    26
    28
    30
    24];  % [mpg]

disp("MPG at 30 mph: ");
disp(myQuadraticSplineInterp(drive_speed, fuel_economy, 30));

disp("MPG at 65 mph: ");
disp(myQuadraticSplineInterp(drive_speed, fuel_economy, 65));

%% Supporting functions

function a = myPolyReg(x, y, n_in)
% MYPOLYREG creates a vector of coefficients for n-th order polynomial fit
% using least-squares regression.
% x - input vector
% y - output vector (length matches x)
% n_in - order (n >= 1)
% a - coefficient vector (n=length(a))

% n_in is order; n is number of coefficients
n = n_in + 1;

% Build the A matrix
% TODO: make fewer redundant calculations
sx = @(x,n) sum(x.^(n));
A = zeros(n);
for i=1:n
    for j=1:n       
        order = (i-1) + (j-1);
        A(i,j) = sx(x,order);
    end
end

% Build the B matrix
sxy = @(x,y,n) sum((x.^(n) .* y));
b = zeros(n,1);
for i=1:n
   order = i - 1;
   b(i) = sxy(x,y,order);
end

% Find coefficients
a = A\b;
end

function Yint = myQuadraticSplineInterp(x, y, Xint)
% MYQUADRATICSPLINEINTERP approximates y(Xint) given points x,y using
% quadratic splines
% x - input vector (MUST BE ASCENDING)
% y - output vector (length matches x)
% Xint - input for interpolation
% Yint - output for interpolation

num_splines = length(x) - 1;
n = length(x);
num_dof = (num_splines * 3);

% Specify matrices
A = zeros(num_dof);
b = zeros(num_dof, 1);

% Fix at points
for i=1:num_splines
    a_col = i*3 - 2;
    b_col = i*3 - 1;
    c_col = i*3;
    
    % Row 2i - 1: fix start point
    row = 2*i - 1;
    A(row,a_col) = x(i).^2;
    A(row,b_col) = x(i);
    A(row,c_col) = 1;
    b(row) = y(i);
    
    % Row 2i: fix end point
    
    row = 2*i;
    b(row) = y(i+1);
    A(row,a_col) = x(i+1).^2;
    A(row,b_col) = x(i+1);
    A(row,c_col) = 1;
end

% Differentiable at knots
row = num_dof - num_splines + 1;
for i=2:num_splines
    pre_a_col = 3*i - 5;
    post_a_col = 3*i - 2;
    pre_b_col = 3*i - 4;
    post_b_col = 3*i - 1;
    
    A(row, pre_a_col) = 2 * x(i);
    A(row, pre_b_col) = 1;
    A(row, post_a_col) = - 2 * x(i);
    A(row, post_b_col) = -1;
    b(row) = 0;
    
    row = row + 1;
end

% Fix a0 as 0
A(num_dof, 1) = 1;
b(num_dof) = 0;

coeff = A\b;

% Pick the spline number
for i=1:n
    if Xint < x(i+1)
        which_spline = i;
        break;
    end
end

a_int = coeff(3*which_spline - 2);
b_int = coeff(3*which_spline - 1);
c_int = coeff(3*which_spline);

model = @(x) (a_int .* (x.^2)) + (b_int .* x) + c_int;
Yint = model(Xint);

end
