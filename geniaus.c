#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define MAX_SEQ_LENGTH 80
#define MAX_COLORS_NUMBER 4
#define MAX_TIME 1000

#define BLUE "color 90"
#define GREEN "color C0"
#define BLACK "color 0F"
#define YELLOW "color E0"
#define RED "color A0"

void displayMenu();
void startGame();
void displayRules();

void generateRandomColor(int *seqLength, int sequence[]);
void setColor(char color[], int waitTime, int seq, int freqBeep, int durationBeep);
int isRightSequence(int seqLength, int sequence[]);

void clearScreen();

int main(){
	srand(time(NULL));
		
	displayMenu();
		
	return 0;
}

void displayMenu(){
	char option, answer;
	int valid;
	
	clearScreen();
			
	printf("# Geniaus #\n\n");
	
	printf("1) Start\n");
	printf("2) Rules\n");
	printf("3) Exit\n\n");
	
	do{
		valid = 1;
		
		option = getch();
		
		if(option != '1' && option != '2' && option != '3')
			valid = 0;
	}while(!valid);
	
	switch(option){
		case '1':	
			startGame();
			Sleep(2000);
			
			printf("\nPRESS ENTER TO RETURN TO THE MENU");
	
			do{
				answer = getch();
			}while(answer != 13);
	
			displayMenu();
			break;
		case '2':
			displayRules();
			break;
		case '3':
			exit(0);
	}	
}

void startGame(){
	int sequence[MAX_SEQ_LENGTH], i, seqLength, time, answer, isRight, score, speed;
	
	clearScreen();
	
	seqLength = score = 0;
	isRight = speed = 1;
	time = MAX_TIME;
			
	while(isRight){
		generateRandomColor(&seqLength, sequence);
				
		for(i = 0; i < seqLength; i++){
			switch(sequence[i]){
				case 1:
					setColor(RED, time, sequence[i], 1000, 600);
					break;
				case 2:
					setColor(YELLOW, time, sequence[i], 800, 500);
					break;
				case 3:
					setColor(GREEN, time, sequence[i], 600, 400);
					break;
				case 4:
					setColor(BLUE, time, sequence[i], 400, 300);		
			}				
		}
		
		system(BLACK);

		isRight = isRightSequence(seqLength, sequence);
		
		if(isRight){
			score += 10;
			
			if(time == 100) continue;
			
			if(score%30 == 0){
				speed++;
				time -= score*speed;
				
				clearScreen();
				
				printf("Accumulated score: %i\n", score);
				Sleep(1000);
				
				if(time < 100){	
					time = 100;
					
					printf("Final speed! The last challenge! Keep going while you can!\n", speed, time);
				}
				else{
					printf("Speed: %i! The game becomes faster!\n", speed, time);
				}
			
				Sleep(2000);	
			
			}
		}
	}
	
	clearScreen();
	
	printf("You made a wrong call, buddy!\n");
	Beep(900, 3000);
	
	Sleep(2000);
	
	clearScreen();
	
	printf("Accumulated score: %i\n", score);
}

void generateRandomColor(int *seqLength, int sequence[]){
	int color;
	
	color = rand()%4+1;
	
	sequence[(*seqLength)++] = color;
}

void setColor(char color[], int waitTime, int seq, int freqBeep, int durationBeep){
	clearScreen();
	
	system(color);
	printf("Color code: %d", seq);
	Beep(freqBeep, durationBeep);
	Sleep(waitTime);
	
	clearScreen();
}

int isRightSequence(int seqLength, int sequence[]){
	int i, answer;
	
	for(i = 0; i < seqLength; i++){
		scanf("%i", &answer);	
				
		if(answer != sequence[i])
			return 0;
	}
	
	return 1;
}

void displayRules(){
	int answer;
	
	clearScreen();
	
	printf("* GENIAUS shows one color and its respective code.\n");
	printf("* You must enter the right color code.\n");
	printf("* The color is going to appear again added with another one, creating a sequence.\n");
	printf("* You must enter both colors code correctly.\n");
	printf("* Every time you enter the sequence correctly, a new color will be added to it.\n");
	printf("* Keep up while you're able to remember the whole color sequence.\n");
	printf("* The speed increases as you score.\n");
	printf("* If you don't remember the sequence, well... you'll see what happens.\n");

	printf("\nPRESS ENTER TO RETURN TO THE MENU");
	
	do{
		answer = getch();
	}while(answer != 13);
	
	displayMenu();
}

void clearScreen(){
	system("cls");	
}
