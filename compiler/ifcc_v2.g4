grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' list_instr myreturn '}' ;

list_instr : instr*;

instr : type? VAR (dec|aff)* 												# init
	  | blockIF																# exprIF
	  | 'putchar' '(' rval ')' ';' 										# callputchar
	  | 'while' '(' rval ')' '{' list_instr '}' 							# exprWHILE
	  | 'for' '(' condIF1 ';' rval? ';' condIF2 ')' '{' list_instr '}'     # exprFOR
	  ;


dec : ',' VAR;
aff : '=' (VAR '=')* rval;

condIF1 : (type VAR)? expr listExpr*
		| ;

condIF2 : expr listExpr*
		| ;

blockIF : 'if' '(' rval ')' '{' list_instr '}' blockELSE;
blockELSE : 'else' '{' list_instr '}' 
		  | ;



listExpr : ',' expr;

expr  :  (VAR '=')? rval;

rval  :	 VAR '++'		# additionRight
	  |  VAR '--'  		# subRight
	  |  '(' expr ')'	# par
	  |  '++' VAR 		# additionLeft
	  |  '--' VAR 		# subLeft
	  |  rval ('*'|'/') rval	# mlpDiv
	  |  rval ('+'|'-') rval	# plsMns
	  |  val						# value
	  |  rval ('=='|'!='|'>'|'>='|'<'|'<=') rval  # comp
	  |  'getchar' '(' ')'   # callgetchar
	  ; 

val : CONST		# getConst
	| VAR		# getVAR
	; 

myreturn : 'return' val ';'	# myReturn
         ;

type : 'int'
	 | 'long'
	 | 'char'
	 ; 


VAR : [a-zA-Z][a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);