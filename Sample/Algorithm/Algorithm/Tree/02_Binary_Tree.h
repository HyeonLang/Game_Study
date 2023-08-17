#pragma once

// 02_Binary_Tree.h

/*
	�� ���� Ʈ��(Binary Tree)
		�� Ʈ���� ������ 2������ Ʈ��
		�� ��尡 ���ĵǾ� ���� ��� Ž���� ������
*/

// ����Ʈ�� ������ ����Ʈ��
#include<iostream>
using namespace std;

class BinaryTree
{
public:
	struct Node
	{
		char data;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	static Node* CreateNode(char data)
	{
		Node* node = new Node();
		node->data = data;
		return node;
	}

	static void DeleteNode(Node** node)
	{
		delete(*node);
		*node = nullptr;
	}

public:
	static void PreOrder(Node* node)
	{
		if (node == nullptr)return;
		cout << " " << node->data;

		PreOrder(node->left);
		PreOrder(node->right);
	}

	static void InOrder(Node* node)
	{
		if (node == nullptr)return;
		InOrder(node->left);
		cout << " " << node->data;
		InOrder(node->right);
	}

	static void PostOrder(Node* node)
	{
		if (node == nullptr)return;
		PostOrder(node->left);
		PostOrder(node->right);
		cout << " " << node->data;
	}
private:

};

int main()
{
	BinaryTree::Node* Root = BinaryTree::CreateNode('R');
	BinaryTree::Node* A = BinaryTree::CreateNode('A');
	BinaryTree::Node* B = BinaryTree::CreateNode('B');
	BinaryTree::Node* C = BinaryTree::CreateNode('C');
	BinaryTree::Node* D = BinaryTree::CreateNode('D');
	BinaryTree::Node* E = BinaryTree::CreateNode('E');

	Root->left = A;
	Root->right = B;

	A->left = C;
	A->right = D;

	B->left = E;

	cout << "PreOrder : ";
	BinaryTree::PreOrder(Root);
	cout << endl;

	cout << "InOrder : ";
	BinaryTree::InOrder(Root);
	cout << endl;

	cout << "PostOrder : ";
	BinaryTree::PostOrder(Root);
	cout << endl;

	return 0;
}