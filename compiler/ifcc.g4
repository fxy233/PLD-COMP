grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' list_expr myreturn '}' ;

list_expr : expr*;

expr : 'int' VAR dec* ';'			    # declaration
	 | 'int' VAR '=' aff ';'  	        # definition
	 |  VAR '=' aff ';'					# affectation
	 |  'putchar' '(' arith ')' ';'		# callputchar
	 |  blockIF blockELSE?				# exprIF
	 ;

blockIF : 'if' '(' arith ')' '{' list_expr '}' ;
blockELSE : 'else' '{' list_expr '}' ;

dec : ',' VAR  					# multiDeclaration 
	;

aff : val 		# valExpr
	| arith		# arithExpr
	| 'getchar' '(' ')'   # callgetchar
	;

arith : '(' arith ')'			# par
	  | arith ('*'|'/') arith	# mlpDiv
	  | arith ('+'|'-') arith	# plsMns
	  | val						# value
	  ;


val : CONST		# getConst
	| VAR		# getVAR
	; 

myreturn : 'return' val ';'	# myReturn
         ;


VAR : [a-zA-Z][a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

