#include "ptvisitor_class.hpp"
//#include "expr_num_class.hpp"
//#include "expression_class.hpp"
//#include "testing.hpp"


int main(int argc, char** argv)
{
	CircLinkedList<int> a;
	//a.insert_after(&(*a.begin()), 3);
	auto front = a.push_front(3);
	auto next_0 = a.insert_after(front, 9);
	auto next_1 = a.insert_after(next_0, 7);
	auto next_2 = a.insert_before(next_1, 20);


	while (!a.empty())
	{
		for (auto iter : a)
		{
			printout(iter.data, "\n");
		}

		a.remove(a.begin());
		//a.remove(a.end()->prev());

		if (!a.empty())
		{
			printout("\n");
		}
	}


	return 0;

	//// We need at least *one* source file.
	//if (argc < 2)
	//{
	//	printerr("Usage:  ", argv[0], " <source_files>\n");
	//	exit(1);
	//}

	//frost_hdl::PTVisitor::ListParsedSrcCode s_list_parsed_src_code;

	////printout("argc:  ", argc, "\n");

	//for (int i=1; i<argc; ++i)
	//{
	//	s_list_parsed_src_code.push_back(std::unique_ptr<frost_hdl
	//		::ParsedSrcCode>(new frost_hdl::ParsedSrcCode(argv[i])));
	//}

	//frost_hdl::PTVisitor visitor(std::move(s_list_parsed_src_code));
	//return visitor.run();

}
