package heap

import (
	"errors"
	"math"
)

var (
	heap Heap
)

type Heap struct {
	array []int
	size  int
}

func (obj *Heap) New(array ...int) {
	if len(array) > 0 {
		obj.array = array
	} else {
		obj.array = make([]int, 0)
	}
}

func (obj *Heap) GetSize() int {
	return obj.size
}

func (obj *Heap) SetSize(value int) {
	obj.size = value
}

func (obj *Heap) GetArrayLength() int {
	return len(obj.array)
}

func (obj *Heap) At(pos int) int {
	return obj.array[pos]
}

func (obj *Heap) Set(value int, pos int) (err error) {
	if len(obj.array) < pos {
		err = errors.New("pos is bigger than the array size")
	} else {
		obj.array[pos] = value
	}
	return
}

func (obj *Heap) Append(value int) {
	obj.array = append(obj.array, value)
}

func (obj *Heap) Parent(i int) int {
	if i%2 == 0 {
		return i>>1 - 1
	} else {
		return i >> 1
	}
}

func (obj *Heap) Left(i int) int {
	return (i << 1) + 1
}

func (obj *Heap) Right(i int) int {
	return (i << 1) + 2
}

func (a *Heap) MaxHeapify(i int) {
	var largest int

	l := a.Left(i)
	r := a.Right(i)

	if l <= a.GetSize()-1 && a.At(l) > a.At(i) {
		largest = l
	} else {
		largest = i
	}

	if r <= a.GetSize()-1 && a.At(r) > a.At(largest) {
		largest = r
	}

	if largest != i {
		tmp := a.At(i)
		a.Set(a.At(largest), i)
		a.Set(tmp, largest)
		a.MaxHeapify(largest)
	}
}

func (a *Heap) BuildMaxHeap() {
	a.SetSize(a.GetArrayLength())
	for i := a.GetArrayLength() / 2; i >= 0; i-- {
		a.MaxHeapify(i)
	}
}

func (a *Heap) Maximum() int {
	return a.At(0)
}

func (a *Heap) ExtractMax() (max int, err error) {
	if a.GetSize() < 1 {
		err = errors.New("Heap Underflow")
		return
	} else {
		max = a.At(0)
		a.Set(a.At(a.GetSize()), 0)
		a.SetSize(a.GetSize() - 1)
		a.MaxHeapify(0)
		return
	}
}

func (a *Heap) IncreaseKey(i int, key int) (err error) {
	if key < a.At(i) {
		return errors.New("New key is smaller than the current key")
	}

	a.Set(key, i)

	for i > 1 && a.At(a.Parent(i)) < a.At(i) {
		tmp := a.At(i)
		a.Set(a.At(a.Parent(i)), i)
		a.Set(tmp, a.Parent(i))
		i = a.Parent(i)
	}
	return
}

func (a *Heap) MaxHeapInsert(key int) {
	a.Append(math.MinInt32)
	a.SetSize(a.GetSize() + 1)
	a.IncreaseKey(a.GetSize()-1, key)
}
