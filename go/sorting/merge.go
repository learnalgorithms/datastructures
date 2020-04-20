package sorting

import (
	"../stack"
)

func MergeSort(items []int, begin int, end int) {
	if begin < end {
		middle := int((begin + end) / 2)
		MergeSort(items, begin, middle)
		MergeSort(items, middle+1, end)
		merge(items, begin, middle, end)
	}
}

func merge(items []int, begin int, middle int, end int) {
	left := new(stack.Stack)
	right := new(stack.Stack)

	for i := middle; i >= begin; i-- {
		left.Push(items[i])
	}
	for i := end; i >= middle+1; i-- {
		right.Push(items[i])
	}

	for i := begin; i <= end; i++ {
		if right.Len() == 0 || left.Len() > 0 && left.Top().(int) < right.Top().(int) {
			items[i] = left.Pop().(int)
		} else {
			items[i] = right.Pop().(int)
		}
	}
}
