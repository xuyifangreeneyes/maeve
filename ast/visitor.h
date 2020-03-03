#ifndef MENHIR_VISITOR_H
#define MENHIR_VISITOR_H

#include "node.h"

namespace menhir {
namespace ast {

class Visitor {
  virtual ~Visitor() = default;

  virtual void visit(AstNode &node) {}


};

} // namespace ast
} // namespace menhir

#endif //MENHIR_VISITOR_H
