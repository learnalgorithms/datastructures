package heap

import (
	"testing"
)

func TestHeapParent(t *testing.T) {
	var heap Heap
	test := heap.Parent(2)
	if test != 0 {
		t.Errorf("HeapParent failed. Expected 0, got: %d\n", test)
	}
	test = heap.Parent(3)
	if test != 1 {
		t.Errorf("HeapParent failed. Expected 1, got: %d\n", test)
	}
	test = heap.Parent(4)
	if test != 1 {
		t.Errorf("HeapParent failed. Expected 1, got: %d\n", test)
	}
	test = heap.Parent(5)
	if test != 2 {
		t.Errorf("HeapParent failed. Expected 2, got: %d\n", test)
	}
}

func TestHeapLeft(t *testing.T) {
	var heap Heap
	test := heap.Left(2)
	if test != 5 {
		t.Errorf("HeapLeft failed. Expected 5, got: %d\n", test)
	}
	test = heap.Left(3)
	if test != 7 {
		t.Errorf("HeapLeft failed. Expected 7, got: %d\n", test)
	}
	test = heap.Left(4)
	if test != 9 {
		t.Errorf("HeapLeft failed. Expected 9, got: %d\n", test)
	}
	test = heap.Left(5)
	if test != 11 {
		t.Errorf("HeapLeft failed. Expected 11, got: %d\n", test)
	}
}

func TestHeapRight(t *testing.T) {
	var heap Heap
	test := heap.Right(2)
	if test != 6 {
		t.Errorf("HeapRight failed. Expected 6, got: %d\n", test)
	}
	test = heap.Right(3)
	if test != 8 {
		t.Errorf("HeapRight failed. Expected 8, got: %d\n", test)
	}
	test = heap.Right(4)
	if test != 10 {
		t.Errorf("HeapRight failed. Expected 10, got: %d\n", test)
	}
	test = heap.Right(5)
	if test != 12 {
		t.Errorf("HeapRight failed. Expected 12, got: %d\n", test)
	}
}

func TestBuildMaxHeap(t *testing.T) {
	test := []int{4, 1, 3, 2, 16, 9, 10, 14, 8, 7}
	heap := []int{16, 14, 10, 8, 7, 9, 3, 2, 4, 1}
	var a Heap
	a.New(true, test...)
	a.BuildHeap()

	if a.GetArrayLength() != 10 {
		t.Errorf("BuildMaxHeap failed, expected array length 10, got %d", a.GetArrayLength())
	}

	for k, v := range heap {
		if v != a.At(k) {
			t.Errorf("BuildMaxHeap failed, expected %d at %d, got %d\n", v, k, a.At(k))
		}
	}
}
