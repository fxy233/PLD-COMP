
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
      visit(ctx->list_instr());
      visit(ctx->myreturn());
      return 0;
  };


  virtual antlrcpp::Any visitDecal(ifccParser::DecalContext *ctx) override {
    
    string var_type(ctx->type()->getText());

    if (var_type == "int") 
    {
        typeSize = 4;
    } else if (var_type == "char") 
    {     
        typeSize = 1;
    } else if (var_type == "long") 
    {
        typeSize = 8;
    }

    visitChildren(ctx);

    typeSize = 0;

    return 0;
  }

  void checkDoubleDec(string var_name)
  {
    if (variables.count(var_name) > 0) 
    {       
      cout << "error: the variable " << var_name << " can't be declared again ! " << endl;
      exit(0); 
    }
  }

  void checkAffWithoutDec(string var_name)
  {
      if (variables.count(var_name) == 0)
      {       
          cout << "error: the variable " << var_name << " haven't been declared ! " << endl;
          exit(0); 
      }
  }

  void checkInitial(string var_name)
  {
    if (variables.count(var_name) == 0)
    {       
      cout << "error: the variable " << var_name << " haven't been declared ! " << endl;
      exit(0); 
    } else
    {
      if (variables[var_name] == 0)
      {
        cout << "error: the variable " << var_name << " haven't been initialized ! " << endl;
        exit(0); 
      }
    }
  }


  virtual antlrcpp::Any visitDec1(ifccParser::Dec1Context *ctx) override {
    
    string var_name(ctx->VAR()->getText());

    checkDoubleDec(var_name);

    variables[var_name] = 0;
    variables_size[var_name] = typeSize;
    
    return 0;
  }

  virtual antlrcpp::Any visitDec2(ifccParser::Dec2Context *ctx) override {
    
    string var_name(ctx->VAR()->getText());

    checkDoubleDec(var_name);

    variables[var_name] = 0;
    variables_size[var_name] = typeSize;
    
    return 0;
  }

  virtual antlrcpp::Any visitAff1(ifccParser::Aff1Context *ctx) override {
    
    int size = ctx->children.size();

    visit(ctx->children[size-1]);  

    for (size = size-3; size >=0; size=size-2)
    {
      string var_name(ctx->children[size]->getText());

      if (typeSize != 0)
      {
        checkDoubleDec(var_name);
        variables[var_name] = 0;
        variables_size[var_name] = typeSize;
      }

      checkAffWithoutDec(var_name);
      
      variables[var_name] = 1;
    }

    return 0;
  }

  virtual antlrcpp::Any visitAff2(ifccParser::Aff2Context *ctx) override {

    int size = ctx->children.size();

    visit(ctx->children[size-1]);

    for (size = size-3; size >=0; size=size-2)
    {
      string var_name(ctx->children[size]->getText());

      if (typeSize != 0)
      {
        checkDoubleDec(var_name);
        variables[var_name] = 0;
        variables_size[var_name] = typeSize;
      }

      checkAffWithoutDec(var_name);
      
      variables[var_name] = 1;
    }
    
    return 0;
  }

  virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override {
    
    visit(ctx->rval());

    if (ctx->VAR() != NULL)
    { 
      string var_name(ctx->VAR()->getText());

      if (typeSize != 0)
      {
        checkDoubleDec(var_name);
        variables[var_name] = 0;
        variables_size[var_name] = typeSize;
      }

      checkAffWithoutDec(var_name);
      variables[var_name] = 1;
    }
    return 0;
  }

  virtual antlrcpp::Any visitCallputchar(ifccParser::CallputcharContext *ctx) override {
    visit(ctx->rval());
    return 0;
  }

  virtual antlrcpp::Any visitExprWHILE(ifccParser::ExprWHILEContext *ctx) override {
    
    visit(ctx->list_instr());
    visit(ctx->rval());

    return 0;
  }

  virtual antlrcpp::Any visitExprFOR(ifccParser::ExprFORContext *ctx) override {

    if (ctx->condFOR1() != NULL)
    {
      visit(ctx->condFOR1());
    }

    visit(ctx->list_instr());

    if (ctx->condFOR2() != NULL)
    {
      visit(ctx->condFOR2());
    }

    visit(ctx->rval());

    return 0;
  }

  virtual antlrcpp::Any visitCondWithDec(ifccParser::CondWithDecContext *ctx) override {
    
    string var_type(ctx->type()->getText());

    if (var_type == "int") 
    {
        typeSize = 4;
    } else if (var_type == "char") 
    {     
        typeSize = 1;
    } else if (var_type == "long") 
    {
        typeSize = 8;
    }

    string var_name(ctx->VAR()->getText());

    checkDoubleDec(var_name);
    
    variables[var_name] = 0;
    variables_size[var_name] = typeSize;
    
    if (ctx->rval() != NULL)
    {

      visit(ctx->rval());  
      if (variables[var_name]  == 0) 
      {
        variables[var_name] = 1;
      }

    } 

    if ( ctx->listExpr() != NULL)
    {
      visit(ctx->listExpr());
    }

    typeSize = 0;

    return 0;

  }

  virtual antlrcpp::Any visitBlockIF(ifccParser::BlockIFContext *ctx) override {
    visit(ctx->rval());
    visit(ctx->list_instr());
    if (ctx->blockELSE() != NULL) 
    {
      visit(ctx->blockELSE());
    }
    return 0;
  }

  virtual antlrcpp::Any visitAdditionLeft(ifccParser::AdditionLeftContext *ctx) override {
    string var_name(ctx->VAR()->getText());

    checkInitial(var_name);

    return 0;
  }

  virtual antlrcpp::Any visitAdditionRight(ifccParser::AdditionRightContext *ctx) override {
    string var_name(ctx->VAR()->getText());

    checkInitial(var_name);

    return 0;
  }

  virtual antlrcpp::Any visitSubLeft(ifccParser::SubLeftContext *ctx) override {
    string var_name(ctx->VAR()->getText());

    checkInitial(var_name);

    return 0;
  }

  virtual antlrcpp::Any visitSubRight(ifccParser::SubRightContext *ctx) override {
    string var_name(ctx->VAR()->getText());

    checkInitial(var_name);

    return 0;
  }

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    visitChildren(ctx);
    return 0;
  }


  virtual antlrcpp::Any visitMlpDiv(ifccParser::MlpDivContext *ctx) override {

    visit(ctx->rval(0));
    visit(ctx->rval(1));
    return 0;
  }

  virtual antlrcpp::Any visitPlsMns(ifccParser::PlsMnsContext *ctx) override {
    visit(ctx->rval(0));
    visit(ctx->rval(1));
    return 0;
  }

  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override {
      visit(ctx->val());
      return 0;
  }

  virtual antlrcpp::Any visitComp(ifccParser::CompContext *ctx) override {
    visit(ctx->rval(1));
    visit(ctx->rval(0));
    
    return 0;

  }

  virtual antlrcpp::Any visitGetVAR(ifccParser::GetVARContext *ctx) override {
    string var_name(ctx->VAR()->getText());

    checkInitial(var_name);

    return 0;
  }
  
  virtual antlrcpp::Any visitMyReturn(ifccParser::MyReturnContext *ctx) override {

  	visit(ctx->val());
    return 0;
  }

  int getVarSize()
  {
    int size = 0;
    map<string, int>::iterator iter;
    iter = variables_size.begin();
    while(iter != variables_size.end()) {
      size += iter->second;
      iter++;

    }
    return size;
  }

private:

  map<string, int> variables;
  map<string, int> variables_size;

  int typeSize = 0;

};

