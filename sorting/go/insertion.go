package main

import "fmt"

func sort(items []int, n int) {
  for i := 1; i < n; i++ {
    for j := i ; (j > 0) && (items[j] < items[j - 1]) ; j-- {
      tmp := items[j]
      items[j] = items[j - 1]
      items[j - 1] = tmp
    }
  }
}

func main() {
  list := []int{3,4,2,1,5,7,8}
  sort(list,7)
  for _,i := range(list) {
    fmt.Println(i)
  }
}
