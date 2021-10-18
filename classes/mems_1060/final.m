%% MEMS 1060 Final
% Author: Shane Riley
% Date: 4/11/2021

% Implement a heat equation PDE with Dirichlet BC's

format long
clear
clc
close all

k = 220;            % [J/mKs]
rho = 2707;         % [kg/m^3]
Cp = 896;           % [J/kgK]
alpha = k/(rho*Cp);

stability = @(h,dt) alpha*dt/(h^2);
is_stable = @(h,dt) (stability(h,dt) <= 1/2);

%% Runtime analysis
h_v = [0.1, 0.05, 0.025, 0.1, 0.05, 0.025, 0.1, 0.05, 0.025];
t_v = [2, 2, 2, 1, 1, 1, 0.5, 0.5, 0.5];
times = zeros(1,length(h_v));
for t_c=1:length(h_v)
    h = h_v(t_c);
    dt = t_v(t_c);
    disp(['Running h = ', num2str(h), ', dt = ', num2str(dt)]);
    t = tic;
    solve(h,dt);
    times(t_c) = toc(t);
end
plot(h_v(1:3),times(1:3), h_v(1:3),times(4:6), h_v(1:3),times(7:end));
title('Runtime anaylsis')
ylabel('Runtime [s]')
xlabel('Spacial step [m]')
legend('dt=2[s]', 'dt=1[s]', 'dt=0.5[s]');
print('runtime', '-dpng');

%% Single case
h = 0.05;           % [m?]
dt = 1;             % [s]
assert(is_stable(h,dt))
[t_range, x_range, y_range, T] = solve(h, dt);
nodes_per_row = length(x_range);
nodes_per_column = length(y_range);
T_slice = @(step) reshape(T(:,step), nodes_per_row, nodes_per_column)';

%%  Make the animation
time_per_frame = 0.02;
myVid = VideoWriter('evolvingTemp');
myVid.FrameRate = floor(1/time_per_frame);
open(myVid);
figure(1);
s = surf(x_range, y_range, T_slice(1));
title('Plate Temperature @ t = 0 [s]');
xlabel('X [m]');
ylabel('Y [m]');
zlabel('T [K]');
for i=5:5:num_steps
    title(['Plate Temperature @ t = ', num2str(floor(i * dt)), ' [s]']);
    s.ZData = T_slice(i);
    pause(time_per_frame);
    frame = getframe(gcf);
    writeVideo(myVid, frame);
end
close(myVid);


%% Make the five frames
frames = linspace(1, length(t_range), 6);
for i=1:length(frames)
    frame = frames(i);
    subplot(2,3,i);
    surf(x_range, y_range, T_slice(frame));
    title(['Temp @ t = ', num2str(t_range(frame)), ' [s]']);
    xlabel('x [m]')
    ylabel('y [m]')
    zlabel('T [K]')
end
set(gcf, 'Position', [1000 622 1090 716]);
sgtitle('Evolving Plate Temperature (h = 0.05 [m]; dt = 1 [s])');
print('states', '-dpng');


%% Solve function (partitioned for runtime analysis)
function [t_range, x_range, y_range, T] = solve(h, dt)
    %% Basic problem definition
    % EQ: delT/delt = alpha((del^2 T/delx^2) + (del^2 T/dely^2))
    xspan = [0 1];      % [m?]
    yspan = [0 1];      % [m?]
    tspan = [0 1000];   % [s]
    T_W = 273;          % [K]
    T_H = 473;          % [K]
    T_I = 273;          % [K]
    k = 220;            % [J/mKs]
    rho = 2707;         % [kg/m^3]
    Cp = 896;           % [J/kgK]
    alpha = k/(rho*Cp);

    x_range = xspan(1):h:xspan(end);
    y_range = yspan(1):h:yspan(end);
    t_range = tspan(1):dt:tspan(end);
    nodes_per_row = length(x_range);
    nodes_per_column = length(y_range);
    num_nodes = nodes_per_row * nodes_per_column;
    num_steps = length(t_range);

    bottom_nodes = 1:nodes_per_row;
    top_nodes = (num_nodes - nodes_per_row + 1):num_nodes;
    right_nodes = nodes_per_row:nodes_per_row:num_nodes;
    left_nodes = 1:nodes_per_row:num_nodes;
    wall_nodes = union(union(bottom_nodes, right_nodes), left_nodes);

    % Node vector 'nodes' will just be concatenations of rows of x
    % T vector

    %% Useful handles

    % Get node above (+y)
    n_up = @(n) n + nodes_per_row;

    % Get node below (-y)
    n_down = @(n) n - nodes_per_row;

    % Get node to left (-x)
    n_left = @(n) n - 1;

    % Get node to right (+x)
    n_right = @(n) n + 1;
    %% Initial condition and BC

    T = zeros(num_nodes, num_steps);

    % Add IC
    T(:, 1) = zeros(num_nodes,1) + T_I;

    % Add BC to states matrix
    for ni = wall_nodes
        T(ni,1) = T_W;
    end
    for ni = top_nodes
        T(ni,1) = T_H;
    end


    % Coeffs
    c_n = (1/dt) + (4*alpha)*((1/h^2));
    c_w = -alpha/h^2;

    % Iterate over timesteps
    for t=2:num_steps

        % delT/delt
        b = zeros(num_nodes, 1);

        % alpha((del^2 T/delx^2) + (del^2 T/dely^2))
        A = zeros(num_nodes);

        % Build the A matrix
        for n=1:num_nodes

            % Check for walls
            if ismember(n,top_nodes)
                A(n,n) = 1;
                b(n) = T_H;
            elseif ismember(n,wall_nodes)
                A(n,n) = 1;
                b(n) = T_W;
            else
                % Inside
                A(n,n) = c_n;
                A(n,n_down(n)) = c_w;
                A(n,n_up(n)) = c_w;
                A(n,n_left(n)) = c_w;
                A(n,n_right(n)) = c_w; 
            end

            % Add to b matrix
            b(n) = T(n,t-1)/dt;
        end

        % Find new temp
        T(:,t) = (A\b);

    end
end





























