package sorting

func InsertionSort(items []int) {
  n := len(items)
  for i := 1; i < n; i++ {
    for j := i ; (j > 0) && (items[j] < items[j - 1]) ; j-- {
      tmp := items[j]
      items[j] = items[j - 1]
      items[j - 1] = tmp
    }
  }
}
