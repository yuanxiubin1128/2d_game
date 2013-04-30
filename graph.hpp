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

  struct Edge {

    Edge() : m_source(0), m_destination(0), m_weight(0) {}
    Edge(pointer source, pointer destination, float weight);
    Edge(const Edge& o);
    Edge& operator=(Edge o) { swap(o); return *this; }
    void swap(Edge& o);

    pointer getSource() const { return m_source; }
    pointer getDestination() const { return m_destination; }
    float getWeight() const { return m_weight; }

    pointer m_source;
    pointer m_destination;
    float m_weight;
  };

  typedef Edge* edge_pointer;
  typedef Edge& edge_reference;


  Graph() : m_vertices() {}
  Graph<T>(const Graph<T>& o) : m_vertices(o.m_vertices) {}
  Graph<T>& operator=(Graph<T> o) { swap(o); return *this; }
  void swap(Graph& o) { std::swap(m_vertices, o.m_vertices); }


  //  Capacity
  bool empty() const  { return m_vertices.empty(); }
  size_type numberOfVertices() const { return m_vertices.size(); }
  size_type numberOfEdges() const;

  // Modifiers
  bool addVertex(const_reference data);
  bool removeVertex(const_reference data);
  bool addEdge(const_reference source, const_reference destination, float weight = 0);
  bool removeEdge(const_reference source, const_reference destination, float weight = 0);
  bool removeAllEdges(const_reference source, const_reference destination);

  // Lookup
  bool contains(const_reference data) const { return find(data) != m_vertices.end(); }
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
  friend class Graph;

  public:
    typedef vertex_iterator self_type;
    typedef vertex_iterator& reference_self_type;
    typedef const vertex_iterator& const_reference_self_type;

    vertex_iterator() : m_it() {}
    ~vertex_iterator() {}
    vertex_iterator(const_reference_self_type o) : m_it(o.m_it) {}
    reference_self_type operator=(self_type o) { swap(o); return *this; }
    void swap(reference_self_type o) { std::swap(m_it, o.m_it); }

    const_reference operator*() { return *((*m_it).m_data); }
    const_pointer operator->() { return (*m_it).m_data; }
    self_type &operator++() { ++m_it; return *this; }
    self_type operator++(int) { self_type tmp(*this); ++(*this); return tmp; }
    self_type operator+(difference_type n) { self_type tmp(*this); tmp.pos_ += n; return tmp; }
    self_type &operator+=(difference_type n) {  m_it += n; return *this; }
    bool operator==(const_reference_self_type o) const { return m_it == o.m_it; }
    bool operator!=(const_reference_self_type o) const { return !(*this == o); }

  private:
    vertex_iterator(typename std::vector<Vertex>::iterator it) : m_it(it) {}
    vertex_iterator(typename std::vector<Vertex>::const_iterator it) : m_it(it) {}

    typename std::vector<Vertex>::const_iterator m_it;
  };

  vertex_iterator vertex_begin() { return vertex_iterator(m_vertices.begin()); }
  const vertex_iterator vertex_begin() const { return vertex_iterator(m_vertices.begin()); }
  vertex_iterator vertex_end() { return vertex_iterator(m_vertices.end()); }
  const vertex_iterator vertex_end() const { return vertex_iterator(m_vertices.end()); }

  class edge_iterator : public std::iterator<std::forward_iterator_tag,
                                             Edge,
                                             difference_type,
                                             edge_pointer,
                                             edge_reference>
  {
  friend class Graph;

  public:
    typedef edge_iterator self_type;
    typedef edge_iterator& reference_self_type;
    typedef const edge_iterator& const_reference_self_type;

    edge_iterator() : m_vertices(),  m_vertex_it(), m_edge_it(), m_edge() {}
    ~edge_iterator() {}
    edge_iterator(const_reference_self_type o);
    reference_self_type operator=(self_type o) { swap(o); return *this; }
    void swap(reference_self_type other);

    const edge_reference operator*() { resetEdge(); return m_edge; }
    const edge_pointer operator->() { resetEdge(); return &m_edge; }
    self_type &operator++() { advance(1); return *this; }
    self_type operator++(int) { self_type tmp(*this); advance(1); return tmp; }
    self_type operator+(difference_type n) { self_type tmp(*this); tmp.pos_ += n; return tmp; }
    self_type &operator+=(difference_type n) {  advance(n); return *this; }
    bool operator==(const_reference_self_type o) const;
    bool operator!=(const_reference_self_type o) const { return !(*this == o); }

  private:
    edge_iterator(std::vector<Vertex> vertices, bool begin = true);

    void resetEdge();
    void advance(int n);

    std::vector<Vertex> m_vertices;
    typename std::vector<Vertex>::iterator m_vertex_it;
    typename std::list<EdgeTo>::iterator m_edge_it;
    Edge m_edge;
  };

  edge_iterator edge_begin() { return edge_iterator(m_vertices); }
  const edge_iterator edge_begin() const { return edge_iterator(m_vertices); }
  edge_iterator edge_end() { return edge_iterator(m_vertices, false); }
  const edge_iterator edge_end() const { return edge_iterator(m_vertices, false); }


private:

  struct EdgeTo {

    EdgeTo(const_reference destination, float weight = 0);
    EdgeTo(const EdgeTo& o) : m_destination(o.m_destination), m_weight(o.m_weight) {}
    EdgeTo& operator=(EdgeTo o) { swap(o); return *this; }
    void swap(EdgeTo& o);

    bool operator==(const EdgeTo& other) const;

    pointer m_destination;
    float m_weight;
  };

  struct Vertex {

    Vertex(const_reference data) : m_data(const_cast<pointer>(&data)) , m_edges() {}
    Vertex(const Vertex& o) : m_data(o.m_data), m_edges(o.m_edges) {}
    Vertex& operator=(Vertex o) { swap(o); return *this; }
    void swap(Vertex& o) { std::swap(m_data, o.m_data); std::swap (m_edges, o.m_edges); }

    bool operator==(const Vertex& other) const;

    void addEdge(const_reference destination, float weight = 0);
    void removeEdge(const_reference destination, float weight = 0);
    void removeAllEdgesTo(const_reference destination);
    std::vector<Edge> edges() const;

    pointer m_data;
    std::list<EdgeTo> m_edges;
  };

  typename std::vector<Vertex >::const_iterator find(const_reference data) const;
  typename std::vector<Vertex >::iterator find(const_reference data);

  std::vector<Vertex> m_vertices;
};


// Edge

template <typename T>
inline Graph<T>::Edge::Edge(pointer source, pointer destination, float weight)
  : m_source(source)
  , m_destination(destination)
  , m_weight(weight)
{}

template <typename T>
inline Graph<T>::Edge::Edge(const Edge& o)
  : m_source(o.m_source)
  , m_destination(o.m_destination)
  , m_weight(o.m_weight)
{}

template <typename T>
inline void Graph<T>::Edge::swap(Edge& o)
{
  std::swap(m_source, o.m_source);
  std::swap(m_destination, o.m_destination);
  std::swap(m_weight, o.m_weight);
}


// edge iterator

template <typename T>
inline Graph<T>::edge_iterator::edge_iterator(const_reference_self_type o)
  : m_vertices(o.m_vertices)
  , m_vertex_it(o.m_vertex_it)
  , m_edge_it(o.m_edge_it)
  , m_edge()
{}

template <typename T>
bool Graph<T>::edge_iterator::operator==(const_reference_self_type o) const
{
  const bool this_is_at_end = m_vertex_it == m_vertices.end();
  const bool other_is_at_end = o.m_vertex_it == o.m_vertices.end();
  if ( this_is_at_end && other_is_at_end ) return true;
  if ( this_is_at_end != other_is_at_end ) return false;

  return *m_vertex_it == *(o.m_vertex_it) &&
         *m_edge_it == *(o.m_edge_it);
}

template <typename T>
inline void Graph<T>::edge_iterator::swap(reference_self_type other)
{
  std::swap(m_vertices, other.m_vertices);
  std::swap(m_vertex_it, other.m_vertex_it);
  std::swap(m_edge_it, other.m_edge_it);
  std::swap(m_edge, other.m_edge);
}

template <typename T>
inline Graph<T>::edge_iterator::edge_iterator(std::vector<Vertex> vertices, bool begin)
  : m_vertices(vertices), m_vertex_it(), m_edge_it(), m_edge()
{
  if (begin) {
    m_vertex_it = m_vertices.begin();
    while (m_vertex_it != m_vertices.end() && m_vertices.empty())
      ++m_vertex_it;

    if (m_vertex_it != m_vertices.end())
      m_edge_it = (*m_vertex_it).m_edges.begin();
  } else {
    m_vertex_it = m_vertices.end();
  }
}

template <typename T>
inline void Graph<T>::edge_iterator::resetEdge()
{
  if (m_vertex_it == m_vertices.end() || (*m_vertex_it).m_edges.empty()) {
    m_edge = Edge();
  } else {
    m_edge = Edge((*m_vertex_it).m_data, (*m_edge_it).m_destination, (*m_edge_it).m_weight);
  }
}

template <typename T>
void Graph<T>::edge_iterator::advance(int n)
{
  while (n > 0 && m_vertex_it != m_vertices.end()) {
    const int edgesAhead = std::distance(m_edge_it, (*m_vertex_it).m_edges.end()) - 1;
    if (n <= edgesAhead) {
      std::advance(m_edge_it, n);
      return;
    }

    if (edgesAhead > 0) n -= edgesAhead;
    ++m_vertex_it;

    if (m_vertex_it != m_vertices.end()) {
      m_edge_it = (*m_vertex_it).m_edges.begin();
      if (m_edge_it != (*m_vertex_it).m_edges.end())
        --n;
    }
  }
}

// EdgeTo

template <typename T>
inline Graph<T>::EdgeTo::EdgeTo(const_reference destination, float weight)
  : m_destination(const_cast<pointer>(&destination))
  , m_weight(weight)
{}

template <typename T>
inline void Graph<T>::EdgeTo::swap(EdgeTo& o)
{
  std::swap(m_destination, o.m_destination);
  std::swap(m_vertices, o.m_weight);
}

template <typename T>
inline bool Graph<T>::EdgeTo::operator==(const EdgeTo& other) const
{
  return m_destination == other.m_destination &&
         m_weight == other.m_weight;
}


// Vertex

template <typename T>
inline bool Graph<T>::Vertex::operator==(const Vertex& other) const
{
  return m_data == other.m_data &&
         m_edges.size() == other.m_edges.size() &&
         m_edges == other.m_edges;
}

template <typename T>
inline void Graph<T>::Vertex::addEdge(const_reference destination, float weight)
{
  m_edges.push_back(EdgeTo(destination, weight));
}

template <typename T>
inline void Graph<T>::Vertex::removeEdge(const_reference destination, float weight)
{
  m_edges.erase(std::find_if(m_edges.begin(), m_edges.end(),
                             [&destination, &weight](const EdgeTo& e)
                             { return e.m_destination == destination &&
                                      e.m_weight == weight;}));
}

template <typename T>
inline void Graph<T>::Vertex::removeAllEdgesTo(const_reference destination)
{
  std::remove_if(m_edges.begin(), m_edges.end(),
                 [&destination](const EdgeTo& e)
                 { return e.m_destination == destination; });
}

template <typename T>
inline std::vector<typename Graph<T>::Edge> Graph<T>::Vertex::edges() const
{
  std::vector<Graph<T>::Edge> retval;

  std::for_each(m_edges.begin(), m_edges.end(),
                 [&retval, this](const EdgeTo& e)
                 { retval.push_back(Edge(this->m_data, e.m_destination, e.m_weight)); });

  return retval;
}


// Graph

template <typename T>
inline typename Graph<T>::size_type Graph<T>::numberOfEdges() const
{
  return std::accumulate(m_vertices.begin(), m_vertices.end(), 0,
                         [](int sum, const Vertex& v)
                         { return sum + v.m_edges.size(); });
}

template <typename T>
inline bool Graph<T>::addVertex(const_reference data)
{
  if (find(data) != m_vertices.end())
    return false;

  m_vertices.push_back(Vertex(data));
  return true;
}

template <typename T>
inline bool Graph<T>::removeVertex(const_reference data)
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
inline bool Graph<T>::removeEdge(const_reference source, const_reference destination, float weight)
{
  typename std::vector<Vertex>::iterator it = find(source);
  if (it == m_vertices.end())
    return false;

  (*it).removeEdge(destination, weight);
  return true;
}

template <typename T>
inline bool Graph<T>::removeAllEdges(const_reference source, const_reference destination)
{
  typename std::vector<Vertex>::iterator it = find(source);
  if (it == m_vertices.end())
    return false;

  (*it).removeAllEdgesEdge(destination);
  return true;
}

template <typename T>
inline std::vector<typename Graph<T>::pointer> Graph<T>::vertices() const
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
inline std::vector<typename Graph<T>::Edge> Graph<T>::edges() const
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
inline typename std::vector<typename Graph<T>::Vertex >::const_iterator Graph<T>::find(const_reference data) const
{
  return std::find_if(m_vertices.begin(), m_vertices.end(),
                      [&data](const Vertex& v)
                      { return *(v.m_data) == data; });
}

template <typename T>
inline typename std::vector<typename Graph<T>::Vertex >::iterator Graph<T>::find(const_reference data)
{
  return std::find_if(m_vertices.begin(), m_vertices.end(),
                      [&data](const Vertex& v)
                      { return *(v.m_data) == data; });
}


#endif // GRAPH_H
