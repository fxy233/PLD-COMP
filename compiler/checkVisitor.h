
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include <map>
#include <string>
#include <limits>

#define ERROR numeric_limits<int>::min()

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CheckVisitor : public ifccBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
      visit(ctx->list_expr());
      visit(ctx->myreturn());
      return 0;
  };

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
    
    string var_name(ctx->VAR()->getText());
    
    if (variables.count(var_name) > 0)  // have been declared before
    {       
      cout << "error: the variable " << var_name << " can't be declared again ! " << endl;
      exit(0); 
    }
  
    variables[var_name] = 0;
    visitChildren(ctx);
    return 0;
  }

  virtual antlrcpp::Any visitDefinition(ifccParser::DefinitionContext *ctx) override {
    
    string var_name(ctx->VAR()->getText());

    if (variables.count(var_name) > 0)  // have been declared before
  	{	  		
      cout << "error: the variable " << var_name << " can't be declared again ! " << endl;
      exit(0); 
  	} else {
  		visit(ctx->aff());
  		variables[var_name] = 1;
  	}
    return 0;
  }

  virtual antlrcpp::Any visitMultiDeclaration(ifccParser::MultiDeclarationContext *ctx) override {
    
    string var_name(ctx->VAR()->getText());
    
    if (variables.count(var_name) > 0)  // have been declared before
    {       
      cout << "error: the variable " << var_name << " can't be declared again ! " << endl;
      exit(0); 
    }
    variables[var_name] = 0;
    return 0;
  }

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {

    string var_name(ctx->VAR()->getText());

    if (variables.count(var_name) == 0)  // have been declared before
    {       
      cout << "error: the variable " << var_name << " haven't been declared ! " << endl;
      exit(0); 
    } 

    visit(ctx->aff());
    variables[var_name] = 1;

    return 0;

  }


  virtual antlrcpp::Any visitMlpDiv(ifccParser::MlpDivContext *ctx) override {

    visit(ctx->arith(0));
    visit(ctx->arith(1));
    return 0;
  }

  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override {
      visit(ctx->val());
      return 0;
  }

  virtual antlrcpp::Any visitPlsMns(ifccParser::PlsMnsContext *ctx) override {
    visit(ctx->arith(0));
    visit(ctx->arith(1));
    return 0;
  }

	
  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    visit(ctx->arith());
    return 0;
  }





  virtual antlrcpp::Any visitMyReturn(ifccParser::MyReturnContext *ctx) override {

  	visit(ctx->val());
    return 0;
  }

  virtual antlrcpp::Any visitValExpr(ifccParser::ValExprContext *ctx) override {
    visit(ctx->val());
    return 0;
  }

  virtual antlrcpp::Any visitArithExpr(ifccParser::ArithExprContext *ctx) override {
    visit(ctx->arith());
    return 0;
  }


  virtual antlrcpp::Any visitGetVAR(ifccParser::GetVARContext *ctx) override {
	  string var_name(ctx->VAR()->getText());

    if (variables.count(var_name) == 0)  // haven't been declared before
    {       
      cout << "error: the variable " << var_name << " hasn't been declared ! " << endl;
      exit(0); 
    }

    if (variables[var_name] == 0)  
    {       
      cout << "error: the variable " << var_name << " hasn't been initialized ! " << endl;
      exit(0); 
    }

    return 0;
  }

private:

  map<string, int> variables;
  
};
