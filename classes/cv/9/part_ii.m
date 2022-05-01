%% PART_II Train a neural network using alexnet
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 4/6/2022
% Version tested: R2020b

% Constants
NUM_MODELS = 10;
DATASTORE_PATH = 'scenes_lazebnik';
NUM_TRAINING = 100;
MAX_EPOCHS = 5;
N_TRIES = 10;
LEARNING_RATE = 0.0001;

% Define the datastore
imds = imageDatastore(DATASTORE_PATH, ...
    'IncludeSubfolders', true, ...
    'LabelSource', 'foldernames');

% Get alexnet
a_net = alexnet;

%% Transfer until FC6
% Define transfer (up until FC6)
layersTransfer = a_net.Layers(1:16);

% Make a network
layers = [...
    % Transfer
    layersTransfer
    % FC of size 8
    fullyConnectedLayer(8)
    % softmax
    softmaxLayer
    % classification
    classificationLayer
];

% Specify training options
options = trainingOptions('sgdm', ...
    'maxEpochs', MAX_EPOCHS, ...
    'InitialLearnRate', LEARNING_RATE);
    %'ExecutionEnvironment', 'multi-gpu');

% Loop through number of tries
test_acc_per_try_a = zeros(N_TRIES, 1);
for i = 1:N_TRIES
    disp(i);
    % Split into training and test
    [imdsTrain, imdsTest] = splitEachLabel(imds, NUM_TRAINING, 'randomize');

    % Train the network
    net = trainNetwork(imdsTrain, layers, options);
    
    % Classify
    class = classify(net, imdsTest);
    
    % Store accuracy
    acc = mean(class == imdsTest.Labels);
    fprintf("Accuracy of model %d (until FC6): %.6f\n", i, acc);
    test_acc_per_try_a(i) = acc;
end

% Get mean and std
mu_acc_a = mean(test_acc_per_try_a);
sd_acc_a = std(test_acc_per_try_a);
fprintf("Mean accuracy (until FC6): %.6f\n", mu_acc_a);
fprintf("SD accuracy (until FC6): %.6f\n", sd_acc_a);

%% Transfer until FC8
% Define transfer (up until FC8)
layersTransfer = a_net.Layers(1:22);

% Make a network
layers = [...
    % Transfer
    layersTransfer
    % FC of size 8
    fullyConnectedLayer(8)
    % softmax
    softmaxLayer
    % classification
    classificationLayer
];

% Loop through number of tries
test_acc_per_try_b = zeros(N_TRIES, 1);
for i = 1:N_TRIES
    disp(i);
    % Split into training and test
    [imdsTrain, imdsTest] = splitEachLabel(imds, NUM_TRAINING, 'randomize');

    % Train the network
    net = trainNetwork(imdsTrain, layers, options);
    
    % Classify
    class = classify(net, imdsTest);
    
    % Store accuracy
    acc = mean(class == imdsTest.Labels);
    fprintf("Accuracy of model %d (until FC8): %.6f\n", i, acc);
    test_acc_per_try_b(i) = acc;
end

% Get mean and std
mu_acc_b = mean(test_acc_per_try_b);
sd_acc_b = std(test_acc_per_try_b);
fprintf("Mean accuracy (until FC8): %.6f\n", mu_acc_b);
fprintf("SD accuracy (until FC8): %.6f\n", sd_acc_b);
