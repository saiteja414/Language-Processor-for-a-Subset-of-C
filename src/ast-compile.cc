#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;
template class Number_Ast<double>;
template class Number_Ast<int>;

int rev = 0;

Code_For_Ast & Ast::compile(){

}

Code_For_Ast & Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register){

}

Code_For_Ast & Assignment_Ast::compile(){
	Code_For_Ast right = rhs->compile();
	list<Icode_Stmt *> final_list = right.get_icode_list();
	Ics_Opd * left = new Mem_Addr_Opd(lhs->get_symbol_entry());
	Register_Descriptor* reg1 = right.get_reg();
	Register_Addr_Opd* reg  = new Register_Addr_Opd(reg1);
	Code_For_Ast * assgn = new Code_For_Ast(final_list, NULL);
	
	if(lhs->get_data_type() == int_data_type){
		Icode_Stmt * astm = new Move_IC_Stmt(store, reg, left);
		assgn->append_ics(* astm);
	}

	else if(lhs->get_data_type() == double_data_type){
		Icode_Stmt * astm = new Move_IC_Stmt(store_d, reg, left);
		assgn->append_ics(* astm);
	}

	right.get_reg()->reset_use_for_expr_result();
	return *assgn;
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Name_Ast::compile(){
	Ics_Opd * name = new Mem_Addr_Opd(this->get_symbol_entry());
	list<Icode_Stmt *> *final_list = new list<Icode_Stmt *>();	
	if(get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Icode_Stmt * stm = new  Move_IC_Stmt(load, name, reg); 
		final_list->push_back(stm);
		Code_For_Ast * res = new Code_For_Ast(*final_list, reg_desc);
		return *res;
	}
	else if(get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Icode_Stmt * stm = new  Move_IC_Stmt(load_d, name, reg); 
		final_list->push_back(stm);
		Code_For_Ast * res = new Code_For_Ast(*final_list, reg_desc);
		return *res;
	}

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register){
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

template <class T>
Code_For_Ast & Number_Ast<T>::compile(){
	// Register_Descriptor * r = machine_desc_object.get_new_register<int_reg>();
	Ics_Opd * num = new Const_Opd<T>(this->constant);
	list<Icode_Stmt *> *final_list = new list<Icode_Stmt *>();	
	if(get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Icode_Stmt * stm = new  Move_IC_Stmt(imm_load, num, reg); 
		final_list->push_back(stm);
		Code_For_Ast * res = new Code_For_Ast(*final_list, reg_desc);
		return *res;
	}
	else if(get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Icode_Stmt * stm = new  Move_IC_Stmt(imm_load_d, num, reg); 
		final_list->push_back(stm);
		Code_For_Ast * res = new Code_For_Ast(*final_list, reg_desc);
		return *res;
	}

}

template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra){
}

Code_For_Ast & Plus_Ast::compile(){
	Code_For_Ast left = lhs->compile();
	Code_For_Ast right = rhs->compile();
	
	Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
	Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
	
	list<Icode_Stmt *> final_list = left.get_icode_list();
	final_list.merge(right.get_icode_list());

	if(lhs->get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * plus = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(add, lreg, rreg, reg);
		plus->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *plus;
	}

	else if(lhs->get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * plus = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(add_d, lreg, rreg, reg);
		plus->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *plus;
	}

}

Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Minus_Ast::compile(){
	Code_For_Ast left = lhs->compile();
	Code_For_Ast right = rhs->compile();
	
	Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
	Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
	
	list<Icode_Stmt *> final_list = left.get_icode_list();
	final_list.merge(right.get_icode_list());

	if(lhs->get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * minus = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(sub, lreg, rreg, reg);
		minus->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *minus;
	}

	else if(lhs->get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * minus = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(sub_d, lreg, rreg, reg);
		minus->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *minus;
	}
}

Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Divide_Ast::compile(){
	Code_For_Ast left = lhs->compile();
	Code_For_Ast right = rhs->compile();
	
	Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
	Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
	
	list<Icode_Stmt *> final_list = left.get_icode_list();
	final_list.merge(right.get_icode_list());

	if(lhs->get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(divd, lreg, rreg, reg);
		res->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *res;
	}

	else if(lhs->get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(div_d, lreg, rreg, reg);
		res->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *res;
	}
}

Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
	
}

Code_For_Ast & Mult_Ast::compile(){
	Code_For_Ast left = lhs->compile();
	Code_For_Ast right = rhs->compile();
	
	Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
	Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
	
	list<Icode_Stmt *> final_list = left.get_icode_list();
	final_list.merge(right.get_icode_list());

	if(lhs->get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(mult, lreg, rreg, reg);
		res->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *res;
	}

	else if(lhs->get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(mult_d, lreg, rreg, reg);
		res->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *res;
	}
}

Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
	
}

Code_For_Ast & UMinus_Ast::compile(){
	Code_For_Ast left = lhs->compile();
	
	Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
	
	list<Icode_Stmt *> final_list = left.get_icode_list();

	if(lhs->get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(uminus, lreg, lreg, reg);
		res->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		return *res;
	}

	else if(lhs->get_data_type() == double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		Icode_Stmt * astm = new Compute_IC_Stmt(uminus_d, lreg, lreg, reg);
		res->append_ics(* astm);
		left.get_reg()->reset_use_for_expr_result();
		return *res;
	}
	
}

Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
}

Code_For_Ast & Conditional_Expression_Ast::compile(){
	Code_For_Ast con = cond->compile();
	list<Icode_Stmt *> final_list = con.get_icode_list();
	string label1 = "label"+to_string(++labelCounter);
	string label2 = "label"+to_string(++labelCounter);
	Code_For_Ast left = lhs->compile();
	if(lhs->get_data_type() == int_data_type){
		Ics_Opd * conreg  = new Register_Addr_Opd(con.get_reg());
		Icode_Stmt  * constm = new Control_Flow_IC_Stmt(beq, conreg, NULL, label1,0);
		Icode_Stmt * gostm = new Label_IC_Stmt(j, label2);
		list<Icode_Stmt *> list1 = left.get_icode_list();
		Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
		Ics_Opd * zer = new Register_Addr_Opd(machine_desc_object.spim_register_table[zero]);
		Icode_Stmt * elstm = new Label_IC_Stmt(label, label1);
		Code_For_Ast right = rhs->compile();
		list<Icode_Stmt *> list2 = right.get_icode_list();
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		list1.push_front(constm);
		Icode_Stmt * lstm = new Compute_IC_Stmt(or_t, lreg, zer, reg);
		list1.push_back(&(*lstm));
		list1.push_back(&(*gostm));
		list1.push_back(&(*elstm));
		Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
		Icode_Stmt * rstm = new Compute_IC_Stmt(or_t, rreg, zer, reg);
		list2.push_back(rstm);
		Icode_Stmt * assg = new Label_IC_Stmt(label, label2);
		list2.push_back(assg);
		for(list<Icode_Stmt *>::iterator it=list1.begin();it!=list1.end();it++){
			final_list.push_back(*it);
		}
		for(list<Icode_Stmt *>::iterator it=list2.begin();it!=list2.end();it++){
			final_list.push_back(*it);
		}
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		right.get_reg()->reset_use_for_expr_result();
		left.get_reg()->reset_use_for_expr_result();
		con.get_reg()->reset_use_for_expr_result();
		return *res;
	}
	else{
		Ics_Opd * conreg  = new Register_Addr_Opd(con.get_reg());
		Icode_Stmt  * constm = new Control_Flow_IC_Stmt(beq, conreg, NULL, label1,0);
		Icode_Stmt * gostm = new Label_IC_Stmt(j, label2);
		list<Icode_Stmt *> list1 = left.get_icode_list();
		Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
		Ics_Opd * zer = new Register_Addr_Opd(machine_desc_object.spim_register_table[zero]);
		Icode_Stmt * elstm = new Label_IC_Stmt(label, label1);
		Code_For_Ast right = rhs->compile();
		list<Icode_Stmt *> list2 = right.get_icode_list();
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		list1.push_front(constm);
		Icode_Stmt * lstm = new Compute_IC_Stmt(or_t, lreg, zer, reg);
		list1.push_back(&(*lstm));
		list1.push_back(&(*gostm));
		list1.push_back(&(*elstm));
		Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
		Icode_Stmt * rstm = new Compute_IC_Stmt(or_t, rreg, zer, reg);
		list2.push_back(rstm);
		Icode_Stmt * assg = new Label_IC_Stmt(label, label2);
		list2.push_back(assg);
		for(list<Icode_Stmt *>::iterator it=list1.begin();it!=list1.end();it++){
			final_list.push_back(*it);
		}
		for(list<Icode_Stmt *>::iterator it=list2.begin();it!=list2.end();it++){
			final_list.push_back(*it);
		}
		Code_For_Ast * res = new Code_For_Ast(final_list, reg_desc);
		right.get_reg()->reset_use_for_expr_result();
		left.get_reg()->reset_use_for_expr_result();
		con.get_reg()->reset_use_for_expr_result();
		return *res;
	}
}


Code_For_Ast & Relational_Expr_Ast::compile(){
	Code_For_Ast left = lhs_condition->compile();
	Code_For_Ast right = rhs_condition->compile();

	Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
	Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());
	if(lhs_condition->get_data_type() == int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);

		list<Icode_Stmt *> final_list = left.get_icode_list();
		final_list.merge(right.get_icode_list());

		Relational_Op dt = this->rel_op; 
		if(dt==less_equalto){
			Icode_Stmt * cstm = new Compute_IC_Stmt(sle, lreg, rreg, reg);
			final_list.push_back(cstm);
		}
		else if(dt==less_than){
			Icode_Stmt * cstm = new Compute_IC_Stmt(slt, lreg, rreg, reg);
			final_list.push_back(cstm);
		}
		else if(dt==greater_than){
			Icode_Stmt * cstm = new Compute_IC_Stmt(sgt, lreg, rreg, reg);
			final_list.push_back(cstm);
		}
		else if(dt==equalto){
			Icode_Stmt * cstm = new Compute_IC_Stmt(seq, lreg, rreg, reg);
			final_list.push_back(cstm);
		}
		else if(dt==greater_equalto){
			Icode_Stmt * cstm = new Compute_IC_Stmt(sge, lreg, rreg, reg);
			final_list.push_back(cstm);
		}
		else{
			Icode_Stmt * cstm = new Compute_IC_Stmt(sne, lreg, rreg, reg);
			final_list.push_back(cstm);
		}
		
		Code_For_Ast * Rel = new Code_For_Ast(final_list, reg_desc);

		left.get_reg()->reset_use_for_expr_result();
		right.get_reg()->reset_use_for_expr_result();
		return *Rel;
	}

	else {
		Register_Descriptor * reg_desc = left.get_reg();
		// Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);

		list<Icode_Stmt *> final_list = left.get_icode_list();
		final_list.merge(right.get_icode_list());

		Relational_Op dt = this->rel_op; 
		if(dt==less_equalto){
			rev = 0;
			Icode_Stmt * cstm = new Compute_IC_Stmt(sle_d, lreg, rreg, lreg);
			final_list.push_back(cstm);
		}
		else if(dt==less_than){
			rev = 0;
			Icode_Stmt * cstm = new Compute_IC_Stmt(slt_d, lreg, rreg, lreg);
			final_list.push_back(cstm);
		}
		else if(dt==greater_than){
			rev = 1;
			Icode_Stmt * cstm = new Compute_IC_Stmt(sgt_d, lreg, rreg, lreg);
			final_list.push_back(cstm);
		}
		else if(dt==equalto){
			rev = 0;
			Icode_Stmt * cstm = new Compute_IC_Stmt(seq_d, lreg, rreg, lreg);
			final_list.push_back(cstm);
		}
		else if(dt==greater_equalto){
			rev = 1;
			Icode_Stmt * cstm = new Compute_IC_Stmt(sge_d, lreg, rreg, lreg);
			final_list.push_back(cstm);
		}
		else{
			rev = 1;
			Icode_Stmt * cstm = new Compute_IC_Stmt(sne_d, lreg, rreg, lreg);
			final_list.push_back(cstm);
		}
		
		Code_For_Ast * Rel = new Code_For_Ast(final_list, reg_desc);

		right.get_reg()->reset_use_for_expr_result();
		return *Rel;
	}	
}

Code_For_Ast & Logical_Expr_Ast::compile(){
	

	Logical_Op dt = this->bool_op; 
	if(dt==_logical_not){

		Register_Descriptor * r = machine_desc_object.get_new_register<int_reg>();

		Code_For_Ast left = lhs_op->compile();

		Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());

		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);

		list<Icode_Stmt *> final_list = left.get_icode_list();


		Ics_Opd * opd1 = new Const_Opd<int>(1);
		Ics_Opd * result = new Register_Addr_Opd(r);
		Move_IC_Stmt * one = new Move_IC_Stmt(imm_load , opd1, result);
		final_list.push_front(one);

		Icode_Stmt * cstm = new Compute_IC_Stmt(not_t, lreg, result, reg);
		final_list.push_back(cstm);
		r->reset_register_occupied();
		Code_For_Ast * Rel = new Code_For_Ast(final_list, reg_desc);

		left.get_reg()->reset_register_occupied();

		return *Rel;
	}

	else{
		Code_For_Ast left = lhs_op->compile();
		Code_For_Ast right = rhs_op->compile();

		Ics_Opd * lreg  = new Register_Addr_Opd(left.get_reg());
		Ics_Opd * rreg  = new Register_Addr_Opd(right.get_reg());

		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);

		list<Icode_Stmt *> final_list = left.get_icode_list();
		list<Icode_Stmt *> list1 = right.get_icode_list();

		if(dt==_logical_or){
			Icode_Stmt * cstm = new Compute_IC_Stmt(or_t, lreg, rreg, reg);
			list1.push_back(cstm);
			final_list.merge(list1);
		}
		else{
			Icode_Stmt * cstm = new Compute_IC_Stmt(and_t, lreg, rreg, reg);
			list1.push_back(cstm);
			final_list.merge(list1);
		}
		
		Code_For_Ast * Rel = new Code_For_Ast(final_list, reg_desc);

		left.get_reg()->reset_register_occupied();
		right.get_reg()->reset_register_occupied();

		return *Rel;
	}
}

Code_For_Ast & Selection_Statement_Ast::compile(){
	if(else_part != NULL){
		Code_For_Ast con = cond->compile();
		int rev1 = rev;
		string label1 = "label"+to_string(++labelCounter);
		string label2 = "label"+to_string(++labelCounter);

		list<Icode_Stmt *> final_list = con.get_icode_list();
		Ics_Opd * conreg  = new Register_Addr_Opd(con.get_reg());


		if(cond->get_data_type() == double_data_type && rev1 == 1){
			Icode_Stmt * constm = new Control_Flow_IC_Stmt(bc1t, conreg, NULL, label1,0); 
			final_list.push_back(constm);
			con.get_reg()->reset_use_for_expr_result();
		}

		else if(cond->get_data_type() == double_data_type && rev1 == 0){
			Icode_Stmt * constm = new Control_Flow_IC_Stmt(bc1f, conreg, NULL, label1 , 0); 
			final_list.push_back(constm);
			con.get_reg()->reset_use_for_expr_result();
		}

		else{
			Icode_Stmt * constm = new Control_Flow_IC_Stmt(beq, conreg, NULL, label1, 0 ); 
			final_list.push_back(constm);
		}

		// con.get_reg()->reset_use_for_expr_result();
		Code_For_Ast ifp = then_part->compile();
		list<Icode_Stmt *> ifl = ifp.get_icode_list(); 
		final_list.merge(ifl);
		Icode_Stmt * gostm = new Label_IC_Stmt(j, label2);
		final_list.push_back(gostm);
		Icode_Stmt * elstm = new Label_IC_Stmt(label, label1);
		final_list.push_back(elstm);
		Code_For_Ast elp = else_part->compile();
		list<Icode_Stmt *> ell = elp.get_icode_list(); 
		final_list.merge(ell);
		Icode_Stmt * lstm = new Label_IC_Stmt(label, label2);
		final_list.push_back(lstm);

		if(cond->get_data_type() == int_data_type){
			con.get_reg()->reset_use_for_expr_result();}
		Code_For_Ast * ifelse = new Code_For_Ast(final_list, NULL);

		return *ifelse;
	}

	else{
		Code_For_Ast con = cond->compile();
		string label1 = "label"+to_string(++labelCounter);

		list<Icode_Stmt *> final_list = con.get_icode_list();
		Ics_Opd * conreg  = new Register_Addr_Opd(con.get_reg());

		if(cond->get_data_type() == double_data_type && rev == 1){
			Icode_Stmt * constm = new Control_Flow_IC_Stmt(bc1t, conreg, NULL, label1, 0); 
			final_list.push_back(constm);
			con.get_reg()->reset_use_for_expr_result();
		}

		else if(cond->get_data_type() == double_data_type && rev == 0){
			Icode_Stmt * constm = new Control_Flow_IC_Stmt(bc1f, conreg, NULL, label1,0); 
			final_list.push_back(constm);
			con.get_reg()->reset_use_for_expr_result();
		}

		else{
			Icode_Stmt * constm = new Control_Flow_IC_Stmt(beq, conreg, NULL, label1, 0); 
			final_list.push_back(constm);
		}
		// con.get_reg()->reset_use_for_expr_result();
		Code_For_Ast ifp = then_part->compile();
		final_list.merge(ifp.get_icode_list());
		Icode_Stmt * lstm = new Label_IC_Stmt(label, label1);
		final_list.push_back(lstm);

		Code_For_Ast * ifelse = new Code_For_Ast(final_list, NULL);

		if(cond->get_data_type() == int_data_type){
			con.get_reg()->reset_use_for_expr_result();}
		return *ifelse;
	}
}

Code_For_Ast & Iteration_Statement_Ast::compile(){
	Code_For_Ast con = cond->compile();
	list<Icode_Stmt *> list1 = con.get_icode_list();
	int rev1 = rev;
	if(cond->get_data_type() == double_data_type){
	con.get_reg()->reset_use_for_expr_result();}
	Code_For_Ast bod = body->compile();
	list<Icode_Stmt *> final_list = bod.get_icode_list();

	string label1 = "label"+to_string(++labelCounter); 
	string label2 = "label"+to_string(++labelCounter);

	Icode_Stmt * gostm = new Label_IC_Stmt(j, label2);
	Icode_Stmt * bstm = new Label_IC_Stmt(label,label1);

	final_list.push_front(bstm);
	if(! is_do_form) final_list.push_front(gostm);

	Icode_Stmt * cstm = new Label_IC_Stmt(label, label2);
	list1.push_front(cstm);
	Ics_Opd * conreg  = new Register_Addr_Opd(con.get_reg());

	if(cond->get_data_type() == double_data_type && rev1 == 1){
		Icode_Stmt * constm = new Control_Flow_IC_Stmt(bc1f, conreg, NULL, label1,0); 
		list1.push_back(constm);
	}

	else if(cond->get_data_type() == double_data_type && rev1 == 0){
		Icode_Stmt * constm = new Control_Flow_IC_Stmt(bc1t, conreg, NULL, label1, 0); 
		list1.push_back(constm);
	}

	else{
		Icode_Stmt * constm = new Control_Flow_IC_Stmt(bne, conreg, NULL, label1, 0); 
		list1.push_back(constm);
	}

	// Icode_Stmt * constm = new Control_Flow_IC_Stmt(bne, conreg, label1); 

	// list1.push_back(constm);
	final_list.merge(list1);

	if(cond->get_data_type() == int_data_type){
			con.get_reg()->reset_use_for_expr_result();}
	Code_For_Ast * whiledo = new Code_For_Ast(final_list, NULL);
	return *whiledo;
}

Code_For_Ast & Sequence_Ast::compile(){
	list<Icode_Stmt *> *final_list = new list<Icode_Stmt *>();
	for(list<Ast *>::iterator it = this->statement_list.begin();it!=this->statement_list.end();it++){
		Code_For_Ast tmp = (*it)->compile();
		final_list->merge(tmp.get_icode_list());
	}
	
	Code_For_Ast * seq = new Code_For_Ast(*final_list, NULL);
	return *seq;
}


Code_For_Ast & Print_Ast::compile(){
	Ics_Opd * v = new Register_Addr_Opd(machine_desc_object.spim_register_table[v0]);
	Ics_Opd * va = new Mem_Addr_Opd(var->get_symbol_entry());
	list<Icode_Stmt *> *final_list = new list<Icode_Stmt *>();
	if(var->get_data_type() == int_data_type){
		Ics_Opd * opd1 = new Const_Opd<int>(1);
		Icode_Stmt * stm1 = new  Move_IC_Stmt(imm_load, opd1, v); 
		final_list->push_back(stm1);
		Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[a0]);
		Icode_Stmt * stm = new  Move_IC_Stmt(load, va, a);
		string label1 = "print";
		Icode_Stmt * pri = new Label_IC_Stmt(label,label1);
		final_list->push_back(stm);
		final_list->push_back(pri);
		machine_desc_object.spim_register_table[a0]->reset_use_for_expr_result();
		machine_desc_object.spim_register_table[v0]->reset_use_for_expr_result();
		Code_For_Ast * seq = new Code_For_Ast(*final_list, NULL);
		return *seq;
	}
	else{
		Ics_Opd * opd1 = new Const_Opd<int>(3);
		Icode_Stmt * stm1 = new  Move_IC_Stmt(imm_load, opd1, v); 
		final_list->push_back(stm1);
		Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[f12]);
		Icode_Stmt * stm = new  Move_IC_Stmt(load_d, va, a);
		string label1 = "print"; 
		Icode_Stmt * pri = new Label_IC_Stmt(label,label1);
		final_list->push_back(stm);
		final_list->push_back(pri);
		machine_desc_object.spim_register_table[f12]->reset_use_for_expr_result();
		machine_desc_object.spim_register_table[v0]->reset_use_for_expr_result();
		Code_For_Ast * seq = new Code_For_Ast(*final_list, NULL);
		return *seq;
	}
}

//Return Ast
Code_For_Ast & Return_Ast::compile(){
	Code_For_Ast * call = new Code_For_Ast();
	if(return_value!=NULL){
		Code_For_Ast right = return_value->compile();
		if(return_value->get_data_type()==int_data_type){
			Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[v1]);
			list<Icode_Stmt *> list1 = right.get_icode_list();
			for(list<Icode_Stmt *>::iterator it=list1.begin();it!=list1.end();it++){
				call->append_ics(*(*it));
			}
			Register_Descriptor* reg1 = right.get_reg();
			Register_Addr_Opd* reg  = new Register_Addr_Opd(reg1);
			Icode_Stmt * astm = new Move_IC_Stmt(mov, reg ,a);
			call->append_ics(*astm);
			right.get_reg()->reset_use_for_expr_result();
		}
		else{

			Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[f0]);
			list<Icode_Stmt *> list1 = right.get_icode_list();
			for(list<Icode_Stmt *>::iterator it=list1.begin();it!=list1.end();it++){
				call->append_ics(*(*it));
			}
			Register_Descriptor* reg1 = right.get_reg();
			Register_Addr_Opd* reg  = new Register_Addr_Opd(reg1);
			Icode_Stmt * astm = new Move_IC_Stmt(move_d, reg, a);
			call->append_ics(*astm);
			right.get_reg()->reset_use_for_expr_result();
		}
	}
	string label2 = "epilogue_"+proc_name;
	Icode_Stmt * gostm = new Label_IC_Stmt(j, label2);
	call->append_ics(*gostm);
	return *call;
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
	
}

//call ast
Code_For_Ast & Call_Ast::compile(){
	list<Ast *>temp = this->actual_param_list;
	temp.reverse();
	Code_For_Ast * call = new Code_For_Ast();
	int counter = 0;
	list<Ast *>::iterator it;
	string name = "temp";
	for(it=temp.begin();it!=temp.end();it++){
		Code_For_Ast right = (*it)->compile();
		list<Icode_Stmt *> list1 = right.get_icode_list();
		for(list<Icode_Stmt *>::iterator it=list1.begin();it!=list1.end();it++){
			call->append_ics(*(*it));
		}
		Register_Descriptor* reg1 = right.get_reg();
		Register_Addr_Opd* reg  = new Register_Addr_Opd(reg1);
		if((*it)->get_data_type()==int_data_type){
			Symbol_Table_Entry *s = new Symbol_Table_Entry(name, int_data_type, 0 , sp_ref);
			s->set_start_offset(counter);
			s->set_symbol_scope(local);
			Ics_Opd * left = new Mem_Addr_Opd(*s);
			Icode_Stmt * astm = new Move_IC_Stmt(store, reg , left);
			right.get_reg()->reset_use_for_expr_result();
			call->append_ics(*astm);
			counter-=4;

		}
		else{
			Symbol_Table_Entry *s = new Symbol_Table_Entry(name, double_data_type, 0 , sp_ref);
			s->set_start_offset(counter);
			s->set_symbol_scope(local);
			Ics_Opd * left = new Mem_Addr_Opd(*s);
			Icode_Stmt * astm = new Move_IC_Stmt(store_d, reg , left);
			right.get_reg()->reset_use_for_expr_result();
			call->append_ics(*astm);
			counter-=8;
		}

	}
	Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[sp]);
	counter = -1*counter;
	string label1 = this->procedure_name;
	Icode_Stmt  * constm = new Control_Flow_IC_Stmt(jal, NULL, NULL, label1, counter);
	call->append_ics(*constm);
	if(program_object.get_procedure_prototype(label1)->get_return_type()==int_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<int_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[v1]);
		Icode_Stmt * astm = new Move_IC_Stmt(mov, a, reg);
		if(return_value_reg!=NULL){
			reg_desc->reset_use_for_expr_result();
		}
		else{
			call->set_reg(reg_desc);
		}
		call->append_ics(*astm);
	}
	else if(program_object.get_procedure_prototype(label1)->get_return_type()==double_data_type){
		Register_Descriptor * reg_desc = machine_desc_object.get_new_register<float_reg>();
		Ics_Opd * reg  = new Register_Addr_Opd(reg_desc);
		Ics_Opd * a = new Register_Addr_Opd(machine_desc_object.spim_register_table[f0]);
		Icode_Stmt * astm = new Move_IC_Stmt(move_d,a,reg);
		call->append_ics(*astm);
		call->set_reg(reg_desc);
	}
	return *call;
}

Code_For_Ast & Call_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
		
}