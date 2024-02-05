#ifndef JSON_STRUCT_DEF_H_
#define JSON_STRUCT_DEF_H_

#include "struct_def.h"
#include <iterator>

template <class T>
struct CommonIterator {
    public:
        explicit CommonIterator(T* pointer) : ptr(pointer) {}

        CommonIterator& operator++() {
            ++ptr;
            return *this;
        }

        T& operator*() {
            return *ptr;
        }
        bool operator!=(const CommonIterator& other) const {
            return ptr != other.ptr;
        }

    private:
        T* ptr;
};


class JsonLogin : public CommonIterator<Login> {
    private:
        Login* data;
        size_t size;

    public:
        explicit JsonLogin(Login* login, size_t login_size) : CommonIterator(login), data(login), size(login_size) {}
        CommonIterator<Login> begin() {
            return CommonIterator(data);
        }
        CommonIterator<Login> end() {
            return CommonIterator(data+size);
        }
};


#endif

