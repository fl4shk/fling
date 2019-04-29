#include "ptvisitor_class.hpp"
//#include "expr_num_class.hpp"
//#include "expression_class.hpp"
//#include "testing.hpp"


int main(int argc, char** argv)
{
	CircLinkedList<int> a;

	auto show = [&a]() -> void
	{
		for (auto iter : a)
		{
			printout(iter.data, "\n");
		}
	};


	std::vector<decltype(a)::NodeIterator> vec;

	vec.push_back(a.push_front(3));
	vec.push_back(a.insert_after(vec.back(), 9));
	vec.push_back(a.insert_after(vec.back(), 7));
	vec.push_back(a.insert_before(vec.back(), 20));

	show();


	//while (!a.empty())
	//{
	//	for (auto iter : a)
	//	{
	//		printout(iter.data, "\n");
	//	}

	//	a.remove(a.begin());
	//	//a.remove(a.end()->prev());

	//	if (!a.empty())
	//	{
	//		printout("\n");
	//	}
	//}



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
