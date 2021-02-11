#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include<ctime>

using namespace std;
int TABLE_SIZE = 10009;
struct treeNode{
    int key;
    treeNode *right;
    treeNode *left;
};
class treeHash{
    struct head{
        treeNode *a;
    };
private:
    head *table = new head[TABLE_SIZE];
    int number;
    int count;
public:
    treeHash(int HashNum);
    void insert(int key);
    void deleteTreeNode(int key);
    void print();
    bool search(int key);
    int getNumber();
    
};
int hashFunction(int key, int size){
    int a = key % size;
    return a;
}
int hashFunction2(int key, int size){
    int cool;
    cool = (key / size) % size;
    return cool;
}

treeHash :: treeHash(int HashNum){
    for(int i = 0; i < TABLE_SIZE; i++){
        table[i].a = NULL;
    }
    number = HashNum;
    count = 0;
}

void treeHash :: insert(int key){
    int hash;
    count++;
    treeNode *temp = new treeNode;
    temp -> key = key;
    temp -> left = NULL;
    temp -> right = NULL;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    if(table[hash].a == NULL){
        table[hash].a = temp;
    }
    else{
        treeNode *temp2 = table[hash].a;
        while(temp2 != NULL){
            if(temp2 -> key > key){
                if(temp2 -> left == NULL){
                    temp2 -> left = temp;
                    break;
                }
                else{
                temp2 = temp2 -> left;
                }
            }
            else{
                if(temp2 -> right == NULL){
                    temp2 -> right = temp;
                    break;
                }
                else{
                temp2 = temp2 -> right;
                }
            }
        }
        
    }
}
void printHelper(treeNode *r){
    if(r != NULL){
        printHelper(r -> left);
        cout << r -> key << " ";
        printHelper(r -> right);
    }
}
void treeHash :: print(){
    for(int i = 0; i < TABLE_SIZE; i++){
    cout << "index " << i << ": ";
    printHelper(table[i].a);
    cout << endl;
    }
}
treeNode *findMin(treeNode *r){
    if(r -> left != NULL){
        return findMin(r -> left);
    }
    return r;
    
}
treeNode *deleteTreeNodeHelp(treeNode *r, int key){
    if(r != NULL){
    if(key < r -> key){
        r -> left = deleteTreeNodeHelp(r -> left, key);
    }
    else if(key > r -> key){
        r -> right = deleteTreeNodeHelp(r -> right, key);
    }
    else{
        if(r -> right == NULL && r -> left == NULL){
            delete r;
            r = NULL;
            return r;
        }
        else if(r -> right == NULL && r -> left != NULL){
            treeNode *temp = r -> left;
            delete r;
            return temp;
        }
        else if(r -> right != NULL && r -> left == NULL){
            treeNode *temp = r -> right;
            delete r;
            return temp;
        }
        else{
            treeNode *temp2 = findMin(r -> right);
            char b = temp2 -> key;
            deleteTreeNodeHelp(r, b);
            r -> key = b;
            return r;
            
        }
    }
    }
    return r;
}
void treeHash :: deleteTreeNode(int key){
    int hash;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    if(table[hash].a == NULL){
        cout << "could not delete" << endl;
    }
    else{
    table[hash].a = deleteTreeNodeHelp(table[hash].a, key);
    count--;
    }
}
bool searchHelp(treeNode *r, int key){
    if(r != NULL){
        if(r -> key < key){
           return searchHelp(r -> right, key);
        }
        else if(r -> key > key){
           return searchHelp(r -> left, key);
        }
        else{
            return true;
        }
    }
    else{
        return false;
    }
}
bool treeHash :: search(int key){
    int hash;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    return searchHelp(table[hash].a, key);
}
int treeHash :: getNumber(){
    return count;
}
struct LLNode{
    int key;
    LLNode *next;
};
class LLHash{
    struct Head{
        LLNode *head;
    };
    private:
    Head *table = new Head[TABLE_SIZE];
    int number;
    int count;
    public:
    LLHash(int hashNum);
    void insert(int key);
    void deleteNode(int key);
    bool search(int key);
    void print();
    int getNumber();
    
};
LLHash :: LLHash(int hashNum){
    for(int i = 0; i < TABLE_SIZE; i++){
        table[i].head = NULL;
    }
    number = hashNum;
    count = 0;
}
void LLHash :: insert(int key){
    count++;
    int hash;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    LLNode *temp = new LLNode;
    temp -> key = key;
    temp -> next = NULL;
    if(table[hash].head == NULL){
        table[hash].head = temp;
    }
    else{
        LLNode *temp1 = table[hash].head;
        while(temp1 -> next != NULL){
            temp1 = temp1 -> next;
        }
        temp1 -> next = temp;
    }
}
void LLHash :: print(){
    for(int i = 0; i < TABLE_SIZE; i++){
        LLNode *temp = table[i].head;
        cout << "index " << i << "; ";
        while(temp != NULL){
            cout << temp -> key << " ";
            temp = temp -> next;
        }
        cout << endl;
    }
}
void LLHash :: deleteNode(int key){
    int hash;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    LLNode *temp = table[hash].head;
    if(table[hash].head -> key == key){
        table[hash].head = table[hash].head -> next;
    }
    else if(temp == NULL){
        cout << "no node to delete" << endl;
    }
    else{
        while (temp -> next != NULL) {
            if(temp -> next -> key == key){
                    cout << "deleting " << temp -> key << endl;
                    temp -> next = temp -> next -> next;
                count --;
            }
            else{
                temp = temp -> next;
            }
            
        }
    }

}
bool LLHash :: search(int key){
    int hash;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    LLNode *temp = table[hash].head;
    while(temp != NULL){
        if(temp -> key == key){
            return true;
        }
        else{
            temp = temp -> next;
        }
    }
    if(temp == NULL){
        return false;
    }
    else{
        return true;
    }
}
int LLHash :: getNumber(){
    return count;
}
class LinearHash{
private:
    int *table = new int[TABLE_SIZE];
    int number;
    int count;
public:
    LinearHash(int hashNum);
    void insert(int key);
    void deleteKey(int key);
    bool search(int key);
    void print();
    int getNumber();
};
LinearHash :: LinearHash(int hashNum){
    for(int i = 0; i < TABLE_SIZE; i++){
        table[i] = -1;
    }
    number = hashNum;
    count = 0;
}
void LinearHash :: insert(int key){
    int hash;
    if(number == 1){
        hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    for(int i = hash; i < TABLE_SIZE; i++){
        if(table[i] == -1){
            table[i] = key;
            count++;
            break;
        }
        else if(i == TABLE_SIZE-1){
            i = -1;
        }
        if(i == hash-1){
            cout << "no room for insert" << endl;
            break;
        }
    }
}
void LinearHash :: deleteKey(int key){
    int hash;
    if(number == 1){
     hash = hashFunction(key, TABLE_SIZE);
    }
    else{
        hash = hashFunction2(key, TABLE_SIZE);
    }
    for(int i = hash; i < TABLE_SIZE; i++){
        if(table[i] == key){
            cout << "deleting " << table[i] << endl;
            table[i] = -1;
            count--;
            break;
        }
        else if(i == TABLE_SIZE){
            i = -1;
        }
        else if(i == hash-1){
            cout << "key does not exist in the linear hash" << key << endl;
            break;
        }
    }
}
bool LinearHash :: search(int key){
    int hash;
    if(number == 1){
    hash = hashFunction(key, TABLE_SIZE);
    }
    else{
    hash = hashFunction2(key, TABLE_SIZE);
    }
    for(int i = hash; i < TABLE_SIZE; i++){
        if(table[i] == key){
            cout << "Found the key" << endl;
            return true;
        }
        else if(i == TABLE_SIZE-1){
            i = -1;
        }
        if(i == hash-1){
            return false;
        }
    }
    return true;
}
void LinearHash :: print(){
    for(int i = 0; i < TABLE_SIZE; i++){
        cout << "index " << i << ": ";
        if(table[i] != -1){
            cout << table[i] << endl;
        }
        else{
            cout << endl;
        }
    }
}
int LinearHash :: getNumber(){
    return count;
}

class cuckooHash{
private:
    int *table = new int[TABLE_SIZE];
    int *table2 = new int[TABLE_SIZE];
    int size;
    //counts the number of times the array gets bigger
    int count;
    //counts the number of elements inserted so load factor can be approximated.
    int load;
    void reHashTable(int lost);
    int tableOneInsert(int key);
    int tableTwoInsert(int key);
    int findPrime(int key);
    
public:
    cuckooHash();
    void newTable();
    void insert(int key);
    bool search(int key);
    void deleteKey(int key);
    double calculateLoad();
    int getAdditions();
    int getLoad();
    void print();
};
cuckooHash :: cuckooHash(){
    for(int i = 0; i < TABLE_SIZE; i++){
        table[i] = -1;
        table2[i] = -1;
    }
    size = TABLE_SIZE;
    count = 0;
    load = 0;
}

int cuckooHash :: findPrime(int s){
    int newS = s + 1;
    int sRoot = floor(sqrt(newS));
    for(int i = 2; i <= sRoot; i++){
        if(newS % i == 0){
            return (findPrime(newS));
        }
    }
    cout << newS << endl;
    return newS;
}
void cuckooHash :: newTable(){
    
}
void cuckooHash :: reHashTable(int lost){
    vector<int> keys;
    count ++;
    load = 0;
    int oldSize = size;
    size = findPrime(size);
    for(int i = 0; i < oldSize; i++){
        if(table[i] != -1){
            keys.push_back(table[i]);
        }
        if(table2[i] != -1){
            keys.push_back(table2[i]);
        }
    }
    keys.push_back(lost);
    int *table3 = new int[size];
    int *table4 = new int[size];
    delete[] table;
    delete[] table2;
    for(int i = 0; i < size; i++){
        table3[i] = -1;
        table4[i] = -1;
    }
    table = table3;
    table2 = table4;
    for(int j = 0; j < keys.size(); j++){
        insert(keys[j]);
        cout << "inserting " << keys[j] << endl;
    }
}
int cuckooHash :: tableTwoInsert(int key){
    int saved;
    int hash = hashFunction2(key, size);
    if(table2[hash] == -1){
        table2[hash] = key;
        return -1;
    }
    else{
        saved = table2[hash];
        table2[hash] = key;
        return saved;
    }
}
int cuckooHash :: tableOneInsert(int key){
    int saved;
    int hash = hashFunction(key, size);
    if(table[hash] == -1){
        table[hash] = key;
        return -1;
    }
    else{
        saved = table[hash];
        table[hash] = key;
        return saved;
    }
}
void cuckooHash :: insert(int key){
    if(search(key) == false){
    int num = key;
    int x = 0;
    int hash = hashFunction(key, size);
    int hash2 = hashFunction2(key, size);
    if(table[hash] == -1){
        load++;
        table[hash] = key;
    }
    else if(table2[hash2] == -1){
        load++;
        table2[hash2] = key;
    }
    else{
        for(int i = 0; i < size; i++){
            x = tableOneInsert(num);
            if(x == -1){
                load++;
                return;
            }
            num = tableTwoInsert(x);
            if(num == -1){
                load++;
                return;
            }
        }
        if(num != -1){
            reHashTable(num);
        }
    }
    
}
}
void cuckooHash :: print(){
    for(int i = 0; i < size; i++){
        cout << "index " << i << ": ";
        if(table[i] != -1){
            cout << table[i] << endl;
        }
        else{
            cout << endl;
        }
    }
    for(int j = 0; j < size; j++){
        cout << "index " << j << ": ";
        if(table2[j] != -1){
            cout << table2[j] << endl;
        }
        else{
            cout << endl;
        }
    }
    cout << "number of additions " << count << endl;
}
bool cuckooHash :: search(int key){
    int hash = hashFunction(key, size);
    int hash2 = hashFunction2(key, size);
    if(table[hash] == key){
        cout << "found " << key << " at position " << hash << " in the first hash table" << endl;
        return true;
    }
    if(table2[hash2] == key){
        cout << "found " << key << " at position " << hash2 << " in the second hash table" << endl;
        return true;
    }
    else{
        cout << "could not find " << key << " in either hash table" << endl;
        return false;
    }
}
void cuckooHash :: deleteKey(int key){
    load--;
    int hash = hashFunction(key, size);
    if(table[hash] == key){
        table[hash] = -1;
        cout << "successfully deleted " << key << " at position " << hash << " in the first hash table" << endl;
        return;
    }
    int hash2 = hashFunction2(key, size);
    if(table2[hash2] == key){
        table2[hash2] = -1;
        cout << "successfully deleted " << key << " at position " << hash2 << " in the second hash table" << endl;
        return;
    }
    else{
        cout << "could not find " << key << " in either hash table" << endl;
    }
}
double cuckooHash :: calculateLoad(){
    double temp;
    int temp2 = size*2;
    temp = (double)load/temp2;
    return temp;
}
int cuckooHash :: getLoad(){
    return load;
}


void insertAll(treeHash *a, treeHash *a1, LLHash *b, LLHash *b1, LinearHash *c, LinearHash *c1, cuckooHash *d, double key, fstream *write, vector<int> numbers, int load){
    float startTime, endTime;
    float execTime;
    int numberAddition;
    int numberAddition1;
    int x;
    
    if(key == .1){
        numberAddition = 0;
        numberAddition1 = 100;
    }
    else if(key == .2){
        numberAddition = 100;
        numberAddition1 = 200;
    }
    else if(key == .5){
        numberAddition = 200;
        numberAddition1 = 300;
    }
    else if(key == .7){
        numberAddition = 300;
        numberAddition1 = 400;
    }
    else if(key == .9){
        numberAddition = 400;
        numberAddition1 = 500;
    }
    else{
        numberAddition = 0;
        numberAddition1 = 100;
    }
    if(key > .5){
        x = 6;
    }
    else{
        x = 7;
    }
    for(int i = 0; i < 6; i++){
        double average = 0;
        if(i == 0){
            *write << "Tree Hash insert function 1 Load Factor " << key << ',';
        }
        else if(i == 1){
            *write << "Tree Hash insert function 2 Load Factor " << key << ',';
        }
        else if(i == 2){
            *write << "Linked List insert function 1 Load Factor " << key << ',';
        }
        else if(i == 3){
            *write << "Linked List insert function 2 Load Factor " << key << ',';
        }
        else if(i == 4){
            *write << "Linear Probe insert function 1 Load Factor " << key << ',';
        }
        else if(i == 5){
            *write << "Linear Probe insert function 2 Load Factor" << key << ',';
        }
        else if(i == 6){
            *write << "Cuckoo Hash insert Load Factor " << key << ',';
        }
        for(int j = numberAddition; j < numberAddition1; j++){
            if(i == 0){
                startTime = clock();
                a -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
                 
            }
            else if(i == 1){
                startTime = clock();
                a1 -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
            }
            else if(i == 2){
                startTime = clock();
                b -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
            }
            else if(i == 3){
                startTime = clock();
                b1 -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
            }
            else if(i == 4){
                startTime = clock();
                c -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
            }
            else if(i == 5){
                startTime = clock();
                c1 -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
            }
            else if(i == 6){
                startTime = clock();
                d -> insert(numbers[load + j]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1-1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
                load++;
            }
        }
        *write << '\n';
    }
}
void searchAll(treeHash *a, treeHash *a1, LLHash *b, LLHash *b1, LinearHash *c, LinearHash *c1, cuckooHash *d, double key, fstream *write, vector<int> numbers, int load){
    float startTime, endTime;
    float execTime;
    int numberAddition;
    int numberAddition1;
    int x;
    if(key == .1){
        numberAddition = 0;
        numberAddition1 = 100;
    }
    else if(key == .2){
        numberAddition = 100;
        numberAddition1 = 200;
    }
    else if(key == .5){
        numberAddition = 200;
        numberAddition1 = 300;
    }
    else if(key == .7){
        numberAddition = 300;
        numberAddition1 = 400;
    }
    else if(key == .9){
        numberAddition = 400;
        numberAddition1 = 500;
    }
    else{
        numberAddition = 0;
        numberAddition1 = 100;
    }
    if(key > .5){
        x = 6;
    }
    else{
        x = 7;
    }
    for(int i = 0; i < 6; i++){
        double average = 0;
        if(i == 0){
            *write << "Tree Hash search function 1 Load Factor " << key << ',';
        }
        else if(i == 1){
            *write << "Tree Hash search function 2 Load Factor " << key << ',';
        }
        else if(i == 2){
            *write << "Linked List search function 1 Load Factor " << key << ',';
        }
        else if(i == 3){
            *write << "Linked List search function 2 Load Factor " << key << ',';
        }
        else if(i == 4){
            *write << "Linear Probe search function 1 Load Factor " << key << ',';
        }
        else if(i == 5){
            *write << "Linear Probe search function 2 Load Factor " << key << ',';
        }
        else if(i == 6){
            *write << "Cuckoo Hash search Load Factor " << key << ',';
        }
        for(int j = numberAddition; j < numberAddition1; j++){
            if(i == 0){
                startTime = clock();
                a -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 1){
                startTime = clock();
                a1 -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 2){
                startTime = clock();
                b -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (float)average/100 << ',';
                }
            }
            else if(i == 3){
                startTime = clock();
                b1 -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 4){
                startTime = clock();
                c -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average, " << (double)average/100 << ',';
                }
            }
            else if(i == 5){
                
                startTime = clock();
                c1 -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average, " << (double)average/100 << ',';
                }
            }
            else if(i == 6){
                startTime = clock();
                d -> search(numbers[rand() % load]);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1-1){
                    *write << '\n' << "average, " << (double)average/100 << ',';
                }
            }
        }
        *write << '\n';
    }
}
void deleteAll(treeHash *a, treeHash *a1, LLHash *b, LLHash *b1, LinearHash *c, LinearHash *c1, cuckooHash *d, double key, fstream *write, vector<int> numbers, int load){
    float startTime, endTime;
    float execTime;
    int numberAddition;
    int numberAddition1;
    int x;
    if(key == .1){
        numberAddition = 0;
        numberAddition1 = 100;
    }
    else if(key == .2){
        numberAddition = 100;
        numberAddition1 = 200;
    }
    else if(key == .5){
        numberAddition = 200;
        numberAddition1 = 300;
    }
    else if(key == .7){
        numberAddition = 300;
        numberAddition1 = 400;
    }
    else if(key == .9){
        numberAddition = 400;
        numberAddition1 = 500;
    }
    else{
        numberAddition = 0;
        numberAddition1 = 100;
    }
    if(key > .5){
        x = 6;
    }
    else{
        x = 7;
    }
    for(int i = 0; i < 6; i++){
        double average = 0;
        if(i == 0){
            *write << "Tree Hash delete function 1 Load Factor " << key << ',';
        }
        else if(i == 1){
            *write << "Tree Hash delete function 2 Load Factor " << key << ',';
        }
        else if(i == 2){
            *write << "Linked List delete function 1 Load Factor " << key << ',';
        }
        else if(i == 3){
            *write << "Linked List delete function 2 Load Factor " << key << ',';
        }
        else if(i == 4){
            *write << "Linear Probe delete function 1 Load Factor " << key << ',';
        }
        else if(i == 5){
            *write << "Linear Probe delete function 2 Load Factor " << key << ',';
        }
        else if(i == 6){
            *write << "Cuckoo Hash delete Load Factor " << key << ',';
        }
        for(int j = numberAddition; j < numberAddition1; j++){
            if(i == 0){
                int temp = numbers[rand() % load];
                while(a -> search(temp) == false){
                    temp = numbers[rand() % load];
                }
                startTime = clock();
                a -> deleteTreeNode(temp);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 1){
                int temp = numbers[rand() % load];
                while(a1 -> search(temp) == false){
                    temp = numbers[rand() % load];
                }
                startTime = clock();
                a1 -> deleteTreeNode(temp);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 2){
                int temp = numbers[rand() % load];
                while(b -> search(temp) == false){
                    temp = numbers[rand() % load];
                }
                startTime = clock();
                b -> deleteNode(temp);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 3){
                int temp = numbers[rand() % load];
                while(b1 -> search(temp) == false){
                    temp = numbers[rand() % load];
                }
                startTime = clock();
                b1 -> deleteNode(temp);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 4){
                int temp = numbers[rand() % load];
                while(c -> search(temp) == false){
                    temp = numbers[rand() % load];
                }
                startTime = clock();
                c -> deleteKey(temp);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 5){
                int temp = numbers[rand() % load];
                while(c1 -> search(temp) == false){
                    temp = numbers[rand() % load];
                }
                startTime = clock();
                c1 -> deleteKey(temp);
                endTime = clock();
                execTime = (float)(endTime - startTime)/CLOCKS_PER_SEC;
                *write << execTime << ',';
                average = execTime + average;
                if(j == numberAddition1 -1){
                    *write << '\n' << "average," << (double)average/100 << ',';
                }
            }
            else if(i == 6){
                startTime = clock();
                d -> deleteKey(rand() % load);
                endTime = clock();
                execTime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
                average = execTime + average;
                if(j == numberAddition1-1){
                    *write << (double)average/100 << ',';
                }
            }
        }
        *write << '\n';
    }
}
int main(int argc, const char * argv[]) {
    string inputFile1;
    string inputFile2;
    string outputFile;
    if(argc == 4){
        //two csv files with the ints for insert
        inputFile1 = argv[1];
        inputFile2 = argv[2];
        //file the data on runtime that is going to be read into.
        outputFile = argv[3];
    }
    else{
        cout << "incorrect amount of arguments" << endl;
        exit(0);
    }
    treeHash a(1);
    treeHash a1(2);
    LLHash b1(2);
    LLHash b(1);
    LinearHash c(1);
    LinearHash c1(2);
    cuckooHash d;
    ifstream read;
    fstream write;
    string input;
    string number;
    int key;
    int temp;
    int load = 0;
    int inserted = 0;
    int dInserted = 0;
    vector<int> numbersA;
    vector<int> numbersB;
    read.open(inputFile1);
   while(getline(read, input,',')) {
        stringstream ss, ss1;
        ss1 << input;
        ss1 >> key;
        numbersA.push_back(key);
   }
    read.close();
    read.open(inputFile1);
    while(getline(read, input,',')) {
        stringstream ss, ss1;
        ss1 << input;
        ss1 >> key;
        numbersB.push_back(key);
    }
    read.close();
    write.open(outputFile);

    
    for(; (double)load/TABLE_SIZE < .1; load++){
        temp = numbersA[inserted];
        a.insert(temp);
        a1.insert(temp);
        b.insert(temp);
        b1.insert(temp);
        c.insert(temp);
        c1.insert(temp);
        inserted++;
     }

   int x = 0;
    
    insertAll(&a, &a1, &b, &b1, &c, &c1, &d, .1, &write, numbersA, inserted);
    inserted = inserted + 100;
    searchAll(&a, &a1, &b, &b1, &c, &c1, &d, .1, &write, numbersA, inserted);
    deleteAll(&a, &a1, &b, &b1, &c, &c1, &d, .1, &write, numbersA, inserted);
    for(; (double)load/TABLE_SIZE < .2; load++){
        int temp = numbersA[inserted];
        a.insert(temp);
        a1.insert(temp);
        b.insert(temp);
        b1.insert(temp);
        c.insert(temp);
        c1.insert(temp);
        inserted++;
    }

    insertAll(&a, &a1, &b, &b1, &c, &c1, &d, .2, &write, numbersA, inserted);
    inserted = inserted + 100;
    searchAll(&a, &a1, &b, &b1, &c, &c1, &d, .2, &write, numbersA, inserted);
    deleteAll(&a, &a1, &b, &b1, &c, &c1, &d, .2, &write, numbersA, inserted);
    
    for(; (double)load/TABLE_SIZE < .5; load++){
        int temp = numbersA[inserted];
        a.insert(temp);
        a1.insert(temp);
        b.insert(temp);
        b1.insert(temp);
        c.insert(temp);
        c1.insert(temp);
        inserted++;
    }

    insertAll(&a, &a1, &b, &b1, &c, &c1, &d, .5, &write, numbersA, inserted);
    inserted = inserted + 100;
    searchAll(&a, &a1, &b, &b1, &c, &c1, &d, .5, &write, numbersA, inserted);
    deleteAll(&a, &a1, &b, &b1, &c, &c1, &d, .5, &write, numbersA, inserted);
    
    for(; (double)load/TABLE_SIZE < .7; load++){
        int temp = numbersA[inserted];
        a.insert(temp);
        a1.insert(temp);
        b.insert(temp);
        b1.insert(temp);
        c.insert(temp);
        c1.insert(temp);
        inserted++;
    }
    
    insertAll(&a, &a1, &b, &b1, &c, &c1, &d, .7, &write, numbersA, inserted);
    inserted = inserted + 100;
    searchAll(&a, &a1, &b, &b1, &c, &c1, &d, .7, &write, numbersA, inserted);
    deleteAll(&a, &a1, &b, &b1, &c, &c1, &d, .7, &write, numbersA, inserted);
    
    for(;(double)load/TABLE_SIZE < .9; load++){
        int temp = numbersA[inserted];
        a.insert(temp);
        a1.insert(temp);
        b.insert(temp);
        b1.insert(temp);
        c.insert(temp);
        c1.insert(temp);
        inserted++;
    }

    
    insertAll(&a, &a1, &b, &b1, &c, &c1, &d, .9, &write, numbersA, inserted);
    inserted = inserted + 100;
    searchAll(&a, &a1, &b, &b1, &c, &c1, &d, .9, &write, numbersA, inserted);
    deleteAll(&a, &a1, &b, &b1, &c, &c1, &d, .9, &write, numbersA, inserted);
    
    for(;load < TABLE_SIZE; load++){
        int temp = numbersA[inserted];
        a.insert(temp);
        a1.insert(temp);
        b.insert(temp);
        b1.insert(temp);
        c.insert(temp);
        c1.insert(temp);
        inserted++;
    }
    insertAll(&a, &a1, &b, &b1, &c, &c1, &d, 1, &write, numbersA, inserted);
    inserted = inserted + 100;
    searchAll(&a, &a1, &b, &b1, &c, &c1, &d, 1, &write, numbersA, inserted);
    deleteAll(&a, &a1, &b, &b1, &c, &c1, &d, 1, &write, numbersA, inserted);
    write.close();
}


