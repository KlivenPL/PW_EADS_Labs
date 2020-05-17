//
// Created by oskar on 17.05.2020.
//

#ifndef PW_EADS_LABS_SPLIT_H
#define PW_EADS_LABS_SPLIT_H
#include "Ring.h"
#include <string>
#include <iostream>

template<typename Key, typename Info>
class RingExtentionMethods {
private:
    void MoveEnumerator(bool direction, std::unique_ptr<IEnumerator<Key,Info>> &enumerator);

    void PushElement(bool direction, Ring<Key, Info> &ring, std::unique_ptr<IEnumerator<Key,Info>> &enumerator);
public:
    void Split(const Ring<Key, Info> &source, int startIndex, int length, bool direction, Ring<Key, Info> &result1, int step1,
          bool direction1, Ring<Key, Info> &result2, int step2, bool direction2);
};

template<typename Key, typename Info>
void RingExtentionMethods<Key, Info>::MoveEnumerator(bool direction, std::unique_ptr<IEnumerator<Key, Info>> &enumerator) {
    if (direction){
        enumerator->MoveNext();
    } else {
        enumerator->MoveBack();
    }
}

template<typename Key, typename Info>
void RingExtentionMethods<Key, Info>::PushElement(bool direction, Ring<Key, Info> &ring, std::unique_ptr<IEnumerator<Key, Info>> &enumerator) {
    if (direction){
        ring.PushBack(enumerator->GetCurrentKey(), enumerator->GetCurrentInfo());
    } else {
        ring.PushFront(enumerator->GetCurrentKey(), enumerator->GetCurrentInfo());
    }
}

template<typename Key, typename Info>
void RingExtentionMethods<Key, Info>::Split(const Ring<Key, Info> &source, int startIndex, int length, bool direction,
        Ring<Key, Info> & result1, int step1, bool direction1, Ring<Key, Info> & result2, int step2, bool direction2) {
    if (source.IsEmpty()) {
        throw typename Ring<Key, Info>::RingException("Cannot split empty Ring");
    }
    if (!result1.IsEmpty()) {
        result1.Clear();
    }
    if (!result2.IsEmpty()) {
        result2.Clear();
    }
    auto e1 = const_cast<Ring<Key, Info>*>(&source)->GetEnumerator(startIndex);
    int currLength = 0;
    while (currLength < length) {
        for (int i = 0; i < step1 && currLength < length; ++i) {
            PushElement(direction1,result1, e1);
            MoveEnumerator(direction, e1);
            currLength++;
        }

        for (int i = 0; i < step2 && currLength < length; ++i) {
            PushElement(direction2, result2, e1);
            MoveEnumerator(direction, e1);
            currLength++;
        }
    }
    if (!direction1){
        result1.Rotate(false);
    }

    if (!direction2){
        result2.Rotate(false);
    }
}

#endif //PW_EADS_LABS_SPLIT_H
