#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "tests.h"

char BASECHARS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345789'!?";

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
	out = malloc(len+1);
	for(i=0;i<len;i++){
		r = rand() % (sizeof(BASECHARS)-1);

		out[i] = BASECHARS[r];
	}

	out[len] = 0;

	return out;
}

void main(){
	char *password;

	struct password *pssword;
	int i;
	int result, remove;
	assert(testcount<=sizeof(result)*8);
	int rcount=1;
	int *results;
	int *newresults;
	MD5_CTX md5c;

	char check;

	int stopmask;
	stopmask = (1<<(testcount))-1;

	pssword = malloc(sizeof(struct password));
	seedrand();
	results = (int *) malloc(sizeof(result));

	results[0] = 0;
	
	for(i=0;i<testcount;i++){
		printf("[%x] %s\n", i, tests[i].name);

	}

	result = 0;
	printf("%x\n", stopmask);
	while(result != stopmask){

		password = genpassword(10);
		pssword->plaintext = password;

		// md5sum
		MD5Init(&md5c);
		MD5Update(&md5c, pssword->plaintext, strlen(pssword->plaintext));
		MD5Final(&md5c);

		pssword->md5digest = (char *)malloc(17);
		memcpy(pssword->md5digest, md5c.digest, 16);
		pssword->md5digest[17]=0;

		result = 0;
		for(i=0; i<testcount;i++){
			result = (result<<1) | tests[i].t(pssword);;
		}

		remove = 0;
		for(i=0; i<rcount;i++){
			//printf("%x %x %x\n", results[i], result, (results[i] | result));
			if(results[i] == (results[i] | result)){
				i--;
				break;
			}
			if(result == (results[i] | result)){
				remove++;
			} else if (remove){
				results[i-remove] = results[i];	
			}
		}
		if(i == rcount){
			newresults = (int *) malloc(sizeof(result) * (rcount-remove+1));
			memcpy(newresults+1, results, rcount-remove);
			newresults[0] = result;
			rcount = rcount-remove+1;
			free(results);
			results = newresults;
			printf("\"%s\"\t[%x]", password, result);
			for(i=0;i<testcount;i++){
				if((1<<i) & result)
					check = 'X';
				else
					check = '_';
				printf("|%c", check);
			}
			printf("\n");
		}
	}
}
