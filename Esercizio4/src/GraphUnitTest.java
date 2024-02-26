package src;

import java.util.ArrayList;
import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.Test;
import org.junit.Before;

public class GraphUnitTest {

   class IntegerVertexComparator implements Comparator<Vertex<Integer>> {
      @Override
      public int compare(Vertex<Integer> v1, Vertex<Integer> v2) {
        return v1.getKey().compareTo(v2.getKey());
      }
   }

   Graph<String,Integer> oriented_graph;
   Graph<String,Integer> not_oriented_graph;
   Comparator<Vertex<Integer>> c_int = new IntegerVertexComparator();

   @Before
   public void createGraphs() {
      oriented_graph = new Graph<String,Integer>(true);
      not_oriented_graph = new Graph<String,Integer>(false);
   }

   @Test
   public void testEmptyOrientedGraph() {
      assertTrue(oriented_graph.getNumNodes() == 0 && oriented_graph.isOriented());
   }

   @Test
   public void testEmptyNotOrientedGraph() {
      assertTrue(not_oriented_graph.getNumNodes() == 0 && !not_oriented_graph.isOriented());
   }

   @Test
   public void testOneNodeOrientedGraph() {
      int vertex = 0;
      oriented_graph.addNode(vertex);
      assertTrue(oriented_graph.getNumNodes() == 1 && oriented_graph.containsNode(vertex));
   }

   @Test
   public void testOneVertexNotOrientedGraph() {
      int vertex = 10;
      not_oriented_graph.addNode(vertex);
      assertTrue(not_oriented_graph.getNumNodes() == 1 && not_oriented_graph.containsNode(vertex));
   }

   @Test
   public void testOneEdgeOrientedGraph() {
      int v0 = 0, v1 = 1;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v1);
      oriented_graph.addEdge(v0, v1, "0:1", null, 7.0);
      assertTrue( oriented_graph.getNumNodes() == 2 && oriented_graph.getNumEdges() == 1);
   }

   @Test
   public void testOneEdgeNotOrientedGraph() {
      int v0 = 0, v1 = 1;
      not_oriented_graph.addNode(v0);
      not_oriented_graph.addNode(v1);
      not_oriented_graph.addEdge(v0, v1, "0:1", "1:0", 7.0);
      assertTrue( not_oriented_graph.getNumNodes() == 2 && not_oriented_graph.getNumEdges() == 2);
   }

   @Test 
   public void testRemoveVertexOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v2);
      oriented_graph.addNode(v3);
      oriented_graph.addEdge(v0, v2, "0:2", null, 6.5);
      oriented_graph.addEdge(v0, v3, "0:3", null, 2.45);
      oriented_graph.removeNode(v0);
      assertTrue(!oriented_graph.containsNode(v0) && oriented_graph.getNumNodes() == 2 && oriented_graph.getNumEdges() == 0);
   }

   @Test 
   public void testRemoveVertexNotOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      not_oriented_graph.addNode(v0);
      not_oriented_graph.addNode(v2);
      not_oriented_graph.addNode(v3);
      not_oriented_graph.addEdge(v0, v2, "0:2", "2:0", 6.5);
      not_oriented_graph.addEdge(v0, v3, "0:3", "3:0", 2.45);
      not_oriented_graph.removeNode(v0);
      assertTrue(!not_oriented_graph.containsNode(v0) && not_oriented_graph.getNumNodes() == 2 && oriented_graph.getNumEdges() == 0);
   }

  @Test 
   public void testRemoveEdgeOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v2);
      oriented_graph.addNode(v3);
      oriented_graph.addEdge(v0, v2, "0:2", null, 6.5);
      oriented_graph.addEdge(v0, v3, "0:3", null, 2.45);
      oriented_graph.removeEdge(v0, v2);
      assertTrue(oriented_graph.getNumNodes() == 3 && oriented_graph.getNumEdges() == 1 
                  && !oriented_graph.containsEdge(v0,v2) && oriented_graph.containsEdge(v0, v3));
   }

   @Test 
   public void testRemoveEdgeNotOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      not_oriented_graph.addNode(v0);
      not_oriented_graph.addNode(v2);
      not_oriented_graph.addNode(v3);
      not_oriented_graph.addEdge(v0, v2, "0:2", "2:0", 6.5);
      not_oriented_graph.addEdge(v0, v3, "0:3", "3:0", 2.45);
      not_oriented_graph.removeEdge(v0, v2);
      assertTrue( not_oriented_graph.getNumNodes() == 3 && not_oriented_graph.getNumEdges() == 2 
                  && !not_oriented_graph.containsEdge(v0,v2) && !not_oriented_graph.containsEdge(v2, v0)
                  && not_oriented_graph.containsEdge(v0, v3) && not_oriented_graph.containsEdge(v3, v0) );
   }

   @Test 
   public void testGetAllNodesOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v2);
      oriented_graph.addNode(v3);
      ArrayList<Integer> nodes = oriented_graph.getAllNodes();
      assertTrue( nodes.size() == 3 && nodes.contains(v0) && nodes.contains(v2) && nodes.contains(v3));
   }

   @Test 
   public void testGetAllNodesNotOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      not_oriented_graph.addNode(v0);
      not_oriented_graph.addNode(v2);
      not_oriented_graph.addNode(v3);
      ArrayList<Integer> nodes = not_oriented_graph.getAllNodes();
      assertTrue( nodes.size() == 3 && nodes.contains(v0) && nodes.contains(v2) && nodes.contains(v3));
   }

   @Test
   public void testGetAllAdjToNodeOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v2);
      oriented_graph.addNode(v3);
      oriented_graph.addEdge(v0, v2, "0:2", null, 6.5);
      oriented_graph.addEdge(v0, v3, "0:3", null, 2.45);
      ArrayList<Integer> adj = oriented_graph.getAllNodesAdjToNode(v0);
      assertTrue(adj.size() == 2 && adj.contains(v2) && adj.contains(v3));
   }

   @Test
   public void testGetAllAdjToNodeNotOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      not_oriented_graph.addNode(v0);
      not_oriented_graph.addNode(v2);
      not_oriented_graph.addNode(v3);
      not_oriented_graph.addEdge(v0, v2, "0:2", "2:0", 6.5);
      not_oriented_graph.addEdge(v0, v3, "0:3", "3:0", 2.45);
      ArrayList<Integer> adj = not_oriented_graph.getAllNodesAdjToNode(v2);
      assertTrue(adj.size() == 1 && adj.contains(v0));
   }

   @Test 
   public void testGetLabelOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v2);
      oriented_graph.addNode(v3);
      oriented_graph.addEdge(v0, v2, "0:2", null, 6.5);
      oriented_graph.addEdge(v0, v3, "0:3", null, 2.45);
      assertEquals("0:2",oriented_graph.getLabelFromNodes(v0, v2).getLabel());
   }

   @Test 
   public void testGetLabelNotOrientedGraph() {
      int v0 = 0, v2 = 2, v3 = 3;
      not_oriented_graph.addNode(v0);
      not_oriented_graph.addNode(v2);
      not_oriented_graph.addNode(v3);
      not_oriented_graph.addEdge(v0, v2, "0:2", "2:0", 6.5);
      not_oriented_graph.addEdge(v0, v3, "0:3", "3:0", 2.45);
      assertEquals("2:0",not_oriented_graph.getLabelFromNodes(v2, v0).getLabel());
   }

   @Test 
   public void testDijkstraOrientedGraph() {
      int v0 = 0, v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7;
      oriented_graph.addNode(v0);
      oriented_graph.addNode(v1);
      oriented_graph.addNode(v2);
      oriented_graph.addNode(v3);
      oriented_graph.addNode(v4);
      oriented_graph.addNode(v5);
      oriented_graph.addNode(v6);
      oriented_graph.addNode(v7);

      oriented_graph.addEdge(v0, v2, "0:2", null, 6.0);
      oriented_graph.addEdge(v0, v3, "0:3", null, 4.0);
      oriented_graph.addEdge(v1, v2, "1:2", null, 2.0);
      oriented_graph.addEdge(v1, v6, "1:6", null, 9.0);
      oriented_graph.addEdge(v2, v5, "2:5", null, 8.0);
      oriented_graph.addEdge(v3, v5, "3:5", null, 4.0);
      oriented_graph.addEdge(v6, v2, "6:2", null, 3.0);
      oriented_graph.addEdge(v7, v6, "7:6", null, 5.0);

      Double v1_distance = oriented_graph.Dijkstra_alg(v0, v1),
             v2_distance = oriented_graph.Dijkstra_alg(v0, v2),
             v3_distance = oriented_graph.Dijkstra_alg(v0, v3),
             v4_distance = oriented_graph.Dijkstra_alg(v0, v4),
             v5_distance = oriented_graph.Dijkstra_alg(v0, v5),
             v6_distance = oriented_graph.Dijkstra_alg(v0, v6),
             v7_distance = oriented_graph.Dijkstra_alg(v0, v7);
      
      assertTrue( v1_distance == Double.MAX_VALUE && v2_distance == 6.0 &&
                  v3_distance == 4.0 && v4_distance == Double.MAX_VALUE && v5_distance == 8.0 && 
                  v6_distance == Double.MAX_VALUE && v7_distance == Double.MAX_VALUE);
   }
}
