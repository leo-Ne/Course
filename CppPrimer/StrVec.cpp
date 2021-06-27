#include <string>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class StrVec{
friend std::ostream& operator<<(std::ostream &os, const StrVec &sv);
public:
  StrVec():element(nullptr), first_free(nullptr), cap(nullptr) {};
  StrVec(const StrVec&); // copy construct fun
  StrVec(StrVec&&) noexcept;
  StrVec& operator=(const StrVec&);// copy assignment func
  ~StrVec(){ free();};

  void push_back(const std::string&);
  size_t size() const {return first_free - element;}
  size_t capacity() const {return cap - element;}
  std::string *begin() const {return element;}
  std::string *end() const  {return first_free;}

private:
//    static std::allocator<std::string> alloc;
    std::allocator<std::string> alloc;
    void chk_n_alloc() {if(size() == capacity()) reallocate();}
    void free();      // realse memory
    void reallocate();
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    std::string   *element;
    std::string   *first_free;
    std::string   *cap;
};

void StrVec::push_back(const std::string& s)
{
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
  auto data = alloc.allocate(e - b);
  return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
  if(element){
    for(auto p = first_free; p!=element; /**/)
      alloc.destroy(--p);
    alloc.deallocate(element, cap - element);
  }
}

StrVec::StrVec(const StrVec &s)
{
  std::cout << "&&strvec copy construct." << std::endl;
  auto newdata =  alloc_n_copy(s.begin(), s.end());
  element = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec && sv) noexcept
  : element(sv.element), first_free(sv.first_free), cap(sv.cap)
{
  std::cout << "&&strvec move construct." << std::endl;
  sv.element = sv.first_free = sv.cap = nullptr;
}

StrVec& StrVec::operator=(const StrVec &s)
{
  auto data = alloc_n_copy(s.begin(), s.end());
  free();
  element = data.first;
  first_free = cap = data.second;
  return *this;
}

void StrVec::reallocate()
{
  auto newcapacity = size() ? 2*size() : 1;
  auto newdata     = alloc.allocate(newcapacity);
  auto dest = newdata;
  auto elem = element;
  for(size_t i=0; i != size(); ++i)
    alloc.construct(dest++, std::move(*elem++));
  free();
  element = newdata;
  first_free = dest;
  cap = element + newcapacity;
}

std::ostream& operator<<(std::ostream &os, const StrVec &sv)
{
  for(auto elem = sv.begin(); elem != sv.end(); elem++)
    os << *elem << '\t';
  return os;
}

int main(void)
{
  StrVec sv;
  sv.push_back("Hello world");
  sv.push_back("TJU SAR!");
  sv.push_back("Hello world");
  sv.push_back("TJU SAR!");
  sv.push_back("TJU SAR!");
  StrVec sv1(std::move(sv));
  std::cout << sv << std::endl;
  std::cout << sv.size() << std::endl;
  std::cout << sv.capacity() << std::endl;
  return 0;
}
