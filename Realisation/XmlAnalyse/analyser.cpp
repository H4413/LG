#include <iostream>
#include <getopt.h>

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
		{"version",	no_argument,	0, 'v'},
		{"verbose",	no_argument,	&verbose_flag, 1},
		{"help", 	no_argument, 	0, 	'h'},
		{"transform", no_argument,	0,	't'},
		{"dtd-well-formed",	required_argument, 	0, 	'd'},
		{"well-formed",		required_argument, 	0,	'w'},
		{"output", 	required_argument, 	0, 	'o'},
		{"xslt", 	required_argument, 	0, 	'x'},
		{0, 0, 0, 0}
	};
	
	for (;;)
	{
		c = getopt_long (argc, argv, "v:htdwox",
			long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				cout << "Option " << long_options[option_index].name;
				if (optarg)
					cout << " with arg " << optarg;
				cout << endl;
			case 'a':
				cout << "Option -a" << endl;
				break;
			case 'b':
				cout << "Option -b" << endl;
				break;
			case 'c':
				cout << "Option -c" << endl;
				break;
			case 'd':
				cout << "Option -d with value " << optarg << endl;
				break;
			case 'f':
				cout << "Option -f with value " << optarg << endl;
			case 'h':
				print_usage();
				return 1;
			case 'v':
				cout << "XML Analyse, version " << VERSION 
					<< "." << SVERSION << endl;
				return 1;
			case '?':
				break;
			default:	
				return 2;
		}
	}
	
	if (verbose_flag)
		cout << "Verbose flag is set" << endl;
	if (optind < argc)
	{
		cout << "Non-option ARGV-elements: ";
		while (optind < argc)
			cout << argv[optind++];
		cout << endl;
	}
	
	return 0;					
}
