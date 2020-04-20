package sorting;

import java.util.*;

public class MergeSort {

	private ArrayList<Integer> numberList;
	
	public static void main(String[] args) {
		ArrayList<Integer> myList = new ArrayList<Integer>();
        myList.add(7);
		myList.add(2);
        myList.add(5);
        myList.add(8);
		myList.add(3);
        myList.add(6);
		myList.add(1);
		myList.add(4);
        MergeSort test = new MergeSort();
		ArrayList<Integer> resultList = test.sort(myList);
        Iterator<Integer> i = myList.iterator();
        while(i.hasNext()){
             System.out.println(i.next());
        }
	}
	
	public ArrayList<Integer> sort(ArrayList<Integer> values){
		this.numberList = values;
		this.mergeSort(0, this.numberList.size() - 1);
		return this.numberList;
		
	}
	
	private void mergeSort(int low, int high) {
        System.out.print("MergeSorting: ");
        for(int i = low; i <= high; i++){
            System.out.print(this.numberList.get(i));
        }
        System.out.println("");
		if (low < high) {
			int middle = (high+low)/2;
			mergeSort(low,middle);
			mergeSort(middle+1,high);
			this.merge(low, middle, high);
			}
	}

	private void merge(int low, int middle, int high) {
		Stack<Integer> left = new Stack<Integer>(); 
		Stack<Integer> right = new Stack<Integer>();
		
		for (int i = middle; i >= low; i--){
			left.push(this.numberList.get(i));
		}
		
		for (int i = high; i >= middle+1; i--){
			right.push(this.numberList.get(i));
		}

		for(int i = low; i <= high; i++){
			if(right.isEmpty() || (!left.isEmpty() && left.peek() < right.peek())){
				this.numberList.set(i, left.pop());
			}
			else {
				this.numberList.set(i, right.pop());
			}
		}
		
	}

}
