%% nm Homework 7
% Author: Shane Riley
% Date: 3/15/2021
format long
%% Problem 1
% Given y per x for the Gateway Arch, find the the length of the arch using
% Rectangle (8 subs), Simpson's 3/8 (9 subs), Gauss quadrature (n=2)
disp(" ");
disp("Problem 1");

f = @(x) 693.9 - 68.8 * cosh(x/99.7);
xspan = [-299.25 299.25];

% To find arc length we need f'(x). Doing so analytically:
df = @(x) (68.8/99.7) .* sinh(x/99.7);

arcint = @(x) sqrt(1 + (df(x)).^2);

% Rectangular method (left sum)
n = 8;
h = range(xspan)/n;
xval = @(i) (i-1)*h + xspan(1);
rectsum = sum(arcint(xval(1:n)) * h);

% Simpson 3/8 with 9 subs
n = 9;
h = range(xspan)/n;
m = n/3;
xval = @(i) (i-1).*h + xspan(1);
simpsum = (3*h/8)* sum([...
    arcint(xval(1))
    3*sum(arcint(xval(2:3:(n))))
    3*sum(arcint(xval(3:3:(n))))
    2*sum(arcint(xval(4:3:(n-1))))
    arcint(xval(n+1))
]);

% Gauss Quadrature with n=2
% Weights and points from book
weights = [1 1];
points = [-0.57735027, 0.57735027];
garcint = @(x) arcint(((xspan(2) - xspan(1)).*x + sum(xspan))/2).*(xspan(2)-xspan(1))./2;
gausssum = sum(weights .* garcint(points));

% Displays
disp("Gateway Arch Length");
disp(['Left Rectangular sum (n=8): ', sprintf('%5.5f', rectsum)]);
disp(['3/8 Simpson Sum (n=9): ', sprintf('%5.5f', simpsum)]);
disp(['Gauss Quadrature (n=2): ',  sprintf('%5.5f', gausssum)]);


%% Problem 2
% Given v(y) data points, find the volumetric flow rate through the pipe
disp(" ");
disp("Problem 2");

r = [...
    0
    0.25
    0.50
    0.75
    1.0
    1.25
    1.5
    1.75
    2.00];
v = [...
    38
    37.6
    36.2
    33.6
    29.7
    24.5
    17.8
    9.6
    0];

R = max(r);

% Q = int(0,R, 2 pi r v(r))

flowint = @(i) 2.*pi.*r(i).*v(i);

% Right reimann sum (n=8):
n = 8;
h = 0.25;
flow = sum(flowint(2:length(r)).*h);
disp(['Flow rate [m^3/s]: ',  sprintf('%5.5f', flow)]);

format long
%% Problem 1
% Given y per x for the Gateway Arch, find the the length of the arch using
% Rectangle (8 subs), Simpson's 3/8 (9 subs), Gauss quadrature (n=2)
disp(" ");
disp("Problem 1");

f = @(x) 693.9 - 68.8 * cosh(x/99.7);
xspan = [-299.25 299.25];

% To find arc length we need f'(x). Doing so analytically:
df = @(x) (68.8/99.7) .* sinh(x/99.7);

arcint = @(x) sqrt(1 + (df(x)).^2);

% Rectangular method (left sum)
n = 8;
h = range(xspan)/n;
xval = @(i) (i-1)*h + xspan(1);
rectsum = sum(arcint(xval(1:n)) * h);

% Simpson 3/8 with 9 subs
n = 9;
h = range(xspan)/n;
m = n/3;
xval = @(i) (i-1).*h + xspan(1);
simpsum = (3*h/8)* sum([...
    arcint(xval(1))
    3*sum(arcint(xval(2:3:(n))))
    3*sum(arcint(xval(3:3:(n))))
    2*sum(arcint(xval(4:3:(n-1))))
    arcint(xval(n+1))
]);

% Gauss Quadrature with n=2
% Weights and points from book
weights = [1 1];
points = [-0.57735027, 0.57735027];
garcint = @(x) arcint(((xspan(2) - xspan(1)).*x + sum(xspan))/2).*(xspan(2)-xspan(1))./2;
gausssum = sum(weights .* garcint(points));

% Displays
disp("Gateway Arch Length");
disp(['Left Rectangular sum (n=8): ', sprintf('%5.5f', rectsum)]);
disp(['3/8 Simpson Sum (n=9): ', sprintf('%5.5f', simpsum)]);
disp(['Gauss Quadrature (n=2): ',  sprintf('%5.5f', gausssum)]);


%% Problem 2
% Given v(y) data points, find the volumetric flow rate through the pipe
disp(" ");
disp("Problem 2");

r = [...
    0
    0.25
    0.50
    0.75
    1.0
    1.25
    1.5
    1.75
    2.00];
v = [...
    38
    37.6
    36.2
    33.6
    29.7
    24.5
    17.8
    9.6
    0];

R = max(r);

% Q = int(0,R, 2 pi r v(r))

flowint = @(i) 2.*pi.*r(i).*v(i);

% Right reimann sum (n=8):
n = 8;
h = 0.25;
flow = sum(flowint(2:length(r)).*h);
disp(['Flow rate [m^3/s]: ',  sprintf('%5.5f', flow)]);
