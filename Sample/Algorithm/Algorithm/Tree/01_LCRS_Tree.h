#pragma once

/*
	※ LCRS-Tree
		ㄴ Left-Child, Right-Sibling
		ㄴ 왼쪽은 자식을, 오른쪽은 형제를 가리키는 트리

	※ 예시)

		 A
		/
	  B -> C -> D
	 /        /
	E       F
*/

#include<iostream>
#include<vector>

using namespace std;

class LCRS_Tree
{
public:
	struct Node
	{
		char data;
		Node* left_child = nullptr;
		Node* right_sibling = nullptr;
	};

	static Node* Create(char data)
	{
		Node* node = new Node();
		node->data = data;
		return node;
	}

	static void Delete(Node** node)
	{
		delete(*node);
		*node = nullptr;
	}

public:
	void AddChild(Node* parent, Node* child)
	{
		if (parent->left_child == nullptr)
			parent->left_child = child;
		else
		{
			Node* node = parent->left_child;

			while (node->right_sibling != nullptr)
				node = node->right_sibling;
			node->right_sibling = child;
		}
	}

	void PrintNode(Node* node, int level)
	{
		for (int i = 0; i < level; i++)
			cout << "-";

		cout << node->data << endl;

		if(node->left_child != nullptr)
			PrintNode(node->left_child, level + 1);

		if(node->right_sibling != nullptr)
			PrintNode(node->right_sibling, level);
	}

	Node* GetNode(Node* root, char data)
	{
		Node* result = nullptr;
		if (root->data == data)
			return root;
		else
		{
			if (root->left_child != nullptr)
				result = GetNode(root->left_child, data);

			if (result != nullptr)
				return result;

			if (root->right_sibling != nullptr)
				result = GetNode(root->right_sibling, data);
		}
		return result;
	}

	// 전위 순회로 특정 데이터를 가진 노드를 찾아 백터에 담아준다.
	void GetNodes(Node* root, char data, vector<Node*>& vec)
	{
		if (root->data == data)
			vec.push_back(root);

		if (root->left_child != nullptr)
			GetNodes(root->left_child, data, vec);

		if (root->right_sibling != nullptr)
			GetNodes(root->right_sibling, data, vec);
	}

private:

};

#include<iostream>
#include"01_LCRS_Tree.h"
using namespace std;

int main()
{
	LCRS_Tree::Node* Root = LCRS_Tree::Create('R');
	LCRS_Tree::Node* A = LCRS_Tree::Create('A');
	LCRS_Tree::Node* B = LCRS_Tree::Create('B');
	LCRS_Tree::Node* C = LCRS_Tree::Create('C');
	LCRS_Tree::Node* D = LCRS_Tree::Create('D');
	LCRS_Tree::Node* E = LCRS_Tree::Create('E');
	LCRS_Tree::Node* F = LCRS_Tree::Create('F');
	LCRS_Tree::Node* G = LCRS_Tree::Create('G');

	LCRS_Tree tree;
	tree.AddChild(Root, A);
	tree.AddChild(Root, B);

	tree.AddChild(A, C);
	tree.AddChild(A, D);

	tree.AddChild(C, E);
	tree.AddChild(C, F);

	tree.AddChild(B, G);

	tree.PrintNode(Root, 0);

	LCRS_Tree::Node* temp = tree.GetNode(Root, 'G');

	vector<LCRS_Tree::Node*> vec;

	tree.GetNodes(Root, 'G', vec);

	for (auto& iter : vec)
	{
		cout << iter->data << endl;
		cout << iter << endl;
	}


	return 0;
}