#include "header.h"

using namespace boost::program_options;

int parseOptions(int ac, char* av[])
{
	options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("player-level,p", value<int>(), "set player level")
	;

	variables_map vm;
	store(parse_command_line(ac, av, desc), vm);
	notify(vm);
	
	if(vm.count("help"))
	{
		cout << desc << endl;
		return 0;
	}
	if(vm.count("player-level"))
	{
		int pl = vm["player-level"].as<int>();
		if(pl>=1 && pl<=40)
		{			
			cout << "Player level was set to: " << pl << endl;
			return pl;
		}
		else
		{
			cout << "ERROR:\tPlayer level must be between 1 and 40" << endl;
			cout << "\tPlayer level was set to: " << pl << endl;
			return 0;
		}
	}
	else
	{
		cout << "ERROR: Player level was not set" << endl << desc << endl;
		return 0;
	}
}
