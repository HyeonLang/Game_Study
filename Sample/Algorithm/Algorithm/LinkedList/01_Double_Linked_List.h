#pragma once

// 01_Double_Linked_List.h

#include<iostream>
using namespace std;

template<typename T>
class DoubleLinkedList
{
public:
	struct Node
	{
		Node* prev = nullptr;
		Node* next = nullptr;
		T data;
	};

	static Node* Create(T data)
	{
		Node* node = new Node();
		node->data = data;
		return node;
	}

	static void Destroy(Node** node)
	{
		delete* node;
		*node = nullptr;
	}

public:

	~DoubleLinkedList()
	{
		Clear();
	}

	void PushBack(T data)
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

	void PushFront(T data)
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


	void Insert(Node* target, T data)
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
			cout << "ÀÎµ¦½º ¿¡·¯" << endl;
			return nullptr;
		}

		Node* node = head;
		while (node != nullptr && index-- > 0)
			node = node->next;
		return node;
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

	void PrintList()
	{
		for (int i = 0; i < size; i++)
			cout << operator[](i)->data << " ";
		cout << endl;
	}

protected:
	Node* head = nullptr;
	Node* tail = nullptr;

	int size = 0;
};

int main()
{
	DoubleLinkedList<int> d1;
	d1.PushBack(10);
	d1.PushBack(20);
	d1.PushBack(30);
	d1.PushBack(40);
	d1.PushFront(0);
	d1.PushFront(-10);
	d1.PrintList();

	d1.PopBack();
	d1.PopFront();
	d1.PrintList();

	d1.Insert(d1[3], 100);
	d1.Insert(d1[3], 200);
	d1.PrintList();

	return 0;
}