#include <iostream>
#include <getopt.h>
#include <fstream>

#include "Xml.h"
#include "DTD.h"
#include "XslTransform.h"

#define VERSION		0
#define SVERSION	1

using namespace std;

bool verbose_flag = false;

void print_usage()
{
    cout << "Usage : analyse ";
    cout << " [--version] [-v, --verbose] [-h,--help] " << endl
            << "\tCOMMAND [ARGS] [-o OUTPUT_FILE] [-x XSLT_FILE]" << endl;
    cout << endl << "The commands can be: " << endl;
    cout << "  -w, --well-formed \t\t Tells if a XML file is well-formed" << endl;
    cout << "  -d, --dtd-well-formed \t Tells if a DTD file is well-formed" << endl;
    cout << "  -V, --validate \t\t Validate an XML file " << endl;
    cout << "  -t, --transform \t\t Transform an XML in HTML " << endl;
    cout << "  -x, --xslt \t\t\t The XSLT file used for the transformation " << endl;
    cout << "  -o, --output \t\t\t Output file for HTML transformation" << endl;
}

int main (int argc, char ** argv)
{
	int c;
	char * xmlName = NULL;
	char * xsltName = NULL;
	char * output = NULL;
	XmlDoc * xml = NULL;
	DTDDocument * dtd = NULL;
	int option_index = 0;
	bool transform_flag = false;
	XslTransform * xslt = NULL;
	
	static struct option long_options[] = 
	{
		{"verbose",	no_argument,	0, 'v'},
		{"version",	no_argument,	0, 'a'},
		{"about",	no_argument,	0, 'a'},
		{"help", 	no_argument, 	0, 	'h'},
		{"transform", 	required_argument,	0,	't'},
		{"validate",	required_argument, 	0, 	'V'},
		{"dtd-well-formed",	required_argument, 	0, 	'd'},
		{"well-formed",		required_argument, 	0,	'w'},
		{"xslt", 	required_argument, 	0, 	'x'},
		{"output", 	required_argument, 	0, 	'o'},
		{0, 0, 0, 0}
	};
	
	if (argc < 2)
	{
		print_usage();
		return 3;
	}
	
	for (;;)
	{
		c = getopt_long (argc, argv, "vahV:d:w:o:t:x:",
			long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
			case 'v':
				verbose_flag = true;
				break;
			case 't':
				transform_flag = true;
				xmlName = optarg;
				break;
			case 'x':
				xsltName = optarg;
				break;
			case 'o':
				output = optarg;
				break;
			case 'V':
				if( (xml = XmlDoc::Parse(optarg)) )
				{
					if ( (dtd = DTDDocument::Parse(xml->GetDTD()->FileName.c_str())) )	
					{			
						if (xml->Validate(dtd))
							cout << "XML is validated" << endl << endl;
						else
							cout << "XML is not valide" << endl << endl;
						delete dtd;
					} else {
						cout << "DTD error" << endl << endl;
					}
					delete xml;
				} else {
					cout << "XML error" << endl << endl;
				}
				break;
			case 'd':
				if ( (dtd = DTDDocument::Parse(optarg)) )
				{
					cout << optarg << ": is a well-formed DTD document." << endl << endl;
					delete dtd;
				} else {
					cout << optarg << ": is not a well-formed DTD document." << endl << endl;
				}
				break;
			case 'w':
				if ( (xml = XmlDoc::Parse(optarg)) )
				{
					cout << optarg << ": is a well-formed XML document." << endl << endl;
					delete xml;
				} else {
					cout << optarg << ": is not a well-formed XML document." << endl << endl;
				}
				break;
			case 'h':
				print_usage();
				return 1;
			case 'a':
				cout << "XML Analyse, version " << VERSION 
					<< "." << SVERSION << endl;
				return 1;
			case '?':
			default:
				return 2;
		}
	}
	
	if (transform_flag)
	{
		if (!xmlName)
		{
			cout << "XML file name error !" << endl;
			return 1;
		}
		if (!xsltName)
		{
			cout << "You need to specify XSLT file name using -x" << endl;
			print_usage();
			return 1;
		}
		xslt = new XslTransform();
		if (output)
			xslt->SetOutputFile(output);
		xslt->Transform(xmlName, xsltName);
	}

	if (optind < argc)
	{
		cout << "Non-option: ";
		while (optind < argc)
			cout << argv[optind++];
		cout << endl;
	}
	
	return 0;					
}
