#include "node.h"
#include <memory>

namespace maeve {
namespace ast {

ClassDecl::ClassDecl(std::string name,
                     std::vector<std::shared_ptr<Decl>> decls_)
    : Decl(std::move(name)) {
  for (auto &&decl : decls_) {
    decls.emplace(decl->name, decl);
  }
}

} // namespace ast
} // namespace maeve