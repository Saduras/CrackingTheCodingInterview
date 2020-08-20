#pragma once
#include <string>
#include <iostream>

namespace SinglyLinkedList
{
	class Node
	{
	public:
		int m_Value;
		Node* m_Next = nullptr;

		Node(const int value)
			: m_Value(value)
		{
		}

		/// <summary>
		/// Adds a new value at the end of the linked list.
		/// </summary>
		/// <param name="value">Value to be added</param>
		void AppendToTail(const int value)
		{
			Node* end = new Node(value);
			Node* current = this;
			while (current->m_Next != nullptr) {
				current = current->m_Next;
			}
			current->m_Next = end;
		}

		/// <summary>
		/// Prints all values in the linked list to the console.
		/// </summary>
		void Print()
		{
			std::string out = std::to_string(m_Value);

			Node* current = this;
			while (current->m_Next != nullptr) {
				current = current->m_Next;
				out += ", " + std::to_string(current->m_Value);
			}
			std::cout << out << std::endl;
		}
	};

	Node* DeleteFirstValue(Node* head, const int value)
	{
		Node* current = head;

		if (current->m_Value == value) {
			head = current->m_Next;
			delete& current;
			return head;
		}

		while (current->m_Next != nullptr) {
			if (current->m_Next->m_Value == value) {
				Node* toDelete = current->m_Next;
				current->m_Next = current->m_Next->m_Next;
				delete toDelete;
				return head; // didn't change
			}
			current = current->m_Next;
		}

		// No match
		return head;
	}
}