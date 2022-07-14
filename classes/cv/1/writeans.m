function [] = writeans(fid, str)
%WRITEANS Helper function to write to both file and stdout
    fprintf(fid, str);
    fprintf(str);
end