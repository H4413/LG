// ### INCLUDE & NAMESPACES ###

// system includes
#include <iostream>
#include <cstdio>
#include <string>

// projet includes
// nothing yet

using namespace std;


// ### CONSTANT DEFINITIONS ###


// ### LOCAL FUNCTIONS PROTOTYPE ###


// ### LOCAL FUNCTIONS IMPLEMENTATIONS ###

/**************************************************************************/
/*!
***************************************************************************/
int main
(
    int          argn,
    char * const argv[]
)
{
    // Check the input command line
    if( argn != 2 )
    {
	cerr << "usage : ./axd filename.xml" << endl;

	return -1;
    }

    // Retrieve the dtd's filename
    FILE * pXmlFile = fopen( argv[ 1 ], "r" );

    if( pXmlFile == NULL )
    {
	cerr << "fichier spécifié introuvable" << endl;
	
	return -1;
    }

    fclose( pXmlFile );

    cout << "hello\n" << endl;

    return 0;
}
