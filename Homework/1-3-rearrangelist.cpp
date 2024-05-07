#include <iostream>
#include "linklist.cpp"

using namespace std;

template <typename T>
void SinglyLinkedList<T>::rearrange() {
    if (head == nullptr || head->next == nullptr) {
        return; // 空链表或只有一个节点,不需要重排
    }

    // 找到中间节点
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 将链表分为两部分
    Node* mid = slow->next;
    slow->next = nullptr;

    // 反转后半部分
    Node* prev = nullptr;
    Node* curr = mid;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // 合并前半部分和反转后的后半部分
    Node* p1 = head->next;
    Node* p2 = prev;
    while (p2) {
        Node* tmp1 = p1->next;
        Node* tmp2 = p2->next;
        p1->next = p2;
        p2->next = tmp1;
        p1 = tmp1;
        p2 = tmp2;
    }
}

int main()
{
    SinglyLinkedList<int> list {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Before rearrange:" << endl;
    list.display();
    list.rearrange();
    cout << "After rearrange:" << endl;
    list.display();
}