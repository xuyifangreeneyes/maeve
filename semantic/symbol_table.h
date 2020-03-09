#ifndef MAEVE_SYMBOL_TABLE_H
#define MAEVE_SYMBOL_TABLE_H

#include "../ast/fwd.h"
#include "../ast/node.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace maeve {

class SymbolTable {
public:
  SymbolTable();

  void enterScope();

  void exitScope();

  bool addSymbol(const std::string &name, std::shared_ptr<ast::Decl> decl);

  std::shared_ptr<ast::Decl> lookup(const std::string &name);
  std::shared_ptr<ast::Decl> globalLookup(const std::string &name);

private:
  struct Scope {
    explicit Scope(std::shared_ptr<Scope> parent) : parent(std::move(parent)) {}

    std::unordered_map<std::string, std::shared_ptr<ast::Decl>> symbols;
    std::shared_ptr<Scope> parent;
  };

  std::shared_ptr<Scope> current;
  std::shared_ptr<Scope> root;

  void addBuiltin();

  std::shared_ptr<ast::VarDecl> argument(std::string name,
                                         ast::BuiltinType::Kind kind);

  std::shared_ptr<ast::FunctionDecl>
  builtinFunction(std::string name, ast::BuiltinType::Kind retKind,
                  std::vector<std::shared_ptr<ast::VarDecl>> args);
};

} // namespace maeve

#endif // MAEVE_SYMBOL_TABLE_H
