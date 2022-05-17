#include "string.h"
#include "red_black_tree.h"
#include "list.h"
#include <iostream>
#include <fstream>
using namespace std;

class nodes
{
public:
	ListOfNum<nodes*> vertex;
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
    void add_vertex(nodes* adjacent, size_t cost)
    {
        vertex.push_back(adjacent);
        cost_ticket.push_back(cost);
    }
    nodes* get_vertex(size_t index)
    {
        return vertex[index];
    }
    size_t get_sum_way()
    {
        return vertex.get_size();
    }
    bool contain_vertex(nodes* adjacent)
    {
        return vertex.contains(adjacent);
    }
    long get_cost(size_t vertex_index)
    {
        return cost_ticket[vertex_index];
    }
};

class Dijkstra_algorithm
{
public:

    ListOfNum<nodes> node;
    void read_from_files(String file)
    {
        ListOfNum<String> text;

        ifstream inputStream;
        inputStream.open(file.get_value());
        char readBuffer[128];
        while (!inputStream.eof())
        {
            inputStream.getline(readBuffer, 32, '\n');
            text.push_back(readBuffer);
        }
        inputStream.clear();
        inputStream.close();
        for (int i = 0; i < text.get_size(); i++)
        {
            ListOfNum<String> line = String::division((text[i]), ';');
            for (size_t i = 0; i < line.get_size(); i++) line[i].quantity();

            String temp = line[0];
            String temp_2 = line[1];
            int cost_one_side = check(line[2]);
            int cost_other_side = check(line[3]);
            nodes root(temp);
            nodes adjacent(temp_2);
            entry_in_graph(root, adjacent, cost_one_side);
            entry_in_graph(adjacent, root, cost_other_side);
        }
    }
    static long check(String& stringToParse)
    {
        long result = -1;
        if (sscanf_s(stringToParse.get_value(), "%i", &result) != 1) return -1;
        if (result < 0) return result;
    }
    void entry_in_graph(nodes& root, nodes& adjacent, int cost)
    {
        if (cost < 0) return;

        int adjacent_index = node.index(adjacent);
        int root_index = node.index(root);

        if (root_index != -1)
        {
            if (adjacent_index == -1)
            {
                node.push_back(adjacent);
                adjacent_index = node.get_size() - 1;
            }
        }
        else
        {
            node.push_back(root);
            root_index = node.get_size() - 1;
            if (adjacent_index == -1)
            {
                node.push_back(adjacent);
                adjacent_index = node.get_size() - 1;
            }
        }
        if (!node[root_index].contain_vertex(&node[adjacent_index]))  node[root_index].add_vertex(&node[adjacent_index], cost);
    }
    void sort(size_t first, size_t last, ListOfNum<nodes*>& temp) {
        if (first < last)
        {
            int left = first, right = last;
            size_t middle = temp.at((left + right) / 2);
            do
            {
                while (temp.at(left) < *middle) left++;
                while (temp.at(right) > *middle)
                {
                    if ((int)right - 1 > -1) right--;
                }
                if (left <= right)
                {
                    swap(left, right);
                    left++;
                    if ((int)right - 1 > -1) right--;
                }
            } while (left <= right);
            sort(first, right);
            sort(left, last);
        }
    }
    int algorithm(size_t fromIndex, size_t toIndex)
    {
        for (size_t i = 0; i < node.get_size(); i++) node[i].length = SIZE_MAX;
        node[fromIndex].length = 0;
        node[fromIndex].way = nullptr;

        ListOfNum<nodes*> border;
        border.push_back(&node[fromIndex]);

        while (border.get_size() > 0)
        {
            nodes* actual = border[0];
            border.remove(0);
            long minCost = SIZE_MAX;
            for (size_t i = 0; i < actual->get_sum_way(); i++)
            {
                nodes* adjacent = actual->get_vertex(i);
                size_t distance = actual->length + actual->get_cost(i);
                if (adjacent->length == SIZE_MAX)
                {
                    adjacent->length = distance;
                    adjacent->way = actual;
                    border.push_back(adjacent);
                }
                else if (distance < adjacent->length)
                {
                    adjacent->length = distance;
                    adjacent->way = actual;
                }
                sort(0, border.get_size() - 1, border);
            }
            cout << "from " << node[fromIndex].title_city << "to " << node[toIndex].title_city;
            if (node[toIndex].length != SIZE_MAX)
            {
                nodes* current = &node[toIndex];
                ListOfNum<nodes*> list;
                while (current != nullptr)
                {
                    list.push_back(current);
                    current = current->way;
                }
                list.swap();
                cout << "shortest route: ";
                for (size_t i = 0; i < list.get_size(); i++)
                {
                    if (i != list.get_size() - 1) cout << list[i]->title_city << " - ";
                }
                cout << "Cost is " << node[toIndex].length << "." << endl;
                return node[toIndex].length;
            }
            else
            {
                cout << "shortest route: not exist" << endl;
                return -1;
            }
        }
    }
};