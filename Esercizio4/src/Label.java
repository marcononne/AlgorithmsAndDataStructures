package src;

public class Label<L extends Comparable<L>> {
   private L label;
   private Double weight;
 
   public Label(L label, Double weight) {
      this.label = label;
      this.weight = weight;
   }

   public L getLabel() {
      return this.label;
   }

   public Double getWeight() {
      return this.weight;
   }

   public void setWeight(Double weight) {
      this.weight = weight;
   }

}
