// Remember BODMAS

#include <string>
#include <map>  // for operations,index dictionary-style thing
#include <vector>
//#include <pair>

#include "nodes.hpp"

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

// constants
constexpr int num_symbols = 6;


//possibly relate to nodes

std::string x = "x";
std::string sine = "sin()";
std::string cosine = "cos()";
std::string exponential = "exp()";
std::string ln = "ln()";


using format_and_locate_return_type = std::pair< std::array<std::string, maximum_number_sections_and_ops> , std::map<char, std::array<int, maximum_number_operations>> >; 
/*
@brief Format function string. e.g. add spaces around operations and on inside of brackets. Also, locate operators by finding their index.

@params function Function raw.

@returns formatted_function Formatted function.
*/
format_and_locate_return_type FormatAndLocate(std::string function) {

	std::array<std::string, maximum_number_sections_and_ops> formatted_function;
	std::array<std::string, maximum_number_sections_and_ops>* formatted_function_pointer = &formatted_function;
	int f_func_i = 0;

	std::string full_str_function = "";

	//std::map<char, std::array<int, maximum_number_operations>> op_locate_dict = {
	/*
	std::map<char, std::vector<int>> op_locate_dict = {
		{ "+" , {} },
		{ "-" , {} },
		{ "*" , {} },
		{ "/" , {} },
		{ "(" , {} },
		{ ")" , {} }
	};
	*/
	/*
	std::array<std::array<int, maximum_number_operations>, 6> indices_of_symbol;
	std::map<char, int> op_locate_dict = {
		{ '+' , 0 },  // i.e. the zero-th array in the 2D-array indices_of_symbol
		{ '-' , 1 },
		{ '*' , 2 },
		{ '/' , 3 },
		{ '(' , 4 },
		{ ')' , 5 }
	};
	*/
	std::map<char, std::array<int, maximum_number_operations>> op_locate_dict;
	std::array<int, maximum_number_operations> empty;
	op_locate_dict['+'] = empty;
	op_locate_dict['-'] = empty;
	op_locate_dict['*'] = empty;
	op_locate_dict['/'] = empty;
	op_locate_dict['('] = empty;
	op_locate_dict[')'] = empty;

	int str_index = 0;
	int next_op_i_add = 0;  // for index in array of addition locations
	int next_op_i_sub = 0;  // for index in array of subtraction locations
	int next_op_i_mul = 0;  // for index in array of multiplication locations
	int next_op_i_div = 0;  // for index in array of division locations
	int next_op_i_obracket = 0;  // for index in array of open-bracket locations
	int next_op_i_cbracket = 0;  // for index in array of close-bracket locations

	std::string section = "";

	// TODO(Catherine) Refactor since lots of duplication
	for (char& c : function) {  // or without &

		if (c == '+' || c == '-' || c == '*' || c == '/') {  // reduces number of if conditions?
			
			full_str_function = full_str_function + " " + c + " ";

			//*formatted_function_pointer++ = section;  // assigns section then incrememts pointer since ++ after
			formatted_function[f_func_i++] = section;  // assigns section then incrememts f_func_i since ++ after
			section = "";

			if (c == '+') {
				op_locate_dict['+'][next_op_i_add] = str_index;
				next_op_i_add++;
			} else if (c == '-') {
				op_locate_dict['-'][next_op_i_sub] = str_index;
				next_op_i_sub++;
			} else if (c == '*') {
				op_locate_dict['*'][next_op_i_mul] = str_index;
				next_op_i_mul++;
			} else if (c == '/') {
				op_locate_dict['/'][next_op_i_div] = str_index;
				next_op_i_div++;
			}

		} else if (c == '(') {
			full_str_function = full_str_function + c + " ";
			op_locate_dict[')'][next_op_i_obracket] = str_index;
			next_op_i_obracket++;
			formatted_function[f_func_i++] = section;
			section = "";
		} else if (c == ')') {
			full_str_function = full_str_function + " " + c;
			op_locate_dict[')'][next_op_i_cbracket] = str_index;
			next_op_i_cbracket++;
			formatted_function[f_func_i++] = section;
			section = "";

		} else {
			full_str_function = full_str_function + c;
			section = section + c;
		}

		str_index++;
	}

	return std::make_pair(formatted_function, op_locate_dict);

};


/*
@brief Parses function string and produces tree of nodes. Recursively.

@params function Function as a string using operations and expressions above.

@returns root Reference (pointer) to root node
*/
std::array<std::string, maximum_number_sections_and_ops> ParseIntoTreeString(std::array<std::string, maximum_number_sections_and_ops> function_array, std::map<char, int[maximum_number_operations]> operations_locations_dict) {


	// https://en.wikipedia.org/wiki/Shunting_yard_algorithm#:~:text=In%20computer%20science%2C%20the%20shunting,abstract%20syntax%20tree%20(AST).
	
	// undefined letters => create new Symbol object with this name

	//do stuff
	std::array<std::string, maximum_number_sections_and_ops> tree_string; // {"index-of-plus", "plus", "x", "2", ""

	// !!! deal with brackets
	// find brackets at deepest level, then do process on string inside those brackets
	// go up a level of brackets, then do process
	// ...
	// brackets around whole string for convenience => final iteration will cover the whole function

	// eg. function ( ( (sin(x + 2) * x) ) * (x+3) )

	// !!! multiplication and division from left to right

	// !!! addition and subtraction from left to right

	// !!! deal with powers

	return tree_string;
};


int ParseTreeStringIntoTree() {

	// Shunting yard algorithm string into tree of nodes

	// As I assign ids, create dictionary of ids and object maybe

	return 0;  // return id of object?

};


int main() {

	std::string myfunctionstring = "x * x";
	std::string myfunctionstring = "( ( (sin(x + 2) * x) ) * (x+3) )";
	auto[formatted_function_output, op_locate_dict_output] = FormatAndLocate(myfunctionstring);  // https://stackoverflow.com/questions/37876288/is-there-a-one-liner-to-unpack-tuple-pair-into-references

	// next Parse ...
	return 0;
};

//TODO Create MakeFile !!!!!!!!

