#include "symbol_table.h"
#include "../ast/node.h"

namespace maeve {

using args = std::vector<std::shared_ptr<ast::VarDecl>>;
using Kind = ast::BuiltinType::Kind;

SymbolTable::SymbolTable() : root(std::make_shared<Scope>(nullptr)) {
  current = root;
  addBuiltin();
}

std::shared_ptr<ast::VarDecl> SymbolTable::argument(std::string name,
                                                    Kind kind) {
  return std::make_shared<ast::VarDecl>(
      std::move(name), std::make_shared<ast::BuiltinType>(kind));
}

std::shared_ptr<ast::FunctionDecl>
SymbolTable::builtinFunction(std::string name, Kind retKind,
                             std::vector<std::shared_ptr<ast::VarDecl>> args) {
  return std::make_shared<ast::FunctionDecl>(
      std::move(name), std::make_shared<ast::BuiltinType>(retKind),
      std::move(args));
}

void SymbolTable::addBuiltin() {
  std::vector<std::shared_ptr<ast::FunctionDecl>> builtinFunctions = {
      builtinFunction("print", Kind::Void, args({argument("s", Kind::String)})),
      builtinFunction("println", Kind::Void,
                      args({argument("s", Kind::String)})),
      builtinFunction("getString", Kind::String, args()),
      builtinFunction("getInt", Kind::Int, args()),
      builtinFunction("toString", Kind::String,
                      args({argument("n", Kind::Int)})),
      builtinFunction("_string_length", Kind::Int, args()),
      builtinFunction(
          "_string_substring", Kind::String,
          args({argument("l", Kind::Int), argument("r", Kind::Int)})),
      builtinFunction("_string_parseInt", Kind::Int, args()),
      builtinFunction("_string_ord", Kind::Int, args()),
      builtinFunction("_array_size", Kind::Int, args())};
  for (auto &&builtinFunction : builtinFunctions) {
    root->symbols.emplace(builtinFunction->name, builtinFunction);
  }
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