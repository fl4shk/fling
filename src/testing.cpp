#include "testing.hpp"

namespace frost_hdl
{

void test_circ_linked_list()
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

	vec.push_back(a.push_back(3));
	vec.push_back(a.push_back(9));
	vec.push_back(a.push_back(7));
	vec.push_back(a.push_back(20));

	show();


	while (!a.empty())
	{
		//show();
		printout("contains:  \n");
		for (auto iter : vec)
		{
			printout("\t", a.contains(iter), "\n");
		}
		//a.pop_front();
		a.pop_back();

		if (!a.empty())
		{
			printout("\n");
		}
	}

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
}

} // namespace frost_hdl
