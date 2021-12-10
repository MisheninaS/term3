#include <iostream>
using namespace std;
template <class T>


class Vector{
public:
    T* arr;
    int len = 0;
    Vector() {};
    void push_back(T el) {
        arr[len] = el;
        len++;
    }
    void pop_back() {
        len--;
    }
    void insert(int pos, T el) {
        if (pos > len) {
            cout << "-1";
        } else {
            for (int i = len; i < pos + 1; i++) {
                arr[i + 1] = arr[i];
            }
            arr[pos] = el;
        }
    }
    void print() {
        for (int i = 0; i < len; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};
int main() {
    Vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.print();
    v.pop_back();
    v.print();
    v.insert(0, 8);
    v.print();
}
