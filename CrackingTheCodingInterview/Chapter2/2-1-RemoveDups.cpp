/**
 * Write code to remove duplicates from an unsorted linked list.
 * FOLLOW UP
 * How would you solve this problem if a temporary buffer is not allowed? 
 */
#include "SinglyLinkedList.h"

#include <unordered_set>

namespace SLL = SinglyLinkedList;

/// <summary>
/// Use unordered set so cache seen values.
/// Space: O(n)
/// Time: O(n)
/// </summary>
/// <param name="head"></param>
void RemoveDups_cached(SLL::Node* head)
{
	SLL::Node* current = head;
	std::unordered_set<int> cache({ head->m_Value });

	while (current != nullptr && current->m_Next != nullptr) {
		if (cache.find(current->m_Next->m_Value) != cache.end()) {
			SLL::Node* toDelete = current->m_Next;
			current->m_Next = current->m_Next->m_Next;
			if(toDelete != nullptr)
				delete toDelete;
		}
		else {
			cache.insert(current->m_Next->m_Value);
		}
		current = current->m_Next;
	}
}

/// <summary>
/// Call recursive to remove all dups of head value
/// Space: O(n) (call stack)
/// Time: O(n^2)
/// </summary>
/// <param name="head"></param>
void RemoveDups_recursive(SLL::Node* head)
{
	SLL::Node* current = head;
	while (current != nullptr && current->m_Next != nullptr) {
		if (current->m_Next->m_Value == head->m_Value) {
			SLL::Node* toDelete = current->m_Next;
			current->m_Next = current->m_Next->m_Next;
			delete toDelete;
		}
		else {
			current = current->m_Next;
		}
	}

	if(head != nullptr)
		RemoveDups_recursive(head->m_Next);
}

/// <summary>
/// Use runner pointer to remove all dup values of current element
/// Space: O(n)
/// Time: O(n^2)
/// </summary>
/// <param name="head"></param>
void RemoveDups_runner(SLL::Node * head)
{
	SLL::Node* current = head;
	while (current != nullptr) {
		SLL::Node* runner = current;
		while (runner->m_Next != nullptr) {
			if (runner->m_Next->m_Value == current->m_Value) {
				// delete runner->next
				SLL::Node* toDelete = runner->m_Next;
				runner->m_Next = runner->m_Next->m_Next;
				delete toDelete;
			}
			else {
				runner = runner->m_Next;
			}
		}
		current = current->m_Next;
	}
}

int main()
{
	SLL::Node* head = new SLL::Node(0);
	head->AppendToTail(1);
	head->AppendToTail(1);
	head->AppendToTail(3);
	head->AppendToTail(0);

	head->Print();
	RemoveDups_runner(head);
	head->Print();

	return 0;
}