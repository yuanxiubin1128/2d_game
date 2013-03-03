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

  assert(g.neighboursOf(5).size() == 0);

  return 0;
}

