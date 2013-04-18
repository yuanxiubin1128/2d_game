#include <iostream>
#include <cassert>


#include "graph.h"

int main()
{
  Graph<int> g;

  assert(g.empty() == true);
  assert(g.numberOfVertices() == 0);
  assert(g.numberOfEdges() == 0);


  int a = 2;
  int b = 5;
  assert(g.addEdge(a, b) == false);

  assert(g.addVertex(a) == true);
  assert(g.addVertex(a) == false);
  assert(g.empty() == false);
  assert(g.numberOfVertices() == 1);
  {
    const std::vector<int*> v = g.vertices();
    assert(v.size() == 1);
    assert(*(v[0]) == 2);
  }

  assert(g.addEdge(a, b) == false);

  assert(g.addVertex(b) == true);
  assert(g.numberOfVertices() == 2);
  {
    const std::vector<int*> v = g.vertices();
    assert(v.size() == 2);
    assert(*(v[0]) == 2);
    assert(*(v[1]) == 5);
  }

  assert(g.numberOfEdges() == 0);
  assert(g.addEdge(a, b) == true);

  assert(g.numberOfEdges() == 1);
  {
    const std::vector<float> eb = g.edgesBetween(2, 5);
    assert(eb.size() == 1);
    assert(eb[0] == 0);
  }
  assert(g.edgesBetween(5, 2).size() == 0);
  assert(g.neighboursOf(2).size() == 1);
  {
    const std::vector<int*> n = g.neighboursOf(2);
    assert(n.size() == 1);
    assert(*(n[0]) == 5);
  }

  int c = 13;
  int d = 1;
  assert(g.numberOfVertices() == 2);
  g.addVertex(c);
  g.addVertex(d);
  assert(g.numberOfVertices() == 4);
  int vertices_array[] = {2, 5, 13, 1};
  std::vector<int> v(vertices_array, vertices_array + sizeof(vertices_array) / sizeof(int) );
  Graph<int>::vertex_iterator g_it;
  std::vector<int>::iterator v_it;

  for (g_it = g.vertex_begin(), v_it = v.begin();
       g_it != g.vertex_end();
       g_it++, v_it++) {
    assert(**g_it == *v_it);
  }


  assert(g.neighboursOf(5).size() == 0);

  Graph<int> g2;
  g2.addVertex(1);
  g2.addVertex(2);
  g2.addVertex(3);
  g2.addVertex(4);

  int vertices_array2[] = {1, 2, 3, 4};
  std::vector<int> v2(vertices_array2, vertices_array2 + sizeof(vertices_array2) / sizeof(int) );
  for (g_it = g2.vertex_begin(), v_it = v2.begin();
       g_it != g2.vertex_end();
       g_it++, v_it++) {
    std::cout << "vector: "
              << *g_it << " "
              << **g_it
              << std::endl;
    assert(**g_it == *v_it);
  }


  assert(g2.addEdge(1, 2) == true);
  assert(g2.addEdge(1, 3) == true);
  assert(g2.addEdge(2, 4) == true);
  std::vector<Graph<int>::Edge> e = g2.edges();

  assert(e.size() == 3);

  for(Graph<int>::edge_iterator edge_it = g2.edge_begin();
      edge_it != g2.edge_end();
      ++edge_it) {
    Graph<int>::pointer source = (*edge_it).getSource();
    Graph<int>::pointer destination = (*edge_it).getDestination();
    std::cout << "edge: "
              << source << " " << *source << " "
              << destination << " " << *destination << " "
              << (*edge_it).getWeight() << std::endl;
  }

  std::cout << "frankon vege" << std::endl;
  return 0;
}

