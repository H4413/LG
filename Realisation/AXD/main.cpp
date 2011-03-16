// ### INCLUDE & NAMESPACES ###

// system includes
#include <iostream>
#include <fstream>
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
    fstream  xmlFile;
    char     dtdHeader[ 100 ];

    cout << argv[ 1 ] << endl;

    xmlFile.open( argv[ 1 ] );

    if( !xmlFile.is_open() )
    {
	cerr << "fichier spécifié introuvable" << endl;
	
	return -1;
    }

    xmlFile >> dtdHeader; 

    cout << dtdHeader << endl;

    xmlFile.close();

    cout << "hello" << endl;

    return 0;
}
