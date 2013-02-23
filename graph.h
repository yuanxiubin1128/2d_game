#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>

// directed, weighted
template <typename T>
class Graph {

private:

  struct Edge {

    Edge(const T& destination, float weight = 0);
    Edge(const Edge& other);
    Edge& operator=(const Edge& other);

    const T* m_destination;
    float m_weight;
  };

  struct Vertex {

    Vertex(const T& data);
    Vertex(const Vertex& other);
    Vertex& operator=(const Vertex& other);
    void addEdge(const T& destination, float weight = 0);
    void removeEdge(const T& destination, float weight = 0);
    void removeAllEdgesTo(const T& destination);

    const T* m_data;
    std::vector<Edge> m_edges;
  };


public:

  Graph();

  //  Capacity
  bool empty() const;
  size_t numberOfVertices() const;
  size_t numberOfEdges() const;

  // Modifiers
  bool addVertex(const T& data);
  bool removeVertex(const T& data);
  bool addEdge(const T& source, const T& destination, float weight = 0);
  bool removeEdge(const T& source, const T& destination, float weight = 0);
  bool removeAllEdges(const T& source, const T& destination);

  // Lookup
  bool contains(const T& data) const;
  std::vector<T> vertices() const;
  std::vector<T> neighboursOf(const T& data) const;
  std::vector<int> edgesBetween(const T& source, const T& destination) const;

  std::string serialize() const;


private:


  typename std::vector<Vertex >::const_iterator find(const T& data) const;
  typename std::vector<Vertex >::iterator find(const T& data);

  std::vector<Vertex> m_vertices;
};

// non-member functions


// template <typename T> typename std::vector<T> subtee_breathFirst(const Graph<T>& graph, const T& root);
// template <typename T> bool connected(const Graph<T>& graph);
// template <typename T> bool circular(const Graph<T>& graph);
// template <typename T> typename std::vector<T> path(const Graph<T>& graph, const T& a, const T& b);




// definitions


// Edge

template <typename T>
Graph<T>::Edge::Edge(const T& destination, float weight)
  : m_destination(&destination)
  , m_weight(weight)
{

}

template <typename T>
Graph<T>::Edge::Edge(const Edge& other)
  : m_destination(other.m_destination)
  , m_weight(other.m_weight)
{

}

template <typename T>
typename Graph<T>::Edge& Graph<T>::Edge::operator=(const Edge& other)
{
  if (this != &other) {
    m_destination = other.m_destination;
    m_weight = other.m_weight;
  }

  return *this;
}


// Vertex

template <typename T>
Graph<T>::Vertex::Vertex(const T& data)
  : m_data(&data)
  , m_edges()
{

}

template <typename T>
Graph<T>::Vertex::Vertex(const Vertex& other)
  : m_data(other.m_data)
  , m_edges(other.m_edges)
{

}

template <typename T>
typename Graph<T>::Vertex& Graph<T>::Vertex::operator=(const Vertex& other)
{
  if (this != &other) {
    m_data = other.m_data;
    m_edges.clear();
    m_edges = other.m_edges;
  }

  return *this;
}

template <typename T>
void Graph<T>::Vertex::addEdge(const T& destination, float weight)
{
  Edge e(destination, weight);
  m_edges.push_back(e);
}

template <typename T>
void Graph<T>::Vertex::removeEdge(const T& destination, float weight)
{
  m_edges.erase(std::find_if(m_edges.begin(), m_edges.end(),
                             [&destination, &weight](const Edge& e)
                             { return e.m_destination == destination &&
                                      e.m_weight == weight;}));
}

template <typename T>
void Graph<T>::Vertex::removeAllEdgesTo(const T& destination)
{
  std::remove_if(m_edges.begin(), m_edges.end(),
                 [&destination](const Edge& e)
                 { return e.m_destination == destination; });
}


// Graph

template <typename T>
Graph<T>::Graph()
  : m_vertices()
{

}

template <typename T>
bool Graph<T>::empty() const
{
  return m_vertices.empty();
}

template <typename T>
size_t Graph<T>::numberOfVertices() const
{
  return m_vertices.size();
}

template <typename T>
size_t Graph<T>::numberOfEdges() const
{
  size_t retval = 0;
  std::accumulate(m_vertices.begin(), m_vertices.end(), retval,
                  [](size_t sum, const Vertex& v)
                  { return sum + v.m_edges.size(); });
  return retval;
}

template <typename T>
bool Graph<T>::addVertex(const T& data)
{
  if (find(data) != m_vertices.end())
    return false;

  Vertex v(data);
  m_vertices.push_back(v);
  return true;
}

template <typename T>
bool Graph<T>::removeVertex(const T& data)
{
  typename std::vector<Vertex>::iterator it = find(data);
  if (it == m_vertices.end())
    return false;

  m_vertices.erase(it);
  return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& source, const T& destination, float weight)
{
  typename std::vector<Vertex>::iterator source_it = find(source);
  if (source_it == m_vertices.end())
    return false;

  typename std::vector<Vertex>::iterator destination_it = find(destination);
  if (destination_it == m_vertices.end())
    return false;

  (*source_it).addEdge(destination, weight);
  return true;
}

template <typename T>
bool Graph<T>::removeEdge(const T& source, const T& destination, float weight)
{
  typename std::vector<Vertex>::iterator it = find(source);
  if (it == m_vertices.end())
    return false;

  (*it).removeEdge(destination, weight);
  return true;
}

template <typename T>
bool Graph<T>::removeAllEdges(const T& source, const T& destination)
{
  typename std::vector<Vertex>::iterator it = find(source);
  if (it == m_vertices.end())
    return false;

  (*it).removeAllEdgesEdge(destination);
  return true;
}

template <typename T>
bool Graph<T>::contains(const T& data) const
{
  return find(data) != m_vertices.end();
}

template <typename T>
std::vector<T> Graph<T>::vertices() const
{
  std::vector<T> retval;
  std::for_each(m_vertices.begin(), m_vertices.end(),
                [&retval](const Vertex& v)
                { retval.push_back(v.m_data); });
  return retval;
}

template <typename T>
std::vector<T> Graph<T>::neighboursOf(const T& data) const
{
  typename std::vector<T> retval;
  typename std::vector<Vertex >::const_iterator vertex_it = find(data);
  if (vertex_it == m_vertices.end())
    return retval;

  std::for_each((*vertex_it).m_edges.begin(), (*vertex_it).m_edges.end(),
                [&retval](const Edge& e)
                { retval.push_back(e.m_weight); });

  return retval;
}

template <typename T>
std::vector<int> Graph<T>::edgesBetween(const T& source, const T& destination) const
{
  std::vector<int> retval;
  typename std::vector<Vertex>::const_iterator vertex_it = find(source);
  if (vertex_it == m_vertices.end())
    return retval;

  std::for_each((*vertex_it).m_edges.begin(), (*vertex_it).m_edges.end(),
                [&retval, &destination](const Edge& e)
                { if (e.m_destination == &destination) retval.push_back(e.m_weight); });

  return retval;
}


template <typename T>
std::string Graph<T>::serialize() const
{
  /// @todo implement me
  return std::string("");
}

template <typename T>
typename std::vector<typename Graph<T>::Vertex >::const_iterator Graph<T>::find(const T& data) const
{
  return std::find_if(m_vertices.begin(), m_vertices.end(),
                      [&data](const Vertex& v)
                      { return v.m_data == &data; });
}

template <typename T>
typename std::vector<typename Graph<T>::Vertex >::iterator Graph<T>::find(const T& data)
{
  return std::find_if(m_vertices.begin(), m_vertices.end(),
                      [&data](const Vertex& v)
                      { return v.m_data == &data; });
}


/*
template <typename T>
typename std::vector<T> subtee_breathFirst(const Graph<T>& graph, const T& root)
{
  std::vector<T> retval;
  std::vector<T> q;

  q.push_back(root);
  while (!q.empty()) {
    T node = q.front();
    q.pop_front();
    retval.push_back(node);

    const std::vector<T> neighbours = graph.neighbours(node);
    typename std::vector<T>::const_iterator it;
    for (it = neighbours.begin(); it != neighbours.end(); ++it)
      q.push_back(*it);
  }
  return retval;
}

template <typename T>
bool connected(const Graph<T>& graph)
{
  std::vector<T> connected;
  const std::vector<T> vertices = graph.vertices();

  typename std::vector<T>::const_iterator it;
  for (it = vertices.begin(); it != vertices.end(); ++it) {
    const std::vector<T> neighbours = graph.neighbours(*it);
    typename std::vector<T>::const_iterator it2;
    for (it2 = neighbours.begin(); it2 != neighbours.end(); ++it2)
      connected.push_back(*it2);
  }

  typename std::vector<T>::const_iterator last = std::unique(connected.begin(), connected.end());
  return graph.size == std::distance(connected.begin(), last);
}

template <typename T>
bool circular(const Graph<T>& graph)
{
  /// @todo implemente me
  return true;
}


template <typename T>
typename std::vector<T> path(const Graph<T>& graph, const T& a, const T& b)
{
   // Dijkstra's algorithm for single-source shortest path

  /// @todo implemente me
  return 0;
}
*/

#endif // GRAPH_H
