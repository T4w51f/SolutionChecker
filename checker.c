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
#define SUMGT "MJThreshold.txt"
#define WINGT "ONThreshold.txt"

/*
*This function will take the answer input from the user
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

/*
*This function returns the grade the student receives based
*off that years grade threshold
*/
void printGrade(int variant, int year, int score, char* session);

int main(void) {
	int variant;
	int year;
	char session[3] = "";
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

	char* studentAns = scanner();
	char* correctAns = dataBaseSolution(variant, year, session);
	
	score = checkAnswer(studentAns, correctAns, incorrectAns);
	printf("You have achieved a score of %.2f%%\n", score / 40.0 * 100.0);
	printWrongs(incorrectAns, correctAns);
	printGrade(variant, year, score, session);
	system("PAUSE");
	return 0;
}

char* scanner(void) {
	int i = 0;
	char* studentAns = malloc(sizeof(char) * 41);

	for (i = 0; i < 40; i++) {
		printf("Enter answer to question %d\n", i + 1);
		scanf("%c", &studentAns[i]);
	}

	return studentAns;
}

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
			incorrectAnswers[index] = 0;
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
	if (count != 0) {
		printf("Aww snap! You got %d questions incorrect \n", count);
		printf("Try the following questions again! \n");
		for (index = 0; index < solutionSize; index++) {
			if (incorrectAnswers[index] != 0) {
				printf("%d ", index + 1);
			}
		}
	}
	else {
		printf("Congratulation! Outstanding work\n");
	}
	printf("\n");
	Sleep(ONESECOND);
	printf("If you want to reveal the correct answers to these problems, enter 1\n");
	scanf("%d", &userInput);
	if (userInput == 1) {
		for (index = 0; index < solutionSize; index++) {
			if (incorrectAnswers[index] == 1) {
				printf("%d)%c;  ", index + 1, correctAnswer[index]);
			}
		}
	}
	printf("\n");
}

void printGrade(int variant, int year, int score, char* session) {
	FILE* MJGT;
	FILE* ONGT;
	int year_key;
	int variant_key;
	int index;
	int A, B, C, D, E, F, U;
	int num;
	if (strcmp(session, "MJ") == 0) {
		MJGT = fopen(SUMGT, "r");
		if (MJGT == NULL) {
			printf("Error in loading file\n");
		}
		else {
			while (fscanf(MJGT, "%d %d", &year_key, &variant_key) == 2) {
				if (year == year_key && variant == variant_key) {

					while (fscanf(MJGT, "%d %d %d %d %d %d %d", &A, &B, &C, &D, &E, &F, &U) == 7) {
						if (score >= A && score < 40)
							printf("You received an 'A' grade\n");
						else if (score >= B && score < A)
							printf("You received a 'B' grade\n");
						else if (score >= C && score < B)
							printf("You received a 'C' grade\n");
						else if (score >= D && score < C)
							printf("You received a 'D' grade\n");
						else if (score >= E && score < D)
							printf("You received an 'E' grade\n");
						else if (score >= F && score < E)
							printf("You received an 'F' grade\n");
						else if (score >= U && score < F)
							printf("You received a 'U' grade\n");
					}
				}
				else {
					for (index = 0; index < 7; index++) {
						fscanf(MJGT, "%d", &num);
						//does nothing
					}
				}
			}
		}
	}
	else if (strcmp(session, "ON") == 0) {
		ONGT = fopen(WINGT, "r");
		if (ONGT == NULL) {
			printf("Error in loading file\n");
		}
		else {
			while (fscanf(ONGT, "%d %d", &year_key, &variant_key) == 2) {
				if (year == year_key && variant == variant_key) {
					while (fscanf(ONGT, "%d %d %d %d %d %d %d", &A, &B, &C, &D, &E, &F, &U) == 7) {
						if (score >= A && score < 40)
							printf("You received an 'A' grade\n");
						else if (score >= B && score < A)
							printf("You received a 'B' grade\n");
						else if (score >= C && score < B)
							printf("You received a 'C' grade\n");
						else if (score >= D && score < C)
							printf("You received a 'D' grade\n");
						else if (score >= E && score < D)
							printf("You received an 'E' grade\n");
						else if (score >= F && score < E)
							printf("You received an 'F' grade\n");
						else if (score >= U && score < F)
							printf("You received a 'U' grade\n");
					}
				}
				else {
					for (index = 0; index < 7; index++) {
						fscanf(ONGT, "%d", &num);
						//does nothing
					}
				}
			}
		}
	}
}

