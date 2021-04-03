grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' list_instr myreturn '}' ;

list_instr : instr*;

instr : type (dec|aff)* ';'												        # decal
	  | expr listExpr* 	';'														# affect
	  | blockIF																    # exprIF
	  | 'putchar' '(' rval ')' ';' 											    # callputchar
	  | 'while' '(' rval ')' '{' list_instr '}' 							    # exprWHILE
	  | 'for' '(' condFOR1? ';' rval? ';' condFOR2? ')' '{' list_instr '}'     	# exprFOR
	  ;



dec : ',' VAR     # dec1
	| VAR  		  # dec2
	;

aff : (VAR '=')* rval    	# aff1
 	| ',' (VAR '=')* rval   # aff2
 	;

condFOR1 : expr listExpr*					 # condWithoutDec
		 | type VAR ('=' rval)? listExpr?    # condWithDec
		 ;

condFOR2 : expr listExpr*;

blockIF : 'if' '(' rval ')' '{' list_instr '}' blockELSE?;
blockELSE : 'else' '{' list_instr '}';


listExpr : ',' expr;
expr  :  (VAR '=')? rval;

rval  :	 VAR '++'		# additionRight
	  |  VAR '--'  		# subRight
	  |  '(' expr listExpr* ')'	# par
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

type : INT
	 | LONG
	 | CHAR
	 ; 

INT : 'int';
LONG : 'long';
CHAR : 'char';
VAR : [a-zA-Z][a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);