#pragma once
using namespace std;
template <class T>
void BubbleSort(T& arr, int Size)
{
    for (int i = 0; i < Size; i++)
        for (int j = i; j < Size; j++)
            if (arr[j] < arr[i])swap(arr[i], arr[j]);
}
template <class T>
int Partition(T& arr, int low, int high)
{
    // pivot (Element to be placed at right position)
    T pivot = &arr[high];
    int i = low - 1;  // Index of smaller element
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= *pivot)
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
template <class T>
/* low  --> Starting index,  high  --> Ending index */
void QuickSort(T& arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);  // Before pi
        QuickSort(arr, pi + 1, high); // After pi
    }
}
template <class T>
void merge(T* arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    /* create temp arrays */
    T L[n1], R[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
template <class T>
void MergeSort(T* arr, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
template <class T>
void CockTailSort(T& arr, int Size)
{
    for (int l = 0, r = Size - 1; l < r;)
    {
        for (int i = l; i < r; i++)
            if (arr[i + 1] < arr[i])swap(arr[i], arr[i + 1]);
        r--;
        for (int i = r; i > l; i--)
            if (arr[i] < arr[i - 1])swap(arr[i], arr[i - 1]);
        l++;
    }
}
template <class T>
void ShellSort(T& arr, int Size)
{
    for (int i = Size >> 1; i; i >>= 1)
        for (int j = i; j < Size; j++)
            for (int k = j; k >= i && (arr[k] < arr[k - i]); k -= i)
                swap(arr[k], arr[k - i]);
}