
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

  		string val = visit(ctx->aff()).as<std::string>();
    	string movl;

  		if (val.at(0) == '$' || val == "%eax")   // CONST | arith
    	{
      		movl = "  movl  " + val + ", " + to_string(variables[var_name]) + "(%rbp)";
    	} else {                // VAR
       		movl = "  movl  " + val + ", %eax\n";
       		movl = movl + "  movl  %eax, " + to_string(variables[var_name]) + "(%rbp)";
    	}

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

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {

    string var_name(ctx->VAR()->getText());

    if (variables.count(var_name) == 0)  // have been declared before
    {       
      cout << "error: a variable haven't been declared ! " << endl;
      return ERROR; 
    } 

    if (variables[var_name] == 1)
    {
      cursor = cursor - 4;
      variables[var_name] = cursor;
    }


    string val = visit(ctx->aff()).as<std::string>();
    string movl;
    
    if (val.at(0) == '$' || val == "%eax")   // CONST | arith
    {
       movl = "  movl  " + val + ", " + to_string(variables[var_name]) + "(%rbp)";
    } else {                // VAR
       movl = "  movl  " + val + ", %eax\n";
       movl = movl + "  movl  %eax, " + to_string(variables[var_name]) + "(%rbp)";
    }

    cout << movl << endl;
    return movl;

  }


/*
  movl  $3, -12(%rbp)
  movl  $5, -8(%rbp)
  movl  -12(%rbp), %eax
  imull -8(%rbp), %eax


  movl  $3, -12(%rbp)
  movl  $5, -8(%rbp)
  movl  -12(%rbp), %eax
  cltd
  idivl -8(%rbp)
  movl  %eax, -4(%rbp)
  */

  virtual antlrcpp::Any visitMlp(ifccParser::MlpContext *ctx) override {

    string ret;

    string operand1(visit(ctx->arith(0)).as<std::string>());
    if (operand1 == "%eax") {
    	ret = "  movl  " + operand1 + ", %edx\n";
    	cout << ret;
    	operand1 = "%edx";
    }

    string operand2(visit(ctx->arith(1)).as<std::string>());
    ret = "  movl  " + operand2 + ", %eax\n";

    ret = ret + "  imull  " + operand1 + ", %eax";

    cout << ret << endl;
    
    string reg("%eax");

    return reg;
  }

  virtual antlrcpp::Any visitDiv(ifccParser::DivContext *ctx) override {

    string ret;

    cout << "  movl  %edx, %ebx\n";

    string operand2(visit(ctx->arith(1)).as<std::string>());
    if (operand2 == "%eax" || operand2.at(0) == '$') {
    	ret = "  movl  " + operand2 + ", %edx\n";
    	cout << ret;
    	operand2 = "%edx";
    }

    string operand1(visit(ctx->arith(0)).as<std::string>());
    ret = "  movl  " + operand1 + ", %eax\n";
    ret = ret + "  cltd\n  idivl " + operand2;
    cout << ret << endl;

    cout << "  movl  %ebx, %edx\n";
    
    string reg("%eax");

    return reg;
  }


  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override {
      return visit(ctx->val()).as<std::string>();
  }

  /*

  movl  -12(%rbp), %edx
  movl  -8(%rbp), %eax
  addl  %edx, %eax
  movl  %eax, -4(%rbp)

  movl  $3, -12(%rbp)
  movl  $5, -8(%rbp)
  movl  -12(%rbp), %eax
  subl  -8(%rbp), %eax
  movl  %eax, -4(%rbp)
*/

  virtual antlrcpp::Any visitPls(ifccParser::PlsContext *ctx) override {

    string ret;

    string operand1(visit(ctx->arith(0)).as<std::string>());
    if (operand1 == "%eax") {
    	ret = "  movl  " + operand1 + ", %edx\n";
    	cout << ret;
    	operand1 = "%edx";
    }

    string operand2(visit(ctx->arith(1)).as<std::string>());
    ret = "  movl  " + operand2 + ", %eax\n";
    ret = ret + "  addl  " + operand1 + ", %eax";
    cout << ret << endl;
    
    string reg("%eax");

    return reg;
  }

  virtual antlrcpp::Any visitMns(ifccParser::MnsContext *ctx) override {

    string ret;

    string operand1(visit(ctx->arith(0)).as<std::string>());
    if (operand1 == "%eax") {
    	ret = "  movl  " + operand1 + ", %edx\n";
    	cout << ret;
    	operand1 = "%edx";
    }

    string operand2(visit(ctx->arith(1)).as<std::string>());
    ret = "  movl  " + operand2 + ", %eax\n";
    ret = ret + "  subl " + operand1 + ", %eax";
    cout << ret << endl;
    
    string reg("%eax");

    return reg;
  }

	
  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    string ret = visit(ctx->arith()).as<std::string>();
    return ret;
  }





  virtual antlrcpp::Any visitMyReturn(ifccParser::MyReturnContext *ctx) override {

  	string ret = "  movl  " + visit(ctx->val()).as<std::string>() + ", %eax";
  	cout << ret << endl;

    return ret;
  }

  virtual antlrcpp::Any visitValExpr(ifccParser::ValExprContext *ctx) override {
    string ret = visit(ctx->val()).as<std::string>();
    return ret;
  }

  virtual antlrcpp::Any visitArithExpr(ifccParser::ArithExprContext *ctx) override {
    string ret = visit(ctx->arith()).as<std::string>();
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

