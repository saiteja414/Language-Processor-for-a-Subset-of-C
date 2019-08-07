%{
#include <stdio.h>
#include <string>
extern "C" void yyerror(char *s);
extern int yylex(void);
extern int yylineno;
Symbol_Table * symTable;
Symbol_Table * globalSymTable;
Symbol_Table * symTableArg;
int integer;
int fun_type;
string proc_name;
int count;
int main_present;
%}

%union {
    int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Sequence_Ast * seq_ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;
}

%token <integer_value> INTEGER_NUMBER
%token <double_value> DOUBLE_NUMBER
%token <string_value> NAME
%token INTEGER
%token FLOAT
%token VOID
%token RETURN
%token PRINT
%token ASSIGN DO WHILE IF ELSE LESS_THAN_EQUAL GREATER_THAN_EQUAL EQUAL NOT_EQUAL LESS_THAN GREATER_THAN AND OR NOT

%right '?'
%left OR
%left AND
%left NOT
%left LESS_THAN_EQUAL GREATER_THAN_EQUAL EQUAL NOT_EQUAL LESS_THAN GREATER_THAN
%left '+' '-'
%left '*' '/'


%%

program 			:	M program1 {if(main_present == 0) {printf("cs316 : Error\n");exit(0);}}
M 					:   { main_present = 0;globalSymTable = new Symbol_Table();}
program1			:	variable_declaration  {if($<symbol_table>1 != NULL){
							(globalSymTable)->append_list(*($<symbol_table>1),yylineno);
							program_object.set_global_table(*(globalSymTable));
							}
						}
						program1
					|   function_declaration program1
                    |   procedure_definition	
					;

function_declaration:   type NAME '('  arg ')' ';'
                    {
                               	if($<integer_value>1 == 0){
				      				Procedure * proc = new Procedure(double_data_type , *($2) , yylineno);
	    	                 			if(true){
				      					program_object.set_proc_to_map( *($2) ,proc );}
				      				else {printf("cs316:Error6\n"); exit(0);}}
	    	                 		else if($<integer_value>1 == 1){
				      				Procedure * proc = new Procedure(int_data_type , *($2) , yylineno);
	    	                 			if(true){
				      					program_object.set_proc_to_map( *($2) ,proc );}
				      				else {printf("cs316:Error7\n"); exit(0);}}
				      			else if($<integer_value>1 == 2){
									if(*($2) == "main"){main_present = 1;}
				      				Procedure * proc = new Procedure(void_data_type , *($2) , yylineno);
	    	                 			if(true){
				      					program_object.set_proc_to_map( *($2) ,proc );}
				      				else {printf("cs316:Error8\n"); exit(0);}}
	                         Procedure * proc = program_object.get_procedure_prototype(*($2));
							if($<symbol_table>4 !=NULL){
								proc->set_formal_param_list(*($<symbol_table>4));
							}
                            
                    }
                    |   type NAME '('  arg_dec_list ')' ';'
                    {
                               	if($<integer_value>1 == 0){
				      				Procedure * proc = new Procedure(double_data_type , *($2) , yylineno);
	    	                 			if(true){
				      					program_object.set_proc_to_map( *($2) ,proc );}
				      				else {printf("cs316:Error9\n"); exit(0);}}
	    	                 		else if($<integer_value>1 == 1){
				      				Procedure * proc = new Procedure(int_data_type , *($2) , yylineno);
	    	                 			if(true){
				      					program_object.set_proc_to_map( *($2) ,proc );}
				      				else {printf("cs316:Error10\n"); exit(0);}}
				      			else if($<integer_value>1 == 2){
									if(*($2) == "main"){main_present = 1;}
				      				Procedure * proc = new Procedure(void_data_type , *($2) , yylineno);
	    	                 			if(true){
				      					program_object.set_proc_to_map( *($2) ,proc );}
				      				else {printf("cs316:Error11\n"); exit(0);}}
	                         Procedure * proc = program_object.get_procedure_prototype(*($2));
							if($<symbol_table>4 !=NULL){
								proc->set_formal_param_list(*($<symbol_table>4));
							}
                            
                    }

arg_dec_list        :   arg_dec_list1 
                    {$<symbol_table>$ = $<symbol_table>1;}
                    ; 

arg_dec_list1         :type
						{
							Symbol_Table_Entry * entry;
                            string name = "dummy" + to_string(count);
                            count++;
							if(integer == 1) entry = new Symbol_Table_Entry(name, int_data_type, yylineno);
							else if (integer == 0) entry = new Symbol_Table_Entry(name, double_data_type, yylineno);
							Symbol_Table * help = new Symbol_Table();
							help->push_symbol(entry);
							$<symbol_table>$ = help;

						}
						|   arg_dec_list1 ',' type  
						{
							Symbol_Table_Entry * entry;
                            string name = "dummy" + to_string(count);
                            count++;
							if(integer == 1) entry = new Symbol_Table_Entry(name, int_data_type, yylineno);
							else if (integer == 0) entry = new Symbol_Table_Entry(name, double_data_type, yylineno);
							Symbol_Table * help = new Symbol_Table();
							help->push_symbol(entry);
							($<symbol_table>1)->append_list(*help,yylineno);
							$<symbol_table>$ = $<symbol_table>1;
							
						}


arg_dec_list2       	:type NAME
						{
							Symbol_Table_Entry * entry;
							if(integer == 1) entry = new Symbol_Table_Entry(*($2), int_data_type, yylineno);
							else if (integer == 0) entry = new Symbol_Table_Entry(*($2), double_data_type, yylineno);
							Symbol_Table * help = new Symbol_Table();
							help->push_symbol(entry);
							$<symbol_table>$ = help;

						}
						|   arg_dec_list2 ',' type NAME   
						{
							Symbol_Table_Entry * entry;
							if(integer == 1) entry = new Symbol_Table_Entry(*($4), int_data_type, yylineno);
							else if (integer == 0) entry = new Symbol_Table_Entry(*($4), double_data_type, yylineno);
							Symbol_Table * help = new Symbol_Table();
							help->push_symbol(entry);
							($<symbol_table>1)->append_list(*help,yylineno);
							$<symbol_table>$ = $<symbol_table>1;
							
						}



declaration_list	: variable_declaration_list 
					{	
						if($<symbol_table>1 != NULL)program_object.set_global_table(*($<symbol_table>1));
					}
					;

procedure_definition	: procedure
						| procedure_definition procedure


procedure 				:	type NAME '('
						 arg ')' '{'
										{
                            proc_name = *($2);
							if($<integer_value>1 == 0){
								Procedure * proc = new Procedure(double_data_type , *($2) , yylineno);
								proc->set_proc_is_defined();
	    	           			if(!(program_object.variable_proc_name_check(*($2)))){
									// printf("double1\n");
									program_object.set_proc_to_map( *($2) ,proc );
								}
								else if(program_object.variable_proc_name_check(*($2)) &&
								 		! program_object.get_procedure_prototype(*($2))->is_proc_defined() &&
								  		program_object.get_procedure_prototype(*($2))->get_return_type() == double_data_type){
										// printf("double2\n");
										program_object.set_proc_to_map( *($2) ,proc );
								}
								else {printf("cs316:Error0\n"); exit(0);}}
	    	           		else if($<integer_value>1 == 1){
								Procedure * proc = new Procedure(int_data_type , *($2) , yylineno);
								proc->set_proc_is_defined();
	    	           			if(! program_object.variable_proc_name_check(*($2))){
									// printf("int1\n");
									program_object.set_proc_to_map( *($2) ,proc );
								}
								else if(program_object.variable_proc_name_check(*($2)) &&
								 		! program_object.get_procedure_prototype(*($2))->is_proc_defined() &&
								  		program_object.get_procedure_prototype(*($2))->get_return_type() == int_data_type){
									// printf("int2\n");
										program_object.set_proc_to_map( *($2) ,proc );
								}
								else {printf("cs316:Error1\n"); exit(0);}}
							else if($<integer_value>1 == 2){
								if(*($2) == "main"){main_present = 1;}
								Procedure * proc = new Procedure(void_data_type , *($2) , yylineno);
								proc->set_proc_is_defined();
	    	           			if(!(program_object.variable_proc_name_check(*($2)))){
									// printf("void2\n");
									program_object.set_proc_to_map( *($2) ,proc );
								}
								else if(program_object.variable_proc_name_check(*($2)) &&
								 		! program_object.get_procedure_prototype(*($2))->is_proc_defined() &&
								  		program_object.get_procedure_prototype(*($2))->get_return_type() == void_data_type){
									// printf("void1\n");
										program_object.set_proc_to_map( *($2) ,proc );
								}
								else {printf("cs316:Error2\n"); exit(0);}}
						    Procedure * proc = program_object.get_procedure_prototype(*($2));
							if($<symbol_table>4 !=NULL){
								proc->set_formal_param_list(*($<symbol_table>4));
							}
                            }
							optional_variable_declaration_list
		                        		statement_list  
		    	           		'}'
	    	           	{
	    	           		Procedure * proc = program_object.get_procedure_prototype(*($2));
							if(($<symbol_table>8)!=NULL){proc->set_local_list(*($<symbol_table>8));}
                            if(($<ast_list>9)!=NULL){proc->set_ast_list(*($<ast_list>9));}
                        }
                     	;

arg 					:
						{	
							$<symbol_table>$ = NULL;
						}
						|	arg_list
						{
							$<symbol_table>$ = $<symbol_table>1;
							symTableArg = $<symbol_table>$;
						}
						;

arg_list				:	type NAME
						{
							Symbol_Table_Entry * entry;
							if(integer == 1) entry = new Symbol_Table_Entry(*($2), int_data_type, yylineno);
							else if (integer == 0) entry = new Symbol_Table_Entry(*($2), double_data_type, yylineno);
							Symbol_Table * help = new Symbol_Table();
							help->push_symbol(entry);
							$<symbol_table>$ = help;

						}
						|   arg_list ',' type NAME   
						{
							Symbol_Table_Entry * entry;
							if(integer == 1) entry = new Symbol_Table_Entry(*($4), int_data_type, yylineno);
							else if (integer == 0) entry = new Symbol_Table_Entry(*($4), double_data_type, yylineno);
							Symbol_Table * help = new Symbol_Table();
							help->push_symbol(entry);
							($<symbol_table>1)->append_list(*help,yylineno);
							$<symbol_table>$ = $<symbol_table>1;
							
						}

optional_variable_declaration_list	:
						{	
							$<symbol_table>$ = NULL;
							symTable = NULL;
						}
						|	variable_declaration_list
						{
							$<symbol_table>$ = $<symbol_table>1;
							symTable = $<symbol_table>$;
						}
						;

variable_declaration_list		:	variable_declaration
								{
									$<symbol_table>$ = $<symbol_table>1;
								}
								|	variable_declaration_list 
									variable_declaration
								{
									if($<symbol_table>1 != NULL && $<symbol_table>2 != NULL) {
										($<symbol_table>1)->append_list(*($<symbol_table>2),yylineno);
									}
									else if($<symbol_table>2 != NULL){
										$<symbol_table>$ = $<symbol_table>2;
									}
									else {
										$<symbol_table>$ = $<symbol_table>1;
									}
								}
								;



variable_declaration			:	declaration ';'
								{
									$<symbol_table>$ = $<symbol_table>1;
								}
								;

declaration				:	type variable_list
						{
							$<symbol_table>$ = $<symbol_table>2;
						}
						;

type 					:	INTEGER
						{
							integer = 1;
							$<integer_value>$ = 1;
						}
						|	FLOAT
						{
							$<integer_value>$ = 0;
							integer = 0;
						}
						|   VOID
						{
							$<integer_value>$ = 2;
							integer = 2;
						}
                        ;

variable_list                           :       NAME variable_list1 
										{
											Symbol_Table_Entry * entry;
											if(integer == 1) entry = new Symbol_Table_Entry(*($1), int_data_type, yylineno);
											else if (integer == 0) entry = new Symbol_Table_Entry(*($1), double_data_type, yylineno);
											Symbol_Table * help = new Symbol_Table();
											help->push_symbol(entry);
											(help)->append_list(*($<symbol_table>2),yylineno);
											$<symbol_table>$ = help;
										};

variable_list1                          :      ','  NAME variable_list1
                                        {
											Symbol_Table_Entry * entry;
											if(integer == 1) entry = new Symbol_Table_Entry(*($2), int_data_type, yylineno);
											else if (integer == 0) entry = new Symbol_Table_Entry(*($2), double_data_type, yylineno);
											Symbol_Table * help = new Symbol_Table();
											help->push_symbol(entry);
											(help)->append_list(*($<symbol_table>3),yylineno);
											$<symbol_table>$ = help;

                                        }
                                        |
                                        {
                                        	$<symbol_table>$ = new Symbol_Table();
                                        }
                                        ;
																				
statement_list	        :
						{
							$<ast_list>$ = new list<Ast *>;	
						}
						|	statement_list
							statement
						{
							($<ast_list>1)->push_back($<ast>2);
							$<ast_list>$ = $<ast_list>1;
                        }
						;

statement 				:	assignment_statement
						{$<ast>$ = $<ast>1;}
						|	selection_statement
						{$<ast>$ = $<ast>1;}
						|	iterative_statement
						{$<ast>$ = $<ast>1;}
						| print_statement
						{$<ast>$ = $<ast>1;}
						|	'{' sequence_statement1 '}'
						{$<ast>$ = $<ast>2;}
						|	function_statement
						{$<ast>$ = $<ast>1;}
                        |   return_statement
                        {$<ast>$ = $<ast>1;};

return_statement        :   RETURN expression ';'
                        {$<ast>$ = new Return_Ast($<ast>2, proc_name, yylineno);}
						|   RETURN ';'
                        {$<ast>$ = new Return_Ast(NULL, proc_name, yylineno);}


function_statement		:	NAME '(' arg_list1 ')' ';'
						{
							Call_Ast * func = new Call_Ast(*($1), yylineno);
							if($<ast_list>3 != NULL)func->set_actual_param_list(*($<ast_list>3));
							Register_Descriptor *reg_d = new Register_Descriptor();
							func->check_actual_formal_param(program_object.get_procedure_prototype(*($1))->get_formal_param_list());
							func->set_register(reg_d);
							$<ast>$ = func;
						};

function_statement1		:	NAME '(' arg_list1 ')' ';'
						{
							Call_Ast * func = new Call_Ast(*($1), yylineno);
							if($<ast_list>3 != NULL)func->set_actual_param_list(*($<ast_list>3));
							func->check_actual_formal_param(program_object.get_procedure_prototype(*($1))->get_formal_param_list());
							$<ast>$ = func;
						};



arg_list1				: 
						{ $<ast_list>$ = NULL; } 
						| arg_list2
						{ $<ast_list>$ = $<ast_list>1; } 
						;

arg_list2				: expression
						{
							$<ast_list>$ = new list<Ast *>;	
							($<ast_list>$)->push_back($<ast>1);
						}
						|  arg_list2 ',' expression 
						{
							$<ast_list>$ = $<ast_list>1;	
							($<ast_list>$)->push_back($<ast>3);
						}

entity					: variable 
						{ 
							$<ast>$ = $<ast>1;
							($<ast>$)->set_data_type(($<ast>1)->get_data_type());
						}
						| constant    
						{ 
							$<ast>$ = $<ast>1;
							($<ast>$)->set_data_type(($<ast>1)->get_data_type());
						}

assignment_statement	:	variable ASSIGN expression ';' 
						{
							Ast * assign = new Assignment_Ast($<ast>1, $<ast>3, yylineno);
							$<ast>$ = assign;
							($<ast>$)->check_ast();	
						}
						|	variable ASSIGN function_statement1 
						{
							Ast * assign = new Assignment_Ast($<ast>1, $<ast>3, yylineno);
							$<ast>$ = assign;
							($<ast>$)->check_ast();
						}
						;


selection_statement		:	IF '(' boolean_expression ')' sequence_statement ELSE sequence_statement
						{
							Ast * ifelse = new Selection_Statement_Ast($<ast>3,$<ast>5, $<ast>7, yylineno);
							$<ast>$ = ifelse;
							($<ast>$)->check_ast();	
						}
						|	IF '(' boolean_expression ')' sequence_statement
						{
							Ast * ifelse = new Selection_Statement_Ast($<ast>3,$<ast>5, NULL , yylineno);
							$<ast>$ = ifelse;	
							($<ast>$)->check_ast();	
						}
						;

iterative_statement		:	WHILE '(' boolean_expression ')' sequence_statement	
						{
							Ast * while_Stm = new Iteration_Statement_Ast($<ast>3 , $<ast>5, yylineno, false);
							$<ast>$ = while_Stm;
							($<ast>$)->check_ast();	
						}
						|	DO sequence_statement WHILE '(' boolean_expression ')' ';'
						{
							Ast * dowhile = new Iteration_Statement_Ast($<ast>5 , $<ast>2, yylineno, true);
							$<ast>$ = dowhile;
							($<ast>$)->check_ast();	
						}
						;

sequence_statement		:	statement
						{
							$<ast>$ = $<ast>1;
						}
						|	'{' sequence_statement1 '}'
						{
							$<ast>$ = $<seq_ast>2;
						}
						|
						{
							printf("cs316: Error12\n");
						}
						;

sequence_statement1 	:	statement
						{
							Sequence_Ast* seq = new Sequence_Ast(yylineno);
							seq->ast_push_back($<ast>1);
							$<seq_ast>$ = seq;
							($<seq_ast>$)->check_ast();	
						}
						| 	sequence_statement1 statement
						{
							$<seq_ast>1->ast_push_back($<ast>2);
							$<seq_ast>$ = $<seq_ast>1;
							($<seq_ast>$)->check_ast();	
						};

print_statement			: PRINT variable ';'
						{
							Ast* print_ast = new Print_Ast($<ast>2, yylineno);
							$<ast>$ = print_ast;
						}


boolean_expression		:	NOT boolean_expression
						{
							Ast* bool_ast = new Logical_Expr_Ast($<ast>2, _logical_not, $<ast>2, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	boolean_expression AND boolean_expression
						{
							Ast* bool_ast = new Logical_Expr_Ast($<ast>1, _logical_and, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	boolean_expression OR boolean_expression
						{
							Ast* bool_ast = new Logical_Expr_Ast($<ast>1, _logical_or, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						
						|	expression LESS_THAN expression
						{
							Ast* bool_ast = new Relational_Expr_Ast($<ast>1, less_than, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	expression LESS_THAN_EQUAL expression
						{
							Ast* bool_ast = new Relational_Expr_Ast($<ast>1, less_equalto, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	expression GREATER_THAN expression
						{
							Ast* bool_ast = new Relational_Expr_Ast($<ast>1, greater_than, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	expression GREATER_THAN_EQUAL expression
						{
							Ast* bool_ast = new Relational_Expr_Ast($<ast>1, greater_equalto, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	expression EQUAL expression
						{
							Ast* bool_ast = new Relational_Expr_Ast($<ast>1, equalto, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	expression NOT_EQUAL expression
						{
							Ast* bool_ast = new Relational_Expr_Ast($<ast>1, not_equalto, $<ast>3, yylineno);
							$<ast>$ = bool_ast;
							($<ast>$)->check_ast();	
						}
						|	'(' boolean_expression ')'
						{
							$<ast>$ = $<ast>2;
						}
						;


expression	: variable 
			{ 
				$<ast>$ = $<ast>1;
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
			}
			| constant    
			{ 
				$<ast>$ = $<ast>1;
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
			}
			
			|'-' uexpression
			{
				$<ast>$ = new UMinus_Ast($<ast>2,NULL,yylineno);
				($<ast>$)->set_data_type(($<ast>2)->get_data_type());
			}

			| expression '+' expression  
			{	
				$<ast>$ = new Plus_Ast($<ast>1,$<ast>3,yylineno);
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
				($<ast>$)->check_ast();	
			}
			| expression '*' expression  
			{
				$<ast>$ = new Mult_Ast($<ast>1,$<ast>3,yylineno);
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
				($<ast>$)->check_ast();	
			}
			| expression '-' expression  
			{
				$<ast>$ = new Minus_Ast($<ast>1,$<ast>3,yylineno);
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
				($<ast>$)->check_ast();	
			}
			| expression '/' expression  
			{
				$<ast>$ = new Divide_Ast($<ast>1,$<ast>3,yylineno);
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
				($<ast>$)->check_ast();	
			}
			| '(' expression ')'
			{
				$<ast>$ = $<ast>2;
				($<ast>$)->set_data_type(($<ast>2)->get_data_type());
			}
			| boolean_expression '?' expression ':' expression
			{
				Ast * cond = new Conditional_Expression_Ast($<ast>1, $<ast>3, $<ast>5, yylineno);
				$<ast>$ = cond;
				($<ast>$)->check_ast();	
			}
			;

uexpression	: '(' expression ')'
			{
				$<ast>$ = $<ast>2;
				($<ast>$)->set_data_type(($<ast>2)->get_data_type());
				($<ast>$)->check_ast();	
			}
			|	variable
			{	$<ast>$ = $<ast>1;
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
				($<ast>$)->check_ast();	
			}
			|	constant
			{	$<ast>$ = $<ast>1;
				($<ast>$)->set_data_type(($<ast>1)->get_data_type());
				($<ast>$)->check_ast();	
			}
			|	'-' uexpression
			{
				$<ast>$ = new UMinus_Ast($<ast>2,NULL,yylineno);
				($<ast>$)->set_data_type(($<ast>2)->get_data_type());	
			}
			;
variable		:	NAME
				{

					if(symTable != NULL && symTable->variable_in_symbol_list_check(*($1))){
						Ast * name = new Name_Ast(*($1), symTable->get_symbol_table_entry(*($1)), yylineno);
						$<ast>$ = name;
					}
					else if(symTableArg != NULL && symTableArg->variable_in_symbol_list_check(*($1))){
						Ast * name = new Name_Ast(*($1), symTableArg->get_symbol_table_entry(*($1)), yylineno);
						$<ast>$ = name;
					}
					else if(program_object.variable_in_symbol_list_check(*($1))){
						Ast * name = new Name_Ast(*($1), program_object.get_symbol_table_entry(*($1)), yylineno);
						$<ast>$ = name;
					}
					else
					{
						printf("cs316: Error : File: , Line: %d: Variable has not been declared\n",yylineno);
						exit(0);
					}
				}
			;

constant		:	INTEGER_NUMBER
				{
					int a1 = yylineno;
					int a2 = (int)$1;
					Ast* number = new Number_Ast<int>(int($1), int_data_type ,(int)yylineno);
					$<ast>$ = number;
				}
				|
				DOUBLE_NUMBER
				{
					int a1 = yylineno;
					int a2 = (int)$1;
					Ast* number = new Number_Ast<double>(double($1), double_data_type ,(int)yylineno);
					$<ast>$ = number;
				}
				;
