package src;

public class Vertex<K extends Comparable<K>> {   
   private K key;
   private Double distance;

   public Vertex(K key) {
      this.key = key;
   }

   public K getKey() {
      return this.key;
   }

   public Double getDistance() {
      return this.distance;
   }

   public void setDistance(Double distance) {
      this.distance = distance;
   }

}
