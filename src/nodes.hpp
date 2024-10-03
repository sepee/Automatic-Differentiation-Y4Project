// NODES
#include <string>

//#include <eigen3/Eigen>  // for working with vectors and matrices later

// DECLARATIONS
template <typename pointerType> int16;
int maximum_number_operations = 25;
int maximum_number_sections_and_ops = 2*maximum_number_operations + 1;  //e.g. x + y * z = 5 sections (where there are 2 operations)


class BaseNode {

	private:
		std::string derivative = "";  // or expression


		auto Evaluate() {
			// evaluate children
		};

		auto Derive(this) {
			// find derivative of this node (using children derivatives)
		};

	public:
		std::string getDerivative(this) {
			return derivative;
		}
		void setDerivative(this, d) {
			this.derivative = d;
		}
		
}; // END BaseNode class

// ------------------------------ OPERATIONS --------------------------------------
class Operation(BaseNode) {

	private:

	public:
		auto Evaluate(this) {
			// evaluate children
		}


}; // END Operation class

class Binary(Operation) {

	private:
		std::string[2] branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		auto getChildren(this) {
			return branches;
		}


}; // END Binary(Operation) class

class Unary(Operation) {

	private:
		std::string[1] branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		auto getChildren(this) {
			return branches;
		}


}; // END Unary(Operation) class

class Add(Binary) {

}; // END Add(Binary) class

class Subtract(Binary) {

}; // END Subtract(Binary) class

class Multiply(Binary) {

}; // END Multiply(Binary) class

class Divide(Binary) {

}; // END Divide(Binary) class

class Sin(Unary) {

}; // END Sin(Unary) class

class Cos(Unary) {

}; // END Cos(Unary) class

class Exponential(Unary) {

}; // END Exponential(Unary) class

class NaturalLog(Unary) {

}; // END NaturalLog(Unary) class


// ------------------------------ EXPRESSIONS --------------------------------------
class Expression(BaseNode) {

	private:

	public:
		auto Evaluate(this) {
			// evaluate children
		}


}; // END Expression class

class Symbol(Expression) {

	private:

	public:
		auto getChildren(this) {
			return branches;
		}


}; // END Symbol(Expression) class

class Number(Expression) {

	private:
		std::string[1] branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		auto getChildren(this) {
			return branches;
		}


}; // END Number(Expression) class

class X(Symbol) {

}; // END X(Symbol) class

