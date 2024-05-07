#include <iostream>
#include <initializer_list>

using namespace std;

struct Node;

template <typename T>
class SinglyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(T val) : data(val), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int length;

public:
    // Constructor
    SinglyLinkedList() : length(0)
    {
        head = new Node(T());
        tail = head;
    }

    SinglyLinkedList(T *data, int size) : length(0)
    {
        head = new Node(T());
        tail = head;

        for (int i = 0; i < size; i++)
        {
            insertBackward(data[i]);
        }
    }

    SinglyLinkedList(initializer_list<T> initList) : length(0)
    {
        head = new Node(T());
        tail = head;

        for (auto &val : initList)
        {
            insertBackward(val);
        }
    }

    // Destructor
    ~SinglyLinkedList()
    {
        clear();
        delete head;
    }

    // 迭代器类
    class iterator
    {
    private:
        Node *ptr; // 指向当前节点的指针
    public:
        iterator(Node *p = nullptr) : ptr(p) {}

        // 重载操作符
        T &operator*() { return ptr->data; } // 解引用
        Node *operator->() { return ptr; }   // 成员访问
        iterator &operator++()
        { // 前置++
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int)
        { // 后置++
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const iterator &other) { return ptr == other.ptr; }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }

        friend class SinglyLinkedList<T>; // 允许SinglyLinkedList访问iterator的私有成员
    };

    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(nullptr); }

    Node *getHead() const { return head; }
    int getLength() const { return length; }

    // Forward Insertion
    void insertForward(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = head->next;
        head->next = newNode;
        if (tail == head)
        {
            tail = head->next;
        }
        length++;
    }

    // Backward Insertion
    void insertBackward(T value)
    {
        tail->next = new Node(value);
        tail = tail->next;
        length++;
    }

    bool insert(T value, int index)
    {
        if(index < 0) return false;
        if(index >= length)
        {
            insertBackward(value);
            return true;
        }
        Node *cur = head->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        Node *newNode = new Node(value);
        newNode->next = cur->next;
        cur->next = newNode;
        length++;
        return true;
    }

    bool remove(int index)
    {
        if(index < 0 || index >= length) return false;
        Node *cur = head;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        Node *temp = cur->next;
        cur->next = temp->next;
        delete temp;
        length--;
        return true;
    }

    bool has(T value)
    {
        Node *cur = head->next;
        while (cur != nullptr)
        {
            if (cur->data == value)
            {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    int getLength()
    {
        return length;
    }

    // Display the list
    void display() const
    {
        Node *current = head->next;
        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null" << endl;
    }

    // Clear the list
    void clear()
    {
        Node *curr = head->next;
        while (curr != nullptr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        head->next = nullptr;
        tail = head;
    }

    T get(int index)
    {
        if (index < 0 || index >= length)
            return T();
        Node *cur = head->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        return cur->data;
    }

    void rearrange();
};