#pragma once

// 06_RB_Tree.h
/*
	�� Red-Black Tree
		�� AVL�� ���� ������ ���ߴ� �ڰ� ���� ���� Ž�� Ʈ��
		�� ��忡 ����, �������� �ο��Ͽ� ������ �����.
		�� ��ټ��� ���α׷��� ���� �����迭(map, set, multi map, multi set)��
		�����ϱ� ���� �ڷᱸ���� ���ȴ�.

	�� RB vs AVL
		�� AVLƮ���� RB Ʈ���� ���� ���� �����ϰ� ������ �����Ѵ�.
			-> RB�� ���� ��尡 ���ӵ� ���� �������� ������ AVL�� ���Խø��� ��������� ������ Ȯ���Ͽ� �������Ѵ�.
		�� AVL�� RB���� ������ �����ϰ� �����ϱ� ������ Ž���� �������� RB���� ���� ������ ������.
		�� AVL Ʈ���� �� ���� Ž���� �ʿ��� ��쿡 ����Ѵ�.
		�� RB Ʈ���� �� ���� ���� ������ �ʿ��� ��쿡 ����Ѵ�.

	�� RB Ʈ���� �Ӽ�
		�� ��� ����� ���� Black�̰ų� Red
		�� ��Ʈ���� �׻� Black
		�� ��� leaf ���(nullptr)�� �׻� Black
		�� red ��尡 ���������� ������ �� ����.
			-> red��尡 �������� �κ��� �ִٸ� �������� ���ش�.
		�� ��Ʈ ��忡�� �� leaf�������� balck��� ������ ������ �����ϴ�.

	�� RB Ʈ���� ����
		�� ���ԵǴ� ����� ������ ������ Red�̴�.
		�� ���� �� Red ��尡 ���������� ������ �ɰ�� �������� �Ѵ�.

	�� ���� �� ������ ��� �ΰ���
		�� Recoloring
			- ���� : ���Ե� ����� �θ��� ���� ������ Red�� ��
			- ���
				- 1. ���Ե� ����� �θ�� �θ� ���� ��带 Black���� �ٲ۴�.
				- 2. ���� ���Ե� ����� �θ��� �θ� ��Ʈ�� �ƴ϶�� Red��
				�ٲپ� �ش�.
				- 3. ���Ե� ����� �θ��� �θ��� ������ Red�� �ٲ���ٸ� �ش� �����
				�θ� Red�� ���� ������ �ش� ����� �θ� �˻��Ͽ� ������ ���ش�.

		�� Restructuring
			- ���� : ���Ե� ����� �θ��� ���� ������ Black�� ���
			 - ���
				- 1. AVL Ʈ�� ó�� �θ��� �θ� �������� ���Ե� ��ġ�� �ľ��ϰ� ȸ�� �����ش�.

				- 2. LL�̰ų� RR�� �� ��Ȳ�� �°� ������, ���� ȸ���� �����Ŀ�
				�θ��� ��ġ�� �ö�� ��带 Black, �ڽ��� ��ġ�� �� ������ Red�� �ٲپ� �ش�.

				- 3. LR�̰ų� RL�� �� AVL�� ���� ȸ���� �ι��ؾ� �ϴµ� ù��° ȸ���� ��Ȳ�� �°�
				������, ���� ȸ���� ���ְ� ���� ȸ���� 2. �� ���� ó�����ش�.

	�� RBƮ���� ����
		�� �����ϴ� ����� ���� RED�� ��� ������ �ϸ� �ȴ�.
			-> RB Ʈ���� ������ ������ ���ؼ��� RED�� ���ӵǰų� BLACK�� �����Ǿ���ϴµ�
			RED�� �����ϴ� �����δ� ������ ������ �ʱ� �����̴�.

		�� ������ ����� �ڸ��� ��ü�ϴ� �ڽ��� �ٸ� BST�� �����ϴ�.
			-> �����Ǵ� ����� ���� �ڽ��� ���� ������ or ������ �ڽ��� ���� ����
			-> ������ �����Ǵ� ��ġ�� ��ü�� �ڽ� ����� ��ġ�̴�
			-> �ش� ��ġ���� ������ �����־�� �Ѵ�.

		�� �����Ϸ��� ����� ���� BLACK�϶��� �߰����� �۾��� ���ش�.


	�� �����Ϸ��� ��尡 BLACK�� �� ������ �ؾ��ϴ� �߰����� �۾�
		�� ������ ����� �ڸ��� ��ü�ϴ� ��带 BALCK���� ĥ�Ѵ�.
		�� ���� ĥ�� �� �ش� ����� ���� ���� ���� ���̽��� ������.
			- ���� ���� RED�� ��� : ���� �߰� �۾��� ����.
			- ���� ���� BLACK�� ��� : �ٽ� �������� ĥ������ ��带 ���� �� �����
			�ϸ� ���̽��� ���� �۾��� ���ش�.

	�� ���� ���� ��� ���̽��� ���� �ؾ��ϴ� �߰����� �۾�

		�� �ܾ� ����
			- ������ ������ ��带 d��� ���� ��
			- c : d�� �ڸ��� ��ü�� �ڽ� ���
			- p : d�� �θ� ���
			- s : d�� ���� ���
			- l, r : s�� ����, ������ �ڽ�(d���� ��ī���)
			- (r or b or w) : �� ����� ��, w�� ��� �ƹ� �����̵� ��� ���ٴ� ��


	- c�� ��ġ�� �� ��尡 ��������Ƿ� c���� ������ ��尡 -1��
	��Ȳ�̸� �̸� ���̽��� ���� �����ִ� �۾��� �Ѵ�.
	- �Ʒ��� ó�� ����� c�� ������ ����̰�, c�� �������� ��Ȳ�� �����ؼ� ó���ؾ� �Ѵ�.


	- 1�� ���̽�. p�� �����̰� s, l, r�� ���� ���� ���
					  p(r)
			 c(b)               s(b)
						 l(b)         r(b)

		  -> p�� s�� ������ ��ȯ�Ѵ�.

					  p(b)
			 c(b)               s(r)
						 l(b)         r(b)

	- 2�� ���̽�. s�� ���̰� r�� ������ ���

					  p(w)
			 c(b)               s(b)
						 l(w)         r(r)

		  ->   p�� �������� ȸ���Ѵ�.
		  ->  p�� s�� ������ ��ȯ�Ѵ�.
		  ->  r�� ������ �ٲ۴�.

							s(w)
				   p(b)               r(b)
			 c(b)         l(w)

	- 3�� ���̽�. s�� ��, l�� ����, r�� ���� ���

					  p(w)
			 c(b)               s(b)
						 l(r)         r(b)

		  ->   s�� ���������� ȸ���Ѵ�.
		  ->  l�� s�� ������ ��ȯ�Ѵ�.
		  ->  2�� ���̽��� �������Ƿ� 2�� ���̽� �۾��� ���ش�.

					  p(w)
			 c(b)               l(b)
									 s(r)
										   r(b)

	- 4�� ���̽�. p, s, l, r ��� ���� ��

					  p(b)
			 c(b)               s(b)
						 l(b)         e(b)

		  -> s�� ���� ����� �ٲ۴�.
		  -> �̷����ϸ� c�� s�� ���� -1�� �Ǿ� p�� �������� -1�� ��
		  -> ������ p�� �ö����Ƿ� p�� ��������(p�� c�� �ȴٴ� ��) �ٽ� ������ ó�����ش�.

					  p(b)
			 c(b)               s(r)
						 l(b)         r(b)

	- 5�� ���̽�. s�� �����̰� p, l, r�� ��
					  p(b)
			 c(b)               s(r)
						 l(b)         r(b)

		  -> p�� �������� ȸ��
		  -> p�� s�� ������ �ٲ۴�.
		  -> c�� �θ� p�� ������ ����� �ٲ����.
		  -> �� ���տ� ���� ���̽� 1, 2, 3�� �ϳ��� ó�����ش�.

						 s(b)
				p(r)               r(b)
		  c(b)         l(b)
*/

#include<iostream>
#include<Windows.h>
using namespace std;

enum EColor
{
	RED,
	BLACK,
};

class RB_Tree
{
public:
	struct Node
	{
		int data;
		bool color = RED;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
	};

	static Node* Create(int data)
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
	// �ܺο��� ����ϴ� ���� �Լ�
	Node* InsertNode(Node* root, Node* node)
	{
		InsertBST(root, node);
		Balance(node);

		// ��Ʈ ��尡 �ٲ� �� ������ ��Ʈ �˻��ؼ� ����
		root = node;
		while (root->parent != nullptr)
			root = root->parent;

		return root;
	}

	// �ش� �����͸� ���� ��� Ž��
	Node* SearchNode(Node* root, int data)
	{
		Node* node = root;

		while (node != nullptr)
		{
			if (data == node->data)
				return node;
			else if (data < node->data)
				node = node->left;
			else
				node = node->right;
		}

		return nullptr;
	}

	Node* DeleteNode(Node* root, Node* node)
	{
		Node* parent = Parent(node);

		// ������ �ڸ��� ��ü�� ���� ���
		Node* child = Successor(node);

		if (child == nullptr)
		{
			if (node == root)
				root = nullptr;
			else
			{
				if (node->color == BLACK)
					FixDoubleBlack(node);

				if (parent->left == node)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}

			Delete(&node);
		}
		else
		{
			node->data = child->data;

			root = DeleteNode(root, child);
		}

		if (root != nullptr)
			while (root->parent != nullptr)
				root = root->parent;

		return root;
	}

	void Display(Node* root, int height)
	{
		if (root == nullptr) return;

		if (root->color == RED) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

		for (int i = 0; i < height; i++)
			cout << '-';

		cout << root->data << endl;
		Display(root->left, height + 1);
		Display(root->right, height + 1);

	}

private:
	//=================================
	// [InsertNode]
	//=================================

	// ���� ��带 ���� Ž�� Ʈ�� ���·� ����
	void InsertBST(Node* root, Node* node)
	{
		if (root == nullptr) return;

		if (root->data > node->data)
		{
			if (root->left == nullptr)
			{
				root->left = node;
				node->parent = root;
			}
			else
				InsertBST(root->left, node);
		}
		else
		{
			if (root->right == nullptr)
			{
				root->right = node;
				node->parent = root;
			}
			else
				InsertBST(root->right, node);
		}

	}

	// ���Ե� ��带 �������� ������ �����ؼ� ������ �����ش�.
	void Balance(Node* node)
	{
		if (Parent(node) == nullptr)
			node->color = BLACK;
		else if (Parent(node)->color == RED)
		{
			if (Uncle(node) == nullptr || Uncle(node)->color == BLACK)
				Restructuring(node);
			else
				Recoloring(node);
		}
	}

	void Recoloring(Node* node)
	{
		GrandParent(node)->color = RED;
		Uncle(node)->color = BLACK;
		Parent(node)->color = BLACK;
		Balance(GrandParent(node));
	}

	void Restructuring(Node* node)
	{
		if (GrandParent(node)->left == Parent(node))
		{
			if (Parent(node)->left == node)
				// LL
			{
				RightRotation(GrandParent(node));
				Parent(node)->color = BLACK;
				Parent(node)->right->color = RED;
			}
			else
				//LR
			{
				LeftRotation(Parent(node));
				RightRotation(Parent(node));
				node->color = BLACK;
				node->right->color = RED;
			}

		}
		else
		{
			if (Parent(node)->right == node)
				// RR
			{
				LeftRotation(GrandParent(node));
				Parent(node)->color = BLACK;
				Parent(node)->left->color = RED;
			}
			else
				//RL
			{
				RightRotation(Parent(node));
				LeftRotation(Parent(node));
				node->color = BLACK;
				node->left->color = RED;
			}
		}
	}

	//=================================
	// [DeleteNode]
	//=================================

	// �ش� ����� �ڸ��� ��ü�� ������ ã���ִ� �Լ�
	Node* Successor(Node* node)
	{
		if (node->left != nullptr && node->right != nullptr)
		{
			Node* temp = node->left;

			while (temp->right != nullptr)
				temp = temp->right;

			return temp;
		}

		if (node->left == nullptr && node->right == nullptr)
			return nullptr;

		if (node->left != nullptr)
			return node->left;
		else
			return node->right;
	}

	void FixDoubleBlack(Node* node)
	{
		Node* child = node;
		Node* parent = Parent(node);
		Node* sibling = Sibling(node);
		Node* left = (sibling != nullptr) ? sibling->left : nullptr;
		Node* right = (sibling != nullptr) ? sibling->right : nullptr;

		bool parent_color = parent->color;
		bool sibling_color = (sibling == nullptr || sibling->color == BLACK) ? BLACK : RED;
		bool left_color = (left == nullptr || left->color == BLACK) ? BLACK : RED;
		bool right_color = (right == nullptr || right->color == BLACK) ? BLACK : RED;

		if (parent_color == RED
			&& sibling_color == BLACK
			&& left_color == BLACK
			&& right_color == BLACK
			)
		{
			parent->color = sibling_color;
			if (sibling != nullptr) sibling->color = parent_color;
		}
		else if (sibling_color == BLACK
				&& right_color == RED
			)
		{
			if (parent->left == child)
				LeftRotation(parent);
			else
				RightRotation(parent);

			parent->color = sibling_color;
			sibling->color = parent_color;

			right->color = BLACK;
		}
		else if( sibling_color == BLACK
			&& left_color == RED
			&& right_color == BLACK
		)
		{
			RightRotation(sibling);

			sibling->color = left_color;
			left->color = sibling_color;

			FixDoubleBlack(child);
		}
		else if (parent_color == BLACK
			&& sibling_color == BLACK
			&& left_color == BLACK
			&& right_color == BLACK
			)
		{
			sibling->color = RED;

			FixDoubleBlack(parent);
		}
		else if (parent_color == BLACK
			&& sibling_color == RED
			&& left_color == BLACK
			&& right_color == BLACK
			)
		{
			parent->color = sibling_color;
			sibling->color = parent_color;

			FixDoubleBlack(child);
		}
	}


	//=================================
	// [MICS]
	//=================================

	// ��带 ������ ��� ���� ȸ�� 
	void LeftRotation(Node* node)
	{
		Node* child = node->right;
		Node* parent = Parent(node);

		if (child == nullptr)
		{
			cout << "node " << node->data << "�� ���� ��尡 �ƴ�(LeftRotation)" << endl;
			return;
		}

		// child�� �θ�� �ø��� node�� child�� �ڽ����� ������.
		node->right = child->left;
		child->left = node;
		node->parent = child;

		if (node->right != nullptr)
			node->right->parent = node;

		// child�� ���� �ö�����Ƿ� node�� �θ� child�� �θ�� �ٲپ��ش�.
		if (parent != nullptr)
		{
			if (node == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}
		child->parent = parent;
	}

	void RightRotation(Node* node)
	{
		Node* child = node->left;
		Node* parent = Parent(node);

		if (child == nullptr)
		{
			cout << "node " << node->data << "�� ���� ��尡 �ƴ�(RightRotation)" << endl;
			return;
		}

		// child�� �θ�� �ø��� node�� child�� �ڽ����� ������.
		node->left = child->right;
		child->right = node;
		node->parent = child;

		if (node->left != nullptr)
			node->left->parent = node;

		// child�� ���� �ö�����Ƿ� node�� �θ� child�� �θ�� �ٲپ��ش�.
		if (parent != nullptr)
		{
			if (node == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}
		child->parent = parent;
	}

	Node* Parent(Node* node)
	{
		return node == nullptr ? nullptr : node->parent;
	}

	Node* Sibling(Node* node)
	{
		Node* parent = Parent(node);

		if (parent == nullptr) return nullptr;
		return (parent->left == node) ? parent->right : parent->left;
	}

	Node* GrandParent(Node* node)
	{
		return Parent(Parent(node));
	}

	Node* Uncle(Node* node)
	{
		Node* grand_parent = GrandParent(node);
		if (grand_parent == nullptr) return nullptr;

		if (Parent(node) == grand_parent->left) return grand_parent->right;
		else return grand_parent->left;
	}
};