#include <iostream>
#include <vector>
void QuickSort(std::vector<int> &a,int left,int right){
    if(left >= right)return;
    int key = a[left];
    int i = left;
    int j = right;
    while(i < j){
        while(i < j && key <= a[j]){
            j--;
        }
        a[i] = a[j];
        while(i < j && key >= a[i]){
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    QuickSort(a,left,key - 1);
    QuickSort(a,key + 1,right);
}
int main()
{
    std::vector<int> a{2,1,5,6,3,4,8,7,9,0};
    QuickSort(a,0,a.size());
    for(auto &e : a){
        std::cout << e << std::endl;
    }
    return 0;
}

