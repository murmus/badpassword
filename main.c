#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "tests.h"

char BASECHARS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345789";

void seedrand(){
	FILE *f;
	int seed;
	f = fopen("/dev/urandom","r");

	fread((void *)&seed, 1, sizeof(int), f);
	fclose(f);

	srand(seed);
}

char *genpassword(int len){
	int i;
	int r;
	char *out;
	out = malloc(len);
	for(i=0;i<len;i++){
		r = rand() % (sizeof(BASECHARS)-1);

		out[i] = BASECHARS[r];
	}


	return out;
}

void main(){
	char *password;

	struct password *pssword;
	int i;
	int results[testcount];

	pssword = malloc(sizeof(struct password));
	seedrand();
	
	password = genpassword(10);
	pssword->plaintext = password;

	printf("%s\n", password);
	for(i=0; i<testcount;i++){
		printf("Executing %s\n", tests[i].name);
		results[i] = tests[i].t(pssword);
	}
	for(i=0; i<testcount;i++){
		printf("[%x] %s\n", results[i], tests[i].name);
	}
}
