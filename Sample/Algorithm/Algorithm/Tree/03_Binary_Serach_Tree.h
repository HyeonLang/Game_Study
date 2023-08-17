#pragma once
// 03_Binary_Serach_Tree.h

/*
	�� ���� Ž�� Ʈ��(Binary Search Tree)
		�� ����1 : ��� Ű���� �����ؾ���(�ߺ�x)
		�� ����2 : ���� ����Ʈ���� ��� Ű������ root�� Ű������ �۴�
		�� ����3 : ������ ����Ʈ���� ��� Ű������ root�� Ű������ ũ��
*/
#include <iostream>
#include <algorithm>
using namespace std;

class BST
{
public:
	struct Node
	{
		int key = 0;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	static Node* Create(int key)
	{
		Node* node = new Node();
		node->key = key;
		return node;
	}

	static void Delete(Node** node)
	{
		delete(*node);
		*node = nullptr;
	}

	// �ݺ����� ���� Ž��
	Node* SearchIteration(Node* node, int key)
	{
		while (node != nullptr)
		{
			if (key == node->key)
				return node;
			else if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}
		return nullptr;
	}

	// ��� �Լ��� ���� Ž��
	Node* SearchRecurrsive(Node* node, int key)
	{
		if (node == nullptr) return nullptr;

		Node* temp = nullptr;

		if (key == node->key)
			return node;
		else
		{
			if (key > node->key)
				temp = SearchRecurrsive(node->right, key);
			else
				temp = SearchRecurrsive(node->left, key);
		}

		return temp;
	}

	// ��� �߰�
	void InsertNode(Node** root, int key)
	{
		Node* parent = nullptr;
		Node* current = *root;

		// root�� nullptr�ϰ��
		if (current == nullptr)
		{
			*root = Create(key);
			return;
		}

		while (current != nullptr)
		{
			parent = current;
			if (current->key < key)
				current = current->right;
			else
				current = current->left;
		}

		if (parent->key < key)
			parent->right = Create(key);
		else
			parent->left = Create(key);

	}

	void DeleteNode(Node** root, int key)
	{
		Node* parent = nullptr;
		Node* current = nullptr;

		// ������ ��� Ž��
		current = *root;

		while (current != nullptr && current->key != key)
		{
			parent = current;
			current = (current->key < key) ? current->right : current->left;
		}
		if (current == nullptr)
		{
			cout << "�ش� Ű���� ���� ��尡 �������� ����" << endl;
			return;
		}

		if (current->left == nullptr && current->right == nullptr)
			// ������ ��尡 �ڽ��� ���� ���
		{
			if (parent != nullptr)
			{
				if (parent->left == current)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}
			else
				*root = nullptr;
		}
		else if (current->left == nullptr || current->right == nullptr)
		// ������ ��尡 �ڽ��� �ϳ� ���� ���
		{
			Node* child = current->left != nullptr ? current->left : current->right;

			if (parent != nullptr)
			{
				if (parent->left == current)
					parent->left = child;
				else
					parent->right = child;
			}
			else
				*root = child;
		}
		else
		// ������ ��尡 �ڽ��� ��� �ִ� ���
		{
			// ������ ����� ������ �ڽ��� ���� ����(���� �ڽ��� ����)��带 ���Ѵ�.
			Node* prev = current;
			Node* next = current->right;
			while (next->left != nullptr)
			{
				prev = next;
				next = next->left;
			}

			if (prev == current)
				prev->right = next->right;
			else
				prev->left = next->right;

			next->left = current->left;
			next->right = current->right;

			if (parent != nullptr)
			{
				if (parent->left == current)
					parent->left = next;
				else
					parent->right = next;
			}
			else
				*root = next;
		}

		Delete(&current);
	}

	int GetNodeCount(Node* node)
	{
		int count = 0;

		if (node != nullptr)
			count = 1 + GetNodeCount(node->left) + GetNodeCount(node->right);

		return count;
	}


	int GetHeight(Node* node)
	{
		int height = -1;
		if (node != nullptr)
		{
			height = 1 + max(GetHeight(node->left), GetHeight(node->right));
		}

		return height;
	}

	void InOrder(Node* node, int depth)
	{
		if (node == nullptr) return;

		InOrder(node->left, depth + 1);

		for (int i = 0; i < depth; i++)
			cout << "-";
		cout << node->key << endl;

		InOrder(node->right, depth + 1);
	}

private:
};

int main()
{
	BST Tree;
	BST::Node* Root = nullptr;

	Tree.InsertNode(&Root, 100);
	Tree.InsertNode(&Root, 50);
	Tree.InsertNode(&Root, 75);
	Tree.InsertNode(&Root, 30);
	Tree.InsertNode(&Root, 150);
	Tree.InsertNode(&Root, 175);
	Tree.InsertNode(&Root, 125);
	Tree.InsertNode(&Root, 110);
	Tree.InsertNode(&Root, 100);

	cout << Tree.SearchIteration(Root, 125)->key << endl;
	cout << Tree.SearchRecurrsive(Root, 125)->key << endl;

	// ���� Ž�� Ʈ������ ���� ��ȸ�� �� ��� ������������ ���� ��µȴ�.
	cout << endl;
	Tree.InOrder(Root, 0);

	Tree.DeleteNode(&Root, 125);

	cout << endl;
	Tree.InOrder(Root, 0);

	cout << "Height : " << Tree.GetHeight(Root) << endl;
	cout << "Node Count : " << Tree.GetNodeCount(Root) << endl;

	return 0;
}