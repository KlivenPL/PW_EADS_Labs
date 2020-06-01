//
// Created by oskar on 16.05.2020.
//

#ifndef PW_EADS_LABS_DICTIONARY_HH
#define PW_EADS_LABS_DICTIONARY_HH
#include <iostream>
#include <memory>
#include <sstream>
#include "IEnumerator.h"

template <typename Key, typename Info>
class Dictionary {
private:
    class Node;
    class DictionaryEnumerator;
    Node *root = nullptr; // the pointer to root node
    std::unique_ptr<DictionaryEnumerator> GetPrivateEnumerator(); // Gets private (node access)an enumerator at given Index
    Node *InsertNode (Node* node, Key &key, Info &info); // returns new root of a subtree
    int Count (Node *node);
    Node *RotateRight (Node *node);
    Node *RotateLeft (Node *node);
    Node *DeleteNode (Node *node, Key &key);
    int GetHeight(Node *node){
        return node ? node->height : 0;
    }
    int GetBalance(Node *node) {
        if (node == nullptr)
            return 0;
        auto hLeft = GetHeight(node->left);
        auto hRight = GetHeight(node->right);

        return hLeft - hRight;
    }
    Node *GetMinKeyNode(Node* node) {
        Node* curr = node;

        while (curr->left != nullptr)
            curr = curr->left;

        return curr;
    }
    std::string PrintInOrder (Node *node, bool keysOnly);
    bool Contains (Node *node, Key &key);
    void Copy (Node *node, Dictionary &target);
    void TryRemoveFromTarget(Node *node, Dictionary &target);

    class Node { // Private class Node
    public:
        Key key;    // That is private class, so key and info will be hidden from user anyway, that's why it can be public
        Info info;
        Node *right = nullptr;
        Node *left = nullptr;
        int height = 1;

        Node (Key key, Info info){
            this->key = key;
            this->info = info;
        };
    };

    class DictionaryEnumerator : public IEnumerator<Key, Info> {  // Enumerator implements IEnumerator "interface"
    private:
        Node **root = nullptr;
        Node *SearchKey(Node *node, Key &key){
            if (node){
                if (node->key == key){
                    return node;
                }
                if (key < node->key){
                    return SearchKey(node->left, key);
                } else {
                    return SearchKey(node->right, key);
                }
            }
            return nullptr;
        }
    public: // Can be public, as it is private class. Outside only IEnumerator is provided.
        Node *currentNode = nullptr;

        Key GetCurrentKey () override;
        Info GetCurrentInfo () override;
        void MoveRight() override;
        void MoveLeft() override;
        bool CanMoveRight() override;
        bool CanMoveLeft() override;
        void MoveToKey(Key key) override;

        DictionaryEnumerator(Node **root, bool isEmpty){
            if (isEmpty){
                return;
            }
            this->root = root;
            this->currentNode = *root;
        }
    };
public:
    // I am not using references as I want to store copies of keys and infos.
    ~Dictionary();
    bool IsEmpty() const;
    void Insert(Key key, Info info); // Inserts the key and info
    bool TryInsert(Key key, Info info); // inserts if key does not exist
    Info Get(Key key); // Gets Info by Key and Occurrence
    bool Contains(Key key); // does dictionary contain the key
    void Remove(Key key); // Removes element by Key (does not remove element's *content*, element is removed from the Dictionary ONLY)
    bool TryRemove(Key key); // removes if key exists
    void Clear(); // Removes every element of the dictionary
    int Count(); // Counts the dictionary;
    std::string PrintAll(bool keysOnly = false); // prints the whole dictionary in inOrder order
    void Copy (Dictionary &target, bool clearTarget = true);

    //-=-=-=-=
    // In the code below in most cases I do not use Enumerator while traversing the Dictionary, as recursive functions would require to copy it over and over, which is not efficient nor elegant
    // using 'bare' Nodes and recursion is more natural for this kind of data structure
    //-=-=-=-=

    std::unique_ptr<IEnumerator<Key, Info>> GetEnumerator();
    // operators
    Dictionary<Key, Info> &operator = (Dictionary<Key, Info> &otherDictionary){
       otherDictionary.Copy(*this);
    }

    Dictionary<Key, Info> operator + (Dictionary<Key, Info> &otherDictionary){
        Dictionary newDict;
        newDict = *this;
        otherDictionary.Copy(newDict, false);
        return newDict;
    }

    Dictionary<Key, Info> operator - (Dictionary<Key, Info> &otherDictionary){ // Removes all elements from dictionary1 that has key present in dictionary2
        Dictionary newDict;
        newDict = *this;
        if (!otherDictionary.IsEmpty())
            TryRemoveFromTarget(otherDictionary.root, newDict);
        return newDict;
    }

    class DictionaryException { // self-explanatory
    private:
        std::string message;
    public:
        explicit DictionaryException(const std::string& message){
            this->message = message;
        }
        friend std::ostream &operator<<(std::ostream &os, const Dictionary<Key, Info>::DictionaryException &ex);
    };
};

template <typename Key, typename Info>
std::ostream &operator<<(std::ostream &os, const typename Dictionary<Key, Info>::DictionaryException &ex) {
    return os << "Dictionary exception: " << ex.message << std::endl;
}

template<typename Key, typename Info>
std::unique_ptr<IEnumerator<Key, Info>> Dictionary<Key, Info>::GetEnumerator() {
    std::unique_ptr<IEnumerator<Key, Info>> ptr(new DictionaryEnumerator(&this->root, IsEmpty()));
    return ptr;
}

template<typename Key, typename Info>
std::unique_ptr<typename Dictionary<Key,Info>::DictionaryEnumerator> Dictionary<Key, Info>::GetPrivateEnumerator() {
    std::unique_ptr<DictionaryEnumerator> ptr(new DictionaryEnumerator(&this->root, IsEmpty()));
    return ptr;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary() {
    Clear();
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::IsEmpty() const {
    return root == nullptr;
}

template<typename Key, typename Info>
Info Dictionary<Key, Info>::Get(Key key) {
    if (IsEmpty()){
        throw DictionaryException("Dictionary is empty");
    }

    auto e1 = GetPrivateEnumerator();
    e1->MoveToKey(key);
    return e1->GetCurrentInfo();
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::Remove(Key key) {
    if (IsEmpty()){
        throw DictionaryException("Dictionary is empty");
    }
    root = DeleteNode(root, key);
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::TryRemove(Key key) {
    if (Contains(key)){
        Remove(key);
        return true;
    }
    return false;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::Clear() {
    if (IsEmpty()){
        return;
    }
    while(root){
        root = DeleteNode(root, root->key);
    }
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::Count(Node *node) {
    if(node == nullptr){
        return 0;
    }
    return 1 + Count(node->right) + Count(node->left);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::Count() {
    return Count(root);
}

template<typename Key, typename Info>
std::string Dictionary<Key, Info>::PrintAll(bool keysOnly) {
    if (IsEmpty()){
        return "";
    }
    return PrintInOrder(root, keysOnly);
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::InsertNode(Node* node, Key &key, Info &info) {
    if (node == nullptr) {
        return new Node(key, info);
    }

    if (key < node->key)
        node->left = InsertNode(node->left, key, info);
    else if (key > node->key)
        node->right = InsertNode(node->right, key, info);
    else 
        throw new DictionaryException("Key already exists");

    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
    int balance = GetBalance(node);

    if (balance > 1 && key < node->left->key)
        return RotateRight(node);

    if (balance < -1 && key > node->right->key)
        return RotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }
    return node;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::Insert(Key key, Info info) {
    auto node = InsertNode(root, key, info);
    root = node;
}
template<typename Key, typename Info>
bool Dictionary<Key, Info>::TryInsert(Key key, Info info) {
    if (!Contains(key)){
        Insert(key, info);
        return true;
    }
    return false;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::RotateLeft(Node *node) {
    Node *right = node->right;
    Node *left = right->left;

    right->left = node;
    node->right = left;

    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    right->height = std::max(GetHeight(right->left), GetHeight(right->right)) + 1;

    return right;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::RotateRight(Node *node) {
    Node *left = node->left;
    Node *right = left->right;

    left->right = node;
    node->left = right;

    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    left->height = std::max(GetHeight(left->left), GetHeight(left->right)) + 1;

    return left;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::DeleteNode(Dictionary::Node *node, Key &key) {
    if (node == nullptr)
        return node;

    if (key < node->key) {
        node->left = DeleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = DeleteNode(node->right, key);
    } else {
        if (node->right == nullptr || node->left == nullptr) {
            Node *tmpNode = node->left ? node->left : node->right;

            if (tmpNode == nullptr) {
                tmpNode = node;
                node = nullptr;
            } else {
                *node = *tmpNode;
            }

            delete tmpNode;
        } else {
            Node* tmpNode = GetMinKeyNode(node->right);
            node->key = tmpNode->key;
            node->right = DeleteNode(node->right, tmpNode->key);
        }
    }

    if (node == nullptr)
        return node;

    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
    int balance = GetBalance(node);

    if (balance > 1 && GetBalance(node->left) >= 0)
        return RotateRight(node);

    if (balance > 1 && GetBalance(node->left) < 0) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    if (balance < -1 && GetBalance(node->right) <= 0)
        return RotateLeft(node);

    if (balance < -1 && GetBalance(node->right) > 0) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    return node;
}

template<typename Key, typename Info>
std::string Dictionary<Key, Info>::PrintInOrder(Dictionary::Node *node, bool keysOnly) {
    std::stringstream stream;
    if (node) {
        stream << PrintInOrder(node->left, keysOnly);
        if (keysOnly)
            stream << (node->left ? ", " : "") << node->key << (node->right ? ", " : "");
        else
            stream << "(" << node->key << ", " << node->info << ")" << std::endl;
        stream << PrintInOrder(node->right, keysOnly);
    }
    return stream.str();
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::TryRemoveFromTarget(Node *node, Dictionary &target) {
    if (node) {
        TryRemoveFromTarget(node->left, target);
        target.TryRemove(node->key);
        TryRemoveFromTarget(node->right, target);
    }
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Contains(Dictionary::Node *node, Key &key) {
    if (node){
        if (key < node->key)
            return Contains(node->left, key);
        else if (key > node->key)
            return Contains(node->right, key);
        else
            return true;
    }
    return false;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Contains(Key key) {
    if (IsEmpty()){
        return false;
    }
    return Contains(root, key);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::Copy(Node *node, Dictionary &target) {
    if (node) { // using preorder to copy.
        target.TryInsert(node->key, node->info);
        Copy(node->left, target);
        Copy(node->right, target);
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::Copy(Dictionary &target, bool clearTarget) {
    if (clearTarget)
        target.Clear();

    if (root)
        Copy(root, target);
}

template<typename Key, typename Info>
Info Dictionary<Key, Info>::DictionaryEnumerator::GetCurrentInfo() {
    if (currentNode) {
        return currentNode->info;
    }
    throw DictionaryException("Current Enumerator element is null");
}

template<typename Key, typename Info>
Key Dictionary<Key, Info>::DictionaryEnumerator::GetCurrentKey() {
    if (currentNode) {
        return currentNode->key;
    }
    throw DictionaryException("Current Enumerator element is null");
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::DictionaryEnumerator::MoveRight() {
    if (CanMoveRight()) {
        this->currentNode = this->currentNode->right;
    }else{
        throw DictionaryException("Cannot MoveRight");
    }
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::DictionaryEnumerator::MoveLeft() {
    if (CanMoveLeft()) {
        this->currentNode = this->currentNode->left;
    }else{
        throw DictionaryException("Cannot MoveLeft");
    }
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::DictionaryEnumerator::CanMoveRight() {
    return currentNode && currentNode->right;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::DictionaryEnumerator::CanMoveLeft() {
    return currentNode && currentNode->left;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::DictionaryEnumerator::MoveToKey(Key key) {
    auto *node = SearchKey(*root, key);
    if (!node){
        throw DictionaryException("Key not found");
    }
    currentNode = node;
}
#endif //PW_EADS_LABS_DICTIONARY_HH
