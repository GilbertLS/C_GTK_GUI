#include <iostream>
using namespace std;

#include "Queue.h"

void queueTest01(); //+=
void queueTest02(); //!
void queueTest03(); //[]
void queueTest04(); //-=
void queueTest05(); //= (used with + and -)
void queueTest06(); //+
void queueTest07(); //-

int main()
{
  queueTest01();
  queueTest02();
  queueTest03();
  queueTest04();
  queueTest05();
  queueTest06();
  queueTest07();
  return 0;
}

void queueTest01() //+=
{
  Queue<int> q1, q2, q3;
  int i1, i2, i3, i4;
  i1 = 1;
  i2 = 2;
  i3 = 3;
  i4 = 4;
  cout << "queueTest01 - += - Adding element to empty queue" << endl;
  q1 += &i1;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest01 - += - Adding element to non-empty queue" << endl;
  q1 += &i2;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest01 - += - Adding empty queue to non-empty queue" << endl;
  q1 += q2;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest01 - += - Adding empty queue to empty queue" << endl;
  q3 += q2;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q3.debugPrint();
  cout << endl;

  cout << "queueTest01 - += - Adding non-empty queue to empty queue" << endl;
  q2 += q1;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q2.debugPrint();
  cout << endl;

  cout << "queueTest01 - += - Adding non-queue to non-empty queue" << endl;
  q3 += &i3;
  q3 += q1;
  cout << "Expected: 3, 1, 2," << endl;
  cout << "Actual:   ";
  q3.debugPrint();
  cout << endl;

  cout << "queueTest01 - += - Cascading (q3 += q2 += q1 += &i4)" << endl;
  q3 += q2 += q1 += &i4;

  cout << "            - q1" << endl;
  cout << "Expected: 1, 2, 4," << endl;
  cout << "Actual:   ";
  q1.debugPrint();

  cout << "            - q2" << endl;
  cout << "Expected: 1, 2, 1, 2, 4," << endl;
  cout << "Actual:   ";
  q2.debugPrint();

  cout << "            - q3" << endl;
  cout << "Expected: 3, 1, 2, 1, 2, 1, 2, 4," << endl;
  cout << "Actual:   ";
  q3.debugPrint();
  cout << endl;
  
}

void queueTest02() //!
{
  Queue<int> q1;
  int i1, i2;
  i1 = 1;
  i2 = 2;
  
  cout << "queueTest02 - ! - Emptying already empty queue" << endl;
  !q1;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest02 - ! - Emptying queue with a couple elements" << endl;
  q1 += &i1;
  q1 += &i2;
  !q1;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
}

void queueTest03() //[]
{
  Queue<int> q1;
  int i1, i2;
  i1 = 1;
  i2 = 2;

  cout << "queueTest03 - [] - Getting element from empty queue" << endl;
  int *ptr = q1[0];
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << ptr << endl << endl;

  cout << "queueTest03 - [] - Getting elements from non-empty queue" << endl;
  q1 += &i1;
  q1 += &i2;
  int *ptr0 = q1[0];
  int *ptr1 = q1[1];
  cout << "Expected: 1, 2" << endl << endl;
  if( ptr0 == NULL)
    cout << "            - q1[0] returned NULL" << endl;
  if( ptr1 == NULL)
    cout << "            - q1[1] returned NULL" << endl;
  if( ptr0 != NULL && ptr1 != NULL)
    cout << "Actual:   " << *ptr0 << ", " << *ptr1 << endl;
  cout << endl;

  cout << "queueTest03 - [] - Getting element out of bounds" << endl;
  int *ptr5 = q1[5];
  cout << "Expected: 0" << endl;
  cout << "Actual:   " << ptr5 << endl << endl;
}

void queueTest04() //-=
{
  Queue<int> q1, q2;
  int i1, i2, i3, i4;
  i1 = 1;
  i2 = 2;
  i3 = 3;
  i4 = 4;

  cout << "queueTest04 - -= - Removing element from empty queue" << endl;
  q1 -= &i1;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest04 - -= - Removing empty queue from empty queue" << endl;
  q1 -= q2;
  cout << "            - q1" << endl;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  cout << "            - q2" << endl;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q2.debugPrint();
  cout << endl;

  cout << "queueTest04 - -= - Removing element from back of queue" << endl;
  q1 += &i1;
  q1 += &i2;
  q1 -= &i2;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest04 - -= - Removing element that is not in queue from queue" << endl;
  q1 += &i2;
  q1 -= &i3;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest04 - -= - Removing empty queue from non-empty queue" << endl;
  q1 -= q2;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest04 - -= - Removing queue from queue" << endl;
  q2 += &i2;
  q2 += &i3;
  q1 -= q2;
  cout << "            - q1" << endl;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  cout << "            - q2" << endl;
  cout << "Expected: 2, 3," << endl;
  cout << "Actual:   ";
  q2.debugPrint();
  cout << endl;

  cout << "queueTest04 - -= - Removing element from front of queue" << endl;
  q1 += &i2;
  q1 -= &i1;
  cout << "Expected: 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest04 - -= - Removing element from middle of queue" << endl;
  q1 += &i1;
  q1 += &i3;
  q1 -= &i1;
  cout << "Expected: 2, 3," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
}

void queueTest05() //=
{
  Queue<int> q1, q2;
  int i1, i2, i3, i4;
  i1 = 1;
  i2 = 2;
  i3 = 3;
  i4 = 4;
  cout << "queueTest05 - = - empty = empty" << endl;
  q1 = q2;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest05 - = - empty = non-empty" << endl;
  q2 += &i1;
  q2 += &i2;
  q1 = q2;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest05 - = - non-empty = non-empty" << endl;
  !q2;
  q2 += &i3;
  q2 += &i4;
  q1 = q2;
  cout << "Expected: 3, 4," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest05 - = - non-empty = empty" << endl;
  !q2;
  q1 = q2;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
}

//Since the + and - use += and -= I wont test cases that have
// been tested by += ad -=
void queueTest06() //+
{
  Queue<int> q1, q2, q3;
  int i1, i2, i3;
  i1 = 1;
  i2 = 2;
  i3 = 3;

  cout << "queueTest06 - + - empty + empty" << endl;
  q1 = q2 + q3;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest06 - + - empty + non-empty" << endl;
  q3 += &i1;
  q1 = q2 + q3;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest06 - + - non-empty + empty" << endl;
  q1 = q3 + q2;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest06 - + - non-empty + non-empty" << endl;
  q2 += &i2;
  q1 = q3 + q2;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest06 - + - empty + element" << endl;
  !q2;
  q1 = q2 + &i1;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest06 - + - element + empty " << endl;
  !q2;
  q1 = &i1 + q2;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest06 - + - non-empty + element" << endl;
  q2 += &i1;
  q1 = q2 + &i2;
  cout << "Expected: 1, 2," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest06 - + - element + non-empty" << endl;
  q1 = &i2 + q2;
  cout << "Expected: 2, 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

}
void queueTest07() //-
{
  Queue<int> q1, q2, q3;
  int i1, i2, i3;
  i1 = 1;
  i2 = 2;
  i3 = 3;

  cout << "queueTest07 - - - empty - empty" << endl;
  q1 = q2 - q3;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest07 - - - empty - non-empty" << endl;
  q3 += &i1;
  q1 = q2 - q3;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest07 - - - non-empty - empty" << endl;
  q1 = q3 - q2;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest07 - - - non-empty - non-empty/not in first" << endl;
  q2 += &i2;
  q1 = q3 - q2;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest07 - - - non-empty - non-empty/in first" << endl;
  q2 += &i1;
  q1 = q3 - q2; //Fix
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;
  
  cout << "queueTest07 - - - empty - element" << endl;
  !q2;
  q1 = q2 - &i1;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest07 - - - non-empty - element(not in queue)" << endl;
  q2 += &i1;
  q1 = q2 - &i2;
  cout << "Expected: 1," << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

  cout << "queueTest07 - - - non-empty - element(in queue)" << endl;
  q1 = q2 - &i1;
  cout << "Expected: " << endl;
  cout << "Actual:   ";
  q1.debugPrint();
  cout << endl;

}
