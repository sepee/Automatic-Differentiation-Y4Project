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

// Type Definitions
using formatted_function_output_type = std::array<std::string, maximum_number_sections_and_ops>;
using op_locate_dict_output_type = std::map<char, std::array<int, maximum_number_operations>>;
using format_locate_output_type = std::pair<formatted_function_output_type, op_locate_dict_output_type>;

// constants
constexpr int num_symbols = 6;


//possibly relate to nodes

std::string x = "x";
std::string sine = "sin()";
std::string cosine = "cos()";
std::string exponential = "exp()";
std::string ln = "ln()";

/*
@brief Rearrange function chunks. Each chunk is either an operation or an expression as a string.
https://en.wikipedia.org/wiki/Shunting_yard_algorithm#:~:text=In%20computer%20science%2C%20the%20shunting,abstract%20syntax%20tree%20(AST)
https://stackoverflow.com/questions/56547298/shunting-yard-algorithm-c
https://www.youtube.com/watch?app=desktop&v=Q00iGR0JEqY

@params function_chunks_in_order Function chunks in order of original function string.

@returns output Formatted function chunks for Shunting Yard algorithm.
*/
formatted_function_output_type ShuntingYard(formatted_function_output_type function_chunks_in_order) {
	// forgetting brackets
	formatted_function_output_type output;
	int output_index = 0;
	formatted_function_output_type stack;
	int stack_index = 0;

	std::string chunk;
	for (int chunk_id = 0; chunk_id < maximum_number_sections_and_ops; chunk_id++) {
		chunk = function_chunks_in_order[chunk_id];
		printf("Chunk: %s\n", chunk.c_str());
		if (chunk == "+" || chunk == "-" || chunk == "*" || chunk == "/") {  // Binary
			printf("stack[stack_index-1]: %s \n", stack[stack_index-1].c_str());
			if (stack[stack_index-1] == "+" || stack[stack_index-1] == "-" || stack[stack_index-1] == "*" || stack[stack_index-1] == "/") {
				printf("Popping: Adding to output: %s\n", stack[stack_index-1].c_str());
				output[output_index++] = stack[stack_index-1];
				stack_index--;
			}
			printf("Adding to stack: %s\n", chunk.c_str());
			stack[stack_index++] = chunk;
		} else if (chunk == "sin" || chunk == "cos" || chunk == "exp" || chunk == "ln") {  //Unary
			printf("Adding to stack: %s\n", chunk.c_str());
			stack[stack_index++] = chunk;
		} else if (chunk == "(") {
			printf("Adding to stack: %s\n", chunk.c_str());
			stack[stack_index++] = chunk;
		} else if (chunk == ")") {
			printf("\nPopping stack\n");
			for (int s = stack_index-1; s >= 0; s--) {  // add stack to output in forward or reverse order
				printf("Stack[s] %s\n", stack[s].c_str());
			}
			printf("\n");
			int count = 0;
			printf("stack_index = %d \n", stack_index);
			for (int s = stack_index-1; s >= 0; s--) {  // add stack to output in forward or reverse order
				printf("Stack[s] %s\n", stack[s].c_str());
				if (stack[s] == "(") {
					count++;
					if (count == 2) {
						printf("Stack[s-1] %s\n", stack[s-1].c_str());
						stack_index = s; // the next index to populate in the stack
						break;
					} else if (count == 1 && s == 0) {
						stack_index = s;
						break;
					}
				} else {
					printf("Popping: Adding to output: %s\n", stack[s].c_str());
					output[output_index++] = stack[s];
				}
			}
		} else if (chunk == "") {
			continue;
		} else {
			printf("Adding to output: %s\n", chunk.c_str());
			output[output_index++] = chunk;
		}

		// Check stack and output
		printf("\n Displaying current stack and output at end of iteration:\n");
		for (int s = stack_index-1; s >= 0; s--) {  // add stack to output in forward or reverse order
			printf("Stack[s] %s\n", stack[s].c_str());
		}
		for (int o = 0; o < output_index; o++) {  // add stack to output in forward or reverse order
			printf("Output[o] %s\n", output[o].c_str());
		}
	}
	return output;
}


using format_and_locate_return_type = std::pair< std::array<std::string, maximum_number_sections_and_ops> , std::map<char, std::array<int, maximum_number_operations>> >; 
/*
@brief Format function string. e.g. add spaces around operations and on inside of brackets. Also, locate operators by finding their index.

@params function Function raw.

@returns formatted_function Formatted function.
*/
format_and_locate_return_type FormatAndLocate(std::string function) {

	function = "(" + function + ")";

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

	printf("Function input:");
	printf("%s", function.c_str());
	printf("\n");
	// TODO(Catherine) Refactor since lots of duplication
	for (char& c : function) {  // or without &
		//for (int f = 0; f < 2*maximum_number_operations; f++) {  // or without &
		printf("Next section:");
		printf("%s", section.c_str());
		printf("\n");
		printf("Character:");
		printf("%c", c);
		printf("\n");
		if (c == '+' || c == '-' || c == '*' || c == '/') {  // reduces number of if conditions?
			
			full_str_function = full_str_function + " " + c + " ";

			//*formatted_function_pointer++ = section;  // assigns section then incrememts pointer since ++ after
			formatted_function[f_func_i++] = section;  // assigns section then incrememts f_func_i since ++ after
			section = "";

			if (c == '+') {
				op_locate_dict['+'][next_op_i_add] = str_index;
				next_op_i_add++;
				formatted_function[f_func_i++] = "+";
			} else if (c == '-') {
				op_locate_dict['-'][next_op_i_sub] = str_index;
				next_op_i_sub++;
				formatted_function[f_func_i++] = "-";
			} else if (c == '*') {
				op_locate_dict['*'][next_op_i_mul] = str_index;
				next_op_i_mul++;
				formatted_function[f_func_i++] = "*";
			} else if (c == '/') {
				op_locate_dict['/'][next_op_i_div] = str_index;
				next_op_i_div++;
				formatted_function[f_func_i++] = "/";
			}

		} else if (c == '(') {
			formatted_function[f_func_i++] = section;  // assigns section then incrememts f_func_i since ++ after
			section = "";

			full_str_function = full_str_function + c + " ";
			op_locate_dict[')'][next_op_i_obracket] = str_index;
			next_op_i_obracket++;
			formatted_function[f_func_i++] = "(";
		} else if (c == ')') {
			formatted_function[f_func_i++] = section;  // assigns section then incrememts f_func_i since ++ after
			section = "";

			full_str_function = full_str_function + " " + c;
			op_locate_dict[')'][next_op_i_cbracket] = str_index;
			next_op_i_cbracket++;
			formatted_function[f_func_i++] = ")";
		} else {
			// TODO(Catherine): Check ^ , i.e. turn ^ into multiple multiplications
			printf("else\n");
			full_str_function = full_str_function + c;
			section = section + c;
			//if (section == "") {
			//	printf("Break\n");
			//	break;
			//}
		}

		str_index++;  // use to get number of total chunks/sections
	}

	// Format for Shunting Yard Algorithm
	// https://en.wikipedia.org/wiki/Shunting_yard_algorithm#:~:text=In%20computer%20science%2C%20the%20shunting,abstract%20syntax%20tree%20(AST).
	formatted_function_output_type formatted_function_reordered = ShuntingYard(formatted_function);

	return std::make_pair(formatted_function_reordered, op_locate_dict);

};


/*
@brief Parses function string and produces tree of nodes. Recursively.

@params function Function as a string using operations and expressions above.

@returns root Reference (pointer) to root node
*/
std::array<std::string, maximum_number_sections_and_ops> ParseIntoTreeString(std::array<std::string, maximum_number_sections_and_ops> function_array, std::map<char, int[maximum_number_operations]> operations_locations_dict) {


	
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


int ParseTreeStringIntoTree(formatted_function_output_type formatted_function_output) {

	// Shunting yard algorithm string into tree of nodes

	// As I assign ids, create dictionary of ids and object maybe

	return 0;  // return id of object? or pointer to first object

};


int main() {
	printf("Starting MAIN...\n");
	//std::string myfunctionstring = "sin(x)*x";  // do not want spaces
	//std::string myfunctionstring = "sin(cos(2 3)/3*9)";  // do not want spaces - TODO(Catherine): Add space strip to formatter
	//std::string myfunctionstring = "( ( (sin(x + 2) * x) ) * (x+3) )";
	std::string myfunctionstring = "3+4*2/(1-5)";  // need to add precedences
	format_locate_output_type format_and_locate_output = FormatAndLocate(myfunctionstring);  // https://stackoverflow.com/questions/37876288/is-there-a-one-liner-to-unpack-tuple-pair-into-references
	
	formatted_function_output_type formatted_function_output = format_and_locate_output.first;
	op_locate_dict_output_type op_locate_dict_output = format_and_locate_output.second;
	printf("Formatted function chunks (with Shunting Yard):");
	for (int f = 0; f<maximum_number_sections_and_ops; f++){
		printf("%s", formatted_function_output[f].c_str());
		printf(",");
	}
	printf("\n");
	// next Parse ...

	// integer of pointer - see return statement inside function
	int result = ParseTreeStringIntoTree(formatted_function_output_type formatted_function_output);

	return 0;
};

//TODO Create MakeFile !!!!!!!!

