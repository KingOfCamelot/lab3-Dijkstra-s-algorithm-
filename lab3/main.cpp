#include <iostream>
#include "Dijkstra’s_algorithm.h"
#include "string.h"

using namespace std;

int main()
{
	String file = "airport.txt";
	Dijkstra_algorithm board;
	board.read_from_files(file);
	board.algorithm(5, 1);
	board.algorithm(3, 5);
	board.algorithm(4, 1);
}