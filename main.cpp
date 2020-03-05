
#include "antlr4-runtime/MxLexer.h"
#include "antlr4-runtime/MxParser.h"
#include "ast/builder.h"
#include "ast/node.h"
#include "ast/printer.h"
#include "utils/error.h"
#include <iostream>
#include <memory>

// class Foo {
// public:
//  virtual ~Foo() = default;
//};
//
// class Bar : public Foo {
//
//};

using namespace maeve::ast;

int main() {
  antlr4::ANTLRFileStream fin("/Users/xuyifan/Documents/maeve/tmp/5.mx");
  MxLexer lexer(&fin);
  antlr4::CommonTokenStream tokens(&lexer);
  MxParser parser(&tokens);
  auto prog = parser.program();
  if (lexer.getNumberOfSyntaxErrors() > 0 ||
      parser.getNumberOfSyntaxErrors() > 0)
    throw maeve::CompileError("syntax error");

  maeve::ast::Builder astBuilder;
  auto astRoot =
      astBuilder.visit(prog).as<std::shared_ptr<maeve::ast::AstNode>>();
  maeve::ast::Printer astPrinter(std::cout);
  astPrinter.visit(*astRoot);

  //  Foo f;
  //  antlrcpp::Any x(f);
  //  Foo f2 = x.as<Foo>();

  //  std::shared_ptr<Type> f =
  //  std::make_shared<BuiltinType>(BuiltinType::Kind::Int);
  //  std::shared_ptr<Type> f = std::make_shared<ClassType>("ffe");
  //  antlrcpp::Any x(f);
  //  std::shared_ptr<Type> f2 = x.as<std::shared_ptr<Type>>();

  //  BuiltinType* f = new BuiltinType(BuiltinType::Kind::Int);
  //  dynamic_cast<Type*>(f);
  //   a = 2;
  //  dynamic_cast<float >(a);
  //  Bar b;
  //  antlrcpp::Any y(b);
  //  Bar b2 = y.as<Bar>();

  //  Bar* q = new Bar();
  //  antlrcpp::Any z(q);
  //  Foo *p = z.as<Bar*>();
  //  return 0;
}
