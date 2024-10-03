// Remember BODMAS

#include <string>
#include <map>  // for operations,index dictionary-style thing

#include <nodes.hpp>

/*

Defined operations:
+ addition
- subtraction
* multiplication
/ division
*/


/*
Defined expressions:
x 
sin()
cos()
exp()
ln()
*/


//possibly relate to nodes

std::string x = "x";
std::string sin = "sin()";
std::string cos = "cos()";
std::string exp = "exp()";
std::string ln = "ln()";


/*
@brief Format function string. e.g. add spaces around operations and on inside of brackets. Also, locate operators by finding their index.

@params function Function raw.

@returns formatted_function Formatted function.
*/
std::string FormatAndLocate(std::string function) {

	std::string[maximum_number_sections_and_ops] formatted_function;
	int formatted_function_pointer = &formatted_function;

	std::string full_str_function = "";

	std::map<char, int[maximum_number_operations]> op_locate_dict = {
		{ "+" , {} },
		{ "-" , {} },
		{ "*" , {} },
		{ "/" , {} },
		{ "(" , {} },
		{ ")" , {} }
	};

	int str_index = 0;
	int next_op_i_add = 0;  // for index in array of addition locations
	int next_op_i_sub = 0;  // for index in array of subtraction locations
	int next_op_i_mul = 0;  // for index in array of multiplication locations
	int next_op_i_div = 0;  // for index in array of division locations
	int next_op_i_obracket = 0;  // for index in array of open-bracket locations
	int next_op_i_cbracket = 0;  // for index in array of close-bracket locations

	std::string section = "";

	// TODO Catherine: refactor since lots of duplication
	for (char& c : function) {  // or without &

		if (c == "+" || c == "-" || c == "*" || c == "/") {  // reduces number of if conditions?
			
			full_str_function = full_str_function + " " + c + " ";

			*formatted_function_pointer++ = section;  // assigns section then incrememts pointer since ++ after
			section = "";

			if (c == "+") {
				op_locate_dict["+"][next_op_i_add] = str_index;
				next_op_i_add++;
			} else if (c == "-") {
				op_locate_dict["-"][next_op_i_sub] = str_index;
				next_op_i_sub++;
			} else if (c == "*") {
				op_locate_dict["*"][next_op_i_mul] = str_index;
				next_op_i_mul++;
			} else if (c == "/") {
				op_locate_dict["/"][next_op_i_div] = str_index;
				next_op_i_div++;
			}

		} else if (c == "(") {
			full_str_function = full_str_function + c + " ";
			op_locate_dict["("][next_op_i_obracket] = str_index;
			next_op_i_obracket++;
			*formatted_function_pointer++ = section;
			section = "";
		} else if (c == ")") {
			full_str_function = full_str_function + " " + c;
			op_locate_dict[")"][next_op_i_cbracket] = str_index;
			next_op_i_cbracket++;
			*formatted_function_pointer++ = section;
			section = "";

		} else {
			full_str_function = full_str_function + c;
			section = section + c;
		}

		str_index++;
	}

	return formatted_function, op_locate_dict;

};


/*
@brief Parses function string and produces tree of nodes. Recursively.

@params function Function as a string using operations and expressions above.

@returns root Reference (pointer) to root node
*/
pointerType Parse(std::string[maximum_number_sections_and_ops] function_array, std::map<char, int[maximum_number_operations]> operations_locations_dict) {

	//do stuff

	// deal with brackets

	// multiplication and division from left to right

	// addition and subtraction from left to right

	// deal with powers


};































