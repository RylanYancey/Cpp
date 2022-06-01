
#include <iostream>
using namespace std;

int main() {
    int size;
    cout << "length of array" << endl;
    cin >> size;

    int *array = (int *)malloc(sizeof(int));

    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

    for (int i = 0; i < 10; i++) {
        cout << array[i] << endl;
    }
}