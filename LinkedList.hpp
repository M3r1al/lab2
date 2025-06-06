#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

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

    Node* GetNode(size_t index) const
    {
        if (index >= length)
            throw std::out_of_range("Index out of range");
        if (index < length / 2)
        {
            Node* temp = head;
            for (size_t i = 0; i < index; i++)
                temp = temp->next;
            return temp;
        }
        Node* temp = tail;
        for (size_t i = 0; i < length - 1 - index; i++)
            temp = temp->previous;
        return temp;
    }

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
            throw std::out_of_range("List is empty");
        return head->data;
    }

    T GetLast() const
    {
        if (!tail)
            throw std::out_of_range("List is empty");
        return tail->data;
    }

    T Get(size_t index) const
    {
        return GetNode(index)->data;
    }

    T& GetLinked(size_t index)
    {
        return GetNode(index)->data;
    }

    const T& GetLinked(size_t index) const
    {
        return GetNode(index)->data;
    }

    LinkedList<T>* GetSubList(size_t start, size_t end) const
    {
        if (start > end || end >= length)
            throw std::out_of_range("Invalid sublist indices");

        LinkedList<T>* sublist = new LinkedList<T>();
        // Перемещаемся к стартовому элементу
        Node* current = GetNode(start);

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

    // теперь O(1)
    void Append(const T& item)
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

    void Prepend(const T& item)
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

    void InsertAt(const T& item, size_t index)
    {
        if (index > length)
            throw std::out_of_range("Index out of range");
        if (index == 0)
        {
            Prepend(item);
            return;
        }
        if (index == length)
        {
            Append(item);
            return;
        }

        Node* temp = GetNode(index - 1);

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
            throw std::invalid_argument("List cannot be null");
        
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
        
        return GetNode(index)->data;
    }

    // Оператор [] для чтения (const версия)
    const T& operator[](size_t index) const
    {
        if (index >= length)
            throw std::out_of_range("Index out of bounds");
        
        return Get(index);
    }

    std::string ToString() const
    {
        if (length == 0)
            return "[]";
        
        std::string s = "[";
        Node* temp = head;
        for (int i = 0; i < length - 1; i++)
        {
            s += std::to_string(temp->data) + ", ";
            temp = temp->next;
        }
        s += std::to_string(temp->data) + "]";

        return s;
    }
};

#endif