/*************************************************************************
    > File Name: stock2.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 日  4/12 12:24:08 2020
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

int mostProfit(int arr[],int n){
  if(n<2) return 0;
  int sum = 0;
  for(int i=1; i<n; i++){
    if(arr[i]>arr[i-1])
      sum += arr[i]-arr[i-1];
  }
  return sum;
}

int maxProfit(vector<int>& prices) {
        if(prices.size()<2) return 0;
        int sum=0;
        for(int i=1; i<prices.size(); i++){ //i从1开始
            if(prices[i]>prices[i-1])
                sum += prices[i] - prices[i-1];
        }
        return sum;
}

int main(){
  int n = 5;
  int arr[] = {7,1,5,3,6};
  //int sum = mostProfit(arr, 5);
  //cout << sum << endl;
  vector<int> prices(arr,arr+n);
  for(int i:prices){
    cout << i<<endl;
  }
  int max = maxProfit(prices);
  cout << max << endl;
  return 0;
}

