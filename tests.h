#include "Md5.c"
#include "tests.c"

typedef int (*test)(struct password*);

struct test{
	char * name;
	test t;
};

int test1(struct password * pass);
int ptsinglequote(struct password * pass);
int md5singlequote(struct password * pass);
int md50e0(struct password *pass);
int md5null(struct password *pass);

struct test tests[] = {
	{"Default Test", &test1},
	{"Single Quote", &ptsinglequote},
	{"md5 Single Quote", &md5singlequote},
	{"md5 0e0..", &md50e0},
	{"md5 null byte", &md5null},
	};

#define testcount sizeof(tests)/sizeof(struct test)
