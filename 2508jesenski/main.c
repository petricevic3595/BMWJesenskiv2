#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "funkcije.h"



int main(void) {

	int izbor = 1;

	kreirajDatoteku("BMW.bin");


	while (izbor) {
		izbor = izbornik("BMW.bin");		// izvrsavanje izbornika dok je uvjet ispunjen
	}

	return 0;
}