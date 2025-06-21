#include <cstdio>


struct Element {
    Element* prev{nullptr};
    Element* next{nullptr};
    const int val;

    // Element(Element* p, Element* n, int val): prev{p}, next{n}, val{val} {}

    int getVal() {return val;}
};

struct LList {
    Element* head{nullptr};
    Element* tail{nullptr};

    void prepend(int val) {
        if (!head) {
            Element* e = new Element{nullptr, nullptr, val};
            head = e;
            tail = e;
            return;
        }

        Element* e = new Element{nullptr, nullptr, val};
        e->next = head;
        head->prev = e;
        head = e;
    }

    void append(int val) {
        if (!tail) {
            Element* e = new Element{nullptr, nullptr, val};
            head = e;
            tail = e;
            return;
        }

        Element* e = new Element{nullptr, nullptr, val};
        tail->next = e;
        e->prev = tail;
        tail = e;
    }

    void traverse() {
        Element* it = head;

        while(it) {
            printf("Element:  %d\n", it->getVal());
            it = it->next;
        }
    }

    void traverseReverse() {
        Element* it = tail;

        while(it) {
            printf("Element:  %d\n", it->getVal());
            it = it->prev;
        }
    }
};

int main() {

    LList list{nullptr, nullptr};

    list.prepend(3);
    list.prepend(2);
    list.prepend(1);
    list.append(4);
    list.append(5);
    list.traverse();
    list.traverseReverse();


}