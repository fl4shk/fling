#include "misc_includes.hpp"
#include "ast_gen_class.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printerr("Usage:  ", argv[0], " filename\n");
		exit(1);
	}
	AstGen(std::vector({string(argv[1])})).run();


	return 0;
}
