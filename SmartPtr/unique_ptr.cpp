#include<iostream>
template<class T> 
class UniquePtr{
    UniquePtr(T* ptr = nullptr)
        :_ptr(ptr){}
    ~UniquePtr(){if(_ptr) delete _ptr;}
    T& operator*(){return *_ptr;}
    T* operator->(){return _ptr;}
    private:
        UniquePtr(UniquePtr<T>const &) = delete;
        UniquePtr& operator=(UniquePtr<T>const &) = delete;
    private:
        T *_ptr;
};

int main()
{
    return 0;
}
