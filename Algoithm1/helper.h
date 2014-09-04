#ifndef __HELPER_H__
#define __HELPER_H__

/* includefiles */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <time.h>

#ifdef PI
#undef PI
#endif

#define FREE_ARG char*

/**
 * Maximum length of input lines 
 */
#define MAX_LINE_LENGTH 2048	   

/**
 * Stores the last timer value 
 */
extern clock_t last_timer_reset;   


int min( int a, int b);	       
int max( int a, int b);
double fmin( double a, double b);
double fmax( double a, double b);


/**
 * Error handling:
 *
 * ERROR(s) writes an error message and terminates the program
 *
 * Example:
 * ERROR("File not found !");
 */
#define ERROR(s)    errhandler( __LINE__, __FILE__, s)

/**
 * Error handling:
 *
 * ERROR(s) writes an error message and terminates the program
 *
 * Example:
 * ERROR("File not found !");
 */
#define ERROUT stdout

/**
 * Error handling:
 *
 * ERROR(s) writes an error message and terminates the program
 *
 * Example:
 * ERROR("File not found !");
 */
void  errhandler( int nLine, const char *szFile, const char *szString );


/**
 * Reading from a datafile.
 *
 * The foloowing three macros help reading values from the parameter file.
 * If a variable cannot be found, the program stops with an error message.
 *
 * Example:
 * READ_INT( "MyFile.dat", imax );
 * READ_STRING( szFile, szProblem );
 */
#define READ_INT( szFileName, VarName)    read_int   ( szFileName, #VarName, &(VarName) ) 

/**
 * Reading from a datafile.
 *
 * The foloowing three macros help reading values from the parameter file.
 * If a variable cannot be found, the program stops with an error message.
 *
 * Example:
 * READ_INT( "MyFile.dat", imax );
 * READ_STRING( szFile, szProblem );
 */
#define READ_DOUBLE( szFileName, VarName) read_double( szFileName, #VarName, &(VarName) )

/**
 * Reading from a datafile.
 *
 * The foloowing three macros help reading values from the parameter file.
 * If a variable cannot be found, the program stops with an error message.
 *
 * Example:
 * READ_INT( "MyFile.dat", imax );
 * READ_STRING( szFile, szProblem );
 */
#define READ_STRING( szFileName, VarName) read_string( szFileName, #VarName,  (VarName) )

void read_string( const char* szFilename, const char* szName, char*  sValue);
void read_int   ( const char* szFilename, const char* szName, int*    nValue);
void read_double( const char* szFilename, const char* szName, double*  Value);

#endif