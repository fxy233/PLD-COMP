grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' expr RETURN CONST ';' '}' ;

expr : 								# affVide
	 | 'int' VAR '=' val ';' expr	# affectation
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
