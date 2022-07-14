%% nm Homework 6
% Author: Shane Riley
% Date: 3/7/2021
format long

%% Problem 1
% Implement four finite difference schemes ranging 1st to 4th order to approximate f'(a). h =
% 10^{-1 through -5). Plot the error per h on a loglog. Write your
% conclusions
% f(x) = exp(x), x = a = 5

f = @(x) exp(x);
df = @(x) exp(x);
a = 5;
tf = f(a);
tdf = df(a);

% 1st order:
% Two-point forward differnence O(h)
order1 = @(x,h) (f(x+h) - f(x))/h;

% 2nd order:
% Two-point central difference O(h^2)
order2 = @(x,h) (f(x+h) - f(x-h))/(2*h);

% 3rd order:
% Four point forward difference O(h^3)
order3 = @(x,h) ( -11*f(x) + 18*f(x+h) - 9*f(x+2*h) + 2*f(x+3*h))/(6*h);

% 4th order:
% Four point central difference O(h^4)
order4 = @(x,h) (f(x-2*h) - 8*f(x-h) + 8*f(x+h) - f(x+2*h))/(12*h);


% error
error = @(a, t) abs(a - t);


% Run the schemes
hvalues = 10.^(-1:-1:-5);

order1errors = zeros(1,length(hvalues));
order2errors = zeros(1,length(hvalues));
order3errors = zeros(1,length(hvalues));
order4errors = zeros(1,length(hvalues));

for i=1:length(hvalues)
    h = hvalues(i);
    order1errors(i) = error(order1(a, h), tdf);
    order2errors(i) = error(order2(a, h), tdf);
    order3errors(i) = error(order3(a, h), tdf);
    order4errors(i) = error(order4(a, h), tdf);
end

% Plot the results

subplot(2,2,1);
loglog(hvalues, order1errors, 'k-');
title("O(h): Two-point forward difference");
xlabel("h Value");
ylabel("Error");
subplot(2,2,2);
loglog(hvalues, order2errors, 'k-');
title("O(h^2): Two-point central difference");
xlabel("h Value");
ylabel("Error");
subplot(2,2,3);
loglog(hvalues, order3errors, 'k-');
title("O(h^3): Four-point forward difference");
xlabel("h Value");
ylabel("Error");
subplot(2,2,4);
loglog(hvalues, order4errors, 'k-');
title("O(h^4): Four-point central difference");
xlabel("h Value");
ylabel("Error");
sgtitle("Error per h in estimating f'(5)");
print("images/figure1",'-dpng');

%% Problem 2
% Given T and x vectors, find the Q_x vector using a O(h^2) scheme

T = [...
    473
    446
    422
    401
    382
    362
    348
    332
    318
    304
    290
    ]';  % [K]
h = 0.01;  % [m]
xT = 0:h:0.10;  % [m]
k = 240;  % 240 [W/m-K]

% Scheme
Qformula = @(tbefore, tafter) (-k/2*h) * (tafter - tbefore);
xQ = [];
Q = [];
% Run scheme
for i=1:length(xT)
    
    % Skip if at an endpoint
    if (i == 1); continue; end
    if (i == length(xT)); continue; end
    xQ(end+1) = xT(i);
    Q(end+1) = Qformula(T(i-1), T(i+1));
end

% Plot
figure(2);

xlabel("Length [m]");
plot(xT, T, 'b-');
ylabel("Temperature [K]");

yyaxis right
plot(xQ, Q, 'r-');
ylabel("Heat Flux [W/m^2]");
title("Fin Temperature and Heat Flux");
legend("Temperature", "Heat Flux");
print("images/figure2",'-dpng');
