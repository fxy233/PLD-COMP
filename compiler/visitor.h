
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
class  Visitor : public ifccBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {

    //  cout << ".globl main\n"
    //        	 "  main: \n"
    //        	 "  pushq %rbp\n"
    //        	 "  movq %rsp, %rbp\n"
    //       << visit(ctx->list_expr()).as<std::string>()
		  // << "  movl  " << visit(ctx->val()).as<std::string>() <<", %eax\n"
    //          "  popq %rbp\n"
    //          "  ret\n";

    cout <<  ".globl main\n"
           	 "  main: \n"
           	 "  pushq %rbp\n"
           	 "  movq %rsp, %rbp\n";
    visit(ctx->list_expr());
    visit(ctx->myreturn());
	cout <<  "  popq %rbp\n"
             "  ret\n";
     return 0;
  };

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
    
    string var_name(ctx->VAR()->getText());
    
    if (variables.count(var_name) > 0)  // have been declared before
    {       
      cout << "error: a variable can't be declared again ! " << endl;
      return ERROR; 
    }
  
    variables[var_name] = 1;
    visitChildren(ctx);

    return 0;
  }

  virtual antlrcpp::Any visitDefinition(ifccParser::DefinitionContext *ctx) override {
    
    string var_name(ctx->VAR()->getText());

    // cout << "var_name : " << var_name << endl;
    // cout << "count : " << variables.count(var_name) << endl;

    if (variables.count(var_name) > 0)  // have been declared before
  	{	  		
  		cout << "error: a variable can't be declared again ! " << endl;
  		return ERROR;	
  	} else {
  		cursor = cursor - 4;
  		variables[var_name] = cursor;

  		string movl = "  movl  " + visit(ctx->val()).as<std::string>() + ", " + to_string(variables[var_name]) + "(%rbp)";

  		cout << movl << endl;
  		return movl;
  	}

    return 0;
  }

  virtual antlrcpp::Any visitMultiDeclaration(ifccParser::MultiDeclarationContext *ctx) override {
    
    string var_name(ctx->VAR()->getText());
    
    if (variables.count(var_name) > 0)  // have been declared before
    {       
      cout << "error: a variable can't be declared again ! " << endl;
      return ERROR; 
    }

    variables[var_name] = 1;
    
    return 0;
  }

  virtual antlrcpp::Any visitMyReturn(ifccParser::MyReturnContext *ctx) override {

  	string ret = "  movl  " + visit(ctx->val()).as<std::string>() + ", %eax";
  	cout << ret << endl;

    return ret;
  }

  virtual antlrcpp::Any visitGetConst(ifccParser::GetConstContext *ctx) override {
    // cout << stoi(ctx->CONST()->getText());

  	string cst = "$" + ctx->CONST()->getText();
  	// cout << cst;

    return cst;
  }

  virtual antlrcpp::Any visitGetVAR(ifccParser::GetVARContext *ctx) override {
    //cout << ctx->VAR()->getText();
	  string var_name(ctx->VAR()->getText());

    if (variables.count(var_name) == 0)  // haven't been declared before
    {       
      cout << "error: a variable haven't been declared ! " << endl;
      return ERROR; 
    }
  	
  	string var = to_string(variables[var_name]) + "(%rbp)";
  	// cout << var;

    return var;
  }

private:

  map<string, int> variables;
  int cursor = 0;
  
};

