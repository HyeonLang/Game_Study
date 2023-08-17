#pragma once

// 02_Ranking_List.h

/*
	�� ��ŷǥ ����� ����

	[menu]
	1. �������Է�
	2. ��ŷǥ Ȯ��
	3. ����
	����(1-3):
	(����ó��)

	1�� ���ý�
	�Ʒ��� ���� �Է¹���
	x��° ĳ���� �̸� :
	x��° ĳ���� ���� :
	x��°ĳ���� elo : -> ��ŷ�� ��� ����
	�����͸� �Է� �� ������ �ٽ� ���θ޴���

	2�� ���ý�
	��ŷǥ ���
	-----------------
	ĳ���͸� ��ŷ ���� elo
*/

#include<iostream>
#include<string>
using namespace std;

struct Character
{
	string name;
	int level;
	int elo;
};

class RankingList
{
public:
	struct Node
	{
		Node* prev = nullptr;
		Node* next = nullptr;
		Character* data;
	};

	static Node* Create(Character* data)
	{
		Node* node = new Node();
		node->data = data;
		return node;
	}

	static void Destroy(Node** node)
	{
		delete (*node)->data;
		delete* node;
		*node = nullptr;
	}

	static Character* CreateCharacter(int index)
	{
		Character* character = new Character();

		cout << index + 1 << "��° ĳ���� �̸� : ";
		cin >> character->name;

		cout << index + 1 << "��° ĳ���� ���� : ";
		cin >> character->level;

		cout << index + 1 << "��° ĳ���� elo : ";
		cin >> character->elo;
		cout << endl;

		return character;
	}

public:

	~RankingList()
	{
		Clear();
	}

	void PushBack(Character* data)
	{
		Node* new_node = Create(data);

		if (head == nullptr)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
		size++;
	}

	void PushFront(Character* data)
	{
		Node* new_node = Create(data);

		if (head == nullptr)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
		size++;
	}

	void PopBack()
	{
		if (size <= 0) return;

		if (size == 1)
		{
			Destroy(&head);
			tail = nullptr;
		}
		else
		{
			tail = tail->prev;
			Destroy(&tail->next);
		}
		size--;
	}

	void PopFront()
	{
		if (size <= 0) return;

		if (size == 1)
		{
			Destroy(&head);
			tail = nullptr;
		}
		else
		{
			head = head->next;
			Destroy(&head->prev);
		}
		size--;
	}


	void PushCharacter(Character* data)
	{
		if (head == nullptr)
		{
			Node* new_node = Create(data);
			head = new_node;
			tail = new_node;
			size++;
		}
		else
		{
			if (data->elo > head->data->elo)
			{
				PushFront(data);
				return;
			}
			else if (data->elo <= tail->data->elo)
			{
				PushBack(data);
				return;
			}

			Node* temp = head;
			while (true)
			{
				if (temp->data->elo >= data->elo
					&& temp->next->data->elo < data->elo)
					break;
				else
					temp = temp->next;
			}

			Insert(temp->next, data);
		}

	}

	void Insert(Node* target, Character* data)
	{
		Node* temp = head;

		while (temp != nullptr)
		{
			if (temp == target) break;
			temp = temp->next;
		}
		if (temp == nullptr) return;

		if (target == head)
			PushFront(data);
		else
		{
			Node* new_node = Create(data);

			new_node->prev = temp->prev;
			new_node->next = temp;

			new_node->prev->next = new_node;
			new_node->next->prev = new_node;
			size++;
		}
	}

	Node* operator[](int index)
	{
		if (index >= size || index < 0)
		{
			cout << "�ε��� ����" << endl;
			return nullptr;
		}

		Node* node = head;
		while (node != nullptr && index-- > 0)
			node = node->next;
		return node;
	}

	void PrintRank()
	{
		cout << "�̸�\t��ũ\t����\telo" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << operator[](i)->data->name
				<< "\t" << i + 1
				<< "\t" << operator[](i)->data->level
				<< "\t" << operator[](i)->data->elo
				<< endl;
		}
		cout << endl;
	}


	int Size()
	{
		return size;
	}

	void Clear()
	{
		for (int i = size; i > 0; i--)
			PopBack();
	}

protected:
	Node* head = nullptr;
	Node* tail = nullptr;

	int size = 0;
};

int main()
{
	RankingList ranking_list;

	int intput_menu;

	bool is_play = true;

	while (is_play)
	{
		cout << "[menu]" << endl;
		cout << "1. ������ �Է�" << endl;
		cout << "2. ��ŷǥ Ȯ��" << endl;
		cout << "3. ����" << endl;
		cout << "����(1~3) : ";
		cin >> intput_menu;

		switch (intput_menu)
		{
		case 1:
		{
			auto new_character = ranking_list.CreateCharacter(ranking_list.Size());
			ranking_list.PushCharacter(new_character);
			break;
		}

		case 2:
		{
			ranking_list.PrintRank();
			break;
		}

		case 3:
			is_play = false;
			break;
		}
	}


	return 0;
}
