/* errexit.c - errexit */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
/*------------------------------------------------------------------------
* errexit - print an error message and exit
*------------------------------------------------------------------------
*/
/*VARARGS1*/

int
errexit(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}
