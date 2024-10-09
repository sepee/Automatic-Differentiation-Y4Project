// NODES
#include <stdint.h>
#include <string>
#include <array>

//#include <eigen3/Eigen>  // for working with vectors and matrices later

// DECLARATIONS
//using pointerType = int16;
constexpr int maximum_number_operations = 25;
constexpr int maximum_number_sections_and_ops = 2*maximum_number_operations + 1;  //e.g. x + y * z = 5 sections (where there are 2 operations)


class BaseNode {

	private:
		int id;
		int id_parent;
		std::array<int, 2> id_children;
		std::string derivative = "";  // or expression


		std::array<int, 2> Evaluate() {
			// evaluate children, returns ids of children objects
			return {0, 0};
		};

		void Derive() {
			// find derivative of this node (using children derivatives)
			std::string d = "something calculated";
			setDerivative(d);
		};

	public:
		std::string getDerivative() {
			derivative = "something";  // TODO(Otis)
			return derivative;
		}

		void setDerivative(std::string d) {
			this->derivative = d;
		}

		int getID() {
			return this->id;
		}

		void setID(int i) {
			this->id = i;
		}

		int getIDparent() {
			return this->id_parent;
		}

		void setIDparent(int i) {
			this->id_parent = i;
		}

		std::array<int, 2> getIDchildren() {
			return this->id_children;
		}

		void setIDchildren(std::array<int, 2> c) {
			this->id_children = c;
		}
		
}; // END BaseNode class

// ------------------------------ OPERATIONS --------------------------------------
class Operation : public BaseNode {

	//private:

	public:
		std::array<int, 2> Evaluate() {
			// evaluate children, returns ids of children objects
			return {0, 0};
		}


}; // END Operation class

class Binary : public Operation {

	private:
		std::array<int, 2> id_children;  // duplicated idea - id_children / branches
		std::array<std::string, 2> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		std::array<std::string, 2> getChildren() {
			return this->branches;
		}


}; // END Binary(Operation) class

class Unary : public Operation {

	private:
		std::array<int, 1> id_children;
		std::array<std::string, 1> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		std::array<std::string, 1> getChildren() {
			return this->branches;
		}


}; // END Unary(Operation) class

class Add : public Binary {

}; // END Add(Binary) class

class Subtract : public Binary {

}; // END Subtract(Binary) class

class Multiply : public Binary {

}; // END Multiply(Binary) class

class Divide : public Binary {

}; // END Divide(Binary) class

class Sin : public Unary {

}; // END Sin(Unary) class

class Cos : public Unary {

}; // END Cos(Unary) class

class Exponential : public Unary {

}; // END Exponential(Unary) class

class NaturalLog : public Unary {

}; // END NaturalLog(Unary) class


// ------------------------------ EXPRESSIONS --------------------------------------
class Expression : public BaseNode {

	//private:

	public:
		std::array<int, 2> Evaluate() {
			// evaluate children, returns ids of children objects
			return {0, 0};
		};


}; // END Expression class

class Symbol : public Expression {

	private:
		std::array<std::string, 1> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		std::array<std::string, 1> getChildren() { // TODO(Otis) check return type
			return this->branches;
		}


}; // END Symbol(Expression) class

class Number : public Expression {

	private:
		std::array<std::string, 1> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		std::array<std::string, 1> getChildren() {
			return this->branches;
		}


}; // END Number(Expression) class

class X : public Symbol {

}; // END X(Symbol) class

