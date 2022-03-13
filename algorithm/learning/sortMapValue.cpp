#include<iostream>
#include<map>
using namespace std;

struct HeapNode{
  HeapNode *left = nullptr;
  HeapNode *right = nullptr;
  string key;
  int count;
  int index;
}

map<string, int, foo> data;
bool foo (int f1, int f2){
  if (f1  < f2 ) :
    return false;
  return true;
}

for (int i = 0; i < xx.size(); i++) {
  data.insert(pair<string, int>(key, count));
}

HeapNode* arr[];

void insert(HeapNode* arr[],int n, HeapNode* node, string key, int count){
  node->key = key;
  node->count = count;
  arr[n] = node;
  if (arr[n/2]->right !=NULL && arr[n/2]->left > arr[n/2]->right) {
    swap(arr[n/2]->left, arr[n/2]->right);
  }
  if (arr[n] > arr[n/2]) {
    n /= 2;
  }
  swap(arr[n], arr[n/2]);
}

void pop(){

}
void sortMapValue(map<string, int>& data) {
  
}

int main(){
  map<string, int> data;
  sortMapValue(data);
  return 0;
}
