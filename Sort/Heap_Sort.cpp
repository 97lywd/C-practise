#include <iostream>
#include <vector>
void AdjustDown(std::vector<int> &v){
    int r = v.size() - 1;
    int key = v[r];
    int parent = (r - 1) / 2;
    while(parent >= 0 && key < v[parent]){
        std::swap(v[parent],v[r]);
        r = parent;
        parent = (r - 1) / 2;
        key = v[r];
    }
}
void Create(std::vector<int> &v){
    AdjustDown(v);
}
int main()
{
    std::vector<int> v{1,8,7,30,10,15,4};
    Create(v);
    for(auto &e : v){
        std::cout << e << std::endl;
    }
    return 0;
}

