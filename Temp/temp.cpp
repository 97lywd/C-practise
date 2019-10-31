/*
 * Illustrates a template template parameter
 *
 */
#include<cstddef>
#include<iostream>
template<class T>
class Array{
    private:
       enum {INIT = 1};
       T* _data;
       size_t _capacity;
       size_t _count;
    public:
        Array(){
            _count = 0;
            _capacity = INIT;
           _data = new T[_capacity];
        }
        ~Array(){delete[]_data;}
        void push_back(const T& t){
            if(_count = _capacity){
            size_t newCap = 2 * _capacity;
            T* newData = new T[newCap];
            for(size_t i = 0; i < _count; i++){
                newData[i] = _data[i];
            }
            delete[]_data;
            _data = newData;
            _capacity = newCap;
            }
            _data[_count] = t;
            _count++;
        }
        void pop_back(){
            if(_count > 0)
                _count--;
        }
        T* begin(){return _data;}
        T* end(){return _data + _count;}
};

template<class T, template<class> class Seq>
class Container{
    private:
        Seq<T> seq;
    public:
        void append(const T& t){seq.push_back(t);}
        T* begin(){return seq.begin();}
        T* end(){return seq.end();}
};


int main()
{
    Container<int,Array> container;
    container.append(1);
    container.append(2);
    container.append(3);
    container.append(4);
    int *p = container.begin();
    while(p != container.end())
        std::cout << *p++ << "\n";
    return 0;
}
