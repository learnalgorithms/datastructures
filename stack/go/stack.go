// Copyright 2012 Francisco Dalla Rosa Soares. All rights reserved.

//Package stack implements a  stack
// use stack := new(Stack) to create a new stack
//and Pop and Push to add and retrieve objects from the stack

package stack

// Element is an element in the stack
type Element struct {

	Value interface {}
	
	Next *Element
}

//The stack representation. 
//The zero value of the Stack is an empty stack ready to use
type Stack struct {
	top *Element
	len int
}

func (stack *Stack) Top() interface{} {
  return stack.top.Value
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

//Init is not necessary to initialize a new stack.
//Use it to Re-initialize an existing stack
func (stack *Stack) Init () {
	stack.len = 0
	stack.top = nil
}
