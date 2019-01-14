#define _CRT_SECURE_NO_WARNINGS

//add compliment feature
//add grade based off threshold feature

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define solutionSize 40
#define RIGHT 1
#define WRONG 0
#define ONESECOND 1000

//The database txt files
#define SUMMER "MJAnswerKey.txt"
#define WINTER "ONAnswerKey.txt"

/*
*This function will take the OMR input from the image
*and store the solutions in a character array/ String
*of size 40.
*
*/

char* scanner(void);


/*
*This function uses the paper info to identify the database 
*solution to compare with student solution and returns the 
*solution as a string of letters.
*/

char* dataBaseSolution(int variant, int year, char* session);

/*
*Matches the students answers with the database solution
*and returns total score. It also stores a non-zero
*value in an array to mark the questions the student got wrong.
*/

int checkAnswer(char studentAnswer[], char correctAnswer[], int incorrectAnswers[]);


/*
*Prints the questions answered incorrectly
*and displays the correct solution
*/

void printWrongs(int incorrectAnswers[], char correctAnswer[]);


int main(void) {
	int variant;
	int year;
	char session[2] = "";
	char name[25] = "";
	int* incorrectAns = malloc(sizeof(int) * solutionSize);
	int score;
	
	printf("Hi there Scholar! Welcome back.\n");
	Sleep(ONESECOND);
	
	printf("How can we help you today? \n\n");
	Sleep(ONESECOND);

	printf("Please enter your name\n");
	scanf("%s", name);
	Sleep(ONESECOND);

	printf("Please enter your question paper variant\n");
	scanf("%d", &variant);
	Sleep(ONESECOND);

	printf("Please enter your question paper year\n");
	scanf("%d", &year);
	Sleep(ONESECOND);

	printf("Choose either MJ or ON session and enter it.\n");
	scanf("%s", session);
	Sleep(ONESECOND);

	char* studentAns = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; //scanner();
	char* correctAns = dataBaseSolution(variant, year, session);
	
	score = checkAnswer(studentAns, correctAns, incorrectAns);

	printf("You have achieved a score of %.2f\n", score / 40.0 * 100.0);

	printWrongs(incorrectAns, correctAns);
	
	system("PAUSE");
	return 0;
}
/*
char* scanner(void) {
	//incomplete
}*/

/*
*The database will be two text files for each variant, with 
*every row referring to a specific paper. The first integer 
*value of the row will refer to the paper year and the second
*integer will refer to the variant. The remaining information
*will be the solution key for 40 questions (1234 to represent
*ABCD).
*/

char* dataBaseSolution(int variant, int year, char* session) {
	FILE* MJ;
	FILE* ON;
	int year_key;
	int variant_key;
	int index;
	int num;
	char* solution = malloc(sizeof(char) * 40);

	if (strcmp(session, "MJ") == 0) {
		MJ = fopen(SUMMER, "r");

		if (MJ == NULL) {
			printf("Error in loading file\n");
		}
		else {
			while (fscanf(MJ, "%d %d", &year_key, &variant_key) == 2) {
				if (year == year_key && variant == variant_key) {
					for (index = 0; index < 40; index++) {
						fscanf(MJ, "%d", &num);
						if (num == 1)
							solution[index] = 'A';
						else if (num == 2)
							solution[index] = 'B';
						else if (num == 3)
							solution[index] = 'C';
						else if (num == 4)
							solution[index] = 'D';
					}
				}
				else {
					for (index = 0; index < 40; index++) {
						fscanf(MJ, "%d", &num);
						//does nothing
					}
				}
			}
		}
	}
	else if (strcmp(session, "ON") == 0) {
		ON = fopen(WINTER, "r");

		if (ON == NULL) {
			printf("Error in loading file\n");
		}
		else {
			while (fscanf(ON, "%d %d", &year_key, &variant_key) == 2) {
				if (year == year_key && variant == variant_key) {
					for (index = 0; index < 40; index++) {
						fscanf(ON, "%d", &num);
						if (num == 1)
							solution[index] = 'A';
						else if (num == 2)
							solution[index] = 'B';
						else if (num == 3)
							solution[index] = 'C';
						else if (num == 4)
							solution[index] = 'D';
					}
				}
				else {
					for (index = 0; index < 40; index++) {
						fscanf(ON, "%d", &num);
						//does nothing
					}
				}
			}
		}
	}
	
	return solution;
}

int checkAnswer(char studentAnswer[], char correctAnswer[], int incorrectAnswers[]) {
	int TotalScore = 0;
	int index;

	for (index = 0; index < solutionSize; index++) {
		if (studentAnswer[index] == correctAnswer[index]) {
			TotalScore++;
		}
		else {
			incorrectAnswers[index] = 1;
		}
	}

	return TotalScore;

}

void printWrongs(int incorrectAnswers[], char correctAnswer[]) {
	int count = 0;
	int index;
	int userInput;

	for (index = 0; index < solutionSize; index++) {
		if (incorrectAnswers[index] != 0) {
			count++;
		}
	}

	printf("Aww snap! You got %d questions incorrect \n", count);
	printf("Try the following questions again! \n");

	for (index = 0; index < solutionSize; index++) {
		if (incorrectAnswers[index] != 0) {
			printf("%d ", index + 1);
		}
	}

	printf("\n");

	Sleep(ONESECOND);

	printf("If you want to reveal the correct answers to these problems, enter 1\n");
	scanf("%d", &userInput);

	if (userInput == 1) {
		for (index = 0; index < solutionSize; index++) {
			if (incorrectAnswers[index] != 0) {
				printf("%d %c  ", index + 1, correctAnswer[index]);
			}
		}
	}

	printf("\n");
}

