#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

using namespace std;

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* previous;
        Node* next;
        Node(T data, Node* previous = nullptr, Node* next = nullptr) : data(data), previous(previous), next(next) {}
    };

    Node* head;
    Node* tail;
    size_t length;

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(const T* items, size_t count) : head(nullptr), tail(nullptr), length(0)
    {
        for (size_t i = 0; i < count; i++)
            Append(items[i]);
    }

    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), length(0)
    {
        Node* current = other.head;
        while (current)
        {
            Append(current->data);
            current = current->next;
        }
    }

    ~LinkedList()
    {
        Node* current = head;
        while (current)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    T GetFirst() const
    {
        if (!head)
            throw out_of_range("List is empty");
        return head->data;
    }

    T GetLast() const
    {
        if (!tail)
            throw out_of_range("List is empty");
        return tail->data;
    }

    T Get(size_t index) const
    {
        if (index >= length)
            throw out_of_range("Index out of range");
        Node* temp = head;
        for (size_t i = 0; i < index; i++)
            temp = temp->next;
        return temp->data;
    }

    LinkedList<T>* GetSubList(size_t start, size_t end) const
    {
        if (start > end || end >= length)
            throw out_of_range("Invalid sublist indices");

        LinkedList<T>* sublist = new LinkedList<T>();
        Node* current = head;
        
        // Перемещаемся к стартовому элементу
        for (size_t i = 0; i < start; ++i)
            current = current->next;

        // Копируем элементы от start до end
        for (size_t i = start; i <= end; ++i)
        {
            sublist->Append(current->data);
            current = current->next;
        }
        
        return sublist;
    }

    size_t GetLength() const
    {
        return length;
    }

    // теперь O(n)
    void Append(T item)
    {
        Node* newNode = new Node(item);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void Prepend(T item)
    {
        Node* newNode = new Node(item);
        newNode->next = head;
        if (head)
            head->previous = newNode;
        else
            tail = newNode; // Если список был пуст, tail становится новым элементом
        head = newNode;
        length++;
    }

    void InsertAt(T item, size_t index)
    {
        if (index > length)
            throw out_of_range("Index out of range");
        if (index == 0)
        {
            Prepend(item);
            return;
        }

        Node* temp = head;
        for (size_t i = 0; i < index - 1; ++i)
            temp = temp->next;

        Node* newNode = new Node(item, temp, temp->next);
        if (temp->next)
            temp->next->previous = newNode;
        else
            tail = newNode; // Если вставляем в конец, обновляем tail
        temp->next = newNode;
        length++;
    }

    LinkedList<T>* Concat(LinkedList<T>* list) const
    {
        if (!list)
            throw invalid_argument("List cannot be null");
        
        LinkedList<T>* result = new LinkedList<T>(*this);
        Node* temp = list->head;
        while (temp)
        {
            result->Append(temp->data);
            temp = temp->next;
        }

        return result;
    }

    // Оператор [] для записи (non-const версия)
    T& operator[](size_t index)
    {
        if (index >= length)
            throw std::out_of_range("Index out of bounds");
        
        return Get(index);
    }

    // Оператор [] для чтения (const версия)
    const T& operator[](size_t index) const
    {
        if (index >= length)
            throw std::out_of_range("Index out of bounds");
        
        return Get(index);
    }

    string ToString() const
    {
        if (length == 0)
            return "[]";
        
        string s = "[";
        for (int i = 0; i < length - 1; i++)
            s += to_string(Get(i)) + ", ";
        s += to_string(Get(length - 1)) + "]";

        return s;
    }
};

#endif