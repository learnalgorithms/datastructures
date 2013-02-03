package sorting

import (
  "testing"
)

func TestMergeSort(t *testing.T){
  items := []int{5,3,1,2,4,6}
  MergeSort(items, 0, 5)
  for i,item := range(items) {
    if item != i + 1 {

      t.Errorf("merge sort failed")
    }
  }
}
func TestInsertionSort(t *testing.T){
  items := []int{5,3,1,2,4,6}
  InsertionSort(items)
  for i,item := range(items) {
    if item != i + 1 {

      t.Errorf("insertion sort failed")
    }
  }
}
