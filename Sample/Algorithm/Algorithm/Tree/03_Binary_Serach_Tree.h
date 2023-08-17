#pragma once
// 03_Binary_Serach_Tree.h

/*
	※ 이진 탐색 트리(Binary Search Tree)
		ㄴ 조건1 : 모든 키값은 유일해야함(중복x)
		ㄴ 조건2 : 왼쪽 서브트리의 모든 키값들은 root의 키값보다 작다
		ㄴ 조건3 : 오른쪽 서브트리의 모든 키값들은 root의 키값보다 크다
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

	// 반복문을 통한 탐색
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

	// 재귀 함수를 통한 탐색
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

	// 노드 추가
	void InsertNode(Node** root, int key)
	{
		Node* parent = nullptr;
		Node* current = *root;

		// root가 nullptr일경우
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

		// 삭제할 노드 탐색
		current = *root;

		while (current != nullptr && current->key != key)
		{
			parent = current;
			current = (current->key < key) ? current->right : current->left;
		}
		if (current == nullptr)
		{
			cout << "해당 키값을 가진 노드가 존재하지 않음" << endl;
			return;
		}

		if (current->left == nullptr && current->right == nullptr)
			// 삭제할 노드가 자식이 없을 경우
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
		// 삭제할 노드가 자식이 하나 있을 경우
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
		// 삭제할 노드가 자식이 모두 있는 경우
		{
			// 삭제될 노드의 오른쪽 자식중 제일 왼쪽(왼쪽 자식이 없는)노드를 구한다.
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

	// 이진 탐색 트리에서 중위 순회를 할 경우 오름차순으로 값이 출력된다.
	cout << endl;
	Tree.InOrder(Root, 0);

	Tree.DeleteNode(&Root, 125);

	cout << endl;
	Tree.InOrder(Root, 0);

	cout << "Height : " << Tree.GetHeight(Root) << endl;
	cout << "Node Count : " << Tree.GetNodeCount(Root) << endl;

	return 0;
}