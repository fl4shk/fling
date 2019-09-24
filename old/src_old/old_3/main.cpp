#include "misc_includes.hpp"

#include "parser_class.hpp"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printerr("Usage:  ", argv[0], " filenames...\n");
		exit(1);
	}

	vector<string> s_filename_vec;
	for (int i=1; i<argc; ++i)
	{
		s_filename_vec.push_back(string(argv[i]));
	}

	frost_hdl::Parser parser(move(s_filename_vec));
	parser.parse_program();
	return 0;
}
