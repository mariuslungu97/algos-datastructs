#include <stdio.h>
#include "dynamic_arr.h"

void printElements(int *elements, int length) {
  for (int i = 0; i < length; i++) {
    printf("%d ", *(elements + i));
  }
  printf("\n");
}

int main() {
  
  MyDynamicArray *myArr = dynamic_array();
  push(myArr, 5);
  push(myArr, 12);
  push(myArr, -1);
  push(myArr, 6);
  push(myArr, 3);
  push(myArr, 44);

  int *arrElements = elements(myArr);
  printElements(arrElements, size(myArr));  // 5, 12, -1, 6, 3, 44

  insert(myArr, 2, 22); // 5, 12, 22, -1, 6, 3, 44
  prepend(myArr, -40); // -40, 5, 12, 22, -1, 6, 3, 44
  int foundIdx = find(myArr, 22);
  printf("22 was found at position %d\n", foundIdx);
  delete_item(myArr, 3); // delete 3
  delete_at(myArr, 3); // delete item at index 3
  delete_at(myArr, 33); // error, index out of bounds

  arrElements = elements(myArr);
  printElements(arrElements, size(myArr));  // -40, 5, 12, -1, 6, 44

  int itemBatch[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  for (int i = 0; i < 20; i++) {
    push(myArr, itemBatch[i]);
  }

  printf("Array size: %d\n", size(myArr)); // 26
  printf("Array capacity: %d\n", capacity(myArr)); // 32
  arrElements = elements(myArr);
  printElements(arrElements, size(myArr));  // -40, 5, 12, -1, 6, 44 + itemBatch
  // delete 18 items => size = 26 - 18 = 8
  for (int i = 0; i < 18; i++) {
    delete_at(myArr, 0); 
  }

  printf("Array size: %d\n", size(myArr)); // 8
  printf("Array capacity: %d\n", capacity(myArr)); // 8 <= 32 / 4 (testing downsize)
  arrElements = elements(myArr);
  printElements(arrElements, size(myArr));  

  return 0;
}