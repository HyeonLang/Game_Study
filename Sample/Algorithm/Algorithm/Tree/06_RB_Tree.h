#pragma once

// 06_RB_Tree.h
/*
	※ Red-Black Tree
		ㄴ AVL과 같이 균형을 맞추는 자가 균형 이진 탐색 트리
		ㄴ 노드에 빨강, 검정색을 부여하여 균형을 맞춘다.
		ㄴ 대다수의 프로그래밍 언어에서 연관배열(map, set, multi map, multi set)을
		구현하기 위한 자료구조로 사용된다.

	※ RB vs AVL
		ㄴ AVL트리는 RB 트리에 비해 좀더 엄격하게 균형을 유지한다.
			-> RB는 빨강 노드가 연속될 때만 재조정을 하지만 AVL은 삽입시마다 조상노드들의 균형을 확인하여 재조정한다.
		ㄴ AVL이 RB보다 균형을 엄격하게 유지하기 때문에 탐색을 빠르지만 RB보다 삽입 삭제시 느리다.
		ㄴ AVL 트리는 더 빠른 탐색이 필요한 경우에 사용한다.
		ㄴ RB 트리는 더 빠른 삽입 삭제가 필요한 경우에 사용한다.

	※ RB 트리의 속성
		ㄴ 모든 노드의 색은 Black이거나 Red
		ㄴ 루트노드는 항상 Black
		ㄴ 모든 leaf 노드(nullptr)는 항상 Black
		ㄴ red 노드가 연속적으로 존재할 수 없다.
			-> red노드가 연속적인 부분이 있다면 재조정을 해준다.
		ㄴ 루트 노드에서 각 leaf노드까지의 balck노드 개수는 언제나 동일하다.

	※ RB 트리의 삽입
		ㄴ 삽입되는 노드의 색깔은 무조건 Red이다.
		ㄴ 삽입 시 Red 노드가 연속적으로 나오게 될경우 재조정을 한다.

	※ 삽입 시 재조정 방법 두가지
		ㄴ Recoloring
			- 조건 : 삽입된 노드의 부모의 형제 색상이 Red일 때
			- 방법
				- 1. 삽입된 노드의 부모와 부모 형제 노드를 Black으로 바꾼다.
				- 2. 만약 삽입된 노드의 부모의 부모가 루트가 아니라면 Red로
				바꾸어 준다.
				- 3. 삽입된 노드의 부모의 부모의 색상이 Red로 바뀌었다면 해당 노드의
				부모가 Red일 수도 있으니 해당 노드의 부모를 검사하여 조정을 해준다.

		ㄴ Restructuring
			- 조건 : 삽입된 노드의 부모의 형제 색상이 Black일 경우
			 - 방법
				- 1. AVL 트리 처럼 부모의 부모를 기준으로 삽입된 위치를 파악하고 회전 시켜준다.

				- 2. LL이거나 RR일 때 상황에 맞게 오른쪽, 왼쪽 회전을 해준후에
				부모의 위치로 올라온 노드를 Black, 자식의 위치가 된 노드들은 Red로 바꾸어 준다.

				- 3. LR이거나 RL일 때 AVL과 같이 회전을 두번해야 하는데 첫번째 회전은 상황에 맞게
				오른쪽, 왼쪽 회전을 해주고 다음 회전은 2. 와 같이 처리해준다.

	※ RB트리의 삭제
		ㄴ 삭제하는 노드의 색이 RED일 경우 삭제만 하면 된다.
			-> RB 트리의 균형이 깨지기 위해서는 RED가 연속되거나 BLACK이 삭제되어야하는데
			RED를 삭제하는 것으로는 균형이 깨지지 않기 때문이다.

		ㄴ 삭제된 노드의 자리를 대체하는 자식은 다른 BST와 동일하다.
			-> 삭제되는 노드의 왼쪽 자식의 제일 오른쪽 or 오른쪽 자식의 제일 왼쪽
			-> 실제로 삭제되는 위치는 대체된 자식 노드의 위치이다
			-> 해당 위치에서 균형을 맞춰주어야 한다.

		ㄴ 삭제하려는 노드의 색이 BLACK일때만 추가적인 작업을 해준다.


	※ 삭제하려는 노드가 BLACK일 때 무조건 해야하는 추가적인 작업
		ㄴ 삭제된 노드의 자리를 대체하는 노드를 BALCK으로 칠한다.
		ㄴ 색을 칠할 때 해당 노드의 원래 색에 따라 케이스가 갈린다.
			- 원래 색이 RED일 경우 : 이후 추가 작업은 없다.
			- 원래 색이 BLACK일 경우 : 다시 검은색이 칠해지는 노드를 더블 블랙 노드라고
			하며 케이스에 따라 작업을 해준다.

	※ 더블 블랙인 경우 케이스에 따라 해야하는 추가적인 작업

		ㄴ 단어 정리
			- 실제로 삭제된 노드를 d라고 했을 때
			- c : d의 자리를 대체한 자식 노드
			- p : d의 부모 노드
			- s : d의 형제 노드
			- l, r : s의 왼쪽, 오른쪽 자식(d기준 조카노드)
			- (r or b or w) : 각 노드의 색, w인 경우 아무 색상이든 상관 없다는 뜻


	- c의 위치에 블랙 노드가 사라졌으므로 c에서 검은색 노드가 -1된
	상황이며 이를 케이스에 따라 맞춰주는 작업을 한다.
	- 아래의 처리 방법은 c가 왼쪽일 경우이고, c가 오른쪽인 상황도 가정해서 처리해야 한다.


	- 1번 케이스. p가 레드이고 s, l, r이 전부 블랙인 경우
					  p(r)
			 c(b)               s(b)
						 l(b)         r(b)

		  -> p와 s의 색상을 교환한다.

					  p(b)
			 c(b)               s(r)
						 l(b)         r(b)

	- 2번 케이스. s가 블랙이고 r이 레드인 경우

					  p(w)
			 c(b)               s(b)
						 l(w)         r(r)

		  ->   p를 왼쪽으로 회전한다.
		  ->  p와 s의 색상을 교환한다.
		  ->  r을 블랙으로 바꾼다.

							s(w)
				   p(b)               r(b)
			 c(b)         l(w)

	- 3번 케이스. s가 블랙, l이 레드, r이 블랙인 경우

					  p(w)
			 c(b)               s(b)
						 l(r)         r(b)

		  ->   s를 오른쪽으로 회전한다.
		  ->  l과 s의 색상을 교환한다.
		  ->  2번 케이스와 같아지므로 2번 케이스 작업을 해준다.

					  p(w)
			 c(b)               l(b)
									 s(r)
										   r(b)

	- 4번 케이스. p, s, l, r 모두 블랙일 때

					  p(b)
			 c(b)               s(b)
						 l(b)         e(b)

		  -> s의 색을 레드로 바꾼다.
		  -> 이렇게하면 c와 s가 전부 -1이 되어 p를 기준으로 -1이 됨
		  -> 문제가 p로 올라갔으므로 p를 기준으로(p가 c가 된다는 뜻) 다시 문제를 처리해준다.

					  p(b)
			 c(b)               s(r)
						 l(b)         r(b)

	- 5번 케이스. s가 레드이고 p, l, r이 블랙
					  p(b)
			 c(b)               s(r)
						 l(b)         r(b)

		  -> p를 왼쪽으로 회전
		  -> p와 s의 색상을 바꾼다.
		  -> c의 부모 p의 색상이 레드로 바뀌었다.
		  -> 색 조합에 따라 케이스 1, 2, 3중 하나로 처리해준다.

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
	// 외부에서 사용하는 삽입 함수
	Node* InsertNode(Node* root, Node* node)
	{
		InsertBST(root, node);
		Balance(node);

		// 루트 노드가 바뀔 수 있으니 루트 검색해서 리턴
		root = node;
		while (root->parent != nullptr)
			root = root->parent;

		return root;
	}

	// 해당 데이터를 가진 노드 탐색
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

		// 본인의 자리를 대체할 후임 노드
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

	// 들어온 노드를 이진 탐색 트리 형태로 삽입
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

	// 삽입된 노드를 기준으로 색깔을 조사해서 균형을 맞춰준다.
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

	// 해당 노드의 자리를 대체할 후임을 찾아주는 함수
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

	// 노드를 축으로 삼아 왼쪽 회전 
	void LeftRotation(Node* node)
	{
		Node* child = node->right;
		Node* parent = Parent(node);

		if (child == nullptr)
		{
			cout << "node " << node->data << "가 내부 노드가 아님(LeftRotation)" << endl;
			return;
		}

		// child를 부모로 올리고 node를 child의 자식으로 내린다.
		node->right = child->left;
		child->left = node;
		node->parent = child;

		if (node->right != nullptr)
			node->right->parent = node;

		// child가 위로 올라왔으므로 node의 부모를 child의 부모로 바꾸어준다.
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
			cout << "node " << node->data << "가 내부 노드가 아님(RightRotation)" << endl;
			return;
		}

		// child를 부모로 올리고 node를 child의 자식으로 내린다.
		node->left = child->right;
		child->right = node;
		node->parent = child;

		if (node->left != nullptr)
			node->left->parent = node;

		// child가 위로 올라왔으므로 node의 부모를 child의 부모로 바꾸어준다.
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