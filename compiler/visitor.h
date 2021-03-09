
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include <map>
#include <string>

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
     int retval = stoi(ctx->CONST()->getText());
     cout<<".globl main\n"
           "  main: \n"
           "  pushq %rbp\n"
           "  movq %rsp, %rbp\n"
           "  movl  $"<<retval<<", %eax\n"
           "  popq %rbp\n"
           "  ret\n";

     return 0;
  };


  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {
    visit(ctx->VAR());
    visit(ctx->val());

    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGetConst(ifccParser::GetConstContext *ctx) override {
    cout << stoi(ctx->CONST()->getText());
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGetVAR(ifccParser::GetVARContext *ctx) override {
    cout << ctx->VAR()->getText();

    return visitChildren(ctx);
  }

private:

  map<string, int> variables;

  
};

