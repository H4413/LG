#include <iostream>
#include <getopt.h>

#include "parser.h"
#include "Xml.h"
#include "DTD.h"

#define VERSION		0
#define SVERSION	1

using namespace std;

static int verbose_flag;

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
	cout << "  -o, --output \t\t\t Output file for HTML transformation" << endl;
	cout << "  -x, --xslt \t\t\t Input XSLT file for HTML transformation" << endl;
	
}

int main (int argc, char ** argv)
{
	int c;
	int option_index = 0;
	
	static struct option long_options[] = 
	{
		{"verbose",	no_argument,	&verbose_flag, 1},
		{"version",	no_argument,	0, 'v'},
		{"help", 	no_argument, 	0, 	'h'},
		{"transform", no_argument,	0,	't'},
		{"validate",	required_argument, 	0, 	'V'},
		{"dtd-well-formed",	required_argument, 	0, 	'd'},
		{"well-formed",		required_argument, 	0,	'w'},
		{"output", 	required_argument, 	0, 	'o'},
		{"xslt", 	required_argument, 	0, 	'x'},
		{0, 0, 0, 0}
	};
	
	if (argc < 2)
	{
		print_usage();
		return 3;
	}
	
	for (;;)
	{
		c = getopt_long (argc, argv, "vhtV:d:w:o:x:",
			long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
			case 'V':
			{
				XmlDoc * xml;
				DTDDocument * dtd;
				if(xmlparse(optarg, xml))
				{
					if (xml)
					{
						if (dtdparse(xml->GetDTD()->name.c_str(), dtd))
							if (dtd)
							{
								//xml->Validate(dtd);
								cout << "XML is validated" << endl << endl;
								delete dtd;
							}
							else
								cout << "DTD error" << endl << endl;
						delete xml;
					}
					else
						cout << "XML error" << endl << endl;
				}
			}
				break;
			case 'd':
				if (dtdparse(optarg, NULL))
					cout << optarg << ": is a well-formed DTD document." << endl << endl;
				else
					cout << optarg << ": is not a well-formed DTD document." << endl << endl;
				break;
			case 'w':	
				if (xmlparse(optarg, NULL))
					cout << optarg << ": is a well-formed XML document." << endl << endl;
				else
					cout << optarg << ": is not a well-formed XML document." << endl << endl;
				break;
			case 'h':
				print_usage();
				return 1;
			case 'v':
				cout << "XML Analyse, version " << VERSION 
					<< "." << SVERSION << endl;
				return 1;
			case '?':
			default:
				return 2;
		}
	}
	
	if (verbose_flag)
		cout << "Verbose flag is set" << endl;
	if (optind < argc)
	{
		cout << "Non-option: ";
		while (optind < argc)
			cout << argv[optind++];
		cout << endl;
	}
	
	return 0;					
}
