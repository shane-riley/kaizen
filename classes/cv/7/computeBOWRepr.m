function [bow] = computeBOWRepr(descriptors, means)

    k = size(means, 1);
    bow = zeros(1, k);
    
    if(isempty(descriptors))
        return
    end
    
    dists = pdist2(descriptors, means);
    [~, inds] = min(dists, [], 2);
    
    for i = 1:k
        bow(i) = sum(inds == i);
    end
    
    bow = bow / sum(bow);    
        