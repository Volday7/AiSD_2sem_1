#pragma once
#include <iostream>

struct node {
	int data;
	node* left;
	node* right;
};


class Set {
private:
	node* head;
	int count;
public:
	Set() noexcept {
		head = nullptr;
		count = 0;
	}
	
	Set(int n) {
		count = n;
		for (int i = 0; i < count; i++) {
			head = Add(head, i*2+1);
		}
	}

	node* GetNode() noexcept {
		return head;
	}

	/*node* sort(node* root, int n) {
		if (root) {
			node* help;
			help = new node;
			help->data = root->data;
			help->left = sort(root->left, n / 2);
			help->right = sort(root->right, n - (n / 2) - 1);
			return help;
		}
	}*/

	node* Add(node* root, int key) {
		if (root == NULL) {
			root = new node;
			root->data = key;
			root->left = nullptr;
			root->right = nullptr;
		}
		else if (root->data < key) {
			root->right = Add(root->right, key);
		}
		else root->left = Add(root->left, key);
		return root;
	}

	bool Insert(int key) {
		//node* tmp = head;
		if (Find(head, key) == false) {
			head=Add(head, key);
			count++;
			return true;
		}
		else return false;
	}

	node* search(node* root, int key)
	{
		while (root != nullptr)
		{
			if (root->data > key)
			{
				root = root->left;
			}
			else if (root->data < key)
			{
				root = root->right;
			}
			else
			{
				return root;
			}
		}
		return nullptr;
	}

	bool Find(node* root, int key) const {
		if (root) {
			if (root->data == key) return true;
			else {
				if (Find(root->left, key) == true) return true;
				else if(Find(root->right, key) == true) return true;
			}
		}
		else return false;
	}

	/*bool Erase(int key) {
		if ((Find(head, key) == false) || (count == 0)) {
			std::cout << "\n!!! There is no such element in the Set. You cannot erase element which is not exist !!!";
			return false;
		}
		else {
			node* tmp = head;
			tmp = search(tmp, key);
			if ((tmp->left == NULL) && (tmp->right == NULL)) {
				node* help = head;
				while (help) {
					if (help->left == tmp) {
						delete tmp;
						help->left = NULL;
					}
					else if (help->right == tmp) {
						delete tmp;
						help->right = NULL;
					}
					else {
						if (help->data < key) help = help->right;
						else help = help->left;
					}
				}
			}
			else if (tmp->right == NULL) {
				node* help = head;
				while (help) {
					if (help->right == tmp) {
						help->right = tmp->left;
						delete tmp;
						help->right->left = NULL;
						help->right->right = NULL;
					}
					else {
						if (help->data < key) help = help->right;
						else help = help->left;
					}
				}
			}
			else if (tmp->left == NULL) {
				node* help = head;
				while (help) {
					if (help->right == tmp) {
						help->right = tmp->right;
						delete tmp;
						help->right->left = NULL;
						help->right->right = NULL;
					}
					else {
						if (help->data < key) help = help->right;
						else help = help->left;
					}
				}
			}
			else {
				node* help = head;
				while (help) {
					if (help->right == tmp) {
						help->right = tmp->left;
						help->right->right = tmp->right;
						delete tmp;
						tmp = NULL;
						break;
					}
					else if (help->left == tmp) {
						help->left = tmp->right;
						help->left->left = tmp->left;
						delete tmp;
						tmp = NULL;
						break;
					}
					else {
						if (help->data < key) help = help->right;
						else help = help->left;
					}
				}
			}
			count--;
			return true;
		}
	}*/

	bool Erase(int key)
	{
		node* tmproot = head, * parent = NULL;
		while (tmproot)
		{
			if (tmproot->data > key)
			{
				parent = tmproot;
				tmproot = tmproot->left;
			}
			else if (tmproot->data < key)
			{
				parent = tmproot;
				tmproot = tmproot->right;
			}
			else if (tmproot->data == key) break;
		}
		if (!tmproot) return false;
		if (!tmproot->right && !tmproot->left)
		{
			if (parent && (parent->data > tmproot->data)) parent->left = NULL;
			else if (parent && (parent->data < tmproot->data)) parent->right = NULL;
			else if (tmproot == head) head = NULL;
			delete tmproot;
			return true;
		}
		else if (!tmproot->left)
		{
			if (parent && (parent->data > tmproot->data)) parent->left = tmproot->right;
			else if (parent && (parent->data < tmproot->data)) parent->right = tmproot->right;
			else if (tmproot == head) head = head->right;
			delete tmproot;
			return true;
		}
		else if (!tmproot->right)
		{
			if (parent && (parent->data > tmproot->data)) parent->left = tmproot->left;
			else if (parent && (parent->data < tmproot->data)) parent->right = tmproot->left;
			else if (tmproot == head) head = head->left;
			delete tmproot;
			return true;
		}
		else
		{
			node* ernode = tmproot->right;
			while (ernode->left)
				ernode = ernode->left;
			int value = ernode->data;
			Erase(ernode->data);
			tmproot->data = value;
			return true;
		}
	}

	void RealPrint(node* root) {
		/*if (root) {
			std::cout << root->data << "\n";
			RealPrint(root->left);
			std::cout << " ";
			RealPrint(root->right);
		}*/
		if (root) {
			RealPrint(root->left);
			std::cout << root->data << " ";
			
			//std::cout << " ";
			RealPrint(root->right);
		}
	}

	void Print() {
		if (count > 0) {
			std::cout << "Set: \n";
			RealPrint(head);
			std::cout << "\n";
		}
		else std::cout << "\n!!! There are no elements in Set !!!\n";
	}
};
