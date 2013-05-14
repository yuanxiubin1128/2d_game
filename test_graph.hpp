#include <cxxtest/TestSuite.h>

#include "graph.hpp"


namespace test { class TestSubsystem1DummyClassSuite; }

class test::TestSubsystem1DummyClassSuite : public CxxTest::TestSuite
{

public:

  void testBasic()
  {

  Graph<int> g;

  TS_ASSERT_EQUALS(g.empty(), true);
  TS_ASSERT_EQUALS(g.numberOfVertices(), 0);
  TS_ASSERT_EQUALS(g.numberOfEdges(), 0);


  int a = 2;
  int b = 5;
  TS_ASSERT_EQUALS(g.addEdge(a, b), false);

  TS_ASSERT_EQUALS(g.addVertex(a), true);
  TS_ASSERT_EQUALS(g.addVertex(a), false);
  TS_ASSERT_EQUALS(g.empty(), false);
  TS_ASSERT_EQUALS(g.numberOfVertices(), 1);
  {
    const std::vector<const int*> v = g.vertices();
    TS_ASSERT_EQUALS(v.size(), 1);
    TS_ASSERT_EQUALS(*(v[0]), 2);
  }

  TS_ASSERT_EQUALS(g.addEdge(a, b), false);

  TS_ASSERT_EQUALS(g.addVertex(b), true);
  TS_ASSERT_EQUALS(g.numberOfVertices(), 2);
  {
    const std::vector<const int*> v = g.vertices();
    TS_ASSERT_EQUALS(v.size(), 2);
    TS_ASSERT_EQUALS(*(v[0]), 2);
    TS_ASSERT_EQUALS(*(v[1]), 5);
  }

  TS_ASSERT_EQUALS(g.numberOfEdges(), 0);
  TS_ASSERT_EQUALS(g.addEdge(a, b), true);

  TS_ASSERT_EQUALS(g.numberOfEdges(), 1);
  {
    const std::vector<int> eb = g.weightsBetween(2, 5);
    TS_ASSERT_EQUALS(eb.size(), 1);
    TS_ASSERT_EQUALS(eb[0], 0);
  }
  TS_ASSERT_EQUALS(g.weightsBetween(5, 2).size(), 0);
  TS_ASSERT_EQUALS(g.neighboursOf(2).size(), 1);
  {
    const std::vector<const int*> n = g.neighboursOf(2);
    TS_ASSERT_EQUALS(n.size(), 1);
    TS_ASSERT_EQUALS(*(n[0]), 5);
  }

  int c = 13;
  int d = 1;
  TS_ASSERT_EQUALS(g.numberOfVertices(), 2);
  g.addVertex(c);
  g.addVertex(d);
  TS_ASSERT_EQUALS(g.numberOfVertices(), 4);
  int vertices_array[] = {2, 5, 13, 1};
  std::vector<int> v(vertices_array, vertices_array + sizeof(vertices_array) / sizeof(int) );
  Graph<int>::vertex_iterator g_it2;
  std::vector<int>::iterator v_it = v.begin();
  g_it2 = g.vertex_begin();
  TS_ASSERT_EQUALS(g_it2, g.vertex_begin());

  for (Graph<int>::vertex_iterator g_it = g.vertex_begin();
       g_it != g.vertex_end();
       ++g_it, ++v_it) {
    std::cout << "victor: "
//               << *g_it << " "
              << *g_it
              << std::endl;
    TS_ASSERT_EQUALS(*g_it, *v_it);
  }


  TS_ASSERT_EQUALS(g.neighboursOf(5).size(), 0);

  Graph<int> g2;
  g2.addVertex(1);
  g2.addVertex(2);
  g2.addVertex(3);
  g2.addVertex(4);

  int vertices_array2[] = {1, 2, 3, 4};
  std::vector<int> v2(vertices_array2, vertices_array2 + sizeof(vertices_array2) / sizeof(int) );
   v_it = v2.begin();
  for (Graph<int>::vertex_iterator g_it = g2.vertex_begin();
       g_it != g2.vertex_end();
       ++g_it, ++v_it) {
//     std::cout << "vector: "
//               << *g_it
//               << std::endl;
    TS_ASSERT_EQUALS(*g_it, *v_it);
  }


  TS_ASSERT_EQUALS(g2.addEdge(1, 2), true);
  TS_ASSERT_EQUALS(g2.addEdge(1, 3), true);
  TS_ASSERT_EQUALS(g2.addEdge(2, 4), true);
  std::vector<Graph<int>::Edge> e = g2.edges();
  TS_ASSERT_EQUALS(e.size(), 3);

  Graph<int>::edge_iterator edge_it;
  Graph<int>::edge_iterator beee = g2.edge_begin();
  edge_it = beee;
//    TS_ASSERT_EQUALS(edge_it, g2.edge_begin());
    int source = (*edge_it).getSource();
    int destination = (*edge_it).getDestination();
    TS_ASSERT_EQUALS (source, 1);
    TS_ASSERT_EQUALS (destination, 2);

    ++edge_it;
    source = (*edge_it).getSource();
    destination = (*edge_it).getDestination();
    TS_ASSERT_EQUALS (source, 1);
    TS_ASSERT_EQUALS (destination, 3);

     ++edge_it;
    source = (*edge_it).getSource();
    destination = (*edge_it).getDestination();
    TS_ASSERT_EQUALS (source, 2);
    TS_ASSERT_EQUALS (destination, 4);

  int aasdads = 23;
//   Graph<int>::edge_iterator edge_it;

  for(/*Graph<int>::edge_iterator*/ edge_it = g2.edge_begin(); edge_it != g2.edge_end(); ++edge_it) {
    int source = (*edge_it).getSource();
    int destination = (*edge_it).getDestination();
//     std::cout << "edge: "
//               << source << " "
//               << destination << " "
//               << (*edge_it).getWeight() << std::endl;
  }

  Graph<int>::edge_iterator edge_it1 = g2.edge_begin();
  edge_it1 += 10;
  TS_ASSERT_EQUALS(edge_it1, g2.edge_end());

  Graph<int>::edge_iterator edge_it2 = g2.edge_begin();
  edge_it2 += 2;
  TS_ASSERT_EQUALS( (*edge_it2).getSource(), 2);
  TS_ASSERT_EQUALS( (*edge_it2).getDestination(), 4);
  TS_ASSERT_EQUALS((*edge_it2).getWeight(), 0);

//   toDot(g2, "itt.dot");
//   Graph<int> read_g;
//   fromDot("itt.dot", read_g);
//   TS_ASSERT_EQUALS(g2, read_g);



  Graph<int> g4;
  g4.addVertex(3);
  Graph<int> g5 = g4;
  Graph<int> g6;
  g6 = g5;
  g6.removeVertex(3);
}

};
