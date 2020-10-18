#include <vector>

class QuickFindUF{
  public:
    QuickFindUF(int N)
    {for(int i=0; i<N; ++i) id.push_back(i); }
    
    inline bool connected(int p, int q) 
    {return id[p] == id[q]; }
    
    inline void unionObj(int p, int q)
    {
      int pid = id[p];
      int qid = id[q];
      for(int i=0; i < id.size(); ++i)
        if(id[i] == pid ) id[i] = qid;
    }

  private:
    std::vector<int> id;
};
