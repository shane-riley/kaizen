%% nm Homework 9
% Author: Shane Riley
% Date: 4/10/2021
format long
clear
clc
close all
%% Problem 1
% Handle a uniform distributed load BVP problem on a beam

EI = 1.4e7;     % [N-m^2]
q = 10000;     % [N/m]
L = 4;          % [m]
y_0 = 0;        % [m]
y_L = 0;        % [m]
h = 0.01;       % [m]
xspan = [0, L]; % [m]

% EQ:
% EI y'' = (1 + y'^2)^1.5 * 0.5q(L*x - x^2)
% (' is an x-derivative)
%
% BC:
% y(0) = y(L) = 0 (pin and roller)

% To solve, use the shooting method
% Convergence criteria and first guesses
epsilon = 0.00001;  % [-]
max_iter = 1000;  % [-]
W_H = 0; % [m/m]
W_L = -5;  % [m/m]

% state vector is [y, y'] as 's'
sdot = @(x, s) [...
    s(2)
    (1 + (s(2))^2 )^(1.5)*0.5*q*(L*x - x^2)/EI
];
get_s0 = @(W) [...
    y_0
    W
];
absdiff = @(x1, x2) abs(x1-x2);

% Use average for first guess, and then walk the bounds inward using
% bisection
W = (W_H + W_L)/2;

for i=1:max_iter
    
    % Run guess
    [t, s] = myEulerExp(sdot, xspan, get_s0(W), h);
    
    % Check convergence
    y_end_found = s(end,1);
    if (absdiff(y_end_found, y_L) < epsilon), break; end
    
    % Set up new W
    if (y_end_found > y_L)
        % Too high, bisect W and W_L
        Wnew = (W + W_L)/2;
        W_H = W;
        W = Wnew;
        
    else
        % Too low, bisect W and W_H
        Wnew = (W + W_H)/2;
        W_L = W;
        W = Wnew;
    end
end

% Precondition: convergence was reached

% Use final state matrix to compute y'' and add to state
acc = zeros(length(t), 1);
for j=1:length(t)
    state_change = sdot(t(j), s(j,:));
    acc(j) = state_change(2);
end
s = [s acc];

% Plots
figure(1)
plot(t,s(:,1));
title("Deflection 'y' of Beam");
xlabel("Length [m]");
ylabel("Height [m]");
print("images/figure2",'-dpng');

figure(2)
plot(t,s(:,2));
title("Angle 'dy/dx' of Beam");
xlabel("Length [m]");
ylabel("Angle [m/m]");
print("images/figure3",'-dpng');

figure(3)
plot(t,s(:,3));
title("Concavity 'd2y/dx2' of Beam");
xlabel("Length [m]");
ylabel("Concavity [m/m^2]");
print("images/figure4",'-dpng');

%% Supporting functions

function [t, s] = myEulerExp(sdot, tspan, s0, h)
% MYEULEREXP computes state information across a time interval using
% Explicit Euler
%
%   sdot: column vector as function handle to find change in state
%
%   tspan: row vector holding time span
%
%   s0: column vector holding initial state
%
%   h: step size

% Set up outputs
t = tspan(1):h:tspan(end);
s = zeros(length(t), length(s0));
s(1,:) = s0';

for i = 2:length(t)
    
    % Step
    time = t(i-1);
    state = s(i-1,:);
    s(i,:) = s(i-1,:) + sdot(time, state)' .* h;
end

end








