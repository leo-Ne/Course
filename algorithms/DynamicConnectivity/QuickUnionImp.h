#include <vector>

class QuickUnion{
  public:
    QuickUnion(int N)
    {
      for(int i=0; i<N; ++i) 
      {id.push_back(i); sz.push_back(1);}
    }
    
    inline bool connected(int p, int q) 
    {return root(p) == root(q); }
    
    inline void unionObj(int p, int q)
    {
      int i = root(p);
      int j = root(q);
      if(i == j) return;
      if(sz[i] < sz[j]) {id[i] = j; sz[j] += sz[i];}
      else              {id[j] = i; sz[i] += sz[j];}
    }

  private:
    std::vector<int> id;
    std::vector<int> sz;

    int root(int i){
      while (i != id[i]) 
      {
        id[i] = id[id[i]];    // change i's parents to parents' parents. This line code will make the tree more flat.
        i = id[i];            // loop condition update!
      }
      return i;
    }
};
