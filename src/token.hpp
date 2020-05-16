#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <iostream>
class token {
public:
  enum type { eof = -1, def = -2, ext = -3, identifier = -4, number = -5 };
  union value {
    double d;
    std::string s;
    value() {};
    explicit value(double v) : d(v) {}
    explicit value(std::string v) : s(std::move(v)) {}
    ~value() {};
  };
  token(type t, std::string v) : _t(t), _v{std::move(v)} {
    std::cout << "constructor called" << std::endl;
  }
  token(type t, double v): _t(t), _v{v} {
    std::cout << "constructor called" << std::endl;
  }

  token(const token &tok) {
    _t = tok._t;
    _v.s = {tok._v.s};
    std::cout << "copy constructor called" << std::endl;
  }

  token(const token &&tok) {
    _t = tok._t;
    _v.s = {tok._v.s};
    std::cout << "move constructor called" << std::endl;
  }

  type type() {
    return _t;
  }

  ~token() {
    std::cout << "deconstrcuted" << std::endl;
  }

private:
  enum type _t;
  value _v;
};

#endif // TOKEN_HPP
