#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10  // Maximum number of files that can be tracked
#define DIRECTORY "filesystem"  // Directory where files are stored
#define MAX_FILENAME_LENGTH 256  // Maximum length of filenames
#define STATE_FILE "filesystem/state.txt"  // File that stores the state of the filesystem

// Structure to store information about files
typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    int in_use;  // Flag to indicate whether the file slot is in use
} File;

File files[MAX_FILES];  // Array to store files

// Initializes the filesystem by creating the directory and loading the state
void initialize_filesystem() {
    char command[100];
    snprintf(command, sizeof(command), "mkdir -p %s", DIRECTORY);  // Create the directory if it doesn't exist
    system(command);  // Execute the command to create the directory
    load_state();  // Load the state from the state file
}

// Loads the current state of the filesystem from a file
void load_state() {
    FILE *fp = fopen(STATE_FILE, "r");  // Open the state file for reading
    if (fp) {
        char filename[MAX_FILENAME_LENGTH];
        while (fscanf(fp, "%255s", filename) == 1) {  // Read filenames from the file
            for (int i = 0; i < MAX_FILES; i++) {
                if (!files[i].in_use) {  // Find an unused slot
                    strncpy(files[i].filename, filename, MAX_FILENAME_LENGTH);  // Copy filename
                    files[i].in_use = 1;  // Mark the slot as in use
                    break;
                }
            }
        }
        fclose(fp);  // Close the file
    }
}

// Updates the state file with the current state of the filesystem
void update_state() {
    FILE *fp = fopen(STATE_FILE, "w");  // Open the state file for writing
    if (fp) {
        for (int i = 0; i < MAX_FILES; i++) {
            if (files[i].in_use) {  // Check if the file slot is in use
                fprintf(fp, "%s\n", files[i].filename);  // Write the filename to the state file
            }
        }
        fclose(fp);  // Close the file
    }
}

// Creates a file in the filesystem
void create_file(const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].in_use) {  // Find an unused slot
            strncpy(files[i].filename, filename, MAX_FILENAME_LENGTH);  // Copy filename
            files[i].in_use = 1;  // Mark the slot as in use
            update_state();  // Update the state file
            printf("File '%s' created successfully.\n", filename);
            return;
        }
    }
    printf("Failed to create file: Maximum file limit reached.\n");
}

// Deletes a file from the filesystem
void delete_file(const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].in_use && strcmp(files[i].filename, filename) == 0) {  // Match filename
            files[i].in_use = 0;  // Mark the slot as not in use
            update_state();  // Update the state file
            printf("File '%s' deleted successfully.\n", filename);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}

// Writes content to a file
void write_to_file(const char *filename, const char *content) {
    char path[MAX_FILENAME_LENGTH];
    snprintf(path, sizeof(path), "%s/%s", DIRECTORY, filename);  // Construct file path
    FILE *fp = fopen(path, "w");  // Open the file for writing
    if (fp) {
        fprintf(fp, "%s", content);  // Write content
        fclose(fp);  // Close the file
        printf("Content written to '%s' successfully.\n", filename);
    } else {
        printf("Failed to write to '%s'. File not found.\n", filename);
    }
}

// Reads content from a file
void read_from_file(const char *filename) {
    char path[MAX_FILENAME_LENGTH];
    snprintf(path, sizeof(path), "%s/%s", DIRECTORY, filename);  // Construct file path
    FILE *fp = fopen(path, "r");  // Open the file for reading
    if (fp) {
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), fp)) {  // Read content
            printf("Content of '%s': %s", filename, buffer);
        } else {
            printf("No content found in '%s'.\n", filename);
        }
        fclose(fp);  // Close the file
    } else {
        printf("Failed to open '%s' for reading.\n", filename);
    }
}

// Lists all files currently in use in the filesystem
void list_files() {
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].in_use) {  // Check if the file slot is in use
            if (!found) {
                printf("Files in filesystem:\n");
                found = 1;  // Set found flag to true after finding the first file
            }
            printf("%s\n", files[i].filename);
        }
    }
    if (!found) {
        printf("No files found.\n");
    }
}
