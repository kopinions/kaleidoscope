#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <memory>
#include <iostream>
#include <string>

class value {
public:
  value(std::string v) : _v(std::move(v)) {}
  std::string string() { return _v; };

private:
  std::string _v;
};
class token {
public:
  enum type {
    eof,
    def,
    ext,
    identifier,
    number,
    singular,
    lparen,
    rparen,
    lbracket,
    rbracket,
    plus,
    hyphen,
    comma,
    colon,
    semicolon,
    asterisk,
    slash,
    pound,
    backslash,
    tilde,
    period
  };
  token(type t, value val) : _type(t), _val(std::make_unique<value>(val)) {}
  std::unique_ptr<value> val() { return std::move(_val); }
  enum type type() { return _type; }

private:
  enum type _type;
  std::unique_ptr<value> _val;
};

#endif // TOKEN_HPP
