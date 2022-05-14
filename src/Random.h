#pragma once
#include <iostream>

class RPS {
public:
	char* random() {
		char* choice[] = {
			(char*)"Rock", (char*)"Paper", (char*)"Scissors"
		};
		srand((unsigned)time(NULL));
		int rn = 0 + rand() % 3;
		return choice[rn];
	}
};