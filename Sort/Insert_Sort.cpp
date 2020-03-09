#include <iostream>
#include <vector>
template<class T>
void InsertSort(std::vector<T> &v){
    for(int i = 1; i < v.size(); i++){
        for(int j = i - 1; j > 0 && v[j] < v[j - 1]; j--){
            std::swap(v[j],v[j - 1]);
        }
    }
}
int main()
{
    std::vector<int> v{1,4,3,2,8,7,0};
    InsertSort(v);
    for(auto &e : v){
        std::cout << e << std::endl;
    }
    return 0;
}

