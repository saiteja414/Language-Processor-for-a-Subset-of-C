#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "icode.hh"

template class Const_Opd<double>;
template class Const_Opd<int>;

using namespace std;

//Code_For_Ast
Code_For_Ast::Code_For_Ast(){

}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg){
	ics_list = ic_l;
	result_register = reg;
}

void Code_For_Ast::append_ics(Icode_Stmt & ics){
	this->ics_list.push_back(&ics);
}

list<Icode_Stmt *>& Code_For_Ast::get_icode_list(){
	return this->ics_list;
}

Register_Descriptor * Code_For_Ast::get_reg(){
	return result_register;
}


void Code_For_Ast::set_reg(Register_Descriptor * reg){
	this->result_register = reg;
}

Code_For_Ast & Code_For_Ast::operator=(const Code_For_Ast & rhs){
	this->ics_list = rhs.ics_list;
	this->result_register = rhs.result_register;
}


//Icode_Stmt
//Move_IC_Stmt
//Compute_IC_Stmt
//Control_Flow_IC_Stmt
//Label_IC_Stmt

//1

Instruction_Descriptor & Icode_Stmt::get_op(){
}

Ics_Opd * Icode_Stmt::get_opd1(){
}

Ics_Opd * Icode_Stmt::get_opd2(){
}

Ics_Opd * Icode_Stmt::get_result(){
}

void Icode_Stmt::set_opd1(Ics_Opd * io){
}

void Icode_Stmt::set_opd2(Ics_Opd * io){
}

void Icode_Stmt::set_result(Ics_Opd * io){
}

void Icode_Stmt::print_icode(ostream & file_buffer){
}

void Icode_Stmt::print_assembly(ostream & file_buffer){
}

//2

Move_IC_Stmt::Move_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * result){
	this->op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
	this->opd1 = opd1;
	this->result = result;
}
 
Move_IC_Stmt & Move_IC_Stmt::operator=(const Move_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->opd1 = rhs.opd1;
	this->result = rhs.result;
}

Instruction_Descriptor & Move_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}

Ics_Opd * Move_IC_Stmt::get_opd1(){
	return this->opd1;
}

void Move_IC_Stmt::set_opd1(Ics_Opd * io){
	*this->opd1 = *io;
}

Ics_Opd * Move_IC_Stmt::get_result(){
	return this->result;
}

void Move_IC_Stmt::set_result(Ics_Opd * io){
	*this->result = *io;
}

void Move_IC_Stmt::print_icode(ostream & file_buffer){
	file_buffer<<"\t"<<this->op_desc.get_name()<<":"<<"    \t";
	this->result->print_ics_opd(file_buffer);
	file_buffer<<" <- ";
	this->opd1->print_ics_opd(file_buffer);
	file_buffer<<"\n";
}

void Move_IC_Stmt::print_assembly(ostream & file_buffer){
	if(this->op_desc.get_mnemonic()!="sw" && this->op_desc.get_mnemonic()!="s.d")
	{
		file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
		this->result->print_asm_opd(file_buffer);
		file_buffer<<", ";
		this->opd1->print_asm_opd(file_buffer);
		file_buffer<<"\n";
	}
	else{
		file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
		this->opd1->print_asm_opd(file_buffer);
		file_buffer<<", ";
		this->result->print_asm_opd(file_buffer);
		file_buffer<<"\n";

	}
}

//3
Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * opd2, Ics_Opd * result){
	this->op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
	this->opd1 = opd1;
	this->opd2 = opd2;
	this->result = result;
}

Compute_IC_Stmt & Compute_IC_Stmt::operator=(const Compute_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->opd1 = rhs.opd1;
	this->opd2 = rhs.opd2;
	this->result = rhs.result;
}

Instruction_Descriptor & Compute_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}

Ics_Opd * Compute_IC_Stmt::get_opd1(){
	return this->opd1;
}

void Compute_IC_Stmt::set_opd1(Ics_Opd * io){
	*this->opd1 = *io;
}

Ics_Opd * Compute_IC_Stmt::get_opd2(){
	return this->opd2;
}	

void Compute_IC_Stmt::set_opd2(Ics_Opd * io){
	*this->opd2 = *io;
}

Ics_Opd * Compute_IC_Stmt::get_result(){
	return this->result;
}

void Compute_IC_Stmt::set_result(Ics_Opd * io){
	*this->result = *io;
}

void Compute_IC_Stmt::print_icode(ostream & file_buffer){
	file_buffer<<"\t"<<this->op_desc.get_name()<<":"<<"    \t";
	this->result->print_ics_opd(file_buffer);
	file_buffer<<" <- ";
	this->opd1->print_ics_opd(file_buffer);
	if(this->op_desc.get_name()!="uminus" && this->op_desc.get_name()!="uminus.d"){
		file_buffer<<" , ";
		this->opd2->print_ics_opd(file_buffer);
	}
	file_buffer<<"\n";
}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer){
	if(this->op_desc.get_assembly_format()==a_op_o1_o2){
		file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
		this->opd1->print_asm_opd(file_buffer);
		file_buffer<<", ";
		this->opd2->print_asm_opd(file_buffer);
		file_buffer<<"\n";
		return;	
	}

	file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
	this->result->print_asm_opd(file_buffer);
	file_buffer<<", ";
	this->opd1->print_asm_opd(file_buffer);
	if(this->op_desc.get_name()!="uminus" && this->op_desc.get_name()!="uminus.d"){
		file_buffer<<", ";
		this->opd2->print_asm_opd(file_buffer);
	}
	file_buffer<<"\n";
}

//4

Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * opd2, string label,int size){
	this->op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
	this->opd1 = opd1;
	this->opd2 = opd2;
	this->offset = label;
	this->actual_param_size = size;
} 

Control_Flow_IC_Stmt & Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->opd1 = rhs.opd1;
	this->opd2 = rhs.opd2; 
	this->offset = rhs.offset;
	this->actual_param_size = rhs.actual_param_size;
}

Instruction_Descriptor & Control_Flow_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}

Ics_Opd * Control_Flow_IC_Stmt::get_opd1(){
	return this->opd1;
}

void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io){
	this->opd1 = io;
}

Ics_Opd * Control_Flow_IC_Stmt::get_opd2(){
	return this->opd2;
}

void Control_Flow_IC_Stmt::set_opd2(Ics_Opd * io){
	this->opd2 = io;
}

string Control_Flow_IC_Stmt::get_Offset(){
	return this->offset;
}

void Control_Flow_IC_Stmt::set_Offset(string label){
	this->offset = label;
}

void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer){
	file_buffer<<"\t"<<this->op_desc.get_name()<<":"<<"    \t";
	this->opd1->print_ics_opd(file_buffer);
	file_buffer<<" , zero : goto "<<offset<<"\n";
}

void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer){
	if(this->op_desc.get_name()=="jal"){
		if(this->actual_param_size!=0){
			file_buffer<<"\t"<<"sub $sp, $sp, "<<this->actual_param_size<<"\n";
		}
		file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
		file_buffer<<this->offset<<"\n";
		if(this->actual_param_size!=0){
			file_buffer<<"\t"<<"add $sp, $sp, "<<this->actual_param_size<<"\n";
		}
		return;
	}
	if(this->op_desc.get_assembly_format()==a_op_st){
		file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
		file_buffer<<this->offset<<"\n";
		return;
	}
	file_buffer<<"\t"<<this->op_desc.get_mnemonic()<<" ";
	this->opd1->print_asm_opd(file_buffer);
	file_buffer<<", $zero, "<<offset<<"\n";
}

//5

Label_IC_Stmt::Label_IC_Stmt(Tgt_Op inst_op, string label){
	this->op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
	this->label = label;
}

Label_IC_Stmt & Label_IC_Stmt::operator=(const Label_IC_Stmt & rhs){
	this->op_desc = rhs.op_desc;
	this->label = rhs.label;
}

Instruction_Descriptor & Label_IC_Stmt::get_inst_op_of_ics(){
	return this->op_desc;
}

string Label_IC_Stmt::get_label(){
	return this->label;
}

void Label_IC_Stmt::set_label(string label){
	this->label  = label;
}

void Label_IC_Stmt::print_icode(ostream & file_buffer){
	if(this->label=="print"){
		file_buffer<<"\t"<<this->label<<"\n";
		return;
	}
	if(this->op_desc.get_name()=="jump"){
		file_buffer<<"\t"<<"goto "<<this->label<<"\n";
		return;
	}
	file_buffer<<"\n"<<this->label<<":";
	file_buffer<<"\t"<<"\n";
}

void Label_IC_Stmt::print_assembly(ostream & file_buffer){
	if(this->label=="print"){
		file_buffer<<"\t"<<"syscall"<<"\n";
		return;
	}
	if(this->op_desc.get_name()=="jump"){
		file_buffer<<"\t"<<"j "<<this->label<<"\n";
		return;
	}
	file_buffer<<"\n"<<this->label<<":";
	file_buffer<<"\t"<<"\n";
}


//Instruction_Descriptor
Instruction_Descriptor::Instruction_Descriptor(Tgt_Op op, string name, string mnn, string ics, Icode_Format icf, Assembly_Format af){
	this->inst_op = op;
	this->name = name;
	this->mnemonic = mnn;
	this->ic_symbol = ics;
	this->ic_format = icf;
	this->assem_format = af;
}

Instruction_Descriptor::Instruction_Descriptor(){

}

Tgt_Op Instruction_Descriptor::get_op(){
	return this->inst_op;
}

string Instruction_Descriptor::get_name(){
	return this->name;
}

string Instruction_Descriptor::get_mnemonic(){
	return this->mnemonic;
}

string Instruction_Descriptor::get_ic_symbol(){
	return this->ic_symbol;
}

Icode_Format Instruction_Descriptor::get_ic_format(){
	return this->ic_format;
}

Assembly_Format Instruction_Descriptor::get_assembly_format(){
	return this->assem_format;
}

void Instruction_Descriptor::print_instruction_descriptor(ostream & file_buffer){
	file_buffer<<this->inst_op<<":";
}

//Ics_Opd
//Mem_Addr_Opd
//Register_Addr_Opd
//Const_Opd

//1
Register_Descriptor * Ics_Opd::get_reg(){
}

void Ics_Opd::print_ics_opd(ostream & file_buffer){
}

void Ics_Opd::print_asm_opd(ostream & file_buffer){
}

//2
Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se){
	this->symbol_entry = &se;
}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer){
	file_buffer<<this->symbol_entry->get_variable_name();
}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer){
	if(this->symbol_entry->get_symbol_scope()==global){
		file_buffer<<this->symbol_entry->get_variable_name();
	}
	else if(this->symbol_entry->get_ref_offset()==sp_ref){
		file_buffer<<this->symbol_entry->get_start_offset()<<"($sp)";
	}
	else{
		file_buffer<<this->symbol_entry->get_start_offset()<<"($fp)";
	}
}

Mem_Addr_Opd & Mem_Addr_Opd::operator= (const Mem_Addr_Opd & rhs){
	this->symbol_entry = rhs.symbol_entry;
}

//3
Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * rd){
	this->register_description = rd;
}

Register_Descriptor * Register_Addr_Opd::get_reg(){
	return this->register_description;
}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer){
	file_buffer<<this->register_description->get_name();
}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer){
	file_buffer<<"$"<<this->register_description->get_name();
}

Register_Addr_Opd & Register_Addr_Opd::operator=(const Register_Addr_Opd & rhs){
	this->register_description = rhs.register_description;
}

//4

template <class T>
Const_Opd<T>::Const_Opd(T num){
	this->num = num;
}

template <class T>
void Const_Opd<T>::print_ics_opd(ostream & file_buffer){
	file_buffer<<this->num;
}

template <class T>
void Const_Opd<T>::print_asm_opd(ostream & file_buffer){
	file_buffer<<this->num;
}

template <class T>
Const_Opd<T> & Const_Opd<T>::operator=(const Const_Opd & rhs){
	this->num = rhs.num;
}

