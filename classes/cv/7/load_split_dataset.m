% load_split_dataset: load dataset, split into train/test

input('Set the path below to where you downloaded the scene dataset...');
pause(3)

scenes_dir = 'scenes_lazebnik/scenes_lazebnik/';

num_classes = 8;
per_class_train = 100;
per_class_test = 50; 
max_per_class = 150;
per_class = per_class_train + per_class_test;

scenes = dir(scenes_dir); 

train_images = zeros(num_classes*per_class_train, 2); % only store image sizes for computeSPMRepr
train_sift = cell(num_classes*per_class_train, 1);
train_labels = zeros(num_classes*per_class_train, 1);
test_images = zeros(num_classes*per_class_test, 2); % only store image sizes for computeSPMRepr
test_sift = cell(num_classes*per_class_test, 1);
test_labels = zeros(num_classes*per_class_test, 1);

train_id = 0;
test_id = 0;

assert(length(scenes) == num_classes + 2); % 8 categories + '..' + '.'

% for each scene class... 
for i = (3 : length(scenes)) % first two entries will be '..' and '.' so skip
    
    scene_entry = scenes(i);      
    scene_dir = [scenes_dir '/' scene_entry.name];
    data_for_this_scene = dir(scene_dir);
	this_class_id = i-2; % use i (scene folder ID) as the scene category label
    	
  	file_id = 0;
    
    % pick IDs in set 1:per_class for train and test_ids
	r = randperm(per_class); 
	train_ids = r(1:per_class_train); % first ones in the random permutation are for training
	test_ids = r(per_class_train+(1:per_class_test)); % the rest are for testing

    % for every file within the given scene folder
    for j = (3 : length(data_for_this_scene)) % skip '.' and '..'
                
        fprintf('Parsing scene type %u, image %u...\n', this_class_id, j); 
		
        % read image and save its size, read and store SIFT descriptors and locations
        this_file = data_for_this_scene(j);
        % if it's a jpg file, use the filename -- the files for SIFT use
        % the same filename except for the extension; skip resized jpg's
        % (will use for HW9)
        if( ~isempty(strfind(this_file.name, 'jpg')) && isempty(strfind(this_file.name, 'resized')) && isempty(strfind(this_file.name, 'mat')) )
			file_id = file_id + 1;
            assert(file_id <= max_per_class);
			overall_id = (this_class_id-1)*per_class + file_id; % just for sanity check later
            
            im_path = [scene_dir '/' this_file.name];
            im_size = size(imread(im_path));
			sift_path = [im_path '.mat'];
            sift = load(sift_path);

            % put this file in train or test set
            if(any(train_ids == file_id)) 
                
                train_id = train_id + 1;
                assert(train_id <= overall_id);
			    assert(train_id <= num_classes * per_class_train);

				train_images(train_id, :) = im_size(1:2);
				train_sift{train_id} = sift; % note how we index a cell array
				train_labels(train_id) = this_class_id;
				
            elseif(any(test_ids == file_id))
			
                test_id = test_id + 1;
                assert(test_id <= overall_id);
                assert(test_id <= num_classes * per_class_test);
                
				test_images(test_id, :) = im_size(1:2);
				test_sift{test_id} = sift;
				test_labels(test_id) = this_class_id;
						
            else
                
                assert(file_id > per_class); % assert we're skipping because we're not using full dataset
            
            end
            
        end
        
    end
            
end

assert(overall_id == num_classes * max_per_class); % dataset contains 150 images per class

% grab SIFT features (values only) on the training set and run K-means

all_desc = [];

disp('reshaping descriptors (will take a minute)...');
for j = 1:size(train_sift, 1)
    desc = train_sift{j}.d'; % want rows to be descriptors, thus transposing
    all_desc = [all_desc; desc]; 
end

assert(size(all_desc, 2) == 128);

disp('running kmeans (will take a few minutes)...');
K = 50;
[~, means] = kmeans(double(all_desc), K);


