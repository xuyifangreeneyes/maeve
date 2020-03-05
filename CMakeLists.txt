cmake_minimum_required(VERSION 3.13)
project(maeve)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS
  antlr4-runtime/MxLexer.h
  antlr4-runtime/MxParser.h
  antlr4-runtime/MxVisitor.h
  antlr4-runtime/MxBaseVisitor.h
  antlr4-runtime/antlr4-runtime.h
  ast/fwd.h
  ast/builder.h
  ast/node.h
  ast/visitor.h
  ast/printer.h
  utils/error.h)

set(SOURCES
  main.cpp
  antlr4-runtime/MxLexer.cpp
  antlr4-runtime/MxParser.cpp
  antlr4-runtime/MxVisitor.cpp
  antlr4-runtime/MxBaseVisitor.cpp
  ast/builder.cpp
  ast/printer.cpp)

add_executable(maeve ${HEADERS} ${SOURCES})
target_include_directories(maeve PRIVATE /usr/local/include/antlr4-runtime)
target_link_libraries(maeve PRIVATE -lantlr4-runtime)