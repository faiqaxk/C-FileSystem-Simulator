#ifndef FILESYSTEM_H
#define FILESYSTEM_H

// Initializes the filesystem by setting up necessary directories and loading the existing state from a file.
void initialize_filesystem();

// Creates a new file with the specified filename within the managed filesystem directory.
// Updates the filesystem state to include this new file.
void create_file(const char *filename);

// Deletes a specified file from the filesystem directory.
// Updates the filesystem state to reflect the removal of this file.
void delete_file(const char *filename);

// Writes the provided content to a specified file. If the file does not exist, the operation will fail.
// The file content is overwritten with the new content provided.
void write_to_file(const char *filename, const char *content);

// Reads the content from a specified file and prints it to the standard output.
// If the file does not exist or cannot be read, an error message is displayed.
void read_from_file(const char *filename);

// Lists all the files currently managed by the filesystem.
// This function prints each file that is marked as in use within the filesystem's state.
void list_files();

// Loads the state of the filesystem from a persistent storage file.
// This function is typically called at program initialization to restore the list of active files.
void load_state();  // Declaration of the load_state function

// Updates the state of the filesystem by writing the current state to a persistent storage file.
// This function is called whenever changes are made to the filesystem (e.g., creating or deleting files).
void update_state();  // Declaration of the update_state function

#endif // FILESYSTEM_H
