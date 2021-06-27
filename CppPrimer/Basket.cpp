#include <iostream>
#include <iterator>
#include <memory>
#include <set>

class Quote{
  public:
    std::string isbn() const {return ISBN;}
    virtual Quote* clone() const &  { return new Quote(*this);}
    virtual Quote* clone() && { return new Quote(std::move(*this));}
  private:
    std::string ISBN;

};

class Bulk_quote: public Quote{
  public:
    virtual Bulk_quote* clone() const & { return new Bulk_quote(*this);}
    virtual Bulk_quote* clone() && {return new Bulk_quote(std::move(*this));}
};

class Basket{
  public:
    void add_item(const Quote &sale) {items.insert(std::shared_ptr<Quote>(sale.clone()));}
    void add_item(const Quote &&sale) {items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));}
    double total_receipt (std::ostream&) const;


  private:
    static bool compare(const std::shared_ptr<Quote> &rhs, const std::shared_ptr<Quote> &lhs)
    { return lhs->isbn() < rhs->isbn();}
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double Basket::total_receipt(std::ostream &os) const
{
  double sum = 0;
  for(auto iter=items.cbegin(); iter!=items.cend(); iter = items.upper_bound(*iter))
  {
    sum += 1;
  }
  os << sum << std::endl;
  return sum;
}

