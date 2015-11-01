#include <iostream>
#include <fstream>
#include <iomanip>
#include <array>

using namespace std;
int swaps(0);

int partition(int array[], int l, int r) {

    int m = (l + r) / 2;

    if (array[m] < array[l]) {
        std::swap(array[l], array[m]);
    }
    if (array[r] < array[l]) {
        std::swap(array[l], array[r]);
    }
    if (array[r]<array[m]){
        std::swap(array[m], array[r]);
    }

    std:swap(array[m], array[l]);
    int pivot = array[l];
    int i = l + 1;

    for (int j = l+1; j <= r; j++) {
        if (array[j] < pivot) {
            std::swap(array[j], array[i]);
            i++;
        }
    }
    std::swap(array[l], array[i-1]);
    return (i-1);
}

int quicksort(int arr[], int l, int r) {

    if (r < l) {
        return 0;
    }
    swaps += r - l;
    
    int pIndex = partition(arr, l, r);
    quicksort(arr, l, pIndex-1);
    quicksort(arr, pIndex+1, r);

    return swaps;
}

int main() {
    //define the size of the array
    int arr[10000];
    //counter
    int i = 0;
    //reading in the external file
    ifstream myfile;
    myfile.open("C:\\Path\\To\\File\\QuickSort.txt", ios::in);
    while (myfile.good()) {
        myfile >> arr[i];
        i++;
    }

    int size = sizeof(arr) / sizeof(arr[0]);
    int swaps = quicksort(arr, 0, size-1);

    std::cout << "Minimum swaps are: " << swaps << std::endl;

    return 0;
}