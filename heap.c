/*
This is a demo c programm test heapup and down.

There are 2 main functions,
- reheapUp
- reheadDown

and it also can sort data when the data are removed from heap.

Platform:
- GCC Version: (Apple LLVM version 9.0.0 (clang-900.0.39.2) Target: x86_64-apple-darwin16.7.0)
- Online Complier (https://www.onlinegdb.com/online_c_compiler)
Author: Tim
*/

#include <stdio.h>
#include <stdlib.h>

int max =100;
int min =1;
int seed =10;

// stack
typedef struct node{
    int     data;
    struct node    *link;
}Node;

typedef struct{
    int     count;
    Node    *top;
}StackHead;
StackHead *CreateStack(){
    StackHead *myStack = (StackHead *) malloc (sizeof(StackHead));
    // malloc (sizeof (StackHead))
    myStack->count = 0;
    myStack->top = NULL;
    return myStack;
}

void Push(StackHead *myStack, int data){
    Node *pNew = (Node *) malloc (sizeof(Node));
    pNew -> data = data;
    pNew -> link = myStack -> top;
    myStack->top = pNew;
    myStack -> count ++;

    printf("%d,", data);

}

int Pop(StackHead *myStack) {
  long rv =0;
  if (myStack -> count !=0) {

    Node *pTop = myStack->top;
    myStack->top = pTop->link;
    myStack -> count --;
    rv = pTop -> data;
    free (pTop);
    pTop = NULL;
  }
  else {
    printf("Stack is empty.\n");
  }
  return rv;
}


// print array
void printArray(int *arr, int size){
  for (int i=0; i<size; i++){
    printf("Array[%d]: %d \n", i,  arr[i]);
  }
}


void reheapUp(int *a,int index)
{
  if(index!=0)
    {
      int parent=(index-1)/2;
    if(a[parent]<a[index])
    {
      int temp=a[parent];
      a[parent]=a[index];
      a[index]=temp;
      reheapUp(a,parent);
    }
  }
}
void reheapDown(int *a, int i, int last)
{
  int rightkey,leftkey,largest;
    if((2*i+1)<=last)
    {
      leftkey=a[2*i+1];
      if((2*i+2)<=last) {
        rightkey=a[2*i+2];
      }
      else {
        rightkey=-1;
        }
      if(leftkey>=rightkey) {
        largest=(2*i+1);
        }
      else {
        largest=(2*i+2);
        }

      if(a[i]<a[largest])
      {
        int temp=a[i];
        a[i]=a[largest];
        a[largest]=temp;
        reheapDown(a,largest,last);
      }
    }
  }

void insert(int *A, int data, int last){
  int i = last ;
  A[i] = data;
  reheapUp(A, i);
}

int delete(int *A, int last){
  int large = A[0];
  A[0] = A[last];
  reheapDown(A, 0, last);
  return large;
}

void fillAndReheapUp(int *out_p, int length){
  /*
  use seed to control the randomlization
  */
  srand(seed);

  for (int i=0; i<length; i++){
    // use max and min to control the range of the array
    int data = (rand()%(max+1-min)) +min;
    insert(out_p, data, i);
  }
}

void removeAllReheapDown( int *out_p, int length, StackHead *myStack){
  for (int i=0; i<length; i++){

    Push(myStack, delete(out_p, length-1-i));

  }
}

int main(){

  int n=10;
  int m =6;

// define a static array
  int A[n];

// populate it reheap all and print it out
  fillAndReheapUp(A, m);
  printArray(A, m);

// delete all and print it out in loop in push function
  StackHead *tmpStack = CreateStack();
  removeAllReheapDown(A, m, tmpStack);





  return 1;
}