#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int palce_start_p(vector<int> &a, int left, int right)
{
    int pivot = a[left];
    int L = left, R = right;
    while (L < R)
    {
        while (L < R && a[R] >= pivot)
        {
            R--;
        }
        if (L < R)
        {
            a[L] = a[R];
            L++;
        }
        while (L < R && a[L] <= pivot)
        {
            L++;
        }
        if (L < R)
        {
            a[R] = a[L];
            R--;
        }
    }
    a[L] = pivot;
    return L;
}
void qsort(vector<int> &a, int left, int right)
{
    if (left >= right)
        return;
    int pivotIdx = palce_start_p(a, left, right);
    qsort(a, left, pivotIdx - 1);
    qsort(a, pivotIdx + 1, right);
}

void quickSort(vector<int> &nums)
{
    qsort(nums, 0, nums.size() - 1);
}
void merge(vector<int>& a, int left, int mid, int right, vector<int>& temp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (int p = left; p <= right; ++p) a[p] = temp[p];
}

void mergeSort(vector<int>& a, int left, int right, vector<int>& temp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid, temp);
    mergeSort(a, mid + 1, right, temp);
    merge(a, left, mid, right, temp);
}

void mergeSort(vector<int> &a) {
        vector<int> temp(a.size());
    mergeSort(a, 0, a.size() - 1, temp);

}
void heapify(vector<int> &a, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left] > a[largest])
        largest = left;
    if (right < n && a[right] > a[largest])
        largest = right;
    if (largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int> &a)
{
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}
void selectionSort(vector<int> &nums)
{
    for (int i = 0; i + 1 < nums.size(); i++)
    {
        int min_index = i;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] < nums[min_index])
            {
                min_index = j;
            }
        }
        swap(nums[i], nums[min_index]);
    }
}
void bubbleSort(vector<int> &nums)
{
    for (size_t i = 0; i + 1 < nums.size(); i++)
    {
        bool swapped = false;
        for (size_t j = 0; j + 1 < nums.size() - i; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void insertionSort(vector<int> &a)
{
    int n = a.size();
    for (int i = 1; i < n; i++)
    {
        int temp = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}
void shellSort(vector<int> &a)
{
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

using SortFunc = void (*)(vector<int> &);

struct SortTask
{
    string name;
    SortFunc func;
    bool enabled;
};

void writeVector(ofstream &outFile, const vector<int> &nums)
{
    for (size_t i = 0; i < nums.size(); ++i)
    {
        if (i)
        {
            outFile << ' ';
        }
        outFile << nums[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums = {3, 5, 3, 2, 5, 9, 6, 8, 45, 7, 3, 3, 5, 8, 1, 2, 5, 3, 6, 8, 0, 7, 5};
    vector<int> sortedNums = nums;
    sort(sortedNums.begin(), sortedNums.end());

    for (int i = 0; i < nums.size(); ++i)
    {
        if (i)
        {
            cout << ' ';
        }
        cout << sortedNums[i];
    }
    cout << '\n';

    const vector<SortTask> tasks = {
        {"quickSort", quickSort, true},
        {"mergeSort", mergeSort, true},
        {"heapSort", heapSort, false},
        {"selectionSort", selectionSort, true},
        {"bubbleSort", bubbleSort, true},
        {"insertionSort", insertionSort, true},
        {"shellSort", shellSort, true},
    };

    ofstream outFile("sort_times.txt");
    if (outFile)
    {
        for (const auto &task : tasks)
        {
            if (!task.enabled || !task.func)
            {
                continue;
            }

            vector<int> data = nums;
            auto start = chrono::steady_clock::now();
            task.func(data);
            auto finish = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
            outFile << task.name << '\n';
            outFile << "time: " << elapsed << " us\n";
            outFile << "result: ";
            writeVector(outFile, data);
            outFile << "\n\n";
        }
    }

    return 0;
}
