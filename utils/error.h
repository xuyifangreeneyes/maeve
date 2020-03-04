#ifndef MENHIR_ERROR_H
#define MENHIR_ERROR_H

#include <exception>
#include <string>

namespace menhir {

class CompileError : public std::exception {
public:
  CompileError(std::string msg) : msg(std::move(msg)) {}

  const char *what() const noexcept override { return msg.c_str(); }

private:
  std::string msg;
};

} // namespace menhir

#endif //MENHIR_ERROR_H
