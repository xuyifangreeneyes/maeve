#ifndef MENHIR_AST_NODE_H
#define MENHIR_AST_NODE_H

#include <vector>

namespace menhir {
namespace ast {

struct AstNode {
  virtual ~AstNode() = default;

  virtual void accept(const Visitor)
};



} // namespace ast
} // namespace menhir

#endif //MENHIR_AST_NODE_H
