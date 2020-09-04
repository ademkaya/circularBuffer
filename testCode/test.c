// circular.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdio.h>
#include <windows.h>
#include "CircularQue.h"

static void fillUpCircularQue(CircularQue_Typedef* ptr);
static void writeCircularQue(CircularQue_Typedef* ptr, uint8_t itemInLine);

void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str);
void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr);
void printIntOnSpesificLocation(uint16_t X, uint16_t Y, int int_);
void clearScreen(void);
void delay(void);

CircularQueFunctions_Typedef* CQue = NULL;
typedef union  {
	/* floating point data to void* implementation */
	float vf;
	void* vp;
}floatUnion_Typedef;
int main()
{	
	bool push		= true;
	bool pop		= false;
	bool reset		= false;
	bool update		= false;
	bool free		= false;
	void* popData	= NULL;

	Initialize_CircularQueLib(&CQue);
	CircularQue_Typedef* ptr = CQue->Init_CircularQue(8);

	CQue->Clear(ptr);

	static floatUnion_Typedef fu;
	memset(&fu, 0, sizeof(fu));

	while (true)
	{	
		if (push) {			
			fu.vf += 1;
			CQue->Push(ptr, ((void*)(fu.vp)));
		}

		if (pop) {
			floatUnion_Typedef fupop;
				fupop.vp = CQue->Pop(ptr);
				printf("popped value : %f\n", fupop.vf);
		}

		if (reset)
			CQue->Clear(ptr);

		if (update)
			CQue->UpdateCapacity(ptr, 20);

		if (free)
			CQue->Free(&ptr);

		writeCircularQue(ptr, 25);
		delay();
	}

	return 0;
}

void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str) {
	printf("\337\33[%d;%dH%s\338", Y, X, str);
}

void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr) {
	printf("\337\33[%d;%dH%c\338", Y, X, chr);
}

void printIntOnSpesificLocation(uint16_t X, uint16_t Y, int int_) {
	printf("\337\33[%d;%dH%d\338", Y, X, int_);
}

void clearScreen(void) {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}

static void fillUpCircularQue(CircularQue_Typedef* ptr) {

	for (uint32_t i = 0; i < ptr->Size; i++) {
		ptr->QuePtr[i] = (void*)i;
	}
	printf("\n");
}

void delay(void) {
	uint32_t dummy = 0;
	for (uint32_t i = 0; i < 100000000L; i++) {
		dummy += 1;
	}
}
static void writeCircularQue(CircularQue_Typedef* ptr,uint8_t itemInLine) {

	printf("\n");
	clearScreen();

	if (ptr == NULL) {
		printf("empty pointer \n");
		return;
	}

	static int line = 5;
	static floatUnion_Typedef fu;
	for (uint32_t i = 0; i < ptr->Size; i++) {

		fu.vp = ptr->QuePtr[i];
		printIntOnSpesificLocation(i * 4, line, fu.vf);

		if (!(i % itemInLine) && (i != 0))
			printf("\n");
	}

	printCharOnSpesificLocation((ptr->HeadCntr) * 4, line + 1, 'H');
	printCharOnSpesificLocation((ptr->TailCntr) * 4, line + 1, 'T');
	//printf("[H: %d T: %d]\n", ptr->HeadCntr, ptr->TailCntr);

	//line += 1;
}