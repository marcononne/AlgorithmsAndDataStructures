package src;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Comparator;

public class HeapMin<T> {
   private ArrayList<T> heapmin;
   private int size;       // current number of T elements inside the array
   private HashMap<T, Integer> map;
   private Comparator<? super T> comparator = null;

   public HeapMin(Comparator<? super T> comparator) {
      this.size = 0;
      this.heapmin = new ArrayList<T>();
      this.map = new HashMap<T, Integer>();
      this.comparator = comparator;
   }

   public int getParentIndex(T child) {
      return getParentIndex(map.get(child));
   }

   private int getParentIndex(int childIndex) {
      if(childIndex <= 2)
         return 0;
      return  (childIndex-1) / 2;
   }

   public int getLeftChildIndex(T parent) {
      return getLeftChildIndex(map.get(parent));
   }

   private int getLeftChildIndex(int parentIndex) {
      if( (2*parentIndex)+1 < size)
         return ((2*parentIndex)+1);
      else
         return parentIndex;
   }

   public int getRightChildIndex(T parent) {
      return getRightChildIndex(map.get(parent));
   }

   private int getRightChildIndex(int parentIndex) {
      if( 2*(parentIndex+1) < size)
         return (2*(parentIndex+1));
      else
         return parentIndex;
   }

   public T getParent(T child) {
      return getParent(map.get(child));
   }

   private T getParent(int childIndex) {
      return this.heapmin.get(getParentIndex(childIndex));
   }

   public T getLeftChild(T parent) {
      return getLeftChild(map.get(parent));
   }

   private T getLeftChild(int parentIndex) {
      return this.heapmin.get(getLeftChildIndex(parentIndex));
   }

   public T getRightChild(T parent) {
      return getRightChild(map.get(parent));
   }

   private T getRightChild(int parentIndex) {
      return this.heapmin.get(getRightChildIndex(parentIndex));
   }

   public void insertElement(T element) {
      heapmin.add(size, element);
      map.put(element, size);
      
      int i = size;
      while(i > 0 && this.comparator.compare(heapmin.get(i), heapmin.get(getParentIndex(i))) < 0) {
         swap(heapmin.get(i), heapmin.get(getParentIndex(i)));
         i = getParentIndex(i);
      }
      size++;
   }

   /**
    * Swap positions of two items in the heap
    * @param item1
    * @param item2
    */
    private void swap(T item1, T item2) {
      int index1 = map.get(item1), index2 = map.get(item2);
      map.replace(item1, index1, index2);
      map.replace(item2, index2, index1);
      swapPositions(index1, index2);
   }
   
   /**
    * Swap positions of two items in the heap.
    * This method doesn't do the changes in the hashtable.
    * @param index of first item
    * @param index of second item
    */
   private void swapPositions(int firstIndex, int secondIndex) {
      T temp = heapmin.get(firstIndex);
      heapmin.set(firstIndex, heapmin.get(secondIndex));
      heapmin.set(secondIndex, temp);
   }

   public int getHeapSize() {
      return this.size;
   }

   public T extractMinimum() {
      T min = this.heapmin.get(0);
      map.remove(min);
      size--;

      T newRoot = this.heapmin.get(this.size);
      this.heapmin.set(0, newRoot);
      map.put(newRoot, 0);

      heapify(0);
      return min;
   }

   private void heapify(int index) {
      T parent = heapmin.get(index), leftChild = getLeftChild(parent), rightChild = getRightChild(parent);

      if( index < (this.size / 2) && index < this.size)  {  // checking if array[index] is a leaf, if not i can procede
         if( ( this.comparator.compare(parent, leftChild) > 0 )
          || ( this.comparator.compare(parent, rightChild) > 0 )) { // if parent is greater than one of its children
            if( ( this.comparator.compare(leftChild, rightChild) < 0 ) ) {
            // the left child is the smaller one, i'm going to swap it with its parent
            	swap(parent, leftChild);
            	heapify(getLeftChildIndex(index));
            } 
            else {
            // the right child is the smaller one, i'm going to swap it with its parent
                swap(parent, rightChild); 
                heapify(getRightChildIndex(index));
            }
         }
      }
   }

   public void print() {
      for (int i = 0; i < this.size; i++) {
         System.out.println("-" + i + " " + heapmin.get(i));
      }
      System.out.print("\n\n\n");
   }

   public void decreaseKey(T oldKey, T newKey){
      if(this.comparator.compare(oldKey, newKey) < 0)
         return;
      
      int i = map.get(oldKey);
      
      map.remove(oldKey);
      map.put(newKey, i);
      heapmin.set(i, newKey);
      
      while(i > 0 && this.comparator.compare(heapmin.get(i), heapmin.get(getParentIndex(i))) < 0) {
         swap(heapmin.get(i), heapmin.get(getParentIndex(i)));
         i = getParentIndex(i);
      }
   }

}
