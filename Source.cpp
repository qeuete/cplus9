#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>

using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& arr) {
        MergeSortRecursive(arr, 0, arr.size() - 1);
    }

private:
    void MergeSortRecursive(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSortRecursive(arr, left, mid);
            MergeSortRecursive(arr, mid + 1, right);
            int n1 = mid - left + 1;
            int n2 = right - mid;

            vector<int> L(n1), R(n2);

            for (int i = 0; i < n1; i++)
                L[i] = arr[left + i];
            for (int j = 0; j < n2; j++)
                R[j] = arr[mid + 1 + j];

            int i = 0, j = 0, k = left;
            while (i < n1 && j < n2) {
                if (L[i] <= R[j]) {
                    arr[k] = L[i];
                    i++;
                }
                else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            }

            while (i < n1) {
                arr[k] = L[i];
                i++;
                k++;
            }

            while (j < n2) {
                arr[k] = R[j];
                j++;
                k++;
            }
        }
    }
};

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    vector<int> arr(10);
    cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }

    MergeSort mergeSort;

    auto sortFunc = [&mergeSort, &arr]() {
        mergeSort.Sort(arr);
        };

    thread mergeSortThread(sortFunc);

    if (mergeSortThread.joinable()) {
        mergeSortThread.join();
    }
    else {
        cerr << "Ошибка: Невозможно создать поток для сортировки." << endl;
        return 1;
    }

    cout << "Отсортированный массив: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}