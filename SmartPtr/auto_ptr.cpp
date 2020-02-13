#include<iostream>
template<class T>
class Auto_ptr{
    public:
        Auto_ptr(T* ptr = nullptr):_ptr(ptr){}
        ~Auto_ptr(){if(_ptr) delete _ptr;}
        Auto_ptr(Auto_ptr<T> &ap)
          :_ptr(ap._ptr)
        {
            ap._ptr = nullptr;
        }
        Auto_ptr<T>& operator=(Auto_ptr<T> &ap){
            if(this != ap){
                if(_ptr)
                  delete _ptr;
                _ptr = ap._ptr;
                ap._ptr = nullptr;
            }
            return *this;
        }
        T& operator*(){
            return *_ptr;
        }
        T& operator->(){
            return _ptr;
        }
    private:
        T *_ptr;
};
class A{
public:
    A(){std::cout << "A()" << std::endl;}
    ~A(){std::cout << "~A()" << std::endl;}
    int m;
};
int main()
{
    Auto_ptr<A> a(new A);
    Auto_ptr<A> copy(a);
//    a->m = 100;
    return 0;
}
