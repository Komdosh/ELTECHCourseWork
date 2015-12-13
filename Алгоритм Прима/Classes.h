//***********************************************************************
//Класс рёбер
class Node
  {
  short first, second;
  float dist;
    public:
    Node(){}
    ~Node(){}
    float getDist()
      {
      return dist;
      }
    friend class Graph;
  };
//***********************************************************************
//Класс графа
class Graph
  {
  Node *nodes, *prima;
  int size, inp, maxEdge, count, countPrima;
  Graph(const Graph&);
  Graph(Graph&&);
  Graph operator = (const Graph&) const;
  Graph operator = (Graph&&) const;
    public:
    Graph(int iMaxEdge) :maxEdge(iMaxEdge), nodes(nullptr), count(0), prima(nullptr),size(0)
      {
      };
    ~Graph()
      {
      nodes = nullptr;
      }
    int setInp(int iInp)
      {
      inp = iInp; return 0;
      }
	int getSize()
      {
      return size;
      }
    int setMem();
    int makeGraph();
    int showGraph();
    int handle();
  };
