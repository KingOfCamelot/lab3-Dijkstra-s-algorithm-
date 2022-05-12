#include "red_black_tree.h"
#include <iomanip>
#include <iostream>

using namespace std;

template<typename T1, typename T2>
red_black_tree_node<T1, T2>* root = nullptr;

template<typename T1, typename T2>
void right_turn(red_black_tree_node<T1, T2>* turn_y)
{
	red_black_tree_node* x = turn_y->left_side;
	turn_y->left_side = x->right_side;
	if (x->right_side != NULL) x->right_side->parent = turn_y;
	x->parent = turn_y->parent;
	if (turn_y->parent == NULL) root = x;
	else
	{
		if (turn_y == turn_y->parent->right_side) turn_y->parent->right_side = x;
		else turn_y->parent->left_side = x;
	}
	x->right_side = turn_y;
	turn_y->parent = x;
}

template<typename T1, typename T2>
void left_turn(red_black_tree_node<T1, T2>* turn_x)
{
	red_black_tree_node* x = turn_x->right_side;
	turn_x->right_side = x->left_side;
	if (x->left_side != NULL) x->left_side->parent = turn_x;
	x->parent = turn_x->parent;
	if (turn_x->parent == NULL) root = x;
	else
	{
		if (turn_x == turn_x->parent->left_side) turn_x->parent->left_side = x;
		else turn_x->parent->right_side = x;
	}
	x->left_side = turn_x;
	turn_x->parent = x;
}

template<typename T1, typename T2>
void swap_node(red_black_tree_node<T1, T2>* x_1, red_black_tree_node<T1, T2>* x_2)
{
	if (x_1->parent == nullptr) root = x_2;
	else if (x_1 == x_1->parent->left_side) x_1->parent->left_side = x_2;
	else x_1->parent->right_side = x_2;
	x_2->parent = x_1->parent;
}

template<typename T1, typename T2>
void red_black_tree<T1, T2>::insert(T1 key, T2 value)
{
	size++;
	red_black_tree_node* x = root;
	red_black_tree_node* y = nullptr;
	red_black_tree_node* node = new red_black_tree_node(key, value, red, nullptr, NULL, NULL);
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key) x = x->left_side;
		else x = x->right_side;
	}
	node->parent = y;
	if (y == nullptr) root = node;
	else if (node->key < y->key) y->left_side = node;
	else y->right_side = node;
	if (node->parent == nullptr)
	{
		node->color = black;
		return;
	}
	if (node->parent->parent == nullptr) return;

	red_black_tree_node* p = node->parent;
	red_black_tree_node* uncle = p->parent;
	while (node->parent != nullptr && node->parent->color == colorEnum::red)
	{
		if (p == uncle->left_side)
		{
			if (uncle->right_side->color == colorEnum::red)
			{
				uncle->right_side->color = black;
				uncle->left_side->color = black;
				uncle->color = red;
				node = uncle;
			}
			else if (p->right_side == node)
			{
				node = p;
				left_turn(node);
			}
			else
			{
				p->color = black;
				uncle->color = red;
				right_turn(uncle);
			}
		}
		else
		{
			if (uncle->left_side->color == colorEnum::red)
			{
				uncle->right_side->color = black;
				uncle->left_side->color = black;
				uncle->color = red;
				node = uncle;
			}
			else
			{
				node = p;
				right_turn(node);
				p->color = black;
				uncle->color = red;
				left_turn(uncle);
			}
		}
	}
	root->color = black;
}

template<typename T1, typename T2>
void red_black_tree<T1, T2>::print(red_black_tree_node<T1, T2>* node)
{
	if (node == NULL) return;
	if (node->parent == NULL) cout << node->key << "-" << node->color << " is root" << endl;
	else if (node->parent->left_side == node) cout << node->key << "-" << node->color << " " << node->parent->key << " left child" << endl;
	else cout << node->key << "-" << node->color << " " << node->parent->key << " right child" << endl;
	print(node->left_side);
	print(node->right_side);
}

template<typename T1, typename T2>
red_black_tree_node<T1, T2>* find_help(red_black_tree_node<T1, T2>* temp, T1 key)
{
	if (temp == NULL || temp->key == key) return temp;
	else if (key > temp->key) return find_help(temp->right_side, key);
	else return find_help(temp->left_side, key);
}

template<typename T1, typename T2>
red_black_tree_node<T1, T2>* red_black_tree<T1, T2>::find(T1 key)
{
	return find_help(root, key);
}

template<typename T1, typename T2>
void red_black_tree<T1, T2>::clear_help(red_black_tree_node<T1, T2>* x)
{
	if (x->left_side)   clear_help(x->left_side);
	if (x->right_side)  clear_help(x->right_side);
	delete x;
}

template<typename T1, typename T2>
void red_black_tree<T1, T2>::clear()
{
	red_black_tree_node* x = root;
	clear_help(x);
	root = nullptr;
}

template<typename T1, typename T2>
void fix_remove(red_black_tree_node<T1, T2>* X)
{
	red_black_tree_node* temp_value;
	while (X != root && X->color == colorEnum::black)
	{
		if (X == X->parent->left_side)
		{
			temp_value = X->parent->right_side;
			if (temp_value->color == colorEnum::red)
			{
				temp_value->color = colorEnum::black;
				X->parent->color = colorEnum::red;
				left_turn(X->parent);
				temp_value = X->parent->right_side;
			}

			if (temp_value->left_side->color == colorEnum::black && temp_value->right_side->color == colorEnum::black)
			{
				temp_value->color = colorEnum::red;
				X = X->parent;
			}
			else
			{
				if (temp_value->right_side->color == colorEnum::black) {
					temp_value->left_side->color = colorEnum::black;
					temp_value->color = colorEnum::red;
					right_turn(temp_value);
					temp_value = X->parent->right_side;
				}

				temp_value->color = X->parent->color;
				X->parent->color = colorEnum::black;
				temp_value->right_side->color = colorEnum::black;
				left_turn(X->parent);
				X = root;
			}
		}
		else
		{
			temp_value = X->parent->left_side;
			if (temp_value->color == colorEnum::red) {
				temp_value->color = colorEnum::black;
				X->parent->color = colorEnum::red;
				right_turn(X->parent);
				temp_value = X->parent->left_side;
			}

			if (temp_value->left_side->color == colorEnum::black && temp_value->right_side->color == colorEnum::black)
			{
				temp_value->color = colorEnum::red;
				X = X->parent;
			}
			else
			{
				if (temp_value->left_side->color == colorEnum::black)
				{
					temp_value->right_side->color = colorEnum::black;
					temp_value->color = colorEnum::red;
					left_turn(temp_value);
					temp_value = X->parent->left_side;
				}

				temp_value->color = X->parent->color;
				X->parent->color = colorEnum::black;
				temp_value->left_side->color = colorEnum::black;
				right_turn(X->parent);
				X = root;
			}
		}
	}
	X->color = colorEnum::black;
}

template<typename T1, typename T2>
void red_black_tree<T1, T2>::remove(T1 key)
{
	red_black_tree_node* deletenode = find(key);
	size--;
	if (deletenode != NULL)
	{
		colorEnum color = deletenode->color;
		red_black_tree_node* X = nullptr;

		if (deletenode->left_side == NULL)
		{
			X = deletenode->right_side;
			swap_node(deletenode, X);
		}
		else if (deletenode->right_side == NULL)
		{
			X = deletenode->left_side;
			swap_node(deletenode, X);
		}
		else
		{
			red_black_tree_node* Y;
			red_black_tree_node* temp = deletenode->right_side;

			while (temp->left_side != NULL)
			{
				temp = temp->left_side;
			}
			Y = temp;

			color = Y->color;
			X = Y->right_side;

			if (Y->parent == deletenode) X->parent = Y;
			else
			{
				swap_node(Y, Y->right_side);
				Y->right_side = deletenode->right_side;
				Y->right_side->parent = Y;
			}
			swap_node(deletenode, Y);

			Y->color = color;
			Y->left_side = deletenode->left_side;
			Y->left_side->parent = Y;
			Y->color = deletenode->color;
		}
		delete deletenode;
		if (color == colorEnum::black) fix_remove(X);
	}
}

template<typename T1, typename T2>
ListOfNum<T2> red_black_tree<T1, T2>::get_values()
{
	ListOfNum list;
	red_black_tree_node* current = root;
	while (size > list.get_size() && current)
	{
		while (current->left_side != NULL && current->left_side)
		{
			list.push_back(current->value);
			current = current->left_side;
		}
		if (current->right_side != NULL && current->right_side)
		{
			list.push_back(current->value);
			current = current->right_side;
			continue;
		}
		else list.push_back(current->value);
		while (current->parent && size > list.get_size())
		{
			current = current->parent;
			if (current->right_side != NULL && current->right_side)
			{
				if (!list.contains(current->right_side->value))
				{
					current = current->right_side;
					break;
				}
			}
			if (current->left_side)
			{
				if (!list.contains(current->left_side->value))
				{
					current = current->right_side;
					break;
				}
			}
		}
	}
	return list;
}

template<typename T1, typename T2>
ListOfNum<T1> red_black_tree<T1, T2>::get_keys()
{
	ListOfNum list;
	red_black_tree_node* current = root;
	while (size > list.get_size() && current)
	{
		while (current->left_side != NULL && current->left_side)
		{
			list.push_back(current->key);
			current = current->left_side;
		}
		if (current->right_side != NULL && current->right_side)
		{
			list.push_back(current->key);
			current = current->right_side;
			continue;
		}
		else list.push_back(current->key);
		while (current->parent && size > list.get_size())
		{
			current = current->parent;
			if (current->right_side != NULL && current->right_side)
			{
				if (!list.contains(current->right_side->key))
				{
					current = current->right_side;
					break;
				}
			}
			if (current->left_side)
			{
				if (!list.contains(current->left_side->key))
				{
					current = current->right_side;
					break;
				}
			}
		}
	}
	return list;
}