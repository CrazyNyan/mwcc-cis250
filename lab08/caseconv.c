#include <stdio.h>      // printf()
#include <string.h>     // For strcmp
#include <fcntl.h>      // open()
#include <unistd.h>     // read, write, close
#include <sys/mman.h>   // mmap()
#include <ctype.h>      // toupper/tolower
#include <sys/stat.h>   // fstat
 
#define PAGESIZE 4096   // Allocated memory

int main (int argc, char *argv[]) { 
  // Data structure to hold the file status buffer
  struct stat status_buffer;

  // Check if the command line arguments match specifcations
  if (argc != 3){
    perror("Usage: ./caseconv.c upper/lower target");
    return 1;
  }
  if (strcmp(argv[1], "upper") != 0 && strcmp(argv[1], "lower") != 0){
    perror("Usage: ./caseconv.c upper/lower target");
    return 1;
  }

  // Open the file
  int converting_file = open(argv[2], O_RDONLY);

  if (converting_file == -1){
    close(converting_file);
    perror("Unable to open the specified file");
    return 1;
  }
  
  // Check the size of the file, if zero return
  if (fstat(converting_file, &status_buffer) == -1){
    close(converting_file);
    perror("Could not get file size!");
    return 1;
  } else if (status_buffer.st_size > PAGESIZE){
    close(converting_file);
    perror("File outside of maximum bounds");
    return 1;
  } else if (status_buffer.st_size == 0){
    close(converting_file);
    return 0;
  }

  // Create the mmap
  char *converting_map = mmap(NULL, status_buffer.st_size, PROT_READ,
                              MAP_PRIVATE, converting_file, 0);

  // Convert the characters and print them to standard out
  
  // Check the arguments and convert accordingly
  if (strcmp(argv[1], "upper") == 0){
    // Print each character individualy
    for (int i = 0; i < status_buffer.st_size; i++){
      char temp_char = converting_map[i];
      printf("%c", toupper(temp_char));
    }
  } else {
    // Print each character individualy
    for (int i = 0; i < status_buffer.st_size; i++){
      char temp_char = converting_map[i];
      printf("%c", tolower(temp_char));
    }
  }

  // Release resorces
  munmap(converting_map, PAGESIZE);
  close(converting_file);

  return 0;
}
