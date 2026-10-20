#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int MAX_LINE = 256;

// Prototypes
void displayTestResults(void);
void displaySummary(void);
void runTest(char args[][MAX_LINE], const int amountOfComm);

int main(){
	int totalTests;
	int successfulTests;
	int failedTests;
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

		// Skip blank lines and lines begining with #
    if (line[0] == '#' || line[0] == 13){
      continue; 
    }

    // TODO Remove trailing newline char
		for (size_t i = 0; line[i] != '\0'; i++){
      if (line[i] == '\n'){
        line[i] = '\0';
        printf("Successfuly replaced\n");
      }
    }

    // Increment the amout of tests
    totalTests++;
    
		// TODO parse each test command into an argument array
    char commands[MAX_LINE][MAX_LINE];
   
    size_t incrementer = 0;
    size_t commandParse = 0;
    
    // Itterate through the line
    for (int i = 0; line[i] != '\0'; i++){
      // Check for a space
      if (line[i] == ' '){
        incrementer++;
        commandParse = (i + 1);
        continue;
      }
      // Set the commands line
      commands[incrementer][i - commandParse] = line[i];
      printf("added %c to %d, %d\n", line[i], incrementer, i - commandParse);
    }

		// Run the test
		runTest(commands, incrementer + 1);

		// TODO Continue even if the test fails
    

    // Clean up the commands array
    // for (int i = 0; i < sizeof(commands); i++){
    //  for (int j = 0; j < sizeof(commands[i]); j++){
    //    commands[i][j] = 0;
    //  }
    //}
	}
  return 1;
}

// Function that runs the commands
void runTest(char args[][MAX_LINE], const int amountOfComm){
  // TESTING the function input
  for (int i = 0; i < amountOfComm; i++){
    printf("%s\n", args[i]);
  }
}
