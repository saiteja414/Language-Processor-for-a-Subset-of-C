#include<string>
#include<fstream>
#include<iostream>

using namespace std;

int Eval_Result::get_int_value(){};
void Eval_Result::set_value(int value){};
double Eval_Result::get_double_value(){};
void Eval_Result::set_value(double value){};
bool Eval_Result::is_variable_defined(){};
void Eval_Result::set_variable_status(bool def){};
void Eval_Result::set_result_enum(Result_Enum){};
Result_Enum Eval_Result::get_result_enum(){};

int Eval_Result_Value::get_int_value(){};
void Eval_Result_Value::set_value(int value){};
double Eval_Result_Value::get_double_value(){};
void Eval_Result_Value::set_value(double value){};
bool Eval_Result_Value::is_variable_defined(){};
void Eval_Result_Value::set_variable_status(bool def){};
void Eval_Result_Value::set_result_enum(Result_Enum){};
Result_Enum Eval_Result_Value::get_result_enum(){};

Eval_Result_Value_Int::Eval_Result_Value_Int(){
	this->defined = 0;
}

Eval_Result_Value_Int::~Eval_Result_Value_Int(){

}

void Eval_Result_Value_Int::set_value(int number){
	this->result_type = int_result;
	this->defined = 1;
	this->value = number;
}

void Eval_Result_Value_Int::set_value(double number){
	this->result_type = int_result;
	this->defined = 1;
	this->value = int(number);
}

int Eval_Result_Value_Int::get_int_value(){
	return this->value;
}

void Eval_Result_Value_Int::set_variable_status(bool def){
	this->defined = def;
}

bool Eval_Result_Value_Int::is_variable_defined(){
	return this->defined;
}

void Eval_Result_Value_Int::set_result_enum(Result_Enum res){
	this->result_type = res;
}

Result_Enum Eval_Result_Value_Int::get_result_enum(){
	return this->result_type;
}



// double
Eval_Result_Value_Double::Eval_Result_Value_Double(){
	this->defined = 0;
}

Eval_Result_Value_Double::~Eval_Result_Value_Double(){

}

void Eval_Result_Value_Double::set_value(int number){
	this->result_type = double_result;
	this->defined = 1;
	this->value = double(number);
}

void Eval_Result_Value_Double::set_value(double number){
	this->result_type = double_result;
	this->defined = 1;
	this->value = number;
}

double Eval_Result_Value_Double::get_double_value(){
	return this->value;
}

void Eval_Result_Value_Double::set_variable_status(bool def){
	this->defined = def;
}

bool Eval_Result_Value_Double::is_variable_defined(){
	return this->defined;
}

void Eval_Result_Value_Double::set_result_enum(Result_Enum res){
	this->result_type = res;
}

Result_Enum Eval_Result_Value_Double::get_result_enum(){
	return this->result_type;
}

//local_environment

Local_Environment::Local_Environment(){

}

Local_Environment::~Local_Environment(){

}

bool Local_Environment::is_variable_defined(string name){
	if(Local_Environment::does_variable_exist(name)){
		return this->variable_table[name]->is_variable_defined();
	}
	else{
		
		return false;
	}
}

Eval_Result *Local_Environment::get_variable_value(string name){
	if(Local_Environment::does_variable_exist(name)){
		return this->variable_table[name];
	}
	else{
		
		return NULL;
	}
}

bool Local_Environment::does_variable_exist(string name){
	if(this->variable_table.find(name)!=this->variable_table.end()){
		return true;
	}
	else{
		return false;
	}
}

void Local_Environment::put_variable_value(Eval_Result & value, string name){
	this->variable_table[name] = &value;
}


void Local_Environment::print(ostream & file_buffer){
	map<string,Eval_Result *>::iterator it;
	for(it = this->variable_table.begin();it!=this->variable_table.end();it++){
		if(it->second->is_variable_defined()){
			if(it->second->get_result_enum()==int_result){
				file_buffer<<VAR_SPACE<<it->first<<" : "<<it->second->get_int_value()<<"\n";
			}
			else{
				file_buffer<<VAR_SPACE<<it->first<<" : "<<it->second->get_double_value()<<"\n";
			}
		}
		else{
			file_buffer<<VAR_SPACE<<it->first<<" : undefined\n";
		}
	}
}

