#pragma once
#include "list.h"

enum colorEnum
{
	red = 0,
	black = 1
};

template<typename T1, typename T2>
struct red_black_tree_node
{
	T1 key;
	T2 value;
	colorEnum color;
	red_black_tree_node* left_side;
	red_black_tree_node* right_side;
	red_black_tree_node* parent;
	red_black_tree_node(T1 k, T2 v, colorEnum c, red_black_tree_node* par, red_black_tree_node* left, red_black_tree_node* right) :
		key(k), color(c), parent(par), left_side(left), right_side(right) { };
};

template<typename T1, typename T2>
class red_black_tree
{
public:
	int size = 0;
	void insert(T1 key, T2 value);
	void remove(T1 key);
	red_black_tree_node* find(T1 key);
	ListOfNum<T1> get_keys();
	ListOfNum<T2> get_values();
	void clear();
	void clear_help(red_black_tree_node* x);
	void print(red_black_tree_node* node);
};