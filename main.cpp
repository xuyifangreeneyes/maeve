
#include <memory>
#include <iostream>
#include "antlr4-runtime/MxLexer.h"
#include "antlr4-runtime/MxParser.h"

int main() {
  antlr4::ANTLRFileStream fin("/Users/xuyifan/Documents/menhir/tmp/1.mx");
  MxLexer lexer(&fin);
  antlr4::CommonTokenStream tokens(&lexer);
  MxParser parser(&tokens);
  auto prog = parser.program();
  return 0;
}

