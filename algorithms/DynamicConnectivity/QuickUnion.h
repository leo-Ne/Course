#include <vector>

class QuickUnion{
  public:
    QuickUnion(int N)
    {for(int i=0; i<N; ++i) id.push_back(i); }
    
    inline bool connected(int p, int q) 
    {return root(p) == root(q); }
    
    inline void unionObj(int p, int q)
    {
      int i = root(p);
      int j = root(q);
      id[i] = j;
    }

  private:
    std::vector<int> id;

    int root(int i){
      while (i != id[i]) i = id[i];
      return i;
    }
};
