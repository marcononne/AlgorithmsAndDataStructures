package src;

import java.util.*;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
/**  
 * COMPILAZIONE ED ESECUZIONE
 * Posizionarsi nella cartella dell'Esercizio (cartella padre di src) dove sono salvati i due file .jar
 * SEQUENZA COMANDI
 * javac src/HeapMin.java
 * javac -classpath .:hamcrest-core-1.3.jar:junit-4.12.jar src/HeapMinUnitTest.java 
 * javac -classpath .:hamcrest-core-1.3.jar:junit-4.12.jar src/HeapMinUnitTestRunner.java 
 * java -classpath .:hamcrest-core-1.3.jar:junit-4.12.jar src/HeapMinUnitTestRunner 
 */
public class HeapMinUnitTestRunner {
   public static void main(String[] args) {
      Result result = JUnitCore.runClasses(HeapMinUnitTest.class);
      for(Failure failure : result.getFailures()) {
         System.out.println(failure.toString());
      }
      System.out.println("Risultato dei test: " + result.wasSuccessful());
   }
}
