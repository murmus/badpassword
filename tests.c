int test1(struct password *pass){
	return 1;
}

int ptsinglequote(struct password *pass){
	char * in;
	int ret;
	in = strstr(pass->plaintext, "'");
	if(in == NULL)
		return 0;
	else
		return 1;
	return ret;
}

int md5singlequote(struct password *pass){
	char * in;
	int i;
	for(i=0; i<16; i++){
		if(pass->md5digest[i]== '\''){
			return 1;
		}
	}
	return 0;
}

int md50e0(struct password *pass){
	if(pass->md5digest[0]== '\x0e' && ((uint8_t) pass->md5digest[1]) <0x10){
		return 1;
	}
	return 0;
}
int md5null(struct password *pass){
	if(strlen(pass->md5digest) != 16)
		return 1;
	return 0;
}
