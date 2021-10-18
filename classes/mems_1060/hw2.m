%% MEMS 1060/2060 Homework 2
% Author: Shane Riley
% Date: 2/8/2021
format long
%% Problem 1
% Plot the given function for the given span of x
disp(" ");
disp("Problem 1");

A = [...
    3   -2  5
    1   -1  0
    2   0   4];
b = [...
    14
    -1
    14];

x = myCramer(A,b);
disp("x = " + x(1));
disp("y = " + x(2));
disp("z = " + x(3));


%% Problem 2
disp(" ");
disp("Problem 2");

% Givens
fun = @(x) sin(x);
c = pi/4;
xspan = [0 pi];
numPoints = 100;
x = linspace(xspan(1), xspan(2), 200);
y2 = myTaylorSinPi4(x, 2);
y4 = myTaylorSinPi4(x, 4);
y6 = myTaylorSinPi4(x, 6);

% Plot results
hold on
figure(1)
plot(x,y2)
plot(x,y4)
plot(x,y6)
fplot(fun, xspan);
legend(["2 term Taylor", "4 term Taylor", "6 term Taylor", "f(x)"], 'Location', 'SW');
xlim(xspan)
xlabel("x")
ylabel("y")
title("Taylor series of f(x) = sin(x)")

% Print figure
print("figure/Taylor", '-dpng');
hold off


%% Problem 3
disp(" ");
disp("Problem 3");

fun = @(x) cos(x) - x^3;
dfun = @(x) -sin(x) - 3*x^2;
tolerance = 0.001;
xspan = [0, pi/2];
nmax = 1000;

disp("f( " + xspan(1) + " ) = " + fun(xspan(1)));
disp("f( " + xspan(2) + " ) = " + fun(xspan(2)));
[c, n] = myNewton(fun, dfun, xspan, tolerance, nmax);
disp("Newton's method after " + n + " iterations:");
disp("c = " + c + "; f(c) = " + fun(c));
[c2, n2] = myRegulaFalsi(fun, xspan, tolerance, nmax);
disp("Regula Falsi method after " + n2 + " iterations:");
disp("c = " + c2 + "; f(c) = " + fun(c2));


%% Problem 4
disp(" ");
disp("Problem 4");

% Values
numIterations = 200;
TcStart = 298;  % K
ThStart = 298;  % K
JcStart = 3000;  % W/m^2
JhStart = 5000;  % W/m^2

start = [...
    TcStart
    ThStart
    JcStart
    JhStart];

% Hint iteration functions
TcNew = @(Jc, Tc) ((Jc - 17.41*Tc + 5188.18)/(5.67e-8))^(1/4);
ThNew = @(Jh, Th) ((2250 + Jh - 1.865*Th)/(5.67e-8))^(1/4);
JcNew = @(Jh, Tc) (2352.71 + 0.71*Jh - 7.46*Tc);
JhNew = @(Jc, Th) (11093 + 0.71*Jc - 7.46*Th);

delta = @(arr) [...
    TcNew(arr(3),arr(1))
    ThNew(arr(4),arr(2))
    JcNew(arr(4),arr(1))
    JhNew(arr(3),arr(2))];

values = zeros(4,numIterations);
values(:,1) = start;
for i=1:numIterations
    % Iterate
    values(:,i+1) = delta(values(:,i));
end

% Get final
disp("After " + numIterations + " iterations:");
disp("Tc = " + values(1,end) + " [K]");
disp("Th = " + values(2,end) + " [K]");
disp("Jc = " + values(3,end) + " [W/m^2]");
disp("Jc = " + values(4,end) + " [W/m^2]");

% Make the plot
figure(2)
hold on
plot(values(1,:),'b-');
plot(values(2,:),'r-');
ylabel("Temperature [K]");
yyaxis right
plot(values(3,:),'b--');
plot(values(4,:),'r--');
xlim([0, numIterations]);
title("Iteration Values for Heater System");
xlabel("Iteration number");
ylabel("Heat Flux [W/m^2]");
legend("Tc", "Th", "Jc", "Jh", 'Location', 'SW');

% Print figure
print("figure/Values", '-dpng');
hold off


%% Supporting functions

function x = myCramer(A, b)
% MYCRAMER evaluates x for Ax = b using Cramer's rule
% A: Coefficient matrix
% b: constant vector

% Check dimensions
[nA,mA] = size(A);
assert (nA == mA);
[nB,mB] = size(b);
assert (nB == nA);
assert (mB == 1);

% Preperation
order = nA;
x = zeros(1, order);
detA = det(A);

% Evaluate solution components in order
for i = 1:order
    Abefore = A(:, 1:i-1);
    Aafter = A(:, i+1:order);
    Asub = [Abefore, b, Aafter];
    x(i) = det(Asub) / detA;
end
end

function y = myTaylorSinPi4(x, n)
% MYTAYLORSINPI4 Gets the y values for a taylor series for sinx centered
% about pi/4
% x: vector of inputs
% n: number of terms
% y: vector of outputs
% TODO: GENERALIZE FOR ALL values of c
c = pi/4;

% Expresses value of of the nth derivative of sin at pi/4
sinDerivativeAtPi4 = @(n) (sqrt(2)/2) * (-1) ^ ((n)*(n-1)/2);

% Construct polynomial as terms in a vector
for count = 1:n
    terms{count} = @(x) sinDerivativeAtPi4(count - 1) * (x - c)^(count - 1) / factorial(count - 1);
end

% Using terms vector, compute y values
y = zeros(1, length(x));
for j = 1:length(x)
    xValue = x(j);
    yValue = 0;
    for termNum = 1:length(terms)
        term = @(x) terms{termNum}(x);
        deltaY = term(xValue);
        yValue = yValue + deltaY;
    end
    y(j) = yValue;
end
end

function [x, n] = myRegulaFalsi(f,xspan,t,nmax)
% MYREGULAFALSI finds a root of f between a and b, to a tolerance of t.
% Moves lower bound forward until a solution is found
% using Regula Falsi
% f: function handle
% xspan: upper and lower bounds;
% t: tolerance
% nmax: max number of iterations
% x: root value found
% n: number of iterations required

a = xspan(1);
b = xspan(2);
n = 0;
while abs(f(a)) > t
    % Iterate
    deltaA = (a - b)/((f(b)/f(a)) - 1);
    a = a + deltaA;
    n = n + 1;
    if n > nmax
        disp("Solution not found within alloted iterations");
        x=NaN;
        return;
    end
end
x = a;
end

function [x, n] = myNewton(f, df, xspan, t, nmax)
% MYNEWTON finds a root of f near a, to a tolerance of t, using Newton's
% Method. Seeds using the midpoint of the interval
% f: function handle
% df: derivative function handle
% xspan: Interval
% t: tolerance
% nmax: max number of iterations
% x: root value found
% n: number of iterations required

xValue = (xspan(2) - xspan(1)) / 2;
n = 0;
while abs(f(xValue)) > t
    % Iterate
    xValue = xValue - (f(xValue)/df(xValue));
    n = n + 1;
    if n > nmax
        disp("Solution not found within alloted iterations");
        x=NaN;
        return;
    end
end
x = xValue;
end


    
    
    
    
