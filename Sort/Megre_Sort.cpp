#include <iostream>
#include <vector>

void Merge(std::vector<int>&a,int left, int right, int mid){
    int index1 = left;
    int index2 = mid + 1; 
    int k = 0;
    std::vector<int> temp(right - left + 1,0);
    while(index1 <= mid && index2 <= right){
        if(a[index1] < a[index2]){
            temp[k++] = a[index1++];
        }else{
            temp[k++] = a[index2++];
        }
    }
    while(index1 <= mid){
        temp[k++] = a[index1++];
    }
    while(index2 <= right){
        temp[k++] = a[index2++];
    }
    for(int i = left, k = 0; i <= right; i++,k++){
        a[i] = temp[k];
    }
}
void MergeSort(std::vector<int>&a,int left,int right){
    if(left >= right) return;
    int mid = (left + right) / 2;
    MergeSort(a,left,mid);
    MergeSort(a,mid+1,right);
    Merge(a,left,right,mid);
}

int main()
{
    std::vector<int> v{3,1,2,4,0,6,5,8,7,9};
    MergeSort(v,0,v.size());
    for(auto &e : v)
        std::cout << e << std::endl;
    return 0;
}

