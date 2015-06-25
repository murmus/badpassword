int test1(struct password *pass){
	return 1;
}

int ptsinglequote(struct password *pass){
	char * in;
	int ret;
	in = strstr(pass->plaintext, "'");
	if(in == NULL)
		ret = 0;
	else
		ret = 1;
	return ret;
}
