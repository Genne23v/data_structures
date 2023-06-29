#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;

typedef struct Heap {
   int size;
   int* arr;
} Heap;

bool compare(int a, int b){
      return a > b;
}

void percolateUp(int arr[], int pos){
   int parent = (pos-1) / 2;
   int temp;

   if (parent >= 0){
      if (compare(arr[parent], arr[pos])){
         temp = arr[pos];
         arr[pos] = arr[parent];
         arr[parent] = temp;
         percolateUp(arr, parent);
      }
   }
}

void percolateDown(int arr[], int pos, int size){
   int lChild = 2 * pos + 1;
   int rChild = lChild + 1;

   int small = -1;
   int temp;

   if (lChild < size){
      small = lChild;
   }

   if(rChild < size && compare(arr[lChild], arr[rChild])){
      small = rChild;
   }

   if (small != -1 && compare(arr[pos], arr[small])){
      temp = arr[pos];
      arr[pos] = arr[small];
      arr[small] = temp;
      percolateDown(arr, small, size);
   }
}

void heapify(int arr[], int size){
   for (int i=(size/2); i>=0; i--){
      percolateDown(arr, i, size);
   }
}

void makeHeap(Heap* heap, int arr[], int size){
   heap->size = size;
   heap->arr = arr;
   heapify(arr, size);
}


/*Only modify this function*/
void insertionSortModified(int arr[],int size){
   Heap heap;
   makeHeap(&heap, arr, size);

   int curr;
   int i, j;
   for(i=2;i<size;i++){
      curr=arr[i];
      for(j=i;j>1 && arr[j-1] > curr;j--){
         arr[j]=arr[j-1];
      }
      arr[j]=curr;
   }
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int size){
   int curr;
   int i, j;
   for(i=1;i<size;i++){
      curr=arr[i];
      for(j=i;j>0 && arr[j-1] > curr;j--){
         arr[j]=arr[j-1];
      }
      arr[j]=curr;
   }
}

