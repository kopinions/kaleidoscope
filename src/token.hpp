#include <string>

class token {
public:
  enum type { eof = -1, def = -2, ext = -3, identifier = -4, number = -5 };
  union value {
    double d;
    std::string s;
  };
};
