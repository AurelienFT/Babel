//
// Created by theo.zapata on 9/24/19.
//

#include <cstdlib>
#include <stdexcept>
#include "CArray.hpp"


template<typename T>
Babel::Network::cArray<T>::cArray(uint32_t size) : _size(size)
{
    _len = 0;
    data = std::malloc(sizeof(T) * size);

    if (data == nullptr)
        throw std::runtime_error("Memory allocation Error");
}

template<typename T>
void Babel::Network::cArray<T>::addElement(T element)
{
    if (_len >= _size) {
        // TODO copy array and realloc
    }

}
