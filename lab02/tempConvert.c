# include <stdio.h>

float convertToCel (float inputTemp){
	return ((inputTemp - 32) * 5 / 9);
}

float convertToFer (float inputTemp){
	return ((inputTemp * 9 / 5) + 32);
}


int main (void){
	float fTemp = 0;
	float fConvertedTemp = 0;
	int selection = 0;
	do {
		fTemp = 0;
		fConvertedTemp = 0;
		printf("Welcome to the Temperature Converter!\n");
		printf("Please select one of the following:\n");
		printf("1. Convert from Fahrenhiet to Celsius\n");
		printf("2. Convert from Celsius to Fahrenhiet\n");
		printf("3. Exit\n");

		scanf("%d", &selection);
	
		printf("You selected %d\n", selection);
		
		if (selection == 1){
			printf("Enter the temperature in Fahrenhiet to be converted\n");
			scanf("%f", &fTemp);
			fConvertedTemp = convertToCel(fTemp);
			printf("That temperature converted to Celsius is:\n%.2f!\n", fConvertedTemp);
		}
		
		if (selection == 2){
			printf("Enter the temperature in Celsius to be converted\n");
			scanf("%f", &fTemp);
			fConvertedTemp = convertToFer(fTemp);
			printf("That temperature converted to Fahrenhiet is:\n%.2f!\n", fConvertedTemp);
		}
		
	} while (selection != 3);
	printf("Exiting program\n");
	return 0;
}

