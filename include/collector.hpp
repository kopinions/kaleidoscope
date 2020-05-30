#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP
namespace llvm {
class Value;
}

class collector {
public:
  virtual ~collector() = default;
  virtual std::list<std::shared_ptr<llvm::Value *>> collect() = 0;
};
#endif // COLLECTOR_HPP
