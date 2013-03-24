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
  g.addVertex(d);
  g.addVertex(c);
  int vertices_array[] = {2, 5, 13, 1};
  std::vector<int> v(vertices_array, vertices_array + sizeof(vertices_array) / sizeof(int) );
  Graph<int>::vertex_iterator g_it;
  std::vector<int>::iterator v_it;
  for (g_it = g.begin(), v_it = v.begin();
       g_it != g.end();
       g_it++, v_it++)
    assert(*g_it == *v_it);


  assert(g.neighboursOf(5).size() == 0);

  Graph<int> g2;
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.addVertex(4);

  int vertices_array2[] = {1, 2, 3, 4};
  std::vector<int> v2(vertices_array2, vertices_array2 + sizeof(vertices_array2) / sizeof(int) );
  for (g_it = g2.begin(), v_it = v2.begin();
       g_it != g2.end();
       g_it++, v_it++)
    assert(*g_it == *v_it);


  assert(g.addEdge(b, c) == true);
  assert(g.addEdge(a, d) == true);
  std::vector<Graph<int>::Edge> e = g.edges();

  assert(e.size() == 3);

  return 0;
}

