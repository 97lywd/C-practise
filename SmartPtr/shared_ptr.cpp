#include<mutex>
#include<thread>
#include <iostream>
template<class T>
class SharedPtr{
    public:
        SharedPtr(T* ptr = nullptr)
          :_ptr(ptr)
          ,_count(new int(1))
          ,_mutex(new std::mutex)
        {}
        SharedPtr(const SharedPtr<T>& sp)
          :_ptr(sp._ptr)
          ,_count(sp._count)
          ,_mutex(sp._mutex)
        {
            AddCount();
        }
        SharedPtr<T>& operator=(const SharedPtr<T>& sp){
            if(_ptr != sp._ptr){
                Release();
                _ptr = sp._ptr;
                _count = sp._count;
                _mutex = sp._mutex;
                AddCount();
            }
            return *this;
        }
        ~SharedPtr(){
            Release();
        }
        T& operator*(){return *_ptr;}
        T& operator->(){return _ptr;}
        int usecount(){return *_count;}
        T* Get(){return _ptr;}
    private:
        void AddCount(){
            _mutex->lock();
            (*_count)++;
            _mutex->unlock();
        }
        void Release(){
            bool deletefg = false;
            _mutex->lock();
            if(--(*_count) == 0){
               delete _ptr;
               delete _count;
               deletefg = true;
            }
            _mutex->unlock();
            if(deletefg == true)
               delete _mutex;
        }
    private:
        T* _ptr;
        int* _count;
        std::mutex* _mutex;
};


int main()
{
  SharedPtr<int> sp(new int(10));
  SharedPtr<int> sp2(sp);
  *sp2 = 20;
  std::cout << "usecount" << sp.usecount() << std::endl;
  std::cout << "usecount" << sp2.usecount() << std::endl;
  std::cout << *sp << std::endl;
  std::cout << *sp2 << std::endl;
  return 0;
}


