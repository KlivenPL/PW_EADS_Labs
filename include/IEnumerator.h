//
// Created by oskar on 29.04.2020.
//

#ifndef CPPZADANIA_IENUMERATOR_H
#define CPPZADANIA_IENUMERATOR_H

template<typename TKey, typename TInfo>
class IEnumerator {
public:
    virtual TKey GetCurrentKey() = 0;
    virtual TInfo GetCurrentInfo() = 0;
    virtual void MoveNext() = 0;
    virtual void MoveBack() = 0;
    virtual bool IsAny() = 0;
    virtual bool CanMove() = 0;
};

#endif //CPPZADANIA_IENUMERATOR_H
