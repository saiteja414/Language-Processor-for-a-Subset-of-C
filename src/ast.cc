#include <stdio.h>
#include <string.h>
using namespace std;
template class Number_Ast<double>;
template class Number_Ast<int>;


//Ast 
int Ast::labelCounter;

Ast::Ast(){

}

Ast::~Ast(){

}

bool Ast::check_ast(){
	return true;
}

Symbol_Table_Entry & Ast::get_symbol_entry(){

}

Data_Type Ast::get_data_type(){
	return this->node_data_type;
}

void Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

bool Ast::is_value_zero(){
	return true;
}

void Ast::print(ostream & file_buffer){
}

//end
//-----------------------------------------------------------------
//Assignment_Ast



Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line){
	this->set_data_type(temp_lhs->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs = temp_lhs;
	this->rhs = temp_rhs;
	this->lineno = line;
}

Assignment_Ast::~Assignment_Ast(){

}

bool Assignment_Ast::check_ast(){
	if(this->lhs->get_data_type()==this->rhs->get_data_type()){
		this->node_data_type = this->lhs->get_data_type();
		return true;
	}
	else{
		printf("cs316: Error\n");
		return false;
	}
}

void Assignment_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_SPACE<<"Asgn:";
	file_buffer<<"\n"<<AST_NODE_SPACE<<"LHS (";
	(this->lhs)->print(file_buffer);
	file_buffer<<")";
	file_buffer<<"\n"<<AST_NODE_SPACE<<"RHS (";
	(this->rhs)->print(file_buffer);
	file_buffer<<")";
}

//end
//-----------------------------------------------------------------
//Name_Ast
Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line){
	this->set_data_type(var_entry.get_data_type());
	this->variable_symbol_entry = &var_entry;
	this->lineno = line;
}

Name_Ast::~Name_Ast(){

}

Symbol_Table_Entry & Name_Ast::get_symbol_entry(){
	return *(this->variable_symbol_entry);
}

Data_Type Name_Ast::get_data_type(){
	return this->node_data_type;
}

void Name_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

void Name_Ast::print(ostream & file_buffer){
	string s = (this->variable_symbol_entry)->get_variable_name();
	file_buffer<<"Name : ";
	file_buffer<<s;
}

//end
//------------------------------------------------------------------ 
//Number_Ast
template <class T>
bool Number_Ast<T>::is_value_zero(){
	if(this->constant==0)return true;
	else return false;
}

template <class T>
Data_Type Number_Ast<T>::get_data_type(){
	return this->node_data_type;
}

template <class T>
void Number_Ast<T>::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}


template <class T>
Number_Ast<T>::Number_Ast(T number, Data_Type constant_data_type, int line){
	this->constant = number;
	this->node_data_type = constant_data_type;
	this->lineno = line;
}


template <class T>
Number_Ast<T>::~Number_Ast(){

}

template <class T>
void Number_Ast<T>::print(ostream & file_buffer){
	file_buffer<<"Num : ";
	file_buffer<<this->constant;
}

//end
//-----------------------------------------------------------------
//arith_exp
Data_Type Arithmetic_Expr_Ast::get_data_type(){
	return this->node_data_type;
}

void Arithmetic_Expr_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

bool Arithmetic_Expr_Ast::check_ast(){
	if(this->lhs->get_data_type()==this->rhs->get_data_type()){
		return true;
	}
	else{
		printf("cs316: Error\n");
		return false;
	}
}

void Arithmetic_Expr_Ast::print(ostream & file_buffer){
}

//end
//--------------------------------------------------------------------
//plus
Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line){
	this->set_data_type(l->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;	
}

void Plus_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: PLUS";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	this->lhs->print(file_buffer);
	file_buffer<<")";	
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	this->rhs->print(file_buffer);
	file_buffer<<")";	
}

//end
//---------------------------------------------------------------------
//minus
Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line){
	this->set_data_type(l->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
}

void Divide_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: DIV";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	this->lhs->print(file_buffer);
	file_buffer<<")";	
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	this->rhs->print(file_buffer);
	file_buffer<<")";	
}
//end
//----------------------------------------------------------------------
//divide
Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line){
	this->set_data_type(l->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
}

void Minus_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: MINUS";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	this->lhs->print(file_buffer);
	file_buffer<<")";	
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	this->rhs->print(file_buffer);
	file_buffer<<")";	
}
//end
//------------------------------------------------------------------------
//mult
Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line){
	this->set_data_type(l->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;	
}

void Mult_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: MULT";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	this->lhs->print(file_buffer);
	file_buffer<<")";	
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	this->rhs->print(file_buffer);
	file_buffer<<")";	
}
//end
//------------------------------------------------------------------
//uminus
UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line){
	this->set_data_type(l->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
}

void UMinus_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: UMINUS";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	this->lhs->print(file_buffer);
	file_buffer<<")";		
}
//end
//------------------------------------------------------------

//conditional
Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* cond, Ast* l, Ast* r, int line){
	this->set_data_type(l->get_data_type());
	this->ast_num_child = ternary_arity;
	this->cond = cond;
	this->lhs = l;
	this->rhs = r;
	this->lineno = line;
}

Conditional_Expression_Ast::~Conditional_Expression_Ast(){

}

void Conditional_Expression_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_SPACE<<"Cond:\n"<<AST_NODE_SPACE<<"IF_ELSE";
	this->cond->print(file_buffer);
	file_buffer<<"\n"<<AST_NODE_SPACE<<"LHS (";
	this->lhs->print(file_buffer);
	file_buffer<<")";
	file_buffer<<"\n"<<AST_NODE_SPACE<<"RHS (";
	this->rhs->print(file_buffer);
	file_buffer<<")";
}

//end

//Relational
Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line){
	this->set_data_type(lhs->get_data_type());
	this->ast_num_child = binary_arity;
	this->lhs_condition = lhs;
	this->rhs_condition = rhs;
	this->rel_op = rop;
	this->lineno = line;
}

Relational_Expr_Ast::~Relational_Expr_Ast(){

}

Data_Type Relational_Expr_Ast::get_data_type(){
	return this->node_data_type;
}


void Relational_Expr_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

bool Relational_Expr_Ast::check_ast(){
	if(this->lhs_condition->get_data_type()==this->rhs_condition->get_data_type()){
		return true;
	}
	else{
		printf("cs316: Error\n");
		return false;
	}
}

void Relational_Expr_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: ";
	Relational_Op dt = this->rel_op; 
	if(dt==less_equalto){
		file_buffer<<"LE";
	}
	else if(dt==less_than){
		file_buffer<<"LT";
	}
	else if(dt==greater_than){
		file_buffer<<"GT";
	}
	else if(dt==equalto){
		file_buffer<<"EQ";
	}
	else if(dt==greater_equalto){
		file_buffer<<"GE";
	}
	else{
		file_buffer<<"NE";
	}
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	this->lhs_condition->print(file_buffer);
	file_buffer<<")";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	this->rhs_condition->print(file_buffer);
	file_buffer<<")";
}

//end

//logical_expr
Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs,  Logical_Op bop, Ast * rhs, int line){
	this->set_data_type(lhs->get_data_type());
	this->ast_num_child = unary_arity;
	this->lhs_op = lhs;
	this->rhs_op = rhs;
	this->bool_op = bop;
	this->lineno = line;
}

Logical_Expr_Ast::~Logical_Expr_Ast(){

}

Data_Type Logical_Expr_Ast::get_data_type(){
	return this->node_data_type;
}


void Logical_Expr_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

bool Logical_Expr_Ast::check_ast(){
	if(this->rhs_op){
		if(this->lhs_op->get_data_type()==this->rhs_op->get_data_type()){
			return true;
		}
		else{
			printf("cs316: Error\n");
			return false;
		}
	}
	else if(this->lhs_op->check_ast()){
		return true;
	}
	else{
		return false;
	}
}

void Logical_Expr_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: ";
	Logical_Op dt = this->bool_op; 
	if(dt==_logical_not){
		file_buffer<<"NOT";
	}
	else if(dt==_logical_or){
		file_buffer<<"OR";
	}
	else{
		file_buffer<<"AND";
	}
	if(dt!=_logical_not){
		file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		this->lhs_op->print(file_buffer);
		file_buffer<<")";
	}
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	this->rhs_op->print(file_buffer);
	file_buffer<<")";
}
//end

//selection
Selection_Statement_Ast::Selection_Statement_Ast(Ast * cond,Ast* then_part, Ast* else_part, int line){
	this->set_data_type(void_data_type);
	this->cond = cond;
	this->then_part = then_part;
	this->else_part = else_part;
	this->ast_num_child = ternary_arity;
	this->lineno = line;
}

Selection_Statement_Ast::~Selection_Statement_Ast(){
}

Data_Type Selection_Statement_Ast::get_data_type(){
	return this->node_data_type;
}

void Selection_Statement_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

bool Selection_Statement_Ast::check_ast(){
	if(this->else_part){
		if(this->cond->check_ast()&&this->then_part->check_ast()&&this->else_part->check_ast()){
			return 1;
		}
	}
	else{
		if(this->cond->check_ast()&&this->then_part->check_ast()){
			return 1;
		}
	}
	return 0;
}

void Selection_Statement_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_SPACE<<"IF : \n"<<AST_SPACE<<"CONDITION (";
	this->cond->print(file_buffer);
	file_buffer<<")";
	file_buffer<<"\n"<<AST_SPACE<<"THEN (";
	this->then_part->print(file_buffer);
	file_buffer<<")";
	if(this->else_part){
		file_buffer<<"\n"<<AST_SPACE<<"ELSE (";
		this->else_part->print(file_buffer);
		file_buffer<<")";
	}
}
//end

//iterative
Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * cond, Ast* body, int line, bool do_form){
	this->ast_num_child = binary_arity;
	this->cond = cond;
	this->body = body;
	this->lineno = line;
	this->is_do_form = do_form;
	this->set_data_type(void_data_type);
}

Iteration_Statement_Ast::~Iteration_Statement_Ast(){
}

Data_Type Iteration_Statement_Ast::get_data_type(){
	return this->node_data_type;
}

void Iteration_Statement_Ast::set_data_type(Data_Type dt){
	this->node_data_type = dt;
}

bool Iteration_Statement_Ast::check_ast(){
	if(this->cond->check_ast()&&this->body->check_ast()){
		return 1;
	}
	else return 0;
}

void Iteration_Statement_Ast::print(ostream & file_buffer){
	if(this->check_ast()){
		if(!(this->is_do_form)){
			file_buffer<<"\n"<<AST_SPACE<<"WHILE : \n";
			file_buffer<<AST_SPACE<<"CONDITION (";
			this->cond->print(file_buffer);
			file_buffer<<")\n"<<AST_SPACE<<"BODY (";
			this->body->print(file_buffer);
			file_buffer<<")";
		}
		else{
			file_buffer<<"\n"<<AST_SPACE<<"DO (";
			this->body->print(file_buffer);
			file_buffer<<")\n"<<AST_SPACE<<"WHILE CONDITION (";
			this->cond->print(file_buffer);
			file_buffer<<")";
		}
	}
	else{
		printf("cs316: Error\n");
		exit(0);
	}
}

//sequence_ast
Sequence_Ast::Sequence_Ast(int line){
    this->lineno = line;
}

Sequence_Ast::~Sequence_Ast(){

}

void Sequence_Ast::ast_push_back(Ast * ast){
	this->statement_list.push_back(ast);
}


void Sequence_Ast::print(ostream & file_buffer){
	int i = 0;
	for(list<Ast *>::iterator it = this->statement_list.begin();it!=this->statement_list.end();it++){
		printf("%d\n",i);
		i++;
		file_buffer<<"\n"<<AST_NODE_SPACE;
		(*it)->print(file_buffer);
	}
	printf("completed\n");
}

//print_Ast

Print_Ast::Print_Ast(Ast *v, int line){
	this->var = v;
	this->lineno = line;
}

Print_Ast::~Print_Ast(){
}

void Print_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_SPACE<<"Print:";
	file_buffer<<"\n"<<AST_NODE_SPACE<<"(";
	(this->var)->print(file_buffer);
	file_buffer<<")";
}

//return

Return_Ast::Return_Ast(Ast * ret_val, string name, int line){
	this->return_value = ret_val;
	this->proc_name =  name;
	this->lineno = line;
	if(ret_val!=NULL){
		if(program_object.get_procedure_prototype(name)->get_return_type()!=ret_val->get_data_type()){
			printf("cs316:Error Wrong return type\n");
			exit(0);
		}
	}
	else{
		if(program_object.get_procedure_prototype(name)->get_return_type()!=void_data_type){
			printf("cs316:Error Wrong return type(you are expecting void)\n");
			exit(0);
		}
	}
}

Return_Ast::~Return_Ast(){

}

Data_Type Return_Ast::get_data_type(){
	return this->return_value->get_data_type();
}

void Return_Ast::print(ostream & file_buffer){
	//todo
	file_buffer<<"\n"<<AST_SPACE<<"Asgn:";
	(this->return_value)->print(file_buffer);
}

//call-ast

Call_Ast::Call_Ast(string name,int line){
	this->procedure_name = name;
	this->lineno = line;
}

Call_Ast::~Call_Ast(){
}

Data_Type Call_Ast::get_data_type(){
	return program_object.get_procedure_prototype(procedure_name)->get_return_type();
}

void Call_Ast::set_register(Register_Descriptor * reg){
	this->return_value_reg = reg;
}


void Call_Ast::check_actual_formal_param(Symbol_Table & formal_param_list){
	list<Ast *> temp = actual_param_list;
	list<Ast *>::iterator it;
	list<Symbol_Table_Entry *>::iterator it1 =  formal_param_list.get_table().begin();
	if(temp.size()==formal_param_list.get_table().size()){
		for(it = temp.begin();it!=temp.end();it++){
			if((*it)->get_data_type()!=(*it1)->get_data_type()){
				printf("cs316:Error data types mismatch\n");
				exit(0);
			}
			it1++;
		}
	}
	else{
		printf("cs316:Error wrong no. of arguments\n");
		exit(0);
	}
}

void Call_Ast::set_actual_param_list(list<Ast *> & param_list){
	this->actual_param_list = param_list;
}

void Call_Ast::print(ostream & file_buffer){
	//todo
	file_buffer<<"\n"<<AST_SPACE<<"FN CALL: "<<this->procedure_name<<"(";
	list<Ast *>::iterator it;
	for(it = this->actual_param_list.begin();it!= this->actual_param_list.end();it++){
		(*it)->print(file_buffer);
	}
	file_buffer<<")";
}


