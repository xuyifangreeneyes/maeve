cmake_minimum_required(VERSION 3.13)
project(maeve)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

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
  semantic/semantic_checker.h
  semantic/symbol_table.h
  codegen/codegen.h
  utils/error.h
  )

set(SOURCES
  main.cpp
  antlr4-runtime/MxLexer.cpp
  antlr4-runtime/MxParser.cpp
  antlr4-runtime/MxVisitor.cpp
  antlr4-runtime/MxBaseVisitor.cpp
  ast/builder.cpp
  ast/node.cpp
  ast/printer.cpp
  semantic/semantic_checker.cpp
  semantic/symbol_table.cpp
  codegen/codegen.cpp
  )

add_executable(maeve ${HEADERS} ${SOURCES})
llvm_map_components_to_libnames(llvm_libs support core irreader native)
target_include_directories(maeve PRIVATE /usr/local/include/antlr4-runtime)
target_link_libraries(maeve PRIVATE -lantlr4-runtime ${llvm_libs})