%% PART_I Train a basic neural network to classify images
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

% Make a network with three layers
layers = [...
% A:
% Input layer 227x227x3
imageInputLayer([227 227 3])
% 50 11x11 layers
convolution2dLayer(11, 50)
% RELU
reluLayer
% Max pooling 3x3 stride=1
maxPooling2dLayer(3, 'Stride', 1)
% B:
% 60 5x5 filters
convolution2dLayer(5, 60)
% RELU
reluLayer
% Max pooling 3x3 stride=2
maxPooling2dLayer(3, 'Stride', 2)
% C:
% FC 8
fullyConnectedLayer(8)
% softmax layer
softmaxLayer
% classification layer
classificationLayer
];

% Specify training options
options = trainingOptions('sgdm', ...
    'maxEpochs', MAX_EPOCHS, ...
    'InitialLearnRate', LEARNING_RATE);
    %'ExecutionEnvironment', 'multi-gpu');

% Loop through number of tries
test_acc_per_try = zeros(N_TRIES, 1);
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
    fprintf("Accuracy of model %d: %.6f\n", i, acc);
    test_acc_per_try(i) = acc;
end

% Get mean and std
mu_acc = mean(test_acc_per_try);
sd_acc = std(test_acc_per_try);
fprintf("Mean accuracy: %.6f\n", mu_acc);
fprintf("SD accuracy: %.6f\n", sd_acc);
