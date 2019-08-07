%{
# include "parser.tab.h"
# include "storetokens.hh"
int line = 1;
int main1 = 0;
%}

digit [0-9] 
operator [-+*/]
whitespace [ \t\r]
alphabet [a-zA-Z_]
falpha [a-zA-Z_0-9]
meta   [,{}();?:]
conditional_operator [?:]
relational_operators [< >]
logical_operators []
%%

{whitespace}+ ;
[\n] 	{line++;}

"//".*

print 				{store_token_name("PRINT",yytext,line);
					return PRINT;}

{operator} 		{store_token_name("ARITHOP",yytext,line);
					return yytext[0];
					}


while				{store_token_name("WHILE",yytext,line);
					return WHILE;
					}

do					{store_token_name("DO",yytext,line);
					return DO;
					}

if					{store_token_name("IF",yytext,line);
					return IF;
					}

else				{store_token_name("ELSE",yytext,line);
					return ELSE;
					}

[<][=]				{store_token_name("LESS_THAN_EQUAL",yytext,line);
					yylval.string_value = new std::string(yytext);
					return LESS_THAN_EQUAL;
					}

[>][=]				{store_token_name("GREATER_THAN_EQUAL",yytext,line);
					yylval.string_value = new std::string(yytext);
					return GREATER_THAN_EQUAL;
					}

[=][=]				{store_token_name("EQUAL",yytext,line);
					yylval.string_value = new std::string(yytext);
					return EQUAL;
					}

[!][=]				{store_token_name("NOT_EQUAL",yytext,line);
					yylval.string_value = new std::string(yytext);
					return NOT_EQUAL;
					}

[<]				{store_token_name("LESS_THAN",yytext,line);
					yylval.string_value = new std::string(yytext);
					return LESS_THAN;
					}

[>]				{store_token_name("GREATER_THAN",yytext,line);
					yylval.string_value = new std::string(yytext);
					return GREATER_THAN;
					}

[&][&]				{store_token_name("AND",yytext,line);
					yylval.string_value = new std::string(yytext);
					return AND;
					}

[|][|]					{store_token_name("OR",yytext,line);
					yylval.string_value = new std::string(yytext);
					return OR;
					}

[!]					{store_token_name("NOT",yytext,line);
					yylval.string_value = new std::string(yytext);
					return NOT;
					}



{digit}+ 		    {store_token_name("NUM",yytext,line);
					yylval.integer_value = atoi(yytext);
					return INTEGER_NUMBER;
					}

{digit}+[.]{digit}+ 		{store_token_name("FNUM",yytext,line);
	 					yylval.double_value = atof(yytext);
						return DOUBLE_NUMBER;
						}

int 		{store_token_name("INTEGER",yytext,line);
					return INTEGER;
			}

float 		{store_token_name("FLOAT",yytext,line);
				return FLOAT;
			}

return 		{store_token_name("RETURN",yytext,line);
				return RETURN;
			}

void 		{store_token_name("VOID",yytext,line);
				return VOID;
			}

= 		{store_token_name("ASSIGN_OP",yytext,line);
				return ASSIGN;
			}

main  {store_token_name("NAME",yytext,line);
				yylval.string_value = new std::string(yytext);
				main1 = 1;
				return NAME;
				}


{alphabet}{falpha}* 		{store_token_name("NAME",yytext,line);
									yylval.string_value = new std::string(strcat(yytext,"_"));
									return NAME;
									}

{meta}  	{store_token_name("META CHAR",yytext,line);
			return yytext[0];
			}

. 		{printf("cfglp error: File: , Line: %d: ERROR\n",line);}
