cmake_minimum_required(VERSION 3.13)
project(menhir)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS
  antlr4-runtime/MxLexer.h
  antlr4-runtime/MxParser.h
  antlr4-runtime/MxVisitor.h
  antlr4-runtime/MxBaseVisitor.h
  antlr4-runtime/antlr4-runtime.h
  ast/ast_builder.h
  ast/node.h
  ast/visitor.h
  utils/error.h)

set(SOURCES
  main.cpp
  antlr4-runtime/MxLexer.cpp
  antlr4-runtime/MxParser.cpp
  antlr4-runtime/MxVisitor.cpp
  antlr4-runtime/MxBaseVisitor.cpp
  ast/ast_builder.cpp)

add_executable(menhir ${HEADERS} ${SOURCES})
target_include_directories(menhir PRIVATE /usr/local/include/antlr4-runtime)
target_link_libraries(menhir PRIVATE -lantlr4-runtime)