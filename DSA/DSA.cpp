#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<unordered_map>
using namespace std;
struct Node;
struct TreeNode;
class Array_ADT{
    private:
    int*arr;
    int capacity;
    int size;
    int resized;
    vector<int>logDelete;
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
    ~Array_ADT() {
        delete[] arr;
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
            resize(size * 2);
        }
        arr[size++]=value;
    }
    void insertElements(int num=0){
        if(capacity<num){
            resize(num);
        }
        int element=0;
        for(int i =size;i<num;i++){
            cout<<"Enter the "<<i+1<<"th Element: ";
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
        if(index<0 || index>=size){
            cout<<"Index out of bounds";
            cout<<"Re-run the function 0<=index<"<<size<<endl;
            return;
        }
        arr[index]=value;
    }
    
    void deleteAt(int index){
        if(index<0 || index>=size){
            cout<<"Index out of bounds";
            cout<<"Re-run the function 0<=index<"<<size<<endl;
            return;
        }
        int value=arr[index];
        for(int i =index;i<size-1;i++){
            arr[i]=arr[i+1];
        }
        size--;
        logDeleted(value);
    }
    
    void deleteLastElement(){
        if(size > 0) {
            deleteAt(size-1);
        }
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
            cout<<"Enter the index number of the search needed to be conducted: ";
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
                default:
                    index=linearSearch(value);
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
        cout<<"The elements deleted from the array are: ";
        for(int i =0;i<logDelete.size();i++){
            cout<<logDelete[i]<<" ";
        }
        cout<<"\n";
    }
    
    void logDeleted(int value){
        logDelete.push_back(value);
    }
};

// Linked List Node Structure
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Linked List Class
class LinkedList {
private:
    Node* head;
    int size;
    
public:
    LinkedList() : head(nullptr), size(0) {}
    
    ~LinkedList() {
        clear();
    }
    
    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
        cout << "Inserted " << value << " at head\n";
    }
    
    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        size++;
        cout << "Inserted " << value << " at tail\n";
    }
    
    void insertAt(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Index out of bounds\n";
            return;
        }
        if (index == 0) {
            insertAtHead(value);
            return;
        }
        Node* newNode = new Node(value);
        Node* curr = head;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        size++;
        cout << "Inserted " << value << " at index " << index << "\n";
    }
    
    void deleteAtHead() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        cout << "Deleted " << temp->data << " from head\n";
        delete temp;
        size--;
    }
    
    void deleteAtTail() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        if (!head->next) {
            cout << "Deleted " << head->data << " from tail\n";
            delete head;
            head = nullptr;
            size--;
            return;
        }
        Node* curr = head;
        while (curr->next->next) {
            curr = curr->next;
        }
        cout << "Deleted " << curr->next->data << " from tail\n";
        delete curr->next;
        curr->next = nullptr;
        size--;
    }
    
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds\n";
            return;
        }
        if (index == 0) {
            deleteAtHead();
            return;
        }
        Node* curr = head;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        Node* temp = curr->next;
        curr->next = temp->next;
        cout << "Deleted " << temp->data << " at index " << index << "\n";
        delete temp;
        size--;
    }
    
    int search(int value) {
        Node* curr = head;
        int index = 0;
        while (curr) {
            if (curr->data == value) {
                cout << "Found " << value << " at index " << index << "\n";
                return index;
            }
            curr = curr->next;
            index++;
        }
        cout << "Element " << value << " not found\n";
        return -1;
    }
    
    void display() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        Node* curr = head;
        cout << "List: ";
        while (curr) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }
    
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        cout << "List reversed\n";
    }
    
    int getSize() { return size; }
    
    void clear() {
        while (head) {
            deleteAtHead();
        }
    }
};

// Stack Class
class Stack {
private:
    vector<int> data;
    int topIndex;
    
public:
    Stack() : topIndex(-1) {}
    
    void push(int value) {
        data.push_back(value);
        topIndex++;
        cout << "Pushed " << value << " onto stack\n";
    }
    
    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Popped " << data[topIndex] << " from stack\n";
        data.pop_back();
        topIndex--;
    }
    
    int top() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return -1;
        }
        return data[topIndex];
    }
    
    bool isEmpty() {
        return topIndex == -1;
    }
    
    int size() {
        return topIndex + 1;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
    
    void clear() {
        data.clear();
        topIndex = -1;
        cout << "Stack cleared\n";
    }
};

// Queue Class
class Queue {
private:
    vector<int> data;
    int frontIndex;
    int rearIndex;
    
public:
    Queue() : frontIndex(0), rearIndex(-1) {}
    
    void enqueue(int value) {
        data.push_back(value);
        rearIndex++;
        cout << "Enqueued " << value << " into queue\n";
    }
    
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Dequeued " << data[frontIndex] << " from queue\n";
        frontIndex++;
        
        // Reset indices when queue becomes empty
        if (frontIndex > rearIndex) {
            frontIndex = 0;
            rearIndex = -1;
            data.clear();
        }
    }
    
    int front() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return data[frontIndex];
    }
    
    int rear() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return data[rearIndex];
    }
    
    bool isEmpty() {
        return frontIndex > rearIndex;
    }
    
    int size() {
        if (isEmpty()) return 0;
        return rearIndex - frontIndex + 1;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue (front to rear): ";
        for (int i = frontIndex; i <= rearIndex; i++) {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
    
    void clear() {
        data.clear();
        frontIndex = 0;
        rearIndex = -1;
        cout << "Queue cleared\n";
    }
};

// Binary Tree Node
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class
class BinarySearchTree {
private:
    TreeNode* root;
    
    TreeNode* insertHelper(TreeNode* node, int value) {
        if (!node) {
            cout << "Inserted " << value << " into BST\n";
            return new TreeNode(value);
        }
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }
    
    TreeNode* deleteHelper(TreeNode* node, int value) {
        if (!node) return node;
        
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }
    
    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    bool searchHelper(TreeNode* node, int value) {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }
    
    void inorderHelper(TreeNode* node) {
        if (node) {
            inorderHelper(node->left);
            cout << node->data << " ";
            inorderHelper(node->right);
        }
    }
    
    void preorderHelper(TreeNode* node) {
        if (node) {
            cout << node->data << " ";
            preorderHelper(node->left);
            preorderHelper(node->right);
        }
    }
    
    void postorderHelper(TreeNode* node) {
        if (node) {
            postorderHelper(node->left);
            postorderHelper(node->right);
            cout << node->data << " ";
        }
    }
    
    void clearHelper(TreeNode* node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    ~BinarySearchTree() {
        clear();
    }
    
    void insert(int value) {
        root = insertHelper(root, value);
    }
    
    void remove(int value) {
        root = deleteHelper(root, value);
        cout << "Deleted " << value << " from BST\n";
    }
    
    bool search(int value) {
        bool found = searchHelper(root, value);
        cout << "Element " << value << (found ? " found" : " not found") << " in BST\n";
        return found;
    }
    
    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorderHelper(root);
        cout << "\n";
    }
    
    void preorderTraversal() {
        cout << "Preorder Traversal: ";
        preorderHelper(root);
        cout << "\n";
    }
    
    void postorderTraversal() {
        cout << "Postorder Traversal: ";
        postorderHelper(root);
        cout << "\n";
    }
    
    void levelOrderTraversal() {
        if (!root) {
            cout << "Tree is empty\n";
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        cout << "Level Order Traversal: ";
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << "\n";
    }
    
    void clear() {
        clearHelper(root);
        root = nullptr;
        cout << "BST cleared\n";
    }
};
class HashTable {
private:
    vector<vector<pair<int, int>>> table;
    int capacity;
    int size;
    int hashFunction(int key) {
        return key % capacity;
    }
public:
    HashTable(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }
    void insert(int key, int value) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                cout << "Updated key " << key << " with value " << value << "\n";
                return;
            }
        }
        table[index].push_back({key, value});
        size++;
        cout << "Inserted key " << key << " with value " << value << " at index " << index << "\n";
    }
    bool search(int key, int& value) {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                cout << "Found key " << key << " with value " << value << "\n";
                return true;
            }
        }
        cout << "Key " << key << " not found\n";
        return false;
    }
    void remove(int key) {
        int index = hashFunction(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                cout << "Removed key " << key << " with value " << it->second << "\n";
                bucket.erase(it);
                size--;
                return;
            }
        }
        cout << "Key " << key << " not found for removal\n";
    }
    void display() {
        cout << "Hash Table:\n";
        for (int i = 0; i < capacity; i++) {
            cout << "Index " << i << ": ";
            if (table[i].empty()) {
                cout << "Empty";
            } else {
                for (const auto& pair : table[i]) {
                    cout << "(" << pair.first << "," << pair.second << ") ";
                }
            }
            cout << "\n";
        }
    }
    int getSize() { return size; }
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        size = 0;
        cout << "Hash table cleared\n";
    }
};
void arrayMenu(Array_ADT& arr) {
    int choice;
    do {
        cout << "\n=== ARRAY MENU ===\n";
        cout << "1. Insert Element\n";
        cout << "2. Insert Multiple Elements\n";
        cout << "3. Update Element at Index\n";
        cout << "4. Delete Element at Index\n";
        cout << "5. Sort the Array\n";
        cout << "6. Search for an Element\n";
        cout << "7. Check if Array is Sorted\n";
        cout << "8. Display Array\n";
        cout << "9. View Array Information\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int val;
                cout << "Enter value to insert: ";
                cin >> val;
                arr.insertElement(val);
                break;
            }
            case 2: {
                int n;
                cout << "How many elements? ";
                cin >> n;
                arr.insertElements(n);
                break;
            }
            case 3: {
                int idx, val;
                cout << "Enter index to update: ";
                cin >> idx;
                cout << "Enter new value: ";
                cin >> val;
                arr.updateAt(idx, val);
                break;
            }
            case 4: {
                int idx;
                cout << "Enter index to delete: ";
                cin >> idx;
                arr.deleteAt(idx);
                break;
            }
            case 5:
                arr.Sorting();
                break;
            case 6: {
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
            case 7:
                cout << "Array is " << (arr.isSorted() ? "sorted" : "not sorted") << "\n";
                break;
            case 8:
                arr.displayArr();
                break;
            case 9:
                arr.displayInfo();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}
void linkedListMenu(LinkedList& list) {
    int choice;
    do {
        cout << "\n=== LINKED LIST MENU ===\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at Tail\n";
        cout << "3. Insert at Index\n";
        cout << "4. Delete at Head\n";
        cout << "5. Delete at Tail\n";
        cout << "6. Delete at Index\n";
        cout << "7. Search Element\n";
        cout << "8. Reverse List\n";
        cout << "9. Display List\n";
        cout << "10. Get Size\n";
        cout << "11. Clear List\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                int val;
                cout << "Enter value to insert at head: ";
                cin >> val;
                list.insertAtHead(val);
                break;
            }
            case 2: {
                int val;
                cout << "Enter value to insert at tail: ";
                cin >> val;
                list.insertAtTail(val);
                break;
            }
            case 3: {
                int idx, val;
                cout << "Enter index: ";
                cin >> idx;
                cout << "Enter value: ";
                cin >> val;
                list.insertAt(idx, val);
                break;
            }
            case 4:
                list.deleteAtHead();
                break;
            case 5:
                list.deleteAtTail();
                break;
            case 6: {
                int idx;
                cout << "Enter index to delete: ";
                cin >> idx;
                list.deleteAt(idx);
                break;
            }
            case 7: {
                int val;
                cout << "Enter value to search: ";
                cin >> val;
                list.search(val);
                break;
            }
            case 8:
                list.reverse();
                break;
            case 9:
                list.display();
                break;
            case 10:
                cout << "Size: " << list.getSize() << "\n";
                break;
            case 11:
                list.clear();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}
void stackMenu(Stack& stack) {
    int choice;
    do {
        cout << "\n=== STACK MENU ===\n";
        cout << "1. Push Element\n";
        cout << "2. Pop Element\n";
        cout << "3. View Top Element\n";
        cout << "4. Check if Empty\n";
        cout << "5. Get Size\n";
        cout << "6. Display Stack\n";
        cout << "7. Clear Stack\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                int val;
                cout << "Enter value to push: ";
                cin >> val;
                stack.push(val);
                break;
            }
            case 2:
                stack.pop();
                break;
            case 3:
                cout << "Top element: " << stack.top() << "\n";
                break;
            case 4:
                cout << "Stack is " << (stack.isEmpty() ? "empty" : "not empty") << "\n";
                break;
            case 5:
                cout << "Stack size: " << stack.size() << "\n";
                break;
            case 6:
                stack.display();
                break;
            case 7:
                stack.clear();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}
void queueMenu(Queue& queue) {
    int choice;
    do {
        cout << "\n=== QUEUE MENU ===\n";
        cout << "1. Enqueue Element\n";
        cout << "2. Dequeue Element\n";
        cout << "3. View Front Element\n";
        cout << "4. View Rear Element\n";
        cout << "5. Check if Empty\n";
        cout << "6. Get Size\n";
        cout << "7. Display Queue\n";
        cout << "8. Clear Queue\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                int val;
                cout << "Enter value to enqueue: ";
                cin >> val;
                queue.enqueue(val);
                break;
            }
            case 2:
                queue.dequeue();
                break;
            case 3:
                cout << "Front element: " << queue.front() << "\n";
                break;
            case 4:
                cout << "Rear element: " << queue.rear() << "\n";
                break;
            case 5:
                cout << "Queue is " << (queue.isEmpty() ? "empty" : "not empty") << "\n";
                break;
            case 6:
                cout << "Queue size: " << queue.size() << "\n";
                break;
            case 7:
                queue.display();
                break;
            case 8:
                queue.clear();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}
void bstMenu(BinarySearchTree& bst) {
    int choice;
    do {
        cout << "\n=== BINARY SEARCH TREE MENU ===\n";
        cout << "1. Insert Element\n";
        cout << "2. Delete Element\n";
        cout << "3. Search Element\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Preorder Traversal\n";
        cout << "6. Postorder Traversal\n";
        cout << "7. Level Order Traversal\n";
        cout << "8. Clear Tree\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int val;
                cout << "Enter value to insert: ";
                cin >> val;
                bst.insert(val);
                break;
            }
            case 2: {
                int val;
                cout << "Enter value to delete: ";
                cin >> val;
                bst.remove(val);
                break;
            }
            case 3: {
                int val;
                cout << "Enter value to search: ";
                cin >> val;
                bst.search(val);
                break;
            }
            case 4:
                bst.inorderTraversal();
                break;
            case 5:
                bst.preorderTraversal();
                break;
            case 6:
                bst.postorderTraversal();
                break;
            case 7:
                bst.levelOrderTraversal();
                break;
            case 8:
                bst.clear();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}
void hashTableMenu(HashTable& ht) {
    int choice;
    do {
        cout << "\n=== HASH TABLE MENU ===\n";
        cout << "1. Insert Key-Value Pair\n";
        cout << "2. Search by Key\n";
        cout << "3. Delete by Key\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Get Size\n";
        cout << "6. Clear Hash Table\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                int key, val;
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> val;
                ht.insert(key, val);
                break;
            }
            case 2: {
                int key, val;
                cout << "Enter key to search: ";
                cin >> key;
                ht.search(key, val);
                break;
            }
            case 3: {
                int key;
                cout << "Enter key to delete: ";
                cin >> key;
                ht.remove(key);
                break;
            }
            case 4:
                ht.display();
                break;
            case 5:
                cout << "Hash table size: " << ht.getSize() << "\n";
                break;
            case 6:
                ht.clear();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}

int main() {
    Array_ADT arr;
    LinkedList list;
    Stack stack;
    Queue queue;
    BinarySearchTree bst;
    HashTable ht;
    int choice;
    cout << "=== COMPREHENSIVE DATA STRUCTURES IMPLEMENTATION ===\n";
    cout << "Welcome to the Data Structures Learning Platform!\n";
    do {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Array Operations\n";
        cout << "2. Linked List Operations\n";
        cout << "3. Stack Operations\n";
        cout << "4. Queue Operations\n";
        cout << "5. Binary Search Tree Operations\n";
        cout << "6. Hash Table Operations\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                arrayMenu(arr);
                break;
            case 2:
                linkedListMenu(list);
                break;
            case 3:
                stackMenu(stack);
                break;
            case 4:
                queueMenu(queue);
                break;
            case 5:
                bstMenu(bst);
                break;
            case 6:
                hashTableMenu(ht);
                break;
            case 0:
                cout << "Thank you for using the Data Structures Platform!\n";
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 0);

    return 0;
}