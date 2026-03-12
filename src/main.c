// Tori program entry point

#include <stddef.h>

#include "tstring.h"
#include "tarray.h"

#include "tlex.h"

int main(int argc, char *argv[]) {
	TString path = string_new("../tests/test.tori", 18);
	tlex_lex(path);

	string_free(path);

	return 0;
}
