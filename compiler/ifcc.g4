grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' list_expr RETURN CONST ';' '}' ;

list_expr : expr*;

expr : 'int' VAR '=' val ';'  	    # affectation
	 ;


val : CONST		# getConst
	| VAR		# getVAR
	; 

VAR : [a-zA-Z][a-zA-Z0-9]* ;
RETURN : 'return' ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
