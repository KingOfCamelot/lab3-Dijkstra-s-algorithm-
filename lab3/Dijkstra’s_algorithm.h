#include "string.h"
#include "red_black_tree.h"
#include "list.h"

class nodes
{
public:
	ListOfNum<nodes*> neighbour;
	ListOfNum<int> cost_ticket;

	nodes* way;
	size_t length;
	String title_city;
	nodes(String& name)
	{
		way = nullptr;
		length = NULL;
		title_city = name;
	}
};