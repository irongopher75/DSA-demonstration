#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
class Array_ADT{
    private:
    int*arr;
    int capacity;
    int size;
    int resized;
    vector<int>logDelete;
    //Sorting Algorithms
    void bubbleSort() {
        cout << "Initial Array: ";
        displayArr();
        for (int i = 0; i < size - 1; ++i) {
            bool swapped = false;
            cout << "\nPass " << i + 1 << ":\n";
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    cout << "Swapping " << arr[j] << " and " << arr[j + 1] << "\n";
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
                displayArr();
            }
            if (!swapped) {
                cout << "No swaps done. Array is sorted.\n";
                break;
            }
        }
    }
    void insertionSort() {
        cout << "Initial Array: ";
        displayArr();
        for (int i = 1; i < size; ++i) {
            int key = arr[i];
            int j = i - 1;
            cout << "\nInserting " << key << " into the sorted subarray\n";
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
                displayArr();
            }
            arr[j + 1] = key;
            displayArr();
        }
    }
    void selectionSort() {
        cout << "Initial Array: ";
        displayArr();
        for (int i = 0; i < size - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < size; ++j) {
                if (arr[j] < arr[minIdx]) minIdx = j;
            }
            cout << "\nSwapping " << arr[i] << " with minimum " << arr[minIdx] << "\n";
            swap(arr[i], arr[minIdx]);
            displayArr();
        }
    }
    //MergeSort
    void mergeSort() {
        cout << "Initial Array: ";
        displayArr();
        mergeSortHelper(0, size - 1);
    }
    void mergeSortHelper(int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortHelper(left, mid);
        mergeSortHelper(mid + 1, right);
        merge(left, mid, right);
    }
    void merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        int* L = new int[n1];
        int* R = new int[n2];
        for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
        for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
        cout << "\nMerging: ";
        for (int i = 0; i < n1; ++i) cout << L[i] << " ";
        cout << "and ";
        for (int i = 0; i < n2; ++i) cout << R[i] << " ";
        cout << "\n";
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
        delete[] L;
        delete[] R;
        cout << "Result: ";
        displayArr();
    }
    //QuickSort
    void quickSort() {
        cout << "Initial Array: ";
        displayArr();
        quickSortHelper(0, size - 1);
    }
    void quickSortHelper(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            cout << "\nPivot placed at index " << pi << "\n";
            displayArr();
            quickSortHelper(low, pi - 1);
            quickSortHelper(pi + 1, high);
        }
    }
    int partition(int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        cout << "\nPartitioning with pivot " << pivot << "\n";
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
                displayArr();
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    //Searching Algorithms
    int binarySearch(int value) {
        int left = 0, right = size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            cout << "Checking index " << mid << " with value " << arr[mid] << endl;
            if (arr[mid] == value) return mid;
            if (value > arr[mid]) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
    int linearSearch(int value) {
        for (int i = 0; i < size; i++) {
            cout << "Checking index " << i << ": " << arr[i] << endl;
            if (arr[i] == value) return i;
        }
        return -1;
    }
    int jumpSearch(int value) {
        int step = sqrt(size);
        int prev = 0;
        while (arr[min(step, size) - 1] < value) {
            cout << "Jumping from index " << prev << " to " << step << endl;
            prev = step;
            step += sqrt(size);
            if (prev >= size)
                return -1;
        }
        for (int i = prev; i < min(step, size); i++) {
            cout << "Checking index " << i << ": " << arr[i] << endl;
            if (arr[i] == value)
                return i;
        }
        return -1;
    }
    int interpolationSearch(int value) {
        int low = 0, high = size - 1;
        while (low <= high && value >= arr[low] && value <= arr[high]) {
            if (arr[low] == arr[high]) {
                if (arr[low] == value) return low;
                else break;
            }
            int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (value - arr[low]);
            if (pos < 0 || pos >= size) break;
            cout << "Probing index " << pos << " with value " << arr[pos] << endl;
            if (arr[pos] == value) return pos;
            if (arr[pos] < value) low = pos + 1;
            else high = pos - 1;
        }
        return -1;
    }

    
    public:
    Array_ADT(int initialCapacity=10){
        capacity=initialCapacity;
        arr = new int[capacity];
        size =0;
        resized=0;
    }
    void resize(int newCapacity){
        int *newArr= new int[newCapacity];
        for(int i =0;i<size;i++){
            newArr[i]=arr[i];
        }
        delete[] arr;
        arr=newArr;
        capacity = newCapacity;
        resized++;
    }
    void insertElement(int value){
        if(size==capacity){
            resize(size * 2);// resize the array by two times its actual memory everytime it runsout
        }
        arr[size++]=value;
    }
    void insertElements(int num=0){
        if(capacity<num){
            resize(num);
        }
        int element=0;
        for(int i =size;i<num;i++){
            cout<<"Enter the "<<i+1<<"th Element";
            cin>>element;
            insertElement(element);
        }
    }
    void Sorting() {
        int option;
        cout << "Choose Sorting Algorithm:\n";
        cout << "1.Bubble Sort\n";
        cout << "2.Insertion Sort\n";
        cout << "3.Selection Sort\n";
        cout << "4.Merge Sort\n";
        cout << "5.Quick Sort\n";
        cout << "Enter your choice (1-5): ";
        cin >> option;
        switch(option) {
            case 1:
                bubbleSort();
                break;
            case 2:
                insertionSort();
                break;
            case 3:
                selectionSort();
                break;
            case 4:
                mergeSort();
                break;
            case 5:
                quickSort();
                break;
            default:
                cout << "Invalid choice. Please select a number between 1 and 5.\n";
                return;
        }

        cout << "\nFinal Sorted Array:\n";
        displayArr();
    }
    void displayArr() {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    void updateAt(int index,int value){
        if(index<0| index>=size){
            cout<<"Index out of bounds";
            cout<<"Re-run the function 0<index<"<<size<<endl;
        }
        arr[index]=value;
    }
    void deleteAt(int index){
        int value=arr[index];
        if(index<0| index>=size){
            cout<<"Index out of bounds";
            cout<<"Re-run the function 0<index<"<<size<<endl;
        }
        for(int i =index;i<size-1;i++){
            arr[i]=arr[i+1];
        }
        size--;
        resize(size);
        logDeleted(value);
    }
    void deleteLastElement(){
        int last=size;
        deleteAt(last);
    }
    bool isSorted(){
        for(int i =0;i<size-1;i++){
            if(arr[i]>arr[i+1]) return false;
        }
        return true;
    }
    int searchFor(int value){
        int index=0;
        if(isSorted()){
            int choice=0;
            cout<<"1.Binary Search\n";
            cout<<"2.Linear Search\n";
            cout<<"3.Jump Search\n";
            cout<<"4.Interpolation Search\n";
            cout<<"Enter the index number of the search needed to be conducted\n";
            cin>>choice;
            switch(choice){
                case 1:
                    index=binarySearch(value);
                    break;
                case 2:
                    index=linearSearch(value);
                    break;
                case 3:
                    index=jumpSearch(value);
                    break;
                case 4:
                    index=interpolationSearch(value);
                    break;
            }
        }
        else{
            cout<<"Running Linear Search\n";
            index=linearSearch(value);
        }
        return index;
    }
    void deleteArray() {
        delete[] arr;
        arr = nullptr;
        size = 0;
        capacity = 0;
        cout << "Array has been deleted.\n";
    }
    void displayInfo(){
        cout<<"Capacity of the Array="<<capacity<<"\n";
        cout<<"Number of elements present in the array="<<size<<"\n";
        cout<<"The array is "<<(isSorted()?"Sorted":"not Sorted")<<"\n";
        cout<<"The array has been resized "<<resized<<" times"<<"\n";
        cout<<"The elements deleted from the array are\n";
        for(int i =0;i<logDelete.size();i++){
            cout<<logDelete[i]<<" ";
        }
        cout<<"\n";
    }
    void logDeleted(int value){
        logDelete.push_back(value);
    }
};
struct Node {
    int data;
    Node* next;
};
class linkedList{
    private:
    Node *head;
    public:
    linkedList(){
        head = nullptr;
    }
    void addElementatTail(int value){
        Node*curr = head;
        Node* newNode = new Node{value, nullptr};
        while(curr!= nullptr){
            curr=curr-> next;
        }
        curr->next = newNode;
    }
    void insertAt(int index,int value){
        Node * curr = head;
        Node* newNode = new Node{value,nullptr};
        int i =0;
        for(i=0;i<index;i++){
            curr = curr->next;
        }
        curr -> next = newNode;
        newNode->next = curr ->next ->next;
    }
};
int main(void) {
    int choice;
    int size;
    string input;
    Array_ADT arr;
    cout << "Enter initial size of array (or press Enter to use default): ";
    getline(cin, input);
    if (!input.empty()) {
        size = stoi(input);
        arr = Array_ADT(size); // overwrite with user-defined size
    }
    do {
        cout << "\nMENU\n";
        cout << "1. Resize\n";
        cout << "2. Insert Element\n";
        cout << "3. Insert Multiple Elements\n";
        cout << "4. Update Element at Index\n";
        cout << "5. Delete Element at Index\n";
        cout << "6. Sort the Array\n";
        cout << "7. Search for an Element\n";
        cout << "8. Check if the Array is Sorted\n";
        cout << "9. View Array Information\n";
        cout << "10. Create New Array\n";
        cout << "11. Delete Current Array\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int newSize;
                cout << "Enter new size: ";
                cin >> newSize;
                arr.resize(newSize);
                break;
            }
            case 2: {
                int val;
                cout << "Enter value to insert: ";
                cin >> val;
                arr.insertElement(val);
                break;
            }
            case 3: {
                int n;
                cout << "How many elements? ";
                cin >> n;
                arr.insertElements(n);
                break;
            }
            case 4: {
                int idx, val;
                cout << "Enter index to update: ";
                cin >> idx;
                cout << "Enter new value: ";
                cin >> val;
                arr.updateAt(idx, val);
                break;
            }
            case 5: {
                int idx;
                cout << "Enter index to delete: ";
                cin >> idx;
                arr.deleteAt(idx);
                break;
            }
            case 6: {
                arr.Sorting();
                break;
            }
            case 7: {
                int val;
                cout << "Enter element to search: ";
                cin >> val;
                int index = arr.searchFor(val);
                if (index != -1)
                    cout << "Found at index: " << index << endl;
                else
                    cout << "Element not found.\n";
                break;
            }
            case 8: {
                if (arr.isSorted())
                    cout << "Array is sorted.\n";
                else
                    cout << "Array is not sorted.\n";
                break;
            }
            case 9: {
                arr.displayInfo();
                break;
            }
            case 10: {
                cout << "Enter new size for the array: ";
                cin >> size;
                arr = Array_ADT(size);
                cout << "New array created with size " << size << ".\n";
                break;
            }
            case 11: {
                arr.deleteArray();
                break;
            }
            case 0: {
                cout << "Exiting...\n";
                break;
            }
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);

}
