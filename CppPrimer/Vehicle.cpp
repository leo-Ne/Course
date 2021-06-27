#include <iostream>
#include <string>


class Vehicle{
friend std::ostream& operator<<(std::ostream &os, const Vehicle &v);

  public:
    Vehicle(int years): number("0000 0000"), owner("No owner"), years(years) {}
    Vehicle(const Vehicle &v): number("0000 0000"), owner("No owner"), years(v.years) {}
    void used(const int& year){ years += year;}
    void own(const std::string &name){owner = name;}
    void regist(const std::string &num){number=num;}
    ~Vehicle(){};
  private:
    std::string number;
    std::string owner;
    int years;
};

std::ostream& operator<<(std::ostream &os, const Vehicle &v)
{
  os << "Vehicle has been used for " << v.years << " years.\n";
  os << "Its registration number is " << v.number << ".\n";
  os << "Its current owner is " << v.owner << ".";

  return os;
}


int main(void)
{
  Vehicle v(0);
  v.used(112);
  v.own("Leo");
  v.regist("8888 8888");
  std::cout << v << std::endl;
  return 0;
}
