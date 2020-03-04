#include "printer.h"
#include "node.h"
#include <iostream>

namespace menhir {
namespace ast {

void Printer::visit(AstNode &node) { node.accept(*this); }

void Printer::visit(BuiltinType &node) {
  using Kind = BuiltinType::Kind;
  std::string content = "BuiltinType ";
  switch (node.kind) {
  case Kind::Int:
    content += "int";
    break;
  case Kind::Bool:
    content += "bool";
    break;
  case Kind::String:
    content += "string";
    break;
  default:
    assert(false);
  }
  println(content);
}

void Printer::visit(ClassType &node) { println("ClassType " + node.name); }

void Printer::visit(ArrayType &node) {
  println("ArrayType");
  ++indent;
  visit(*node.baseType);
  println("dim " + std::to_string(node.dim));
  --indent;
}

void Printer::visit(BinaryExpr &node) {
  std::vector<std::string> ops = {"Mul",    "Div",  "Mod", "Add",    "Sub",
                                  "Lsft",   "Rsft", "Lt",  "Gt",     "Le",
                                  "Ge",     "Eq",   "Neq", "BitAnd", "BitOr",
                                  "BitXor", "And",  "Or",  "Assign"};
  println("BinaryExpr " + ops[node.op]);
  ++indent;
  println("lhs");
  visit(*node.lhs);
  println("rhs");
  visit(*node.rhs);
  --indent;
}

void Printer::visit(UnaryExpr &node) {
  std::vector<std::string> ops = {"PreInc", "PreDec", "PostInc", "PostDec",
                                  "Pos",    "Neg",    "Not",     "BitNot"};
  println("UnaryExpr" + ops[node.op]);
  ++indent;
  visit(*node.operand);
  --indent;
}

void Printer::visit(FunctionCall &node) {
  println("FunctionCall");
  ++indent;
  println("args");
  for (auto &&arg : node.args) {
    visit(*arg);
  }
  --indent;
}

void Printer::visit(ArrayAccess &node) {
  println("ArrayAccess");
  ++indent;
  println("array");
  visit(*node.array);
  println("index");
  visit(*node.index);
  --indent;
}

void Printer::visit(MemberAccess &node) {
  println("MemberAccess");
  ++indent;
  println("instance");
  visit(*node.instance);
  println("field");
  println(node.field);
  --indent;
}

void Printer::visit(NewExpr &node) {
  println("NewExpr");
  ++indent;
  println(node.name);
  println("dim " + std::to_string(node.dim));
  for (auto &&size : node.shape) {
    visit(*size);
  }
  --indent;
}

void Printer::visit(VarExpr &node) { println("VarExpr" + node.name); }

void Printer::visit(LiteralInt &node) {
  println("LiteralInt " + std::to_string(node.value));
}

void Printer::visit(LiteralBool &node) {
  println("LiteralBool " + std::string(node.value ? "true" : "false"));
}

void Printer::visit(LiteralString &node) {
  println("LiteralString " + node.value);
}

void Printer::visit(LiteralNull &node) { println("LiteralNull"); }

void Printer::visit(CompoundStmt &node) {
  println("CompoundStmt");
  ++indent;
  for (auto &&stmt : node.stmts) {
    visit(*stmt);
  }
  --indent;
}

void Printer::visit(ExprStmt &node) {
  println("ExprStmt");
  ++indent;
  visit(*node.expr);
  --indent;
}

void Printer::visit(VarDeclStmt &node) {
  println("VarDeclStmt");
  ++indent;
  visit(*node.varDecl);
  --indent;
}

void Printer::visit(IfStmt &node) {
  println("IfStmt");
  ++indent;
  println("cond");
  visit(*node.cond);
  println("then");
  visit(*node.then);
  if (node.otherwise) {
    println("else");
    visit(*node.otherwise);
  }
  --indent;
}

void Printer::visit(ForStmt &node) {
  println("ForStmt");
  ++indent;
  if (node.init) {
    println("init");
    visit(*node.init);
  }
  if (node.cond) {
    println("cond");
    visit(*node.cond);
  }
  if (node.step) {
    println("step");
    visit(*node.step);
  }
  println("body");
  visit(*node.body);
  --indent;
}

void Printer::visit(WhileStmt &node) {
  println("WhileStmt");
  ++indent;
  println("cond");
  visit(*node.cond);
  println("body");
  visit(*node.body);
  --indent;
}

void Printer::visit(ReturnStmt &node) {
  println("ReturnStmt");
  ++indent;
  visit(*node.value);
  --indent;
}

void Printer::visit(BreakStmt &node) { println("BreakStmt"); }

void Printer::visit(ContinueStmt &node) { println("ContinueStmt"); }

void Printer::visit(EmptyStmt &node) { println("EmptyStmt"); }

void Printer::visit(VarDecl &node) {
  println("VarDecl " + node.name);
  ++indent;
  println("type");
  visit(*node.type);
  if (node.initExpr) {
    println("initExpr");
    visit(*node.initExpr);
  }
  --indent;
}

void Printer::visit(FunctionDecl &node) {
  println("FunctionDecl " + node.name);
  ++indent;
  if (node.retType) {
    println("retType");
    visit(*node.retType);
  }
  if (!node.args.empty()) {
    println("args");
    for (auto &&arg : node.args) {
      visit(*arg);
    }
  }
  println("body");
  visit(*node.body);
  --indent;
}

void Printer::visit(ClassDecl &node) {
  println("ClassDecl " + node.name);
  ++indent;
  for (auto &&decl : node.decls) {
    visit(*decl);
  }
  --indent;
}

void Printer::visit(AstRoot &node) {
  for (auto &&decl : node.decls) {
    visit(*decl);
  }
}

void Printer::println(const std::string &content) {
  for (size_t i = 0; i < indent; ++i) {
    out << '\t';
  }
  out << content << std::endl;
}

} // namespace ast
} // namespace menhir
