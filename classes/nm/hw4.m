%% nm Homework 4
% Author: Shane Riley
% Date: 2/28/2021
format long
%% Problem 1
% Given the area, find the principal moments and axes of inertia
disp(" ");
disp("Problem 1");

I_x = 7523;     % [mm^4]
I_y = 3210;     % [mm^4]
I_xy = 2640;    % [mm^4]

A = [...
    I_x    -I_xy
    -I_xy    I_y
    ];

% Solve using the characteristic equation. Done on paper. Roots/eigenvalues
% checked using stock function

coeff = [...
    1
    - (I_x + I_y)
    I_x * I_y - I_xy^2
    ];
e = roots(coeff);

% Find eigenvectors from eigenvalues

char = @(lambda) A - lambda .* eye(2);

% Find v such that Av = 0

% Find matrix
r_char = @(x) rref(char(x));  % row reduce
r_char_e1 = r_char(e(1));
r_char_e2 = r_char(e(2));

% Find v
v_e1 = [-r_char_e1(1,:); 0,1]\[0;1]; % fix v_2 to 1
v_e2 = [-r_char_e2(1,:); 0,1]\[0;1]; % fix v_2 to 1

% Normalize v
normalize = @(x) x/norm(x);

v_e1_norm = normalize(v_e1);
v_e2_norm = normalize(v_e2);

disp("Eigenvalues: ")
fprintf('%1.4f\n', e(1));
fprintf('%1.4f\n', e(2));

disp("Eigenvectors: ")
disp(v_e1_norm);
disp(v_e2_norm);
    
%% Problem 2
% Write a user-defined function to find eigenvalues. Use it to solve the
% for the vibration frequencies and corresponding eigenvectors of an
% acetylene molecule
disp(" ");
disp("Problem 2");

amu = 1.6605 * 10^-27; % [kg/amu]
k_ch = 592;         % [kg/s^2]
k_cc = 1580;        % [kg/s^2]
m_h = 1*amu;        % [amu]
m_c = 12*amu;       % [amu]


% Matrix for amplitude vibrations
coeff = [...
    (k_ch/m_h)   -(k_ch/m_h)   0   0
    -(k_ch/m_c)   (k_ch+k_cc)/m_c   -(k_cc/m_c)   0
    0   -(k_cc/m_c)   (k_ch+k_cc)/m_c   -(k_ch/m_c)
    0   0   -(k_ch/m_h)   (k_ch/m_h)
    ];

% Get eigenvalues
e = AllEig(coeff);

% Handle machine error
eround = round(e,5,'significant');
eround(4) = 0;

omega = eround.^(0.5);

disp("Eigenvalues: ")
for i=1:length(eround)
    disp(eround(i));
end

disp("Omega: ")
for i=1:length(eround)
    disp(omega(i));
end


%% Supporting functions

function e = AllEig(A)
% ALLEIG returns a vector of eigenvalues for a given matrix A (uses QR
% factorization)
% A - nxn matrix
% e - vector of eigenvalues

NUM_ITER = 1000;  % TODO: add a convergence criteria

[n, ~] = size(A);
I = eye(n);

pQ = I;
Anew = A;
for iteration=1:NUM_ITER
    
    % Seed QR
    Q = I;
    R = Anew;
    for i=1:n-1

        % c vector
        c = R(:,i);
        c(1:i-1)=0;

        % e vector
        e1(1:n,1) = 0;
        if c(i) > 0
            e1(i)=1;
        else
            e1(i)=-1;
        end
        v = c + norm(c)*e1;

        % householder
        H = I-(2/(v'*v))*(v*v');

        % Iterate values
        Q = Q*H;
        R = H*R;
    end
    
    % New A
    Anew = R*Q;
    pQ = pQ*Q;
end

% Get eigenvalues using Q and R
e=diag(Anew);
disp(pQ);
end

