package src;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;
import java.util.Comparator;

public class Graph<L extends Comparable<L>, K extends Comparable<K>> {
   private HashMap<K, HashMap<K, Label<L>>> adjacency;
   private boolean isOriented;
   private HashMap<K, Vertex<K>> keyToVertex;
   private HashMap<K,K> parents;
   private HeapMin<Vertex<K>> queue;

   class VertexComparator implements Comparator<Vertex<K>> {
      @Override
      public int compare(Vertex<K> vertex1, Vertex<K> vertex2) {
         Double weight1 = vertex1.getDistance(), weight2 = vertex2.getDistance();
         if(weight1 < weight2)
            return -1;
         else if (weight1 > weight2)
            return 1;
         else 
            return vertex1.getKey().compareTo(vertex2.getKey());
      }
   }
   /* Creazione di un grafo vuoto - O(1) */
   public Graph(boolean isOriented) {
      this.adjacency = new HashMap<>();
      this.isOriented = isOriented;
      this.keyToVertex = new HashMap<>();
      this.parents = new HashMap<>();
      Comparator<Vertex<K>> comparator = new VertexComparator();
      this.queue = new HeapMin<Vertex<K>>(comparator);
   }
   /* Aggiunta di un nodo – O(1) */
   public void addNode(K key) {
      if(!adjacency.containsKey(key)){
         this.adjacency.put(key, new HashMap<>());
         Vertex<K> v = new Vertex<K>(key);
         this.keyToVertex.put(key, v);
      }
   }
   /* Aggiunta di un arco – O(1) */
   public void addEdge(K srcNode, K destNode, L label, L reverseLabel, Double weight) {
      if(! (adjacency.get(srcNode)).containsKey(destNode)) {
         Label<L> l = new Label<L>(label, weight);
         HashMap<K,Label<L>> toInsert;
         if(this.adjacency.get(srcNode).isEmpty())
            toInsert = new HashMap<>();
         else
            toInsert = this.adjacency.get(srcNode);
         
         toInsert.put(destNode, l);
         this.adjacency.put(srcNode, toInsert);
      }
      if(!isOriented) {
         addReverseEdge(destNode, srcNode, reverseLabel, weight);
      }
   }

   private void addReverseEdge(K srcNode, K destNode, L label, Double weight){
      if(! (adjacency.get(srcNode)).containsKey(destNode)) {
         Label<L> l = new Label<L>(label, weight);
         HashMap<K,Label<L>> toInsert;
         if(this.adjacency.get(srcNode).isEmpty())
            toInsert = new HashMap<>();
         else
            toInsert = this.adjacency.get(srcNode);
         
         toInsert.put(destNode, l);
         this.adjacency.put(srcNode, toInsert);
      }
   }
   /* Verifica se il grafo è diretto – O(1) */
   public boolean isOriented() {
      return this.isOriented;
   }
   /* Verifica se il grafo contiene un dato nodo – O(1) */
   public boolean containsNode(K node) {
      return this.adjacency.containsKey(node);
   }
   /* Verifica se il grafo contiene un dato arco – O(1) */
   public boolean containsEdge(K srcNode, K destNode) {
      return this.adjacency.get(srcNode).containsKey(destNode);
   }
   /* Cancellazione di un nodo – O(n) */
   public void removeNode(K node) {
      this.adjacency.remove(node);
      this.keyToVertex.remove(node);
      Set<K> keys = this.adjacency.keySet();
      for(K key : keys) {
         if(this.adjacency.get(key).containsKey(node))
            this.adjacency.get(key).remove(node);
      }
   }
   /* Cancellazione di un arco – O(1) */
   public void removeEdge(K srcNode, K destNode) {
      if(this.adjacency.get(srcNode).containsKey(destNode))
         this.adjacency.get(srcNode).remove(destNode);
      if(!isOriented) {
         if(this.adjacency.get(destNode).containsKey(srcNode))
            this.adjacency.get(destNode).remove(srcNode);
      }
   }
   /* Determinazione del numero di nodi – O(1) */
   public int getNumNodes() {
      return this.adjacency.size();
   }
   /* Determinazione del numero di archi – O(n) */
   public int getNumEdges() {
      int ris = 0;
      Set<K> keys = this.adjacency.keySet();
      for(K key : keys) {
         ris += this.adjacency.get(key).size();
      }
      return ris;
   }
   /* Recupero dei nodi del grafo – O(n) */
   public ArrayList<K> getAllNodes() {
      ArrayList<K> nodes = new ArrayList<>();
      Set<K> keys = this.adjacency.keySet();
      for(K key : keys) {
         nodes.add(key);
      }
      return nodes;
   }
   /* Recupero degli archi del grafo – O(n) */
   public ArrayList<Label<L>> getAllEdges() {
      ArrayList<Label<L>> edges = new ArrayList<>();
      Set<K> keys = this.adjacency.keySet();
      for(K key : keys) {
         Set<K> adj = this.adjacency.get(key).keySet();
         for(K k : adj)
            edges.add(this.adjacency.get(key).get(k));
      }
      return edges;
   }
   /* Recupero nodi adiacenti di un dato nodo – O(1)  (*) */
   public ArrayList<K> getAllNodesAdjToNode(K node) {
      ArrayList<K> nodes = new ArrayList<K>();
      Set<K> keys = this.adjacency.get(node).keySet();
      for(K key : keys)
         nodes.add(key);
      return nodes;
   }
   /* Recupero etichetta associata a una coppia di nodi – O(1) (*) */
   public Label<L> getLabelFromNodes(K srcNode, K destNode) {
      return this.adjacency.get(srcNode).get(destNode);
   }

   public Double Dijkstra_alg(K srcNode, K destNode) { 
      initializeSingleSource(srcNode);
      for(K key : this.adjacency.keySet()) {
         this.queue.insertElement(this.keyToVertex.get(key));
      }
      while(this.queue.getHeapSize() > 0) {
         Vertex<K> vertex = this.queue.extractMinimum();
         ArrayList<K> adj = getAllNodesAdjToNode(vertex.getKey());
         for(K key : adj) {
            relax(vertex, this.keyToVertex.get(key));
         }
      }
      return ( (this.keyToVertex.get(destNode)).getDistance());
   }

   private void initializeSingleSource(K srcNode) { 
      ArrayList<K> nodes = getAllNodes();
      for(K key : nodes) {
         if(key.compareTo(srcNode) == 0)
            this.keyToVertex.get(key).setDistance(0.0); 
         else
            this.keyToVertex.get(key).setDistance(Double.MAX_VALUE);
         
         this.parents.put(key, null);
      }
   }

   private void relax(Vertex<K> v1, Vertex<K> v2) { 
      Double v1_distance = v1.getDistance(), v2_distance = v2.getDistance();
      Double edge_weight = this.adjacency.get(v1.getKey()).get(v2.getKey()).getWeight();
      if(v2_distance > v1_distance + edge_weight) {
         Vertex<K> new_Vertex2 = new Vertex<K>(v2.getKey());
         new_Vertex2.setDistance(v1_distance + edge_weight);
         this.keyToVertex.replace(v2.getKey(), new_Vertex2);
         this.parents.put(v2.getKey(), v1.getKey());
         this.queue.decreaseKey(v2, new_Vertex2);
      }
   }

   public void getPath(K srcNode, K destNode) {
      ArrayList<K> path = new ArrayList<>();
      K step = destNode;
      while(step.compareTo(srcNode) != 0) {
         path.add(step);
         step = this.parents.get(step);
      }
      path.add(srcNode);
      for(int i=path.size()-1; i>=0; i--) {
         if(i % 5 != 0)
            System.out.print(path.get(i) + " - ");
         else 
            System.out.println(path.get(i));
      }
      System.out.println();
   }
}
