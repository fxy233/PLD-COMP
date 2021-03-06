#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"
#include "checkVisitor.h"


using namespace antlr4;
using namespace std;

int main(int argn, const char **argv) {
  stringstream in;
  if (argn==2) {
     ifstream lecture(argv[1]);
     in << lecture.rdbuf();
  }
  ANTLRInputStream input(in.str());
  ifccLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
//  for (auto token : tokens.getTokens()) {
//    std::cout << token->toString() << std::endl;
//  }

  ifccParser parser(&tokens);
  tree::ParseTree* tree = parser.axiom();

  Visitor visitor;
  CheckVisitor checkVisitor;
  checkVisitor.visit(tree);
  int size = checkVisitor.getVarSize();
  visitor.setVarSize(size);
  map<string, int> tab = checkVisitor.getTab();
  map<string, int> tab_size = checkVisitor.getTabSize();
  map<string, int> fct = checkVisitor.getFctSize();
  visitor.setTabVar(tab, tab_size);
  visitor.setFctSize(fct);
  visitor.visit(tree);

  return 0;
}
