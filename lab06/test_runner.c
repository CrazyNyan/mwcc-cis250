#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 256

// Prototypes
void displayTestResults(void);
void displaySummary(void);
void runTest(char* commandBeingRun, char *args[]);

int main(){
	int totalTests = 0;
	int successfulTests = 0;
	int failedTests = 0;
	// Open tests.txt for reading. If the file can't be opened, throw an error
	FILE *testplanFile;
	char line[MAX_LINE];

	testplanFile = fopen("tests.txt", "r");

	if(testplanFile == NULL){
		perror("Unable to open tests.txt");
		return 1;
	}

	// Use the Standard Library to read the file line by line with fgets()
	while(fgets(line, sizeof(line), testplanFile) != NULL){
    // Remove trailing newline char
		strtok(line, "\n");
    
    // Copy the command in it's entirety
    char* commandToRun;
    strcpy(commandToRun, line);

    // Create a tokenized char array
    char* tok = strtok(line, " ");

    // Skip blank lines and lines begining with #
    if (tok[0] == '#' || tok == NULL){
      continue;
    }

    // Increment the amout of tests
    totalTests++;
		
    // Parse each test command into an argument array suitable for execvp()
    char *args[256] = {NULL};
    int argc = 0;
    while(tok != NULL && argc < 255){
      args[argc++] = tok;
      tok = strtok(NULL, " ");
    }

		// Run the test
		runTest(commandToRun, args);

		// TODO Continue even if the test fails
    
	}
  return 0;
}

// Function that runs the commands
void runTest(char* commandBeingRun, char *args[]){
  // TODO Run the commands 
  // Display the command
  printf("===============================\n");
  printf("Running the command: %s\n", commandBeingRun);
  printf("===============================\n");

  // Fork the process

  pid_t pid = fork();

  // Checking fork status
  if (pid == -1){
    perror("Fork");

  } else if (pid == 0){ // Child code
    // Exec the command
    execvp(args[0], args);

    // Catch an error, if the command was incorrectly executed, perror triggers
    perror(commandBeingRun);
    exit(1);

  } else {              // Parent code
    // Wait for child
    int status;

    wait(&status);

  }

}
