#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>


// directed, weighted
/// @todo weight type as param too?

template <typename T>
class Graph {

private:
  class Vertex;
  class EdgeTo;

public:

  typedef size_t size_type;
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::ptrdiff_t difference_type;

  class Edge {
  public:
    Edge() : m_source(0), m_destination(0), m_weight(0) {}

    Edge(pointer source, pointer destination, float weight) :
      m_source(source), m_destination(destination), m_weight(weight) {}

    pointer getSource() const { return m_source; }
    pointer getDestination() const { return m_destination; }
    float getWeight() const { return m_weight; }

  private:
    pointer m_source;
    pointer m_destination;
    float m_weight;
  };
  typedef Edge* edge_pointer;
  typedef Edge& edge_reference;


  Graph();

  //  Capacity
  bool empty() const;
  size_type numberOfVertices() const;
  size_type numberOfEdges() const;

  // Modifiers
  bool addVertex(const_reference data);
  bool removeVertex(const_reference data);
  bool addEdge(const_reference source, const_reference destination, float weight = 0);
  bool removeEdge(const_reference source, const_reference destination, float weight = 0);
  bool removeAllEdges(const_reference source, const_reference destination);

  // Lookup
  bool contains(const_reference data) const;
  std::vector<pointer> vertices() const;
  std::vector<pointer> neighboursOf(const_reference data) const;

  /// @todo come up with a more clear name
  std::vector<float> edgesBetween(const_reference source, const_reference destination) const;
  std::vector<Edge> edges() const;

  // iterators
  class vertex_iterator : public std::iterator<std::forward_iterator_tag,
                                               value_type,
                                               difference_type,
                                               pointer,
                                               reference>
  {
  public:
    typedef vertex_iterator self_type;
    typedef vertex_iterator& reference_self_type;
    typedef const vertex_iterator& const_reference_self_type;

    vertex_iterator() : m_it() {}
    vertex_iterator(typename std::vector<Vertex>::iterator it) : m_it(it) {}
    ~vertex_iterator() {}
    vertex_iterator(const_reference_self_type o) : m_it(o.m_it) {}
    reference_self_type operator=(const_reference_self_type o)
      { if (this != &o) { m_it = o.m_it; } return *this; }

    reference operator*() { return *((*m_it).m_data); }
    pointer operator->() { return (*m_it).m_data; }

    self_type &operator++() { ++m_it; return *this; }
    self_type operator++(int) { self_type tmp(*this); ++(*this); return tmp; }
    self_type operator+(difference_type n) { self_type tmp(*this); tmp.pos_ += n; return tmp; }
    self_type &operator+=(difference_type n) {  m_it += n; return *this; }
    bool operator==(const_reference_self_type o) { return m_it == o.m_it; }
    bool operator!=(const_reference_self_type o) { return !(*this == o); }

  private:
    typename std::vector<Vertex>::iterator m_it;
  };

  vertex_iterator vertex_begin() { return vertex_iterator(m_vertices.begin()); }
  vertex_iterator vertex_end() { return vertex_iterator(m_vertices.end()); }

  class edge_iterator : public std::iterator<std::forward_iterator_tag,
                                             Edge,
                                             difference_type,
                                             edge_pointer,
                                             edge_reference>
  {
  public:
    typedef edge_iterator self_type;
    typedef edge_iterator& reference_self_type;
    typedef const edge_iterator& const_reference_self_type;

    edge_iterator() : m_vertex_it(), m_edge_it(), m_edge(0) {}
    edge_iterator(typename std::vector<Vertex>::iterator vertex_it,
                  typename std::list<EdgeTo>::iterator edge_it)
      : m_vertex_it(vertex_it), m_edge_it(edge_it) {}
    ~edge_iterator() { if (m_edge) delete m_edge; }

    edge_iterator(const_reference_self_type o)
      : m_vertex_it(o.m_vertex_it), m_edge_it(o.m_edge_it) {}
    reference_self_type operator=(const_reference_self_type o)
      { if (this != &o) { m_vertex_it = o.m_vertex_it; m_edge_it = o.m_edge_it; } return *this; }

    edge_reference operator*() { if (!m_edge) { initEdge(); } return *m_edge; }
    edge_pointer operator->() { if (!m_edge) { initEdge(); } return m_edge; }

    self_type &operator++() { advance(1); return *this; }
    self_type operator++(int) { self_type tmp(*this); advance(1); return tmp; }
    self_type operator+(difference_type n) { self_type tmp(*this); tmp.pos_ += n; return tmp; }
    self_type &operator+=(difference_type n) {  advance(n); return *this; }
    bool operator==(const_reference_self_type o)
      { return m_vertex_it == o.m_vertex_it && m_edge_it == o.m_edge_it; }
    bool operator!=(const_reference_self_type o) { return !(*this == o); }

  private:
    void initEdge()
      { m_edge = new Edge(*m_vertex_it, (*m_edge_it).m_destination, (*m_edge_it).m_weight); }
    void invalidateEdge() { if (m_edge) delete m_edge; }

    void advance(int n)
    {
      invalidateEdge();
      /// @todo Do the stepping
    }

    typename std::vector<Vertex>::iterator m_vertex_it;
    typename std::list<EdgeTo>::iterator m_edge_it;
    edge_pointer m_edge;
  };

  edge_iterator edge_begin() { return edge_iterator(m_vertices.begin()); }
  edge_iterator edge_end() { return edge_iterator(m_vertices.end()); }


private:

  struct EdgeTo {

    EdgeTo(const_reference destination, float weight = 0);
    EdgeTo(const EdgeTo& other);
    EdgeTo& operator=(const EdgeTo& other);

    pointer m_destination;
    float m_weight;
  };

  struct Vertex {

    Vertex(const_reference data);
    Vertex(const Vertex& other);
    Vertex& operator=(const Vertex& other);
    void addEdge(const_reference destination, float weight = 0);
    void removeEdge(const_reference destination, float weight = 0);
    void removeAllEdgesTo(const_reference destination);
    std::vector<Edge> edges() const;

    pointer m_data;
    std::list<EdgeTo> m_edges;
  };

  Graph<T>(const Graph<T>& o) {  /** @todo impelemnt me */ }
  Graph<T>& operator=(const Graph<T>& o) { /** @todo impelemnt me */ }

  typename std::vector<Vertex >::const_iterator find(const_reference data) const;
  typename std::vector<Vertex >::iterator find(const_reference data);

  std::vector<Vertex> m_vertices;
};


// Edge

template <typename T>
Graph<T>::EdgeTo::EdgeTo(const_reference destination, float weight)
  : m_destination(const_cast<pointer>(&destination))
  , m_weight(weight)
{

}

template <typename T>
Graph<T>::EdgeTo::EdgeTo(const EdgeTo& other)
  : m_destination(other.m_destination)
  , m_weight(other.m_weight)
{

}

template <typename T>
typename Graph<T>::EdgeTo& Graph<T>::EdgeTo::operator=(const EdgeTo& other)
{
  if (this != &other) {
    m_destination = other.m_destination;
    m_weight = other.m_weight;
  }

  return *this;
}


// Vertex

template <typename T>
Graph<T>::Vertex::Vertex(const_reference data)
  : m_data(const_cast<pointer>(&data))
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
void Graph<T>::Vertex::addEdge(const_reference destination, float weight)
{
  EdgeTo e(destination, weight);
  m_edges.push_back(e);
}

template <typename T>
void Graph<T>::Vertex::removeEdge(const_reference destination, float weight)
{
  m_edges.erase(std::find_if(m_edges.begin(), m_edges.end(),
                             [&destination, &weight](const EdgeTo& e)
                             { return e.m_destination == destination &&
                                      e.m_weight == weight;}));
}

template <typename T>
void Graph<T>::Vertex::removeAllEdgesTo(const_reference destination)
{
  std::remove_if(m_edges.begin(), m_edges.end(),
                 [&destination](const EdgeTo& e)
                 { return e.m_destination == destination; });
}

template <typename T>
std::vector<typename Graph<T>::Edge> Graph<T>::Vertex::edges() const
{
  std::vector<Graph<T>::Edge> retval;

  std::for_each(m_edges.begin(), m_edges.end(),
                 [&retval, this](const EdgeTo& e)
                 { retval.push_back(Edge(this->m_data, e.m_destination, e.m_weight)); });

  return retval;
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
typename Graph<T>::size_type Graph<T>::numberOfVertices() const
{
  return m_vertices.size();
}

template <typename T>
typename Graph<T>::size_type Graph<T>::numberOfEdges() const
{
  return std::accumulate(m_vertices.begin(), m_vertices.end(), 0,
                  [](int sum, const Vertex& v)
                  { return sum + v.m_edges.size(); });
}

template <typename T>
bool Graph<T>::addVertex(const_reference data)
{
  if (find(data) != m_vertices.end())
    return false;

  Vertex v(data);
  m_vertices.push_back(v);
  return true;
}

template <typename T>
bool Graph<T>::removeVertex(const_reference data)
{
  typename std::vector<Vertex>::iterator it = find(data);
  if (it == m_vertices.end())
    return false;

  m_vertices.erase(it);
  return true;
}

template <typename T>
bool Graph<T>::addEdge(const_reference source, const_reference destination, float weight)
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
bool Graph<T>::removeEdge(const_reference source, const_reference destination, float weight)
{
  typename std::vector<Vertex>::iterator it = find(source);
  if (it == m_vertices.end())
    return false;

  (*it).removeEdge(destination, weight);
  return true;
}

template <typename T>
bool Graph<T>::removeAllEdges(const_reference source, const_reference destination)
{
  typename std::vector<Vertex>::iterator it = find(source);
  if (it == m_vertices.end())
    return false;

  (*it).removeAllEdgesEdge(destination);
  return true;
}

template <typename T>
bool Graph<T>::contains(const_reference data) const
{
  return find(data) != m_vertices.end();
}

template <typename T>
std::vector<typename Graph<T>::pointer> Graph<T>::vertices() const
{
  std::vector<T*> retval;
  std::for_each(m_vertices.begin(), m_vertices.end(),
                [&retval](const Vertex& v)
                { retval.push_back(v.m_data); });
  return retval;
}

template <typename T>
std::vector<typename Graph<T>::pointer> Graph<T>::neighboursOf(const_reference data) const
{
  typename std::vector<T*> retval;
  typename std::vector<Vertex >::const_iterator vertex_it = find(data);
  if (vertex_it == m_vertices.end())
    return retval;

  std::for_each((*vertex_it).m_edges.begin(), (*vertex_it).m_edges.end(),
                [&retval](const EdgeTo& e)
                { retval.push_back(e.m_destination); });

  return retval;
}

template <typename T>
std::vector<float> Graph<T>::edgesBetween(const_reference source, const_reference destination) const
{
  std::vector<float> retval;
  typename std::vector<Vertex>::const_iterator vertex_it = find(source);
  if (vertex_it == m_vertices.end())
    return retval;

  std::for_each((*vertex_it).m_edges.begin(), (*vertex_it).m_edges.end(),
                [&retval, &destination](const EdgeTo& e)
                { if (*(e.m_destination) == destination)
                    retval.push_back(e.m_weight); });

  return retval;
}

template <typename T>
std::vector<typename Graph<T>::Edge> Graph<T>::edges() const
{
  std::vector<typename Graph<T>::Edge> retval;

  std::for_each(m_vertices.begin(), m_vertices.end(),
                [&retval](const Vertex& v)
                { const std::vector<Edge> e = v.edges();
                  retval.insert(retval.end(), e.begin(), e.end());
                });

  return retval;
}


template <typename T>
typename std::vector<typename Graph<T>::Vertex >::const_iterator Graph<T>::find(const_reference data) const
{
  return std::find_if(m_vertices.begin(), m_vertices.end(),
                      [&data](const Vertex& v)
                      { return *(v.m_data) == data; });
}

template <typename T>
typename std::vector<typename Graph<T>::Vertex >::iterator Graph<T>::find(const_reference data)
{
  return std::find_if(m_vertices.begin(), m_vertices.end(),
                      [&data](const Vertex& v)
                      { return *(v.m_data) == data; });
}


#endif // GRAPH_H
