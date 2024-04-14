#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Initialize the filesystem; this loads any existing file information and prepares the environment.
    initialize_filesystem();

    // Check if the correct number of arguments has been provided, otherwise display usage instructions.
    if (argc == 1) {
        printf("Usage: %s [command] [filename] [content(optional)]\n", argv[0]);
        return 1;  // Exit with an error code if not enough arguments are provided.
    }

    const char *command = argv[1];  // The command to execute (create, delete, write, read, list).

    // Handling of the 'list' command which requires no additional arguments beyond the command itself.
    if (strcmp(command, "list") == 0) {
        list_files();  // Call the function that lists all files.
    } else if (argc > 2) {  // Ensure there are enough arguments for commands that require a filename.
        const char *filename = argv[2];  // The filename on which the operation will be performed.

        // Handling of the 'create' command to create a new file.
        if (strcmp(command, "create") == 0) {
            create_file(filename);  // Create a file with the provided filename.
        } 
        // Handling of the 'delete' command to delete an existing file.
        else if (strcmp(command, "delete") == 0) {
            delete_file(filename);  // Delete the file with the provided filename.
        }
        // Handling of the 'write' command which requires an additional argument for content.
        else if (strcmp(command, "write") == 0 && argc > 3) {
            const char *content = argv[3];  // The content to write to the file.
            write_to_file(filename, content);  // Write the provided content to the specified file.
        }
        // Handling of the 'read' command to display the content of a file.
        else if (strcmp(command, "read") == 0) {
            read_from_file(filename);  // Read and display the content of the specified file.
        } else {
            printf("Invalid command.\n");  // Print an error message if the command is unrecognized.
        }
    } else {
        // If there are not enough arguments for any command except 'list', print an error.
        printf("Insufficient arguments.\n");
    }

    return 0;  // Successful execution of the program.
}
