#include <iostream>
#include <chrono>

//SHELL SORT
void shellSort(int arr[], int n)
{
    int gap = n/2;

    while (gap>0)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j-gap] > temp)
            {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}


//MERGE SORT
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
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

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

//Binary Tree Sort
struct Node
{
    int key;
    struct Node *left, *right;
};
  
struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void storeSorted(Node *root, int arr[], int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}
Node* insert(Node* node, int key)
{
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key);
  
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
  
    /* return the (unchanged) Node pointer */
    return node;
}
  
// This function sorts arr[0..n-1] using Tree Sort
void treeSort(int arr[], int n)
{
    struct Node *root = NULL;
  
    // Construct the BST
    root = insert(root, arr[0]);
    for (int i=1; i<n; i++)
        root = insert(root, arr[i]);
  
    // Store inorder traversal of the BST
    // in arr[]
    int i = 0;
    storeSorted(root, arr, i);
}


//RADIX SORT
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using
// Radix Sort
void radixSort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}


//QUICK SORT
int partition(int arr[], int start, int end)
{
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(int arr[], int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}

//HEAP SORT
void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root Since we are using 0 based indexing
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
 
// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {10, 8, 17, 2, 19, 21, 30};
    int n = sizeof(arr)/sizeof(arr[0]);
    std::cout << "Array sebelum diurutkan: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl << std::endl;


    //SHELL SORT
    std::cout << "Shell sort: \n";
    int arr1[] = {10, 8, 17, 2, 19, 21, 30};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    auto begin = std::chrono::high_resolution_clock::now();
    shellSort(arr1, n1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "Array setelah diurutkan: ";
    for (int i = 0; i < n1; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Execution time: " << duration.count() << " Nanoseconds\n\n";


    //MERGE SORT
    int arr2[] = {10, 8, 17, 2, 19, 21, 30};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    std::cout << "Merge sort: \n";

    begin = std::chrono::high_resolution_clock::now();
    mergeSort(arr2, 0, n2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "Array setelah diurutkan: ";
    for (int i = 0; i < n2; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Execution time: " << duration.count() << " Nanoseconds\n\n";
    

    //BINARY TREE SORT
    int arr3[] = {10, 8, 17, 2, 19, 21, 30};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    std::cout << "Binary tree sort: \n";

    begin = std::chrono::high_resolution_clock::now();
    treeSort(arr3, n3);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "Array setelah diurutkan: ";
    for (int i = 0; i < n3; i++)
    {
        std::cout << arr3[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Execution time: " << duration.count() << " Nanoseconds\n\n";
    

    //RADIX SORT
    int arr4[] = {10, 8, 17, 2, 19, 21, 30};
    int n4 = sizeof(arr3)/sizeof(arr3[0]);
    std::cout << "Radix sort: \n";

    begin = std::chrono::high_resolution_clock::now();
    radixSort(arr4, n3);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "Array setelah diurutkan: ";
    for (int i = 0; i < n3; i++)
    {
        std::cout << arr4[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Execution time: " << duration.count() << " Nanoseconds\n\n";
    

    //QUICK SORT
    int arr5[] = {10, 8, 17, 2, 19, 21, 30};
    int n5 = sizeof(arr3)/sizeof(arr3[0]);
    std::cout << "Quick sort: \n";

    begin = std::chrono::high_resolution_clock::now();
    quickSort(arr5,0, n5);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "Array setelah diurutkan: ";
    for (int i = 0; i < n3; i++)
    {
        std::cout << arr5[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Execution time: " << duration.count() << " Nanoseconds\n\n";
    
    //HEAP SORT
    int arr6[] = {10, 8, 17, 2, 19, 21, 30};
    int n6 = sizeof(arr3)/sizeof(arr3[0]);
    std::cout << "Heap sort: \n";

    begin = std::chrono::high_resolution_clock::now();
    heapSort(arr6, n5);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "Array setelah diurutkan: ";
    for (int i = 0; i < n3; i++)
    {
        std::cout << arr6[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Execution time: " << duration.count() << " Nanoseconds\n\n";
    
    return 0;
}
