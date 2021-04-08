
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include <map>
#include <string>
#include <limits>
#include <stack>

#define ERROR numeric_limits<int>::min()

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {

  	map<string, int>::iterator iter;
    iter = variables.begin();
    while(iter != variables.end()) {
    	cout << ".comm  " << iter->first <<","<<to_string(iter->second)<<",0\n";
    	iter++;
    }

    cout <<  ".globl main\n"
           	 "  main: \n"
           	 "  pushq %rbp\n"
           	 "  movq %rsp, %rbp\n"
             "  subq $" << to_string(fct_size["main"]+4) << ", %rsp\n"; 
    
    visit(ctx->list_instr());
    //visit(ctx->myreturn());

	  cout <<  ".L" << returnLabel << ":" << endl;
    cout <<  "  movq %rbp, %rsp\n"
             "  popq %rbp\n"
             "  ret\n";

    returnLabel++;

    if (ctx->defFunction() != NULL)
    {
    	visit(ctx->defFunction());
    }
    
    return 0;
  };

  virtual antlrcpp::Any visitDecGlobal(ifccParser::DecGlobalContext *ctx) override {
    return 0;
  }

  virtual antlrcpp::Any visitListPara(ifccParser::ListParaContext *ctx) override {
  	int i = 0;
    int j = 1;
    int nb = 0;
    for (;j<ctx->children.size();) 
    {
        string paraType(ctx->children[i]->getText());
        int paraSize = 0;
        if (paraType == "int") 
        {
            paraSize = 4;
        } else if (paraType == "char") 
        {     
            paraSize = 1;
        }

        string paraName(ctx->children[j]->getText());

        cursor = cursor - paraSize;
        variables[paraName] = cursor;
        variables_size[paraName] = paraSize;

        cout << "	movl  " << paramReg[nb] << ", " << to_string(variables[paraName]) << "(%rbp)\n";

        i = i + 3;
        j = j + 3;
        nb++;
 	}

  	return 0;
  }


  virtual antlrcpp::Any visitFunct(ifccParser::FunctContext *ctx) override {
  	
  	variables.clear();
  	variables_size.clear();
  	cursor = 0;

  	string fctName(ctx->VAR()->getText());
    cout << ".globl  " << fctName << "\n.type " << fctName << ",  @function" << endl;
  	cout <<  fctName
  		 <<	 ": \n"
           	 "  pushq %rbp\n"
           	 "  movq %rsp, %rbp\n"
             "  subq $" << to_string(fct_size[fctName]+4) << ", %rsp\n"; 
    
    if (ctx->listPara() != NULL)
    {
    	visit(ctx->listPara());
    }

    visit(ctx->list_instr());

    // if (ctx->myreturn() != NULL)
    // {
    // 	visit(ctx->myreturn());	
    // }
    
    cout <<  ".L" << returnLabel << ":" << endl;

    cout <<  "  movq %rbp, %rsp\n"
             "  popq %rbp\n"
             "  ret\n";
    returnLabel++;

  	return 0;
  }


  virtual antlrcpp::Any visitCallfunction(ifccParser::CallfunctionContext *ctx) override {

  	string fctName(ctx->children[0]->getText());

  	if (ctx->children.size() > 3)
  	{
  		int nb = 0;
  		int i = 2;
  		for (; i< ctx->children.size();)
  		{
        string rvalue = visit(ctx->children[i]).as<std::string>();
  			cout << "	movl  " << rvalue << ", " << paramReg[nb] << endl;
  			nb++;
  			i = i+2;
  		}
  	}

  	cout << "	call  " << fctName << endl;

  	string reg("%eax");
  	return reg;
  }

  virtual antlrcpp::Any visitDecal(ifccParser::DecalContext *ctx) override {
    
    string var_type(ctx->type()->getText());

    if (var_type == "int") 
    {
        typeSize = 4;
    } else if (var_type == "char") 
    {     
        typeSize = 1;
    } 

    visitChildren(ctx);

    typeSize = 0;

    return 0;
  }


  virtual antlrcpp::Any visitDec1(ifccParser::Dec1Context *ctx) override {
    
    string var_name(ctx->VAR()->getText());
    if (ctx->CONST() == NULL) 
    {
    	variables[var_name] = 0;
    	variables_size[var_name] = typeSize;
    }	
    return 0;
  }

  virtual antlrcpp::Any visitDec2(ifccParser::Dec2Context *ctx) override {
    
    string var_name(ctx->VAR()->getText());
    if (ctx->CONST() == NULL) 
    {
    	variables[var_name] = 0;
    	variables_size[var_name] = typeSize;
    }	
    return 0;
  }

  
  virtual antlrcpp::Any visitAff1(ifccParser::Aff1Context *ctx) override {
    
    int size = ctx->children.size();

    string val = visit(ctx->children[size-1]).as<std::string>();	// getRvalue

    if (sizeTmp != 0)
    {
      typeSize = sizeTmp;
      sizeTmp = 0;
    }
    

    for (size = size-3; size >=0; size=size-2)
    {
    	string var_name(ctx->children[size]->getText());

    	// if (var_name == "]")
    	// {
    	// 	string tab_name(ctx->children[size-3]->getText());
  			// string index(ctx->children[size-1]->getText());

  			// int index = stoi(index);
  			// index = index * variables_size[tab_name];

  			// string str_index = index == 0 ? "" :to_string(index);
  			// string var = str_index + "+" + var_name + "(%rip)";

  			// string movl;
    	// 	if (val.at(0) == '$' || val == "%eax")   // CONST | arith
	   	// 	{
	    //   		movl = "  movl  " + val + ", " + var;
	   	// 	} else {                // VAR
	    //  		movl = "  movl  " + val + ", %eax\n";
	    //    		movl = movl + "  movl  %eax, " + var;
	    // 	}
    	// 	cout << movl << endl;

    	// 	size = size - 3;

    	// 	continue;
    	// }

    	variables_size[var_name] = typeSize;
    	
    	cursor = cursor - variables_size[var_name];
    	variables[var_name] = cursor;
    	
    	string movl;
    	if (val.at(0) == '$' || val == "%eax")   // CONST | arith
	   	{
	      	movl = "  movl  " + val + ", " + to_string(variables[var_name]) + "(%rbp)";
	   	} else {                // VAR
	     	movl = "  movl  " + val + ", %eax\n";
	       	movl = movl + "  movl  %eax, " + to_string(variables[var_name]) + "(%rbp)";
	    }
    	cout << movl << endl;
    }

    return 0;
  }


  virtual antlrcpp::Any visitAff2(ifccParser::Aff2Context *ctx) override {

  	int size = ctx->children.size();

    string val = visit(ctx->children[size-1]).as<std::string>();	// getRvalue

    if (sizeTmp != 0)
    {
      typeSize = sizeTmp;
      sizeTmp = 0;
    }

    for (size = size-3; size >=0; size=size-2)
    {
    	string var_name(ctx->children[size]->getText());

    	// if (var_name == "]")
    	// {
    	// 	string tab_name(ctx->children[size-3]->getText());
  			// string index(ctx->children[size-1]->getText());

  			// int index = stoi(index);
  			// index = index * variables_size[tab_name];

  			// string str_index = index == 0 ? "" :to_string(index);
  			// string var = str_index + "+" + var_name + "(%rip)";

  			// string movl;
    	// 	if (val.at(0) == '$' || val == "%eax")   // CONST | arith
	   	// 	{
	    //   		movl = "  movl  " + val + ", " + var;
	   	// 	} else {                // VAR
	    //  		movl = "  movl  " + val + ", %eax\n";
	    //    		movl = movl + "  movl  %eax, " + var;
	    // 	}
    	// 	cout << movl << endl;

    	// 	size = size - 3;

    	// 	continue;
    	// }

    	variables_size[var_name] = typeSize;
    	
    	cursor = cursor - variables_size[var_name];
    	variables[var_name] = cursor;
    	
    	string movl;
    	if (val.at(0) == '$' || val == "%eax")   // CONST | arith
	   	{
	      	movl = "  movl  " + val + ", " + to_string(variables[var_name]) + "(%rbp)";
	   	} else {                // VAR
	     	movl = "  movl  " + val + ", %eax\n";
	       	movl = movl + "  movl  %eax, " + to_string(variables[var_name]) + "(%rbp)";
	    }
    	cout << movl << endl;
    }
    
    return 0;
  }



  /*
	rule expr
  */

  virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override {

    //cout << "val expression : " << val << endl; 

  	if (ctx->children.size() > 4)  // array
  	{
  	    string tab_name(ctx->VAR()->getText());

      string val = visit(ctx->children[5]).as<std::string>();
    	cout << "  movl  " + val + ", %esi\n";
        string index_reg(visit(ctx->children[2]).as<std::string>());
      cout << "   movl  " << index_reg << ", %edi\n";
      cout << "   cltq  " << endl;
      cout << "   leaq  0(,%rdi,4), %rcx" << endl;
      cout << "   leaq  " << tab_name << "(%rip), %rdx\n";

      string var = "(%rcx, %rdx)";
	    cout << "  movl  %esi, " << var << endl;
        cout << "  movl %esi, %eax\n";
	    string reg("%eax");
  		return reg;
  	}	else
    {
      if (ctx->VAR() != NULL)
      { 
        string val = visit(ctx->children[2]).as<std::string>();
        string var_name(ctx->VAR()->getText());
        if (typeSize != 0) 
        {
          variables[var_name] = 0;
          variables_size[var_name] = typeSize;
        }
        if (variables[var_name]  == 0) 
        {
          cursor = cursor - variables_size[var_name];
          variables[var_name] = cursor;
        }
        string movl;
        movl = "  movl  " + val + ", %eax\n";
        movl = movl + "  movl  %eax, " + to_string(variables[var_name]) + "(%rbp)";
        cout << movl << endl;
      } else {
        string val = visit(ctx->children[0]).as<std::string>();
        string movl;
        movl = "  movl  " + val + ", %eax\n";
        cout << movl;
      }
      string reg("%eax");
      return reg;
    }

  	
  }

  /*
  	callputchar
  */

  virtual antlrcpp::Any visitCallputchar(ifccParser::CallputcharContext *ctx) override {
    string reg( visit(ctx->rval()).as<std::string>() );
    cout << "   movl   " << reg << ",  %edi\n";
    cout << "   call   putchar@PLT\n";

    return 0;
  }

  /*
  	while
  */

  virtual antlrcpp::Any visitExprWHILE(ifccParser::ExprWHILEContext *ctx) override {
    
    int tmpLabel = label;
    label += 2;
    cout << "   jmp  .L" << tmpLabel << endl;
    cout << ".L" << to_string(tmpLabel+1) << ":\n";

    visit(ctx->list_instr());

    cout << ".L" << to_string(tmpLabel) << ":\n";
    
    string reg( visit(ctx->rval()).as<std::string>() );
    cout << "   movl  " << reg << ",%eax\n";
    reg = "%eax";

    cout << " cmpl  $0, " << reg << endl;
    cout << " jne  .L" << to_string(tmpLabel+1) << endl;
    
    return 0;
  }

  /*
	rule for
  */

  virtual antlrcpp::Any visitExprFOR(ifccParser::ExprFORContext *ctx) override {

  	if (ctx->condFOR1() != NULL)
  	{
  		visit(ctx->condFOR1());
  	}

    int tmpLabel = label;
    label += 2;

    cout << "   jmp  .L" << tmpLabel << endl;
    cout << ".L" << to_string(tmpLabel+1) << ":\n";

    visit(ctx->list_instr());

    if (ctx->condFOR2() != NULL)
  	{
  		visit(ctx->condFOR2());
  	}

    cout << ".L" << tmpLabel << ":\n";
    string reg( visit(ctx->rval()).as<std::string>() );
    cout << "   movl  " << reg << ",%eax\n";
    reg = "%eax";
    cout << " cmpl  $0, " << reg << endl;
    cout << " jne  .L" << to_string(tmpLabel+1) << endl;

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
    } 

    string var_name(ctx->VAR()->getText());
  	variables[var_name] = 0;
    variables_size[var_name] = typeSize;
  	
  	if (ctx->rval() != NULL)
  	{	
  		if (ctx->CONST() != NULL)
  		{
  			string tab_name(ctx->VAR()->getText());
	  		string i(ctx->CONST()->getText());

	  		int index = stoi(i);
	  		index = index * variables_size[tab_name];

	  		string str_index = index == 0 ? "" :to_string(index)+"+";
	  		string var = str_index + var_name + "(%rip)";

	  		string val = visit(ctx->rval()).as<std::string>();	

	  		string movl;
	    	if (val.at(0) == '$' || val == "%eax")   // CONST | arith
		   	{
		      	movl = "  movl  " + val + ", " + var;
		   	} else {                // VAR
		     	movl = "  movl  " + val + ", %eax\n";
		       	movl = movl + "  movl  %eax, " + var;
		    }
		    cout << movl << endl; 


  		} else
  		{
  			string val = visit(ctx->rval()).as<std::string>();	
	  		if (variables[var_name]  == 0) 
	    	{
	    		cursor = cursor - variables_size[var_name];
	    		variables[var_name] = cursor;
	    	}
	    	
	    	string movl;
	    	
	    	if (val.at(0) == '$' || val == "%eax")   // CONST | arith
		   	{
		      	movl = "  movl  " + val + ", " + to_string(variables[var_name]) + "(%rbp)";
		   	} else {                // VAR
		     	movl = "  movl  " + val + ", %eax\n";
		       	movl = movl + "  movl  %eax, " + to_string(variables[var_name]) + "(%rbp)";
		    }

		    cout << movl << endl;
  		}	

  	}	

  	if ( ctx->exprMulti() != NULL)
  	{
  		visit(ctx->exprMulti());
  	}

    typeSize = 0;

    return 0;

  }

  /*
	rule if
  */

  virtual antlrcpp::Any visitBlockIF(ifccParser::BlockIFContext *ctx) override {
    
    string reg( visit(ctx->rval()).as<std::string>() );
    
    if (reg != "%eax") {
        cout << " 	movl	" << reg << ",%eax\n";
        reg = "%eax";
    }
    cout << "	cmpl	$0, " << reg << endl;

    int tmp = label;
    cout << "	je  .L" << to_string(label) << endl;
    label += 2;
    visit(ctx->list_instr());
    cout << "	jmp  .L" << to_string(tmp+1) << endl;
	  cout << ".L" << to_string(tmp) << ":\n";
    
    if (ctx->blockELSE() != NULL) 
    {
    	visit(ctx->blockELSE());
    }

    cout << ".L" << to_string(tmp+1)<< ":\n";
    
    return 0;
  }

  /*
	rule rval
  */

  virtual antlrcpp::Any visitAdditionLeft(ifccParser::AdditionLeftContext *ctx) override {
    string reg = "";

    if (ctx->children.size() < 3)   
    {
      string var_name(ctx->children[1]->getText());
    	reg = to_string(variables[var_name]) + "(%rbp)";
    } else {                        // array
      string var_name(ctx->children[1]->getText());
      string index_reg(visit(ctx->children[3]).as<std::string>());

      cout << "   movl  " << index_reg << ", %eax\n";
      cout << "   cltq  " << endl;
      cout << "   leaq  0(,%rax,4), %rcx" << endl;
      cout << "   leaq  " << var_name << "(%rip), %rdx\n";

      reg = "(%rcx, %rdx)";

    }

/*
    if (variables_size[var_name] == 1)
    {
      cout << "  movsbl  " << reg << ", %eax\n";
    } else {
      cout << "  movl  " << reg << ", %eax\n";
    }
*/

    cout << "  addl  $1, " << reg << endl;
    cout << "  movl  " << reg << ", %eax\n";
    
    string ret("%eax");
    
    return ret;
  }

  virtual antlrcpp::Any visitAdditionRight(ifccParser::AdditionRightContext *ctx) override {
    string reg = "";

    if (ctx->children.size() < 3)  
    {
      string var_name(ctx->children[0]->getText());
    	reg = to_string(variables[var_name]) + "(%rbp)";
    } else {       
      string var_name(ctx->children[0]->getText());                 // array
	  	string index_reg(visit(ctx->children[2]).as<std::string>());

      cout << "   movl  " << index_reg << ", %eax\n";
      cout << "   cltq  " << endl;
      cout << "   leaq  0(,%rax,4), %rcx" << endl;
      cout << "   leaq  " << var_name << "(%rip), %rdx\n";

      reg = "(%rcx, %rdx)";
    }
/*
    if (variables_size[var_name] == 1)
    {
      cout << "  movsbl  " << reg << ", %eax\n";
    } else {
      cout << "  movl  " << reg << ", %eax\n";
    }
*/
    cout << "  addl  $1, " << reg << endl;
    
    string ret("%eax");
    
    return ret;
  }

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    sizeTmp = typeSize;
    typeSize = 0;

    visitChildren(ctx);

    string ret("%eax");
    return ret;
  }

  virtual antlrcpp::Any visitSubLeft(ifccParser::SubLeftContext *ctx) override {
    string reg = "";

    if (ctx->children.size() < 3)   
    {
      string var_name(ctx->children[1]->getText());
    	reg = to_string(variables[var_name]) + "(%rbp)";
    } else {     
      string var_name(ctx->children[1]->getText());                 // array
	  	string index_reg(visit(ctx->children[3]).as<std::string>());

      cout << "   movl  " << index_reg << ", %eax\n";
      cout << "   cltq  " << endl;
      cout << "   leaq  0(,%rax,4), %rcx" << endl;
      cout << "   leaq  " << var_name << "(%rip), %rdx\n";

      reg = "(%rcx, %rdx)";
    }

    cout << "  subl  $1, " << reg << endl;
    cout << "  movl  " << reg << ", %eax\n";
    
    string ret("%eax");
    
    return ret;
  }

  virtual antlrcpp::Any visitSubRight(ifccParser::SubRightContext *ctx) override {
    string reg = "";

    if (ctx->children.size() < 3)   
    {
      string var_name(ctx->children[0]->getText());
    	reg = to_string(variables[var_name]) + "(%rbp)";
    } else {        
      string var_name(ctx->children[0]->getText());                // array
	  	string index_reg(visit(ctx->children[2]).as<std::string>());

      cout << "   movl  " << index_reg << ", %eax\n";
      cout << "   cltq  " << endl;
      cout << "   leaq  0(,%rax,4), %rcx" << endl;
      cout << "   leaq  " << var_name << "(%rip), %rdx\n";

      reg = "(%rcx, %rdx)";
    }

    cout << "  movl  " << reg << ", %eax\n";
    cout << "  subl  $1, " << reg << endl;
    
    string ret("%eax");
    
    return ret;
  }

  virtual antlrcpp::Any visitMlpDiv(ifccParser::MlpDivContext *ctx) override {

    string op = ctx->children[1]->getText();
    string ret;

    if (op == "*")
    {

      string operand1(visit(ctx->rval(0)).as<std::string>());
      if (operand1 == "%eax") {
        ret = "  movl  " + operand1 + ", %edx\n";
        cout << ret;
        operand1 = "%edx";
      }

      string operand2(visit(ctx->rval(1)).as<std::string>());
      ret = "  movl  " + operand2 + ", %eax\n";

      ret = ret + "  imull  " + operand1 + ", %eax";

      cout << ret << endl;
      
      string reg("%eax");

      return reg;

    } else {

      cout << "  movl  %edx, %ebx\n";

      string operand2(visit(ctx->rval(1)).as<std::string>());
      cursor = cursor - 4;
      ret = "  movl  " + operand2 + ", %edx\n";
      ret = ret + "  movl  %edx, " + to_string(cursor) + "(%rbp)\n";
      cout << ret;
      operand2 = to_string(cursor) + "(%rbp)";

      string operand1(visit(ctx->rval(0)).as<std::string>());
      ret = "  movl  " + operand1 + ", %eax\n";
      ret = ret + "  cltd\n  idivl " + operand2;
      cout << ret << endl;

      cursor = cursor + 4;
      cout << "  movl  %ebx, %edx\n";
      
      string reg("%eax");

      return reg;

    }

    string reg("%eax");
	return reg;
  }

  virtual antlrcpp::Any visitPlsMns(ifccParser::PlsMnsContext *ctx) override {

    string op = ctx->children[1]->getText();
    string ret;

    if (op == "+")
    {

      string operand1(visit(ctx->rval(0)).as<std::string>());
      if (operand1 == "%eax") {
        ret = "  movl  " + operand1 + ", %edx\n";
        cout << ret;
        operand1 = "%edx";
      }

      string operand2(visit(ctx->rval(1)).as<std::string>());
      ret = "  movl  " + operand2 + ", %eax\n";
      ret = ret + "  addl  " + operand1 + ", %eax";
      cout << ret << endl;
      
      string reg("%eax");

      return reg;

    } else {

      string operand2(visit(ctx->rval(1)).as<std::string>());
      if (operand2 == "%eax") {
        ret = "  movl  " + operand2 + ", %edx\n";
        cout << ret;
        operand2 = "%edx";
      }

      string operand1(visit(ctx->rval(0)).as<std::string>());
      ret = "  movl  " + operand1 + ", %eax\n";
      ret = ret + "  subl " + operand2 + ", %eax";
      cout << ret << endl;
      
      string reg("%eax");

      return reg;

    }

    string reg("%eax");
    
    return reg;
  }
  virtual antlrcpp::Any visitAndOr(ifccParser::AndOrContext *ctx) override {
      string op = ctx->children[1]->getText();
      if (op == "&") {
          string operand1(visit(ctx->rval(0)).as<std::string>());
          cout << "  movl  " + operand1 + ", %edx\n";
          string operand2(visit(ctx->rval(1)).as<std::string>());
          cout << "  movl  " + operand2 + ", %eax\n";
          cout << "  andl %edx, %eax \n";
          string reg("%eax");
          return reg;
      } else if (op == "|") {
          string operand1(visit(ctx->rval(0)).as<std::string>());
          cout << "  movl  " + operand1 + ", %edx\n";
          string operand2(visit(ctx->rval(1)).as<std::string>());
          cout << "  movl  " + operand2 + ", %eax\n";
          cout << "  orl %edx, %eax \n";
          string reg("%eax");
          return reg;
      }
      string reg("%eax");
      return reg;
  }
	

  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override {

  	string val = visit(ctx->val()).as<std::string>();

    return val;
  }


  virtual antlrcpp::Any visitComp(ifccParser::CompContext *ctx) override {
    string op = ctx->children[1]->getText();
    string ret;

    string operand2(visit(ctx->rval(1)).as<std::string>());
    ret = "  movl  " + operand2 + ", %edx\n";
    cout << ret;
    operand2 = "%edx";

    string operand1(visit(ctx->rval(0)).as<std::string>());
    int tmp = label;
    label += 2;

    cout << "  movl  " + operand1 + ", %eax\n";
    operand1 = "%eax";

    cout << "  cmpl  " + operand2 + ", " + operand1 << endl;
    if (op == "==") {
        cout << "  je   .L" << to_string(tmp) << endl;
    } else if (op == "!=") {
        cout << "  jne   .L" << to_string(tmp) << endl;
    } else if (op == ">") {
        cout << "  jg   .L" << to_string(tmp) << endl;
    } else if (op == ">=") {
        cout << "  jge   .L" << to_string(tmp) << endl;
    } else if (op == "<") {
        cout << "  jl   .L" << to_string(tmp) << endl;
    } else if (op == "<=") {
        cout << "  jle   .L" << to_string(tmp) << endl;
    }
    cout << "  movl $0, %eax\n";
    cout << "  jmp   .L" << to_string(tmp + 1) << endl;
    cout << ".L" << to_string(tmp) << ":" << endl;
    cout << "  movl  $1, %eax\n";
    cout << ".L" << to_string(tmp + 1) << ":" << endl;
    string reg("%eax");
    return reg;

  }


  virtual antlrcpp::Any visitCallgetchar(ifccParser::CallgetcharContext *ctx) override {
    cout << "   call   getchar@PLT\n";
    string reg("%eax");
    return reg;
  }



  /*
	rule val
  */

  virtual antlrcpp::Any visitGetConst(ifccParser::GetConstContext *ctx) override {

  	string cst = "$" + ctx->CONST()->getText();

    return cst;
  }

  virtual antlrcpp::Any visitGetVAR(ifccParser::GetVARContext *ctx) override {
	
	  string var_name(ctx->VAR()->getText());
  	
  	string var = to_string(variables[var_name]) + "(%rbp)";

    return var;
  }

  virtual antlrcpp::Any visitGetTab(ifccParser::GetTabContext *ctx) override {

  	string var_name(ctx->VAR()->getText());
  	string index_reg(visit(ctx->children[2]).as<std::string>());

    cout << "   movl  " << index_reg << ", %eax\n";
    cout << "   cltq  " << endl;
    cout << "   leaq  0(,%rax,4), %rcx" << endl;
    cout << "   leaq  " << var_name << "(%rip), %r8\n";
    cout << "   movl  (%rcx, %r8), %eax\n";

    string reg = "%eax";
  	return reg;
  }

  /*
	return 
  */

  virtual antlrcpp::Any visitMyReturn(ifccParser::MyReturnContext *ctx) override {

  	string ret = "  movl  " + visit(ctx->rval()).as<std::string>() + ", %eax";
  	cout << ret << endl;
    cout << "   jmp   .L" << to_string(returnLabel) << endl; 

    return ret;
  }


  void setVarSize(int size){
      varSize = size;
  }

  void setTabVar(map<string, int> &tab, map<string, int> &tabSize)
  {
  	map<string, int>::iterator iter;
    iter = tab.begin();
    while(iter != tab.end()) {
    	variables[iter->first] = iter->second;
    	iter++;
    }

    iter = tabSize.begin();
    while(iter != tabSize.end()) {
    	variables_size[iter->first] = iter->second;
    	iter++;
    }

  }

  void setFctSize(map<string, int> &fct)
  {
  	map<string, int>::iterator iter;
    iter = fct.begin();
    while(iter != fct.end()) {
    	fct_size[iter->first] = iter->second;
    	iter++;
    }

  }

private:

  map<string, int> variables;
  map<string, int> variables_size;

  map<string, int> fct_size;

  string paramReg[6] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"}; 
  int cursor = 0;
  int label = 10;
  int returnLabel = 2;
  int varSize = 0;
  int typeSize = 0;
  int sizeTmp = 0;
  
};

