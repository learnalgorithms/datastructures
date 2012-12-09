package stack

type Element struct {
	Value interface {}
	Next *Element
}

type Stack struct {
	top *Element
	len int
}



func (stack *Stack) Pop() interface{} {
	topElement := stack.top
	stack.top = topElement.Next
	stack.len--
	return topElement.Value
}
func (stack *Stack) Push (value interface{}) {
	newElement := new(Element)
	newElement.Value = value
	newElement.Next = stack.top
	stack.len++
	stack.top = newElement
}

func (stack *Stack) Len () int {
	return stack.len
}

func (stack *Stack) Init () {
	stack.len = 0
	stack.top = nil
}
