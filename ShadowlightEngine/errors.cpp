#include "stdafx.h"

void RaiseErrorA(const char* err, const char* mess, const char* fname, int line)
{
	// Print the error, format with message if err contains a '%s'
	printf(err, mess);
	printf(" at %s:%i\n", fname, line);
}
