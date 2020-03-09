#include <iostream>
#include <vector>
template<class T>
void SelectSort(std::vector<T> &v){
    for(int i = 0; i < v.size(); i++){
        int min = i;
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < v[min]){
                min = j;
            } 
        }
        std::swap(v[i],v[min]);
    }
}
int main()
{
    std::vector<int> v{1,4,5,2,3,8,7};
    SelectSort(v);
    for(auto &e : v){
        std::cout << e ;
    }
    return 0;
}

