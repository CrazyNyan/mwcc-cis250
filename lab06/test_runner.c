#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 256

// Prototypes
void displayTestResults(const int testsPassed, const int testsFailed);
int runTest(char* commandBeingRun, char *args[]);

int main(){
	int totalTests = 0;
	int successfulTests = 0;
	int failedTests = 0;
  int testStatus = 0;

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
    
    // Copy th command in it's entirety
    char commandToRun[MAX_LINE];
    strcpy(commandToRun, line);

    // Create a tokenized char array
    char* tok = strtok(line, " ");

    // Skip blank lines and lines begining with #
    if (tok[0] == '#' || tok == NULL || tok[0] == '\n'){
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
		testStatus = runTest(commandToRun, args);

		// Record the results of the test
    if (testStatus == 0){
      successfulTests++;
    } else if (testStatus == 1){
      failedTests++;
    } else {
      perror("Critical error with tests");
      return 1;
    }

	}

  // Display the results to the user
  displayTestResults(successfulTests, failedTests);

  return 0;
}

// Function that runs the commands
int runTest(char* commandBeingRun, char *args[]){ 
  // Display the command
  printf("================================\n");
  printf("Command being tested: %s\n", commandBeingRun);
  printf("================================\n");

  // Fork the process
  pid_t pid = fork();

  // Checking fork status
  if (pid == -1){
    perror("Fork");

  } else if (pid == 0){ // Child code
    // Exec the command
    printf("================================\n");
    printf("Starting\n");
    printf("================================\n");
    execvp(args[0], args);

    // Catch an error, if the command was incorrectly executed
    _exit(1);

  } else {              // Parent code
    // Wait for child
    int status;

    // Check to see how the child did and return the result
    wait(&status);

    // Display result
    if (WEXITSTATUS(status) == 0){
      printf("================================\n");
      printf("PASSED\n");
      printf("================================\n");
    } else {
      printf("================================\n");
      printf("FAILED\n");
      printf("================================\n");
    }
    
    return WEXITSTATUS(status);
  }
  
  // If reached, error
  return -1;
}

void displayTestResults(const int testsPassed, const int testsFailed){
  // Display results
  printf("================================\nTEST SUMMARY\n================================\n");
  printf("Tests executed: %d\n", (testsPassed + testsFailed));
  printf("Tests passed:   %d\n", testsPassed);
  printf("Tests failed:   %d\n", testsFailed);
  printf("================================\n");
}
