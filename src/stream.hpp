#ifndef STREAM_HPP
#define STREAM_HPP
#include <functional>
#include <memory>

template<typename T>
class suspension {
 public:
  suspension(std::function<std::unique_ptr<T>()> const &f) :_f(f) {};
  T const & force() const {
    if (!_memo) {
      _memo = _f();
    }
    return *_memo;
  };
 private:
  std::function<std::unique_ptr<T>()> _f;
  std::unique_ptr<T> mutable _memo;
};

template <typename T> class stream;
  
template <typename T>
class cons {
 public:
  cons(const T & car, const stream<T> & cdr): _car(car), _cdr(cdr) {}
  stream<T> cdr() const{
    return _cdr;
  }
 T car() const {
    return _car;
  }
 private:
  T _car;
  stream<T> _cdr;
};

template  <typename T>
class item {
   public:
    item(const T & car, const stream<T> & cdr) : _cons(new cons<T>(car, cdr)){}

    T value() const {
      return _cons->car();
    }

   private:
    std::unique_ptr<const cons<T>> _cons; 
};

template<typename T>
class stream {
 public:
  stream(std::function<std::unique_ptr<const item<T>>()> f) : _lazied(std::make_shared<suspension<const item<T>>>(f)){
  }
  stream() {}

  T get() const {
    return _lazied->force().value();
  }
private:
  std::shared_ptr<suspension<const item<T>>> _lazied; 
};
#endif// STREAM_HPP
