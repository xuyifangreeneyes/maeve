#include "symbol_table.h"

namespace maeve {

SymbolTable::SymbolTable() : root(std::make_shared<Scope>(nullptr)) {
  current = root;
}

void SymbolTable::enterScope() {
  current = std::make_shared<Scope>(std::move(current));
}

void SymbolTable::exitScope() { current = current->parent; }

bool SymbolTable::addSymbol(const std::string &name,
                            std::shared_ptr<ast::Decl> decl) {
  if (current->symbols.find(name) != current->symbols.end()) {
    return false;
  }
  current->symbols.emplace(name, std::move(decl));
  return true;
}

std::shared_ptr<ast::Decl> SymbolTable::lookup(const std::string &name) {
  std::shared_ptr<Scope> scope = current;
  while (scope) {
    auto iter = scope->symbols.find(name);
    if (iter != current->symbols.end()) {
      return iter->second;
    }
    scope = scope->parent;
  }
  return nullptr;
}

std::shared_ptr<ast::Decl> SymbolTable::globalLookup(const std::string &name) {
  auto iter = root->symbols.find(name);
  if (iter != root->symbols.end())
    return iter->second;
  return nullptr;
}

} // namespace maeve