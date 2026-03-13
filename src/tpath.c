// Basic filepath manipulation library
// See `src/tpath.h` for documentation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "tstring.h"

#ifdef _WIN32
// Windows
TString tpath_real(TString path) {
	char *buff = string_get(path);

	char *real = _fullpath(NULL, buff, 0);

	if(!real) {
		printf("Error: Call to _fullpath() failed\n");
		exit(1);
	}

	TString out = string_new(real, strlen(real));

	free(buff);
	free(real);

	return out;
}

#else
// POSIX
TString tpath_real(TString path) {
	char *buff = string_get(path);

	char *real = realpath(buff, NULL);

	if(!real) {
		printf("Error: Call to realpath() failed: %s\n", strerror(errno));
		exit(1);
	}

	TString out = string_new(real, strlen(real));
	
	free(buff);
	free(real);

	return out;
}

#endif