#ifndef MAEVE_ERROR_H
#define MAEVE_ERROR_H

#include <exception>
#include <string>

namespace maeve {

class CompileError : public std::exception {
public:
  explicit CompileError(std::string msg) : msg(std::move(msg)) {}

  const char *what() const noexcept override { return msg.c_str(); }

private:
  std::string msg;
};

} // namespace maeve

#endif //MAEVE_ERROR_H
