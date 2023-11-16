#include <iostream>

template<typename T>
class Queue{
private:
    struct Node{
        T data;
        Node* next;
    };
    size_t m_size;
    Node* head;
    Node* tail;
public:
    Queue(): m_size(0), head(nullptr), tail(nullptr){}

    // Copy constructor
    Queue(const Queue & other): Queue(){
        Node * current = other.head;
        while (current != nullptr){
            push(current->data);
            current = current->next;
        }
    }

    // Copy assignment
    Queue& operator=(const Queue & other){
        if (this != other){
            Queue temp(other);
            std::swap(other, temp);
        }
    }

    // Move constructor
    Queue(Queue&& other) noexcept : m_size(other.m_size), head(other.head), tail(other.tail){
        other.m_size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }

    // Move assignment
    Queue& operator=(Queue&& other) noexcept {
        if (this != other){
            clear();
            Queue temp(other);
            std::swap(this, temp);
        }
        return *this;
    }


    void clear(){
        while (!empty()){
            pop();
        }
    }

    ~Queue(){
        clear();
    }



    void pop(){
        if (empty()){
            throw std::out_of_range("Queue is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        m_size -= 1;
    }
    void push(const T& new_data){
        Node* newNode = new Node{new_data, nullptr};
        if (empty()){
            head = newNode;
        }else{
            tail->next = newNode;
        }
        tail = newNode;
        m_size += 1;
    }

    T& front(){
        if (empty()){
            throw std::out_of_range("Queue is empty");
        }
        return head->data;
    }
    bool empty(){ return m_size == 0;}
    size_t size(){return m_size;}

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    Queue<int> queue{};
    queue.push(0);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.pop();

    Queue queue2 = queue;
    Queue queue3(queue);
    Queue queue4(std::move(queue));
    Queue queue5 = std::move(queue4);

    return 0;
}
