%% PART_III Train a neural network using alexnet and data augmentation
%
% Author: Shane Riley
% Course: Course Name Removed
% Date: 4/6/2022
% Version tested: R2020b

% Constants
DATASTORE_PATH = 'scenes_lazebnik';
NUM_TRAINING = 10;
MAX_EPOCHS = 5;
N_TRIES = 10;
LEARNING_RATE = 0.0001;

AUGMENTATION_TYPES = { ...
    % Rotation and scaling
    imageDataAugmenter(...
    'RandRotation', [0 360], ...
    'RandScale', [0.5 1])
    % Both reflections
    imageDataAugmenter(...
    'RandXReflection', true, ...
    'RandYReflection', true)
    % Both translations
    imageDataAugmenter(...
    'RandXTranslation', [-5 5], ...
    'RandYTranslation', [-5 5])
};

AUGMENTATION_TITLES = { ...
    'Rotations and Scalings'
    'Reflections'
    'Translations'
};

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

n_aug = numel(AUGMENTATION_TYPES);
mu_accs = zeros(n_aug, 1);
std_accs = zeros(n_aug, 1);
% Loop through augmentations
for j = 1:n_aug
    title = AUGMENTATION_TITLES{j};
    aug = AUGMENTATION_TYPES{j};
    % Loop through number of tries
    test_acc_per_try = zeros(N_TRIES, 1);
    for i = 1:N_TRIES
        disp(i);
        % Split into training and test
        [imdsTrain, imdsTest] = splitEachLabel(imds, NUM_TRAINING, 'randomize');
        
        % Augment the data
        imdsTrain = augmentedImageDatastore([227 227 3], imdsTrain, ...
            'DataAugmentation', aug);

        % Train the network
        net = trainNetwork(imdsTrain, layers, options);

        % Classify
        class = classify(net, imdsTest);

        % Store accuracy
        acc = mean(class == imdsTest.Labels);
        fprintf("Acc %s %d: %.6f\n", title, i, acc);
        test_acc_per_try(i) = acc;
    end
    mu_accs(j) = mean(test_acc_per_try);
    std_accs(j) = std(test_acc_per_try);
    
    fprintf("Mean accuracy %s: %.6f\n", title, mu_accs(j));
    fprintf("SD accuracy %s: %.6f\n", title, std_accs(j));
end

