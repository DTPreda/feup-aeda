#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge()=default;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
    Edge<N ,E>& operator=(const Edge<N, E> second);
};

template <class N, class E>
Edge<N ,E>& Edge<N,E>::operator=(const Edge<N, E> second){
    (*this).destination = second.destination;
    (*this).value = second.value;
    return *this;
}

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    bool findNode(const N inf);
    bool findEdge(const N begin,const N end);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges() const;
    unsigned numNodes() const;
    void order() const;
    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g){
    g.print(out);
    return out;
}


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
class EdgeAlreadyExists{
public:
    const N begin, end;
    EdgeAlreadyExists(const N b, const N e): begin(b), end(e){}
};

template<class N>
class EdgeDoesNotExist {
public:
    const N begin, end;
    EdgeDoesNotExist(const N b, const N e): begin(b), end(e){}
};

template <class N>
std::ostream & operator<<(std::ostream & out, const EdgeAlreadyExists<N> &ed){
    out << "Edge already exists: " << ed.begin << " , " << ed.end;
    return out;
}

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &ed){
    out << "Edge does not exist: " << ed.begin << " , " << ed.end;
    return out;
}


template <class N, class E>
Graph<N, E>::Graph() {}

template <class N, class E>
Graph<N, E>::~Graph() {
    nodes.resize(0);
}

template <class N, class E>
unsigned Graph<N, E>::numNodes() const{
    return nodes.size();
}

template <class N, class E>
unsigned Graph<N, E>::numEdges() const{
    unsigned i = 0;
    for(auto node : nodes){
        i += (*node).edges.size();
    }
    return i;
}

template <class N, class E>
Graph<N, E>& Graph<N, E>::addNode(const N &inf) {
    for(auto node : nodes){
        if((*node).info == inf){
            throw NodeAlreadyExists<N>(inf);
        }
    }
    Node<N, E>* n = new Node<N,E>(inf); //n must be initialized like this, otherwise it would be stored as a local variable and wouldn't make it out of the function
    nodes.push_back(n);
    return (*this);
}

template <class N, class E>
bool Graph<N, E>::findNode(const N inf){
    for(auto node : nodes){
        if(node->info == inf){
            return true;
        }
    }
    return false;
}

template <class N, class E>
bool Graph<N, E>::findEdge(const N begin,const N end){
    for(auto node : nodes){
        for(auto edge: node->edges){
            if(node->info == begin && edge.destination->info == end){
                return true;
            }
        }
    }
    return false;
}

template <class N, class E>
Graph<N, E>& Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
    if(!findNode(begin)){
        throw NodeDoesNotExist<N>(begin);
    }
    else if(!findNode(end)){
        throw NodeDoesNotExist<N>(end);
    }
    else if(findEdge(begin, end)){
        throw EdgeAlreadyExists<N>(begin, end);
    }
    else{
        for(auto node : nodes){
            if(node->info == end){
                Edge<N, E>*e = new Edge<N, E>(node, val);
                for(auto nd : nodes){
                    if(nd->info == begin){
                        nd->edges.push_back(*e);
                        return *this;
                    }
                }
            }

        }
    }
}

template <class N, class E>
E& Graph<N, E>::edgeValue(const N &begin, const N &end){
    if(!findNode(begin)){
        throw NodeDoesNotExist<N>(begin);
    }
    else if(!findNode(end)){
        throw NodeDoesNotExist<N>(end);
    }
    else if(!findEdge(begin, end)){
        throw EdgeDoesNotExist<N>(begin, end);
    }
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i]->info == begin){
            for(int j = 0; j < nodes[i]->edges.size(); j++){
                if(nodes[i]->edges[j].destination->info == end){
                    return (nodes[i]->edges[j].value);
                }
            }
        }
    }
}

template <class N, class E>
Graph<N,E>& Graph<N,E>::removeEdge(const N &begin, const N &end) {
    if(!findNode(begin)){
        throw NodeDoesNotExist<N>(begin);
    } else if(!findNode(end)){
        throw NodeDoesNotExist<N>(end);
    } else if(!findEdge(begin, end)){
        throw EdgeDoesNotExist<N>(begin, end);
    }
    else{
        for(int i = 0; i < nodes.size(); i++){
            if(nodes[i]->info == begin){
                for(int j = 0; j < nodes[i]->edges.size(); j++){
                    if(nodes[i]->edges[j].destination->info == end){
                        for(int k = j; k < nodes[i]->edges.size() - 1; k++){
                            nodes[i]->edges[k + 1] = nodes[i]->edges[k];
                        }
                        nodes[i]->edges.resize(nodes[i]->edges.size() - 1);
                        return *this;
                    }
                }
            }
        }
    }
}

template<class N, class E>
void Graph<N, E>::order() const{
    bool check1, check2;
    for(int i = 0; i < nodes.size(); i++){
        do{
            check1 = false;
            for(int j = 0; j <= nodes[i]->edges.size() - 2 && nodes[i]->edges.size() >= 2; j++){
                if(nodes[i]->edges[j].value > nodes[i]->edges[j + 1].value){
                    Edge<N, E>* temp = new Edge<N, E>(nodes[i]->edges[j].destination ,nodes[i]->edges[j].value);
                    *temp = nodes[i]->edges[j];
                    nodes[i]->edges[j] = nodes[i]->edges[j + 1];
                    nodes[i]->edges[j + 1] = *temp;
                    check1 = true;
                }
            }
        } while (check1);
    }
    do{
        check2 = false;
        for(int k = 0; k <= nodes.size() - 2 && nodes.size() >= 2; k++){
            if(nodes[k]->info > nodes[k + 1]->info){
                Node<N, E>* temp2 = new Node<N, E>(nodes[k]->info);
                *temp2 = *nodes[k];
                *nodes[k] = *nodes[k + 1];
                *nodes[k + 1] = *temp2;
                check2 = true;
            }
        }
    } while (check2);
}

template <class N, class E>
void Graph<N, E>::print(std::ostream &os) const {
    order();
    for(auto node : nodes){
        os << "( " << node->info;
        for(auto edge : node->edges){
            os << "[ " << edge.destination->info << " " << edge.value << "] ";
        }
        os << ") ";
    }
}