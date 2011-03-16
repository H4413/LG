// ### INCLUDE & NAMESPACES ###

// system includes
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>

// projet includes
// nothing yet

using namespace std;


// ### CONSTANT DEFINITIONS ###


// ### LOCAL FUNCTIONS PROTOTYPE ###

int retrieveDTDFileName
(
    char   * const xmlFileName,
    string *       dtdFileName
);

int escapeCharUntil
(
    fstream    & textFile,
    char const   delim
);


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

    string dtdName;

    retrieveDTDFileName( argv[ 1 ], &dtdName );

    string commandLine( "../AnalyseurXML/analyseXML < " );
    commandLine += argv[ 1 ];

    system( commandLine.c_str() );

    commandLine = "../AnalyseurDTD/analyseDTD < ";
    commandLine += dtdName;

    system( commandLine.c_str() );

    return 0;
}

/**************************************************************************/
/*!
***************************************************************************/
int retrieveDTDFileName
(
    char   * const xmlFileName,
    string *       dtdFileName
)
{
    dtdFileName->clear();
    
    fstream  xmlFile;
    string   curLine;

    xmlFile.open( xmlFileName, ios::in );

    if( !xmlFile.is_open() )
    {
	cerr << "fichier spécifié introuvable" << endl;
	
	return -1;
    }

    getline( xmlFile, curLine );

    while( curLine.find( "DOCTYPE" ) == string::npos )
    {
	getline( xmlFile, curLine );
    }

    if( xmlFile.eof() )
    {
	return -2;
    }
    
    size_t   firstQuotePos = curLine.find( '"' );

    if( xmlFile.eof() )
    {
	return -2;
    }

    size_t   lastQuotePos  = curLine.rfind( '"' );

    cout << lastQuotePos << endl;
    dtdFileName->assign( curLine.substr( firstQuotePos + 1, lastQuotePos - firstQuotePos - 1 ) );

    cout << *dtdFileName << endl;

    /*
     * Procédure
     * 1. tant que la ligne courante ne commence pas par <!DOCTYPE (ou <!)
     * aller à la ligne suivante
     * 2. consommer des caractères jusqu'au 1er " rencontré.
     * 3. lire jusqu'au " suivant
     * 4. tadaaa
     */

    xmlFile.close();

    return 0;
}

