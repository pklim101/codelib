/*************************************************************************
    > File Name: binaryTreeSum.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 五  4/ 3 17:19:50 2020
 ************************************************************************/

#include<iostream>
using namespace std;

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};


bool search(Node* node, int& sum, int& n) {
    if (node == NULL)
        return false;
    sum += node->key;
    if(sum == n)
        return true;
    search(node->left, node->key, sum, n);
    search(node->right, node->key, sum, n);
    return false;
}

int main() {
    //int a;
    //cin >> a;
    Node* node = NULL;
    int sum = 0;
    int n = 0;
    bool find = search(node, sum, n);
    cout << "Hello World!" << endl;
}

