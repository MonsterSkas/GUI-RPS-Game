#pragma once
#include <iostream>

class Title {

public:
	char* random() {
		char* titles[] = {
			(char*)"LOL", (char*)"LOL?", (char*)"HAHA", (char*)"Noice",
			(char*)"Cool", (char*)"Cool?", (char*)"Hmm"
		};
		srand((unsigned)time(NULL));
		int rn = 0 + rand() % 7;
		return titles[rn];
	}
};