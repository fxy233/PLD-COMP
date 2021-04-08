grammar ifcc;

axiom : prog;

prog : decGlobal* 'int' 'main' '(' ')' '{' list_instr '}' defFunction?;

defFunction : funct*;

decGlobal : returnType VAR '(' listPara? ')' ';' ;

listPara : type VAR (',' type VAR)*	;

funct : returnType VAR '(' listPara? ')' '{' list_instr '}';

returnType : INT
		   | CHAR
		   | 'void'
		   ;

list_instr : instr*;

instr : type (dec1|aff1) (dec2|aff2)* ';'										# decal
	  | expr listExpr* 	';'														# affect
	  | blockIF																    # exprIF
	  | 'putchar' '(' rval ')' ';' 											    # callputchar
	  | 'while' '(' rval ')' '{' list_instr '}' 							    # exprWHILE
	  | 'for' '(' condFOR1? ';' rval? ';' condFOR2? ')' '{' list_instr '}'     	# exprFOR
	  | myreturn  # myReturnInstr
	  ;



dec1 : VAR ('[' CONST ']')?;
dec2 : ',' VAR ('[' CONST ']')?;



aff1 : (VAR '=')* rval;
aff2 : ',' (VAR '=')* rval;

condFOR1 : expr listExpr*					 # condWithoutDec
		 | type VAR ('[' CONST ']')? ('=' rval)? exprMulti?   # condWithDec
		 ;

condFOR2 : expr listExpr*;

blockIF : 'if' '(' rval ')' '{' list_instr '}' blockELSE?;
blockELSE : 'else' '{' list_instr '}';


exprMulti : listExpr*;
listExpr : ',' expr;
expr  :  (VAR ('[' rval ']')? '=')? rval;

rval  :	 VAR ('[' rval ']')? '++'		# additionRight
	  |  VAR ('[' rval ']')? '--'  		# subRight
	  |  '(' expr listExpr* ')'	# par
	  |  '++' VAR ('[' rval ']')? 		# additionLeft
	  |  '--' VAR ('[' rval ']')?		# subLeft
	  |  rval ('*'|'/') rval	# mlpDiv
	  |  rval ('+'|'-') rval	# plsMns
	  |  val						# value
	  |  rval ('=='|'!='|'>'|'>='|'<'|'<=') rval  # comp
	  |  rval ('|'|'&') rval  # andOr
	  |  'getchar' '(' ')'   # callgetchar
	  |  rval '(' (rval (',' rval)* )? ')'		# callfunction
	  ; 

val : CONST		# getConst
	| VAR		# getVAR
	| VAR '[' rval ']'		# getTab
	;

myreturn : 'return' rval ';'	# myReturn
         ;

type : INT
	 | CHAR
	 ; 

INT : 'int';
CHAR : 'char';
VAR : [a-zA-Z][a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);