#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>

class token {
public:
  enum type { eof = -1, def = -2, ext = -3, identifier = -4, number = -5 };
  union value {
    double d;
    std::string s;
    value() {}
    value(double v) : d(v) {}
    value(std::string v) : s(v) {}
    ~value() {}
  };
  
  explicit token(type t, std::string v): _t(t), _v{v} {
    
  }

  token(const token & tok) {
    _t = tok._t;
    _v.s = {tok._v.s};
  }
    

private:
  type _t;
  value _v;
};

#endif // TOKEN_HPP
