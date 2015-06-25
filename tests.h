#include "tests.c"

typedef int (*test)(struct password*);

struct test{
	char * name;
	test t;
};

int test1(struct password * pass);
int ptsinglequote(struct password * pass);

struct test tests[] = {
	{"Default Test", &test1},
	{"Single Quote", &ptsinglequote},
	};

#define testcount sizeof(tests)/sizeof(struct test)
