//
// Created by oskar on 29.04.2020.
//

#ifndef CPPZADANIA_IENUMERATOR_H
#define CPPZADANIA_IENUMERATOR_H

#include <functional>

template<typename TKey, typename TInfo>
class IEnumerator {
public:
    virtual TKey GetCurrentKey() = 0;
    virtual TInfo GetCurrentInfo() = 0;
    virtual void MoveRight() = 0;
    virtual void MoveLeft() = 0;
    virtual bool CanMoveRight() = 0;
    virtual bool CanMoveLeft() = 0;
    virtual void MoveToKey(TKey key) = 0;
};

#endif //CPPZADANIA_IENUMERATOR_H
