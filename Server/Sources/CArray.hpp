//
// Created by theo.zapata on 9/24/19.
//

#ifndef CPP_BABEL_2019_CARRAY_HPP
#define CPP_BABEL_2019_CARRAY_HPP

#include <stdint-gcc.h>

namespace Babel {
    namespace Network {
        template <typename T>
        class cArray {
        public:
            T *data = nullptr;

            explicit cArray(uint32_t size);
            void addElement(T element);
            void removeAt(uint32_t pos);

        private:
            uint32_t _len;  // Number of element
            uint32_t _size; // Size available in memory
        };
    }
}


#endif //CPP_BABEL_2019_CARRAY_HPP
