#define FUSE_USE_VERSION 26

#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>

#include "os.h"

// Move structs into typespace
typedef struct os_root_directory os_root_directory;
typedef struct os_directory_entry os_directory_entry;
typedef struct os_file_entry os_file_entry;
typedef struct os_directory os_directory;
typedef struct os_index_block os_index_block;
typedef struct os_data_block os_data_block;

// State information
// File id for .disk
FILE *fid = 0;

// Helpful Macros
#define GOTO_START(fid) fseek(fid, 0, SEEK_SET)

// Helpful functions

// Load root
int load_root(os_root_directory *rootptr)
{
	// Assume space is allocated already
	// Seek the beginning of the file
	GOTO_START(fid);

	// Read into ptr from file
	fread(rootptr, sizeof(os_root_directory), 1, fid);
	
	// Success
	return 0;
}

// Save root
int save_root(os_root_directory *rootptr)
{
	// Assume space is allocated already
	// Seek the beginning of the file
	GOTO_START(fid);

	// Write from ptr to file
	fwrite(rootptr, sizeof(os_root_directory),1,fid);

	// Success
	return 0;
}

// Load dir
int load_block(size_t blocknum, void *ptr)
{
	// Assume space is allocated already
	// Seek the block
	fseek(fid, blocknum*BLOCK_SIZE, SEEK_SET);
	// Read the block
	fread(ptr, BLOCK_SIZE, 1, fid);

	// Success
	return 0;
}

// Save dir
int save_block(size_t blocknum, void *ptr)
{
	// Assume space is allocated already
	// Seek the block
	fseek(fid, blocknum*BLOCK_SIZE, SEEK_SET);
	// Write the block
	fwrite(ptr, BLOCK_SIZE, 1, fid);

	// Success
	return 0;
}

// Get free block
size_t allocate_block(os_root_directory *rootptr)
{
	// NOTE: THIS MODIFIES THE ROOT, make sure to save the root after calling this
	// Use the simple implementation
	
	rootptr->last_allocated_block++;
	printf("Block allocated: %ld\n", rootptr->last_allocated_block);
	return rootptr->last_allocated_block;

}

/**
 * Called whenever the system wants to know the file attributes, including
 * simply whether the file exists or not.
 *
 * `man 2 stat` will show the fields of a `struct stat` structure.
 */
static int os_getattr(const char *path, struct stat *statbuf)
{
	// Clear out `statbuf` first -- this function initializes it.
	memset(statbuf, 0, sizeof(struct stat));

	// Check if the path is the root directory.
	if (strcmp(path, "/") == 0) {

		// Populate the statbuf
		statbuf->st_mode = S_IFDIR | 0755;
		statbuf->st_nlink = 2;

		// Success
		return 0;
	}
	// Else

	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Decompose the path into dir, file, extension
	// No malloc since sizes known at compile-time
	char directory[MAX_FILENAME+1] = "";
	char filename[MAX_FILENAME+1] = "";
	char extension[MAX_EXTENSION+1] = "";

	// Scan path into boxes
	sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);

	// If filename has not filled in, is a directory
	// Check dir name exists
	if (strcmp(directory,"")==0){
		// Return mem
		free(root);
		// Fail
		return -ENOENT;
	}

	// Loop through directories
	for (size_t i = 0; i < root->num_directories; i++)
	{
		// check dname
		if (strcmp(directory, root->directories[i].dname)==0)
		{
			// Matched directory

			// Check whether filename exists
			if (strcmp(filename,"") == 0) {
				// Filename does not exist and found directory, success
				// Populate statbuf
				statbuf->st_mode = S_IFDIR | 0755;
				statbuf->st_nlink = 2;

				// Return mem
				free(root);
				// Success
				return 0;
			}
			// Else
			// Ensure extension exists
			if (strcmp(extension,"") == 0) {
				// Return mem
				free(root);
				// No extension, fail
				return -ENOENT;
			}
			// Else
			
			// Read in file
			size_t dir_blocknum = root->directories[i].n_start_block;

			// Get dir space
			os_directory_entry *dir = (os_directory_entry *)malloc(sizeof(os_directory_entry));
			load_block(dir_blocknum, dir);

			// Loop through files in entry
			for (size_t j = 0; j < dir->num_files; j++) {
				// Check file name
				if (strcmp(filename, dir->files[j].fname) == 0 && strcmp(extension, dir->files[j].fext) == 0) {
					// Found the file!

					// Populate the statbuf
					statbuf->st_mode = S_IFREG | 0666;
					statbuf->st_nlink = 1;
					statbuf->st_size = dir->files[j].fsize;

					// return mem
					free(dir);
					free(root);

					// Success
					return 0;
				}
			}
			// Return mem
			free(dir);
		}
	}
	
	// Return mem
	free(root);
	// Failed to find the dir or file, return -ENOENT
	return -ENOENT;

}

/**
 * Called whenever the contents of a directory are desired. Could be from `ls`,
 * or could even be when a user presses TAB to perform autocompletion.
 */
static int os_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			  off_t offset, struct fuse_file_info *fi)
{

	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Check if the path is the root directory.
	if (strcmp(path, "/") == 0) {

		// Add the usual entries
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);

		// Loop through the directories
		for (size_t i = 0; i < root->num_directories; i++) {
			// Add to buff
			filler(buf, root->directories[i].dname /* +1? */, NULL, 0);
		}

		// Free mem
		free(root);
		// Success
		return 0;
	}

	// Not root

	// Unpack dir name
	char name[MAX_FILENAME+1] = "";
	char extra[32] = "";
	// This is super unsafe but we're doing it anyway
	sscanf(path, "/%[^/]/%[^/]", name, extra);

	// Assume extra is still empty--no mention in assignment

	// Find dir name in directories
	for (size_t i = 0; i < root->num_directories; i++) {
		if (strcmp(name, root->directories[i].dname) == 0) {
			// Found the directory

			// Add the usual entries
			filler(buf, ".", NULL, 0);
			filler(buf, "..", NULL, 0);

			// Check out the directory
			size_t dir_blocknum = root->directories[i].n_start_block;
			os_directory_entry *dir = (os_directory_entry *)malloc(sizeof(os_directory_entry));
			load_block(dir_blocknum, dir);

			char newpath[MAX_FILENAME+MAX_EXTENSION+1];
			for (size_t j = 0; j < dir->num_files; j++) {
				// Reset newpath
				strcpy(newpath,"");
				// Add name
				strcat(newpath,dir->files[j].fname);
				// Add dot
				strcat(newpath,".");
				// Add extension
				strcat(newpath,dir->files[j].fext);
				// Write to buf
				filler(buf, newpath, NULL, 0);
			}

			// Free mem
			free(dir);
			free(root);
			// Success
			return 0;
		}
	}
	// Directory was never found
	// Free mem
	free(root);
	// Fail
	return -ENOENT;
}

/**
 * Creates a directory. Ignore `mode` since we're not dealing with permissions.
 */
static int os_mkdir(const char *path, mode_t mode)
{
	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Assume path is not malformed

	// Ensure space
	if (root->num_directories == MAX_DIRS_IN_ROOT)
	{
		// No room
		// Free mem
		free(root);
		// Fail
		return -ENOSPC;
	}

	// Ensure path is valid
	char name[MAX_FILENAME+1] = "";
	char extra[32] = "";
	// This is super unsafe but we're doing it anyway
	sscanf(path, "/%[^/]/%[^/]", name, extra);
	
	// Check illegal path
	if (strlen(extra) != 0) {
		// Not a directory in root
		// Free mem
		free(root);
		// Fail
		return -EPERM;
	}

	// Check too long
	if (strlen(name) > MAX_FILENAME) {
		// Too long
		// Free mem
		free(root);
		// Fail
		return -ENAMETOOLONG;
	}

	// Check directory already exists
	for (size_t i = 0; i < root->num_directories; i++)
	{
		if (strcmp(name, root->directories[i].dname) == 0) {
			// Dir already exists
			// Free mem
			free(root);
			// Fail
			return -EEXIST;
		}
	}

	// Get a new directory entry
	os_directory_entry new_dir_entry;
	new_dir_entry.num_files = 0;

	// Find a block for directory
	size_t blocknum_to_place = allocate_block(root);

	// Save the entry
	save_block(blocknum_to_place, &new_dir_entry);

	// Make a new directory in root
	os_directory new_dir;
	new_dir.n_start_block = blocknum_to_place;
	strcpy(new_dir.dname, name);

	// Add dir to root record
	root->directories[root->num_directories] = new_dir;
	root->num_directories++;

	// Save the root
	save_root(root);

	// Free mem
	free(root);

	// Success
	return 0;
}

/**
 * Removes a directory.
 */
static int os_rmdir(const char *path)
{
	return 0;
}

/**
 * Does the actual creation of a file. `mode` and `dev` can be ignored.
 */
static int os_mknod(const char *path, mode_t mode, dev_t dev)
{
	// Decompose the path into dir, file, extension
	// No malloc since sizes known at compile-time
	char directory[MAX_FILENAME+1] = "";
	char filename[MAX_FILENAME+1] = "";
	char extension[MAX_EXTENSION+1] = "";

	// Scan path into boxes
	sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);

	// If filename empty, fail
	if (strcmp(filename,"") == 0) {
		return -EPERM;
	}

	// If name or extension too long, fail
	if (strlen(filename) > MAX_FILENAME || strlen(extension) > MAX_EXTENSION) {
		return -ENAMETOOLONG;
	}

	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Loop through directories
	for (size_t i = 0; i < root->num_directories; i++) {
		if (strcmp(root->directories[i].dname, directory) == 0) {
			// Directory found!

			// Check out the directory
			size_t dir_blocknum = root->directories[i].n_start_block;
			os_directory_entry *dir = (os_directory_entry *)malloc(sizeof(os_directory_entry));
			load_block(dir_blocknum, dir);

			// Make sure filename does not already exist
			for (size_t j = 0; j < dir->num_files; j++) {
				if (strcmp(filename, dir->files[j].fname) == 0 && strcmp(extension, dir->files[j].fext) == 0) {
					// Exists, fail
					// Free mem
					free(dir);
					free(root);
					// Fail
					return -EEXIST;
				}
			}

			// Ensure size
			if (dir->num_files == MAX_FILES_IN_DIR) {
				// Fail
				// Free mem
				free(dir);
				free(root);
				// Fail
				return -ENOSPC;
			}
			// Make a new file entry
			// Get an index block
			size_t blocknum_to_place = allocate_block(root);
			// Nothing to place since file starts with no data blocks

			// Make new file entry
			os_file_entry new_file;
			new_file.fsize = 0;
			new_file.n_index_block = blocknum_to_place;
			strcpy(new_file.fname, filename);
			strcpy(new_file.fext, extension);

			// Add file to dir
			dir->files[dir->num_files] = new_file;
			dir->num_files++;

			// Save the directory and root
			save_block(dir_blocknum, dir);
			save_root(root);

			// Free mem
			free(dir);
			free(root);
			// Success
			return 0;
		}
	}

	// Never found directory
	// No error statement in doc for this
	// Free mem
	free(root);
	// Fail
	return -1;
}

/**
 * Deletes a file.
 */
static int os_unlink(const char *path)
{
	return 0;
}

/**
 * Read `size` bytes from file into `buf`, starting from `offset`.
 */
static int os_read(const char *path, char *buf, size_t size, off_t offset,
		       struct fuse_file_info *fi)
{
	// Decompose the path into dir, file, extension
	// No malloc since sizes known at compile-time
	char directory[MAX_FILENAME+1] = "";
	char filename[MAX_FILENAME+1] = "";
	char extension[MAX_EXTENSION+1] = "";

	// Scan path into boxes
	sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);

	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Loop through the directories
	for (size_t i = 0; i < root->num_directories; i++) {
		if (strcmp(directory, root->directories[i].dname) == 0) {
			// Found the directory!

			// Ensure dir name is not requested filename
			if (strcmp(filename,"") == 0) {
				// requested file is dir
				// Free mem
				free(root);
				// Fail
				return -EISDIR;
			}

			// Assume filename and extension exist

			// Check out the directory
			size_t dir_blocknum = root->directories[i].n_start_block;
			os_directory_entry *dir = (os_directory_entry *)malloc(sizeof(os_directory_entry));
			load_block(dir_blocknum, dir);

			// Find filename
			for (size_t j = 0; j < dir->num_files; j++) {
				if (strcmp(filename, dir->files[j].fname) == 0 && strcmp(extension, dir->files[j].fext) == 0) {
					// Found the file!

					// Grab the index block
					size_t index_blocknum = dir->files[j].n_index_block;
					os_index_block *idx = (os_index_block *)malloc(sizeof(os_index_block));
					load_block(index_blocknum, idx);
					size_t filesize = dir->files[j].fsize;

					// Ensure ending block in bounds
					printf("Sizes: %ld/%ld\n", size+offset, filesize);
					if ((size + offset) > filesize) {
						// Make size smaller to equalize
						size = filesize - offset;
					}
					
					// Get starting block and offset
					size_t start_block_i = offset / BLOCK_SIZE;
					size_t end_block_i = (offset + size) / BLOCK_SIZE;
					size_t start_block_offset = offset % BLOCK_SIZE;

					// Assume that read is valid
					size_t bytes_read = 0;
					for (size_t block_i = start_block_i; block_i <= end_block_i; block_i++) {
						// Find location of datablock
						size_t dat_blocknum = idx->entries[block_i];

						// Find first and end byte nums of this block
						size_t start_byte = block_i*BLOCK_SIZE;
						size_t end_byte = (block_i + 1)*BLOCK_SIZE;

						// Four cases
						// Whole read in this block
						if ((size_t)offset >= start_byte && (offset + size) < end_byte) {
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE+start_block_offset,SEEK_SET);
							fread(buf+bytes_read,size,1,fid);
							bytes_read+=size;
						}
						// Read starts in this block
						else if ((size_t)offset >= start_byte) {
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE+start_block_offset,SEEK_SET);
							fread(buf+bytes_read,BLOCK_SIZE-start_block_offset,1,fid);
							bytes_read+=BLOCK_SIZE-start_block_offset;
						}
						// Read ends in this block
						else if (offset + size < end_byte) {
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE,SEEK_SET);
							fread(buf+bytes_read,(size-bytes_read),1,fid);
							bytes_read += (size - bytes_read);
						}
						// Reads the whole block
						else {
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE,SEEK_SET);
							fread(buf+bytes_read,BLOCK_SIZE,1,fid);
							bytes_read += BLOCK_SIZE;
						}
					}

					// Success!
					free(idx);
					free(dir);
					free(root);
					return size;
				}
			}
			// Did not find the file
			// Free mem
			free(dir);
			free(root);
			// Fail
			return -ENOENT;
		}
	}
	// Did not find the directory
	// Free mem
	free(root);
	// Fail
	return -ENOENT;
}

/**
 * Write `size` bytes from `buf` into file, starting from `offset`.
 */
static int os_write(const char *path, const char *buf, size_t size,
			off_t offset, struct fuse_file_info *fi)
{
	// Decompose the path into dir, file, extension
	// No malloc since sizes known at compile-time
	char directory[MAX_FILENAME+1] = "";
	char filename[MAX_FILENAME+1] = "";
	char extension[MAX_EXTENSION+1] = "";

	// Scan path into boxes
	sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);

	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Loop through the directories
	for (size_t i = 0; i < root->num_directories; i++) {
		if (strcmp(directory, root->directories[i].dname) == 0) {
			// Found the directory!

			// Ensure dir name is not requested filename
			if (strcmp(filename,"") == 0) {
				// requested file is dir
				// Free mem
				free(root);
				// Fail
				return -EISDIR;
			}

			// Assume filename and extension exist

			// Check out the directory
			size_t dir_blocknum = root->directories[i].n_start_block;
			os_directory_entry *dir = (os_directory_entry *)malloc(sizeof(os_directory_entry));
			load_block(dir_blocknum, dir);

			// Find filename
			for (size_t j = 0; j < dir->num_files; j++) {
				if (strcmp(filename, dir->files[j].fname) == 0 && strcmp(extension, dir->files[j].fext) == 0) {
					// Found the file!

					// Grab the index block
					size_t index_blocknum = dir->files[j].n_index_block;
					os_index_block *idx = (os_index_block *)malloc(sizeof(os_index_block));
					load_block(index_blocknum, idx);
					size_t filesize = dir->files[j].fsize;

					// Ensure ending block in bounds
					if ((size + offset) > filesize) {
						
						// Add data blocks as necessary
						size_t curr_nblocks = filesize == 0 ? 0 : (filesize / BLOCK_SIZE) + 1;
						size_t needed_nblocks = ((size + offset) / BLOCK_SIZE) + 1;

						for (size_t new_datblock_i = curr_nblocks; new_datblock_i < needed_nblocks; new_datblock_i++) {
							// Get space for a block
							size_t new_dat_blocknum = allocate_block(root);
							idx->entries[new_datblock_i] = new_dat_blocknum;
						}

						dir->files[j].fsize = size + offset;
						printf("New size: %ld\n", size + offset);
						filesize = dir->files[j].fsize;
					}
					
					// Get starting block and offset
					size_t start_block_i = offset / BLOCK_SIZE;
					size_t end_block_i = (offset + size) / BLOCK_SIZE;
					size_t start_block_offset = offset % BLOCK_SIZE;

					// Assume that read is valid
					size_t bytes_written = 0;
					for (size_t block_i = start_block_i; block_i <= end_block_i; block_i++) {
						// Find location of datablock
						size_t dat_blocknum = idx->entries[block_i];

						// Find first and end byte nums of this block
						size_t start_byte = block_i*BLOCK_SIZE;
						size_t end_byte = (block_i + 1)*BLOCK_SIZE;

						// Four cases
						// Whole read in this block
						if ((size_t)offset >= start_byte && (offset + size) < end_byte) {
							printf("Case 1:\n");
							printf("%ld,%s\n",dat_blocknum*BLOCK_SIZE+start_block_offset,buf+bytes_written);
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE+start_block_offset,SEEK_SET);
							fwrite(buf+bytes_written,size,1,fid);
							bytes_written+=size;
						}
						// Read starts in this block
						else if ((size_t)offset >= start_byte) {
							printf("Case 2:\n");
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE+start_block_offset,SEEK_SET);
							fwrite(buf+bytes_written,BLOCK_SIZE-start_block_offset,1,fid);
							bytes_written+=BLOCK_SIZE-start_block_offset;
						}
						// Read ends in this block
						else if (offset + size < end_byte) {
							printf("Case 3:\n");
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE,SEEK_SET);
							fwrite(buf+bytes_written,(size-bytes_written),1,fid);
							bytes_written += (size - bytes_written);
						}
						// Reads the whole block
						else {
							printf("Case 4:\n");
							// Load from this block
							fseek(fid,dat_blocknum*BLOCK_SIZE,SEEK_SET);
							fwrite(buf+bytes_written,BLOCK_SIZE,1,fid);
							bytes_written += BLOCK_SIZE;
						}
					}

					// Success!
					// Save dir
					save_block(dir_blocknum, dir);

					// Save idx
					save_block(index_blocknum, idx);

					// Save root
					save_root(root);

					free(idx);
					free(dir);
					free(root);
					return size;
					
				}
			}
			// Did not find the file
			// Free mem
			free(dir);
			free(root);
			// Fail
			return -ENOENT;
		}
	}
	// Did not find the directory
	// Free mem
	free(root);
	// Fail
	return -ENOENT;
}

/**
 * Called when a new file is created (with a 0 size) or when an existing file
 * is made shorter. We're not handling deleting files or truncating existing
 * ones, so all we need to do here is to initialize the appropriate directory
 * entry.
 */
static int os_truncate(const char *path, off_t size)
{
	return 0;
}

/**
 * Called when we open a file.
 */
static int os_open(const char *path, struct fuse_file_info *fi)
{
	// Decompose the path into dir, file, extension
	// No malloc since sizes known at compile-time
	char directory[MAX_FILENAME+1] = "";
	char filename[MAX_FILENAME+1] = "";
	char extension[MAX_EXTENSION+1] = "";

	// Scan path into boxes
	sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);

	// Load the root
	os_root_directory *root = (os_root_directory *)malloc(sizeof(os_root_directory));
	load_root(root);

	// Loop through the directories
	for (size_t i = 0; i < root->num_directories; i++) {
		if (strcmp(directory, root->directories[i].dname) == 0) {
			// Found the directory!

			// Ensure dir name is not requested filename
			if (strcmp(filename,"") == 0) {
				// requested file is dir
				// Free mem
				free(root);
				// Fail
				return -ENOENT;
			}

			// Assume filename and extension exist

			// Check out the directory
			size_t dir_blocknum = root->directories[i].n_start_block;
			os_directory_entry *dir = (os_directory_entry *)malloc(sizeof(os_directory_entry));
			load_block(dir_blocknum, dir);

			// Find filename
			for (size_t j = 0; j < dir->num_files; j++) {
				if (strcmp(filename, dir->files[j].fname) == 0 && strcmp(extension, dir->files[j].fext) == 0) {
					// Found the file!
					// Return mem
					free(dir);
					free(root);
					// Success
					return 0;
				}
			}
			// Did not find the file
			// Free mem
			free(dir);
			free(root);
			// Fail
			return -ENOENT;
		}
	}
	// Did not find the directory
	// Free mem
	free(root);
	// Fail
	return -ENOENT;
}

/**
 * Called when close is called on a file descriptor, but because it might
 * have been dup'ed, this isn't a guarantee we won't ever need the file
 * again. For us, return success simply to avoid the unimplemented error
 * in the debug log.
 */
static int os_flush(const char *path, struct fuse_file_info *fi)
{
	// Success!
	return 0;
}

/**
 * This function should be used to open and/or initialize your `.disk` file.
 */
static void *os_init(struct fuse_conn_info *fi)
{
	// Open fid
	fid = fopen(".disk", "rb+");

	// Make a root
	os_root_directory root;
	root.last_allocated_block = 0;
	root.num_directories = 0;
	save_root(&root);

	return NULL;
}

/**
 * This function should be used to close the `.disk` file.
 */
static void os_destroy(void *args)
{
	// Close fid
	fclose(fid);
}

/*
 * Register our new functions as the implementations of the syscalls.
 */
static struct fuse_operations os_oper = {
	.getattr	= os_getattr,
	.readdir	= os_readdir,
	.mkdir		= os_mkdir,
	.rmdir		= os_rmdir,
	.read		= os_read,
	.write		= os_write,
	.mknod		= os_mknod,
	.unlink		= os_unlink,
	.truncate	= os_truncate,
	.flush		= os_flush,
	.open		= os_open,
	.init		= os_init,
	.destroy	= os_destroy,
};

/*
 * Don't change this.
 */
int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &os_oper, NULL);
}
