package sorting

import (
	"../heap"
)

func HeapSort(items []int) (sorted []int) {
	var heap heap.Heap

	heap.New(true, items...)
	heap.BuildHeap()

	for i := heap.GetArrayLength() - 1; i > 0; i-- {
		tmp := heap.At(0)
		heap.Set(heap.At(i), 0)
		heap.Set(tmp, i)
		heap.SetSize(heap.GetSize() - 1)
		heap.Heapify(0)
	}

	for k, _ := range items {
		sorted = append(sorted, heap.At(k))
	}
	return
}
