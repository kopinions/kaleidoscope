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

template<typename T>
class stream {
 private:
};
