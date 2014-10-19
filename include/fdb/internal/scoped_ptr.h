#ifndef INCLUDE_FDB_INTERNAL_PTR_SCOPEDPTR_H
#define INCLUDE_FDB_INTERNAL_PTR_SCOPEDPTR_H

namespace fdb {
namespace internal {

    template <class T>
    class scoped_ptr {
    protected:
        T* ptr_ = nullptr;
    public:
        virtual operator T* () const;
        virtual operator T** () const;
        virtual scoped_ptr& operator= (T* rhs);
    };

    template <class T>
    scoped_ptr<T>::operator T* () const {
        return ptr_;
    }

    template <class T>
    scoped_ptr<T>::operator T** () const {
        return const_cast<T**>(&ptr_);
    }

    template <class T>
    scoped_ptr<T>& scoped_ptr<T>::operator= (T* rhs) {
        ptr_ = rhs;
        return *this;
    }
}}
#endif