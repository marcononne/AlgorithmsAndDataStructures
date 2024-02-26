package src;

import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.Test;
import org.junit.Before;

public class HeapMinUnitTest {

   class IntegerComparator implements Comparator<Integer> {
      @Override
      public int compare(Integer i1, Integer i2){
          return i1.compareTo(i2);
      }
  }

   class StringComparator implements Comparator<String> {
   @Override
   public int compare(String i1, String i2){
       return i1.compareTo(i2);
   }
}

   class DoubleComparator implements Comparator<Double> {
      @Override
      public int compare(Double i1, Double i2){
         return i1.compareTo(i2);
      }
   }
   
   static HeapMin<String> stringMinHeap;
   static HeapMin<Integer> intMinHeap;
   static HeapMin<Double> doubleMinHeap;
   Comparator<Integer> c_int = new IntegerComparator();
   Comparator<String> c_string = new StringComparator();
   Comparator<Double> c_double = new DoubleComparator();

   @Before
   public void createMinHeaps() {
      stringMinHeap = new HeapMin<>(c_string);
      intMinHeap = new HeapMin<>(c_int);
      doubleMinHeap = new HeapMin<>(c_double);
   }
   
   @Test
   public void testEmptyHeap() {
      assertEquals(stringMinHeap.getHeapSize(), 0);
   }

   @Test 
   public void testOneStringInHeap() {
      stringMinHeap.insertElement("dirigente");
      assertEquals(stringMinHeap.getHeapSize(), 1);
   }

   @Test
   public void testGetLeftChild() {
      stringMinHeap.insertElement("dirigente");
      stringMinHeap.insertElement("zaino");
      stringMinHeap.insertElement("dottore");
      assertEquals(stringMinHeap.getLeftChild("dirigente"), "zaino");
   }

   @Test
   public void testGetRightChild() {
      stringMinHeap.insertElement("dirigente");
      stringMinHeap.insertElement("zaino");
      stringMinHeap.insertElement("dottore");
      assertEquals(stringMinHeap.getRightChild("dirigente"), "dottore");
   }

   @Test
   public void testExtractMinimum() {
      intMinHeap.insertElement(100);
      intMinHeap.insertElement(95);
      intMinHeap.insertElement(200);
      intMinHeap.insertElement(87);
      intMinHeap.insertElement(4);
      intMinHeap.insertElement(5);
      intMinHeap.insertElement(6);
      assertEquals((Integer)4, intMinHeap.extractMinimum());
   }

   @Test
   public void testDecreaseKey() {
      doubleMinHeap.insertElement(10.35);
      doubleMinHeap.insertElement(9.37);
      doubleMinHeap.insertElement(9.38);
      doubleMinHeap.insertElement(40.29);
      doubleMinHeap.insertElement(18.17);
      doubleMinHeap.insertElement(9.41);
      doubleMinHeap.insertElement(99.01);
      doubleMinHeap.decreaseKey(99.01, 98.99);
      assertEquals(doubleMinHeap.getRightChild(9.38), (Double)98.99);
   }

   @Test
   public void testDecreasedKeyBecomesMinimum() {
      doubleMinHeap.insertElement(10.35);
      doubleMinHeap.insertElement(9.37);
      doubleMinHeap.insertElement(9.38);
      doubleMinHeap.insertElement(40.29);
      doubleMinHeap.insertElement(18.17);
      doubleMinHeap.insertElement(9.41);
      doubleMinHeap.insertElement(99.01);
      doubleMinHeap.decreaseKey(99.01, 5.02);
      assertEquals(doubleMinHeap.extractMinimum(),(Double)5.02);
   }
}
