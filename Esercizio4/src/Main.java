package src;

import java.io.File;
import java.io.FileNotFoundException;  
import java.util.Scanner;
import java.time.LocalTime;

public class Main {
   
   public static Graph<String,String> generateGraph(String classpath, boolean isOriented) {
      Graph<String,String> g = new Graph<String,String>(isOriented);
      try {
         File file_graph = new File(classpath);
         Scanner reader = new Scanner(file_graph);
         while(reader.hasNextLine()) {
            String data, v1, v2, label, reverseLabel;
            data = reader.nextLine();
            String[] keys = data.split(",");
            v1 = new String(keys[0]);
            v2 = new String(keys[1]);
            label = keys[0] + ':' + keys[1];            
            Double weight = Double.parseDouble(keys[2]);
            g.addNode(v1);
            g.addNode(v2);
            if(!isOriented) {
               reverseLabel = keys[1] + ":" + keys[0];
               g.addEdge(v1, v2, label, reverseLabel, weight);
            } else
               g.addEdge(v1, v2, label, null, weight);
         }
         reader.close();
      } catch(FileNotFoundException e) {
         System.out.println("Error occurred during reading");
         e.printStackTrace();
      }
      return g;
   }
   
   public static void main(String[] args) {
      if(args.length > 0) {
         System.out.println("Reading from file... started at " + LocalTime.now());
         Graph<String,String> g = generateGraph(args[0], false);
         System.out.println("DONE! Graph contains " + g.getNumNodes() + " nodes and " + g.getNumEdges() + " edges \n");
         System.out.println("Calculating... started at " + LocalTime.now());
         String src = "torino", dest = "catania";
         Double dest_distance = g.Dijkstra_alg(src, dest);
         System.out.println("DONE! Procedure ended at " + LocalTime.now());
         System.out.println("Path from Torino to Catania ( " + dest_distance/1000 + " km ): \n");
         g.getPath(src, dest);
      } else
         System.out.println("Error passing the command line argument: re-run with the path to the file italian_dist_graph.csv");
   }
}
