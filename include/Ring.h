//
// Created by oskar on 16.05.2020.
//

#ifndef PW_EADS_LABS_RING_H
#define PW_EADS_LABS_RING_H
#include <iostream>
#include <memory>
#include "IEnumerator.h"

template <typename Key, typename Info>
class Ring {
private:
    class Node;
    class RingEnumerator;
    Node *any = nullptr; // the pointer to any node ("first")
    std::unique_ptr<RingEnumerator> GetPrivateEnumerator(int startIndex); // Gets private (node access)an enumerator at given Index
    void DeleteNode (Node *node);

    class Node { // Private class Node
    public:
        Key key;    // That is private class, so key and info will be hidden from user anyway, that's why it can be public
        Info info;
        Node *next = nullptr;
        Node *back = nullptr;

        Node (Key key, Info info){
            this->key = key;
            this->info = info;
        };
    };

    class RingEnumerator : public IEnumerator<Key, Info> {  // Enumerator implements IEnumerator "interface"
    public: // Can be public, as it is private class. Outside only IEnumerator is provided.
        Node *currentNode = nullptr;
        Node **any = nullptr;
        Key GetCurrentKey () override;
        Info GetCurrentInfo () override;
        void MoveNext() override;
        void MoveBack() override;
        bool IsAny() override;
        bool CanMove() override;

        RingEnumerator(int startIndex, Node **any, bool isEmpty){
            if (startIndex < 0){
                throw RingException("Index must be non-negative");
            }
            this->any = any;
            if (isEmpty){
                return;
            }
            Node *node = *any;
            int currIndex = 0;
            do {
                if (currIndex++ == startIndex) {
                    this->currentNode = node;
                    return;
                }
                node = node->next;
            } while(node != *any);
            throw RingException("Index out of bounds");
        }
    };
public:
    // Ring();  // No need for constructor - default one is enough
    // I am not using references as I want to store copies of keys and infos.
    ~Ring();
    bool IsEmpty() const;
    Info Get(Key key, int occurrence = 1); // Gets Info by Key and Occurrence
    Info GetByIndex(int index); // Gets Info by index
    int GetIndex(Key key, int occurrence); //Gets index of element based on Key and Occurrence
    void PushFront(Key key, Info info); // Adds an element to the front
    void PushBack(Key key, Info info); // Adds an element to the back
    void InsertAfter(Key key, Info info, Key afterKey, int occurrence); // Inserts an element after given Key, Info and Occurrence
    void Rotate(bool direction); // Changes the Any pointer to next or back element of the ring (rotates clockwise or counterclockwise)
    Ring<Key, Info> Reversed(); // gets the reverse (new instance)
    Ring<Key, Info> Subring(int startIndex, int endIndex); // gets the subring of ring (new instance)
    void Remove(Key key, int occurrence); // Removes element by Key and Reference (does not remove element's *content*, element is removed from the Ring ONLY)
    void RemoveAll(Key key); // Removes all elements of given Key
    void RemoveAtIndex(int index); // Removes en element at given index
    void Clear(); // Removes every element of the ring
    int Count(); // Counts the ring;
    void PrintAll(); // couts the whole ring

    std::unique_ptr<IEnumerator<Key, Info>> GetEnumerator(int startIndex); // Gets an enumerator at given Index
    // operators
    Ring<Key, Info> &operator = (Ring<Key, Info> &otherRing){
        if (otherRing.any == this->any)
            return *this;

        if (any != nullptr){
            Clear();
        }

        if (otherRing.IsEmpty()){
            return *this;
        }

        auto e1 = otherRing.GetEnumerator(0);

        // deep copying elements
        do {
            this->PushBack(e1->GetCurrentKey(), e1->GetCurrentInfo());
            e1->MoveNext();
        } while(!e1->IsAny());

        return *this;
    }

    friend Ring<Key, Info> operator + (Ring<Key, Info> &ring1, Ring<Key, Info> &ring2){
        // here usage of friend is justified - this method creates new instance of ring and does not modify existing ones.
        // it is more explicit than usage of Ring<Key, Info> operator + (Ring<Key, Info> &ring2)
        // it does not use any private data anyway

        auto e1 = ring1.GetEnumerator(0);
        auto e2 = ring2.GetEnumerator(0);

        auto newRing = Ring<Key, Info>();

        if (!ring1.IsEmpty()){
            do {
                newRing.PushBack(e1->GetCurrentKey(), e1->GetCurrentInfo());
                e1->MoveNext();
            } while(!e1->IsAny());
        }

        if (!ring2.IsEmpty()) {
            do {
                newRing.PushBack(e2->GetCurrentKey(), e2->GetCurrentInfo());
                e2->MoveNext();
            } while(!e2->IsAny());
        }

        return newRing;
    }

    friend Ring<Key, Info> operator - (Ring<Key, Info> &ring1, Ring<Key, Info> &ring2){ // Removes all elements from ring1 that has key present in ring2
        // here usage of friend is justified - this method creates new instance of ring and does not modify existing ones.
        // it is more explicit than usage of Ring<Key, Info> operator - (Ring<Key, Info> &ring2)
        // it does not use any private data anyway

        auto newRing = Ring<Key, Info>();

        if (ring1.IsEmpty())
            return newRing;

        if (ring2.IsEmpty()){
            newRing = ring1; // = operator is overloaded, will deep copy elements
            return newRing;
        }

        std::unique_ptr<IEnumerator<Key,Info>> e2 = ring2.GetEnumerator(0);
        newRing = ring1; // copying all elements from ring1 into newRing

        do {
            try {
                newRing.RemoveAll(e2->GetCurrentKey());
            } catch (RingException &ex){} // here we have to catch exception, as removing non-existing key is not allowed

            e2->MoveNext();
        } while(!e2->IsAny());

        return newRing;
    }

    class RingException { // self-explanatory
    private:
        std::string message;
    public:
        explicit RingException(const std::string& message){
            this->message = message;
        }
        friend std::ostream &operator<<(std::ostream &os, const Ring<Key, Info>::RingException &ex);
    };
};

template <typename Key, typename Info>
std::ostream &operator<<(std::ostream &os, const typename Ring<Key, Info>::RingException &ex) {
    return os << "Ring exception: " << ex.message << std::endl;
}

template<typename Key, typename Info>
std::unique_ptr<IEnumerator<Key, Info>> Ring<Key, Info>::GetEnumerator(int startIndex) {
    std::unique_ptr<IEnumerator<Key, Info>> ptr(new RingEnumerator(startIndex, &any, IsEmpty()));
    return ptr;
}

template<typename Key, typename Info>
std::unique_ptr<typename Ring<Key,Info>::RingEnumerator> Ring<Key, Info>::GetPrivateEnumerator(int startIndex) {
    std::unique_ptr<RingEnumerator> ptr(new RingEnumerator(startIndex, &any, IsEmpty()));
    return ptr;
}

template<typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    Clear();
}

template<typename Key, typename Info>
bool Ring<Key, Info>::IsEmpty() const {
    return any == nullptr;
}

template<typename Key, typename Info>
Info Ring<Key, Info>::Get(Key key, int occurrence) {
    if (IsEmpty()){
        throw RingException("Ring is empty");
    }

    auto e1 = GetEnumerator(0);
    int currOccurrence = 0;
    do {
        if (e1->GetCurrentKey() == key && ++currOccurrence == occurrence){
            return e1->GetCurrentInfo();
        }
        e1->MoveNext();
    } while(!e1->IsAny());

    throw RingException("Given key was not found");
}

template<typename Key, typename Info>
Info Ring<Key, Info>::GetByIndex(int index) {
    if (IsEmpty()){
        throw RingException("Ring is empty");
    }

    auto e1 = GetEnumerator(0);
    int currIndex = 0;
    do {
        if (currIndex++ == index){
            return e1->GetCurrentInfo();
        }
        e1->MoveNext();
    } while(!e1->IsAny());

    throw RingException("Given key was not found");
}

template<typename Key, typename Info>
int Ring<Key, Info>::GetIndex(Key key, int occurrence) {
    if (IsEmpty()){
        throw RingException("Given key was not found");
    }
    auto e1 = GetEnumerator(0);
    int currIndex = 0;
    int currOccurrence = 0;
    do {
        if (key == e1->GetCurrentKey() && ++currOccurrence == occurrence){
            return currIndex;
        }
        currIndex++;
        e1->MoveNext();
    } while(!e1->IsAny());
    throw RingException("Given key was not found");
}

template<typename Key, typename Info>
void Ring<Key, Info>::PushFront(Key key, Info info) {
    auto newElement = new Node(key, info);

    if (IsEmpty()){
        any = newElement;
        any->next = newElement;
        any->back = newElement;
        return;
    }

    newElement->back = any->back;
    newElement->next = any;
    any->back->next = newElement;

    any->back = newElement;
    any = newElement;
}

template<typename Key, typename Info>
void Ring<Key, Info>::PushBack(Key key, Info info) {
    auto newElement = new Node(key, info);

    if (IsEmpty()){
        any = newElement;
        any->next = newElement;
        any->back = newElement;
        return;
    }

    auto e1 = GetPrivateEnumerator(0);
    e1->MoveBack(); // to move to the end of the ring

    newElement->next = any;
    newElement->back = e1->currentNode;
    e1->currentNode->next = newElement;
    any->back = newElement;
}

template<typename Key, typename Info>
void Ring<Key, Info>::InsertAfter(Key key, Info info, Key afterKey, int occurrence) {
    if (any == nullptr){
        Node *newElement = new Node(key, info);
        any = newElement;
        any->next = any;
        any->back = any;
        return;
    }
    Node *ptr = any;

    auto e1 = GetPrivateEnumerator(0);
    int currOccurrence = 0;
    do {
        if (e1->GetCurrentKey() == afterKey && ++currOccurrence == occurrence){
            ptr = e1->currentNode;
            break;
        }
        e1->MoveNext();
    } while(!e1->IsAny());

    if(currOccurrence == occurrence){
        if (ptr->next == any){
            // we are at the "end" of the ring
            PushBack(key, info);
        }else{
            Node *newElement = new Node(key, info);

            newElement->next = ptr->next;
            newElement->back = ptr;
            ptr->next = newElement;
            newElement->next->back = newElement;
        }
        return;
    }
    throw RingException("Given key does not exist");
}

template<typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::Reversed() {
    Ring ring;
    if (IsEmpty()){
        return ring;
    }
    auto e1 = GetPrivateEnumerator(0);
    do {
        ring.PushFront(e1->GetCurrentKey(), e1->GetCurrentInfo());
        e1->MoveNext();
    } while(!e1->IsAny());
}

template<typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::Subring(int startIndex, int endIndex) {
    int count = Count();

    if (startIndex > count || startIndex < 0 || startIndex > endIndex)
        throw RingException("Start index must be in bounds not higher than End Index");

    if (endIndex > count || endIndex < 0 || endIndex < startIndex)
        throw RingException("End index must be in bounds not lower than Start Index");

    auto enumerator = GetEnumerator(startIndex);
    auto ring = Ring();

    for (int i = 0; i < endIndex-startIndex + 1; ++i) {
        ring.PushBack(enumerator->GetCurrentKey(), enumerator->GetCurrentInfo());
        if (!enumerator->IsAny() && enumerator->CanMove())
            enumerator->MoveNext();
    }
    return ring;
}

template<typename Key, typename Info>
void Ring<Key, Info>::DeleteNode(Ring::Node *node) {
    if (!node)
        return;
    if (node == node->back){
        delete any;
        any = nullptr;
        return;
    }

    node->back->next = node->next;
    node->next->back = node->back;

    if (node == any){
        any = any->next;
    }
    delete node;
}

template<typename Key, typename Info>
void Ring<Key, Info>::Remove(Key key, int occurrence) {
    if (IsEmpty()){
        throw RingException("Given key does not exist");
    }

    int index = GetIndex(key, occurrence);
    RemoveAtIndex(index);
}

template<typename Key, typename Info>
void Ring<Key, Info>::RemoveAtIndex(int index) {
    if (index < 0){
        throw RingException("Index must be non-negative");
    }

    auto e1 = GetPrivateEnumerator(0);
    int currIndex = 0;
    do {
        if (currIndex++ == index){
            currIndex--;
            break;
        }
        e1->MoveNext();
    } while(!e1->IsAny());

    if (currIndex != index){
        throw RingException("Given key does not exist");
    }

    DeleteNode(e1->currentNode);
    e1->currentNode = nullptr;
}

template<typename Key, typename Info>
void Ring<Key, Info>::RemoveAll(Key key) {
    if (IsEmpty()){
        throw RingException("Given key does not exist");
    }
    bool didDelete = false;
    auto e1 = GetPrivateEnumerator(0);
    do {
        if (key == e1->GetCurrentKey()){
            e1->MoveBack();
            DeleteNode(e1->currentNode->next);
            didDelete = true;
        }
        if (e1->currentNode)
            e1->MoveNext();
    } while(!e1->IsAny() && e1->CanMove() && e1->currentNode);

    if (!didDelete){
        throw RingException("Given key does not exist");
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::Clear() {
    if (IsEmpty()){
        return;
    }
    auto e1 = GetPrivateEnumerator(0);
    do {
        if (e1->CanMove()) {
            e1->MoveBack();
                DeleteNode(e1->currentNode->next);
        }
        if (e1->CanMove())
            e1->MoveNext();
    } while(e1->CanMove());
    any = nullptr;
}

template<typename Key, typename Info>
int Ring<Key, Info>::Count() {
    if (IsEmpty()){
        return 0;
    }
    auto e1 = GetPrivateEnumerator(0);
    int currIndex = 0;
    do {
        currIndex++;
        e1->MoveNext();
    } while(!e1->IsAny());
    return currIndex;
}

template<typename Key, typename Info>
void Ring<Key, Info>::PrintAll() {
    auto e1 = GetEnumerator(0);
    int index = 0;
    do {
        std::cout << ++index << ": (" << e1->GetCurrentKey() << "\t" << e1->GetCurrentInfo() << ")" << std::endl;
        e1->MoveNext();
    } while(!e1->IsAny());
}

template<typename Key, typename Info>
void Ring<Key, Info>::Rotate(bool direction) {
    if (IsEmpty()){
        return;
    }
    if (direction){
        any = any->next;
    } else {
        any = any->back;
    }
}

template<typename Key, typename Info>
Info Ring<Key, Info>::RingEnumerator::GetCurrentInfo() {
    if (CanMove()) {
        return currentNode->info;
    }
    throw RingException("Current Enumerator element is null");
}

template<typename Key, typename Info>
Key Ring<Key, Info>::RingEnumerator::GetCurrentKey() {
    if (CanMove()) {
        return currentNode->key;
    }
    throw RingException("Current Enumerator element is null");
}

template<typename Key, typename Info>
void Ring<Key, Info>::RingEnumerator::MoveNext() {
    if (CanMove()) {
        this->currentNode = this->currentNode->next;
    }else{
        throw RingException("Cannot MoveNext - the ring is empty");
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::RingEnumerator::MoveBack() {
    if (CanMove()) {
        this->currentNode = this->currentNode->back;
    }else{
        throw RingException("Cannot MoveNext - the ring is empty");
    }
}

template<typename Key, typename Info>
bool Ring<Key, Info>::RingEnumerator::IsAny() {
    return currentNode == *any;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::RingEnumerator::CanMove() {
    return *any != nullptr && currentNode != nullptr;
}

#endif //PW_EADS_LABS_RING_H
