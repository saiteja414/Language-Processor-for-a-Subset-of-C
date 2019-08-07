#include<string>
#include<fstream>
#include<iostream>
template class Number_Ast<double>;
template class Number_Ast<int>;

using namespace std;

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env){

}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){

}

Eval_Result & Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result &Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(check_ast()){
        this->print(file_buffer);
        if(this->lhs->get_data_type()==int_data_type){
            Eval_Result *right = new Eval_Result_Value_Int();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            string name = this->lhs->get_symbol_entry().get_variable_name();
            if(this->lhs->get_symbol_entry().get_symbol_scope()!=global)eval_env.put_variable_value(*right,name);
	        else interpreter_global_table.put_variable_value(*right,name);
            file_buffer<<"\n"<<AST_SPACE<<name<<" : "<<right->get_int_value()<<"\n\n";
            return *right;
        }
        else{
            Eval_Result *right = new Eval_Result_Value_Double();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            string name = this->lhs->get_symbol_entry().get_variable_name();
            if(this->lhs->get_symbol_entry().get_symbol_scope()!=global)eval_env.put_variable_value(*right,name);
	        else interpreter_global_table.put_variable_value(*right,name);
            file_buffer<<"\n"<<AST_SPACE<<name<<" : "<<right->get_double_value()<<"\n\n";
            return *right;
        }
    }
    else 
    {
        printf("cs316: Error\n");
        exit(0);
    }
}

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){
    string name = this->get_symbol_entry().get_variable_name();
    if(this->get_data_type()==int_data_type){
        Eval_Result *right = new Eval_Result_Value_Int();
        if(this->get_symbol_entry().get_symbol_scope()!=global){
            *right = *eval_env.get_variable_value(name);
        }
        else{
            *right = *interpreter_global_table.get_variable_value(name);
        }
        file_buffer<<AST_SUB_NODE_SPACE<<name<<" : "<<right->get_int_value()<<"\n";
    }
    else{
        Eval_Result *right = new Eval_Result_Value_Double();
        if(this->get_symbol_entry().get_symbol_scope()!=global){
            *right = *eval_env.get_variable_value(name);
        }
        else{
            *right = *interpreter_global_table.get_variable_value(name);
        }
        file_buffer<<AST_SUB_NODE_SPACE<<name<<" : "<<right->get_double_value()<<"\n";
    }
} 

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env){
    if(this->get_symbol_entry().get_symbol_scope()!=global){
        return *(eval_env.get_variable_value(this->get_symbol_entry().get_variable_name()));
    }
    else{
        return *(interpreter_global_table.get_variable_value(this->get_symbol_entry().get_variable_name()));
    }
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){
    if(this->get_symbol_entry().get_symbol_scope()!=global){
        eval_env.put_variable_value(result, this->get_symbol_entry().get_variable_name());
    }
    else{
        interpreter_global_table.put_variable_value(result, this->get_symbol_entry().get_variable_name());
    }
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->get_symbol_entry().get_symbol_scope()!=global){
    	if(eval_env.get_variable_value(this->get_symbol_entry().get_variable_name())->is_variable_defined()){
    		return *(eval_env.get_variable_value(this->get_symbol_entry().get_variable_name()));
    	}
    	else{
    		printf("cs316: Error variable not declared\n");
    		exit(0);
    	}	
    }
    else{
        return *(interpreter_global_table.get_variable_value(this->get_symbol_entry().get_variable_name()));
    }
}

template <class T>
Eval_Result & Number_Ast<T>::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->get_data_type() == int_data_type){
        Eval_Result *val = new Eval_Result_Value_Int();
        val->set_value(this->constant);
        return *val;
    }
    else{
        Eval_Result *val = new Eval_Result_Value_Double();
        val->set_value(this->constant);
        return *val;
    }
}

Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->get_data_type() == int_data_type){
            Eval_Result * left = new Eval_Result_Value_Int();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Int();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Int();
            val->set_value(right->get_int_value() + left->get_int_value());
            return *val;
        }
        else{
            Eval_Result * left = new Eval_Result_Value_Double();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Double();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Double();
            val->set_value(right->get_double_value() + left->get_double_value());
            return *val;
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->get_data_type() == int_data_type){
            Eval_Result * left = new Eval_Result_Value_Int();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Int();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Int();
            val->set_value(left->get_int_value() - right->get_int_value());
            return *val;
        }
        else{
            Eval_Result * left = new Eval_Result_Value_Double();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Double();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Double();
            val->set_value(left->get_double_value() - right->get_double_value());
            return *val;
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->get_data_type() == int_data_type){
            Eval_Result * left = new Eval_Result_Value_Int();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Int();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Int();
            if(right->get_int_value() != 0)val->set_value(left->get_int_value() / right->get_int_value());
            else printf("cs316: Error dividing by 0\n");
            return *val;
        }
        else{
            Eval_Result * left = new Eval_Result_Value_Double();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Double();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Double();
            if(right->get_double_value() != 0)val->set_value(left->get_double_value() / right->get_double_value());        ///comparing with double
            else printf("cs316: Error dividing by 0\n");
            return *val;
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->get_data_type() == int_data_type){
            Eval_Result * left = new Eval_Result_Value_Int();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Int();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Int();
            val->set_value(left->get_int_value() * right->get_int_value());
            return *val;
        }
        else{
            Eval_Result * left = new Eval_Result_Value_Double();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            Eval_Result * right = new Eval_Result_Value_Double();
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            Eval_Result *val = new Eval_Result_Value_Double();
            val->set_value(left->get_double_value() * right->get_double_value());
            return *val;
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->lhs->get_data_type()==int_data_type){
        Eval_Result *val = new Eval_Result_Value_Int();
        Eval_Result * right;
        right = &(this->lhs->evaluate(eval_env,file_buffer));
        val->set_value(-1*right->get_int_value());
        return *val;
    }
    else{
        Eval_Result *val = new Eval_Result_Value_Double();
        Eval_Result * right;
        right = &(this->lhs->evaluate(eval_env,file_buffer));
        val->set_value(-1*right->get_double_value());
        return *val;
    }
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->lhs_condition->get_data_type()==int_data_type){
            Eval_Result *left = new Eval_Result_Value_Int(); 
            Eval_Result *right = new Eval_Result_Value_Int();
            left = &(this->lhs_condition->evaluate(eval_env,file_buffer));
            right = &(this->rhs_condition->evaluate(eval_env,file_buffer));
            Eval_Result *var = new Eval_Result_Value_Int();
            var->set_value(0);
            Relational_Op dt = this->rel_op; 
            if(dt==less_equalto){    
                if(left->get_int_value()<=right->get_int_value()){
                    var->set_value(1);
                }
            }
            else if(dt==less_than){
                if(left->get_int_value()<right->get_int_value()){
                    var->set_value(1);
                }
            }
            else if(dt==greater_than){
                if(left->get_int_value()>right->get_int_value()){
                    var->set_value(1);
                }
            }
            else if(dt==greater_equalto){
                if(left->get_int_value()>=right->get_int_value()){
                    var->set_value(1);
                }
            }
            else if(dt==equalto){
                if(left->get_int_value()==right->get_int_value()){
                    var->set_value(1);
                }
            }
            else{
                if(left->get_int_value()!=right->get_int_value()){
                    var->set_value(1);
                }
            }
            return *var;
        }
        else{
            Eval_Result *left = new Eval_Result_Value_Double(); 
            Eval_Result *right = new Eval_Result_Value_Double();
            left = &(this->lhs_condition->evaluate(eval_env,file_buffer));
            right = &(this->rhs_condition->evaluate(eval_env,file_buffer));
            Eval_Result *var = new Eval_Result_Value_Int();
            var->set_value(0);
            Relational_Op dt = this->rel_op; 
            if(dt==less_equalto){    
                if(left->get_double_value()<=right->get_double_value()){
                    var->set_value(1);
                }
            }
            else if(dt==less_than){
                if(left->get_double_value()<right->get_double_value()){
                    var->set_value(1);
                }
            }
            else if(dt==greater_than){
                if(left->get_double_value()>right->get_double_value()){
                    var->set_value(1);
                }
            }
            else if(dt==greater_equalto){
                if(left->get_double_value()>=right->get_double_value()){
                    var->set_value(1);
                }
            }
            else if(dt==equalto){
                if(left->get_double_value()==right->get_double_value()){
                    var->set_value(1);
                }
            }
            else{
                if(left->get_double_value()!=right->get_double_value()){
                    var->set_value(1);
                }
            }
            return *var;
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

// _logical_not,
// _logical_or,
// _logical_and

Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        Eval_Result *left = new Eval_Result_Value_Int(); 
        Eval_Result *right = new Eval_Result_Value_Int();
        left = &(this->lhs_op->evaluate(eval_env,file_buffer));
        Eval_Result *var = new Eval_Result_Value_Int();
        var->set_value(0);
        Logical_Op dt = this->bool_op;
        if(dt==_logical_not){    
            if(!(left->get_int_value())){
                var->set_value(1);
            }
        }
        else{
            right = &(this->rhs_op->evaluate(eval_env,file_buffer));
            if(dt==_logical_or){
                if(left->get_int_value()||right->get_int_value()){
                    var->set_value(1);
                }
            }
            else{
                if(left->get_int_value()&&right->get_int_value()){
                    var->set_value(1);
                }
            }
        }
        return *var;
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}


Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->get_data_type()==int_data_type){
            Eval_Result *left = new Eval_Result_Value_Int(); 
            Eval_Result *right = new Eval_Result_Value_Int();
            Eval_Result *con = new Eval_Result_Value_Int();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            con = &(this->cond->evaluate(eval_env,file_buffer));
            Eval_Result *var = new Eval_Result_Value_Int();
            if(con->get_int_value()==1){
                var->set_value(left->get_int_value());
            }
            else var->set_value(right->get_int_value());
            return *var;
        }
        else{
            Eval_Result *left = new Eval_Result_Value_Double(); 
            Eval_Result *right = new Eval_Result_Value_Double();
            Eval_Result *con = new Eval_Result_Value_Int();
            left = &(this->lhs->evaluate(eval_env,file_buffer));
            right = &(this->rhs->evaluate(eval_env,file_buffer));
            con = &(this->cond->evaluate(eval_env,file_buffer));
            Eval_Result *var = new Eval_Result_Value_Double();
            if(con->get_int_value()==1){
                var->set_value(left->get_double_value());
            }
            else var->set_value(right->get_double_value());
            return *var;
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    
    if(this->check_ast()){
        Eval_Result *left = new Eval_Result_Value_Int(); 
        Eval_Result *right = new Eval_Result_Value_Int();
        left = &(this->cond->evaluate(eval_env,file_buffer)); 
        if(left->get_int_value()==1){
            right = &(this->then_part->evaluate(eval_env,file_buffer));
        }
        else if(this->else_part){
            right = &(this->else_part->evaluate(eval_env,file_buffer));
        }
        else{

        }
        return *right;
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}


Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(this->check_ast()){
        if(this->is_do_form){
            Eval_Result *left = new Eval_Result_Value_Int();    
            do{
                this->body->evaluate(eval_env,file_buffer);
                left = &(this->cond->evaluate(eval_env,file_buffer));
            }while(left->get_int_value()==1);
        }
        else{
            Eval_Result *left = new Eval_Result_Value_Int();
            left = &(this->cond->evaluate(eval_env,file_buffer));    
            while(left->get_int_value()==1){
                this->body->evaluate(eval_env,file_buffer);
                left = &(this->cond->evaluate(eval_env,file_buffer));
            }
        }
    }
    else{
        printf("cs316: Error\n");
        exit(0);
    }
}

Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    for(list<Ast*>::iterator it = this->statement_list.begin();it!=this->statement_list.end();it++){
        (*it)->evaluate(eval_env,file_buffer);
    }
}


// Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

// }

Eval_Result & Call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}



void Symbol_Table::create(Local_Environment & local_global_variables_table){
    list<Symbol_Table_Entry *> table = this->variable_table;
    list<Symbol_Table_Entry *>::iterator it;
    for(it = table.begin();it!=table.end();it++){
        string name = (*it)->get_variable_name();
        if((*it)->get_data_type()==int_data_type){
            Eval_Result *var = new Eval_Result_Value_Int();
            if((*it)->get_symbol_scope()==global)var->set_value(0);
            local_global_variables_table.put_variable_value(*var,name);
        }
        else{
            Eval_Result *var = new Eval_Result_Value_Double();
            if((*it)->get_symbol_scope()==global)var->set_value(0);
            local_global_variables_table.put_variable_value(*var,name);
        }
    }
}

