package src;

import java.util.*;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

/**  
 * COMPILAZIONE ED ESECUZIONE
 * Posizionarsi nella cartella dell'Esercizio (cartella padre di src) dove sono salvati i due file .jar
 * SEQUENZA COMANDI
 * javac src/Vertex.java src/Label.java src/HeapMin.java src/Graph.java
 * javac -classpath .:hamcrest-core-1.3.jar:junit-4.12.jar src/GraphUnitTest.java 
 * javac -classpath .:hamcrest-core-1.3.jar:junit-4.12.jar src/GraphUnitTestRunner.java 
 * java -classpath .:hamcrest-core-1.3.jar:junit-4.12.jar src/GraphUnitTestRunner 
 */
public class GraphUnitTestRunner {
   public static void main(String[] args) {
      Result result = JUnitCore.runClasses(GraphUnitTest.class);
      for(Failure failure : result.getFailures()) {
         System.out.println(failure.toString());
      }
      System.out.println("Risultato dei test: " + result.wasSuccessful());
   }
}

