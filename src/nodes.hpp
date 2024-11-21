// NODES
#include <stdint.h>
#include <string>
#include <array>

// using namespace std;

//#include <eigen3/Eigen>  // for working with vectors and matrices later

// DECLARATIONS
//using pointerType = int16;
constexpr int maximum_number_operations = 25;
constexpr int maximum_number_sections_and_ops = 2*maximum_number_operations + 1;  //e.g. x + y * z = 5 sections (where there are 2 operations)


class BaseNode {

	private:
		int _id;
		int _id_parent;
		//std::array<int, 2> id_children;
		int _id_children_a;
		int _id_children_b;
		std::string _derivative;
		std::string _s;
		float _v = 0;
		int _p = 0;

		std::array<int, 2> Evaluate() {
			// evaluate children, returns ids of children objects
			return {0, 0};
		};

		void Differentiate() {
			// forward differentiate
		}

		std::string Derive() {
			// find derivative of this node (using children derivatives)
			std::string d = "something calculated";
			setDerivative(d);
			return d;
		};

	public:
		BaseNode(int id) {  // Constructor - TODO(Catherine) define contructor with string and value for all classes
			_id = id;
			_s = "[BASE NODE]";
		}

		std::string getString() { // __str__ replacement
			return this->_s;
		}

		void setString(std::string s) {
			this->_s = s;
		}

		float getValue() {
			return this->_v;
		}

		void setValue(float v) {
			this->_v = v;
		}

		int getPartial() {
			return this->_p;
		}

		void setPartial(int p) {
			this->_p = p;
		}

		std::string getDerivative() {
			return "something";  // TODO(Otis)
		}

		void setDerivative(std::string d) {
			this->_derivative = d;
		}

		int getID() {
			return this->_id;
		}

		void setID(int i) {
			this->_id = i;
		}

		int getIDparent() {
			return this->_id_parent;
		}

		void setIDparent(int i) {
			this->_id_parent = i;
		}

		//std::pair<int, int> getIDchildren() {
		//	return std::pair(this->_id_children_a, this->_id_children_b);
		//}

		std::array<int, 2> getIDchildren() {
			std::array<int, 2> children;
			children[0] = this->_id_children_a;
			children[1] = this->_id_children_b;
			return children;
		}

		void setIDchildren(std::array<int, 2> c) {
			this->_id_children_a = c[0];
			this->_id_children_b = c[1];
		}

		void setIDfirstChild(int c) {
			this->_id_children_a = c;
		}

		void setIDsecondChild(int c) {
			this->_id_children_b = c;
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
		void getString() {
			printf("[BINARY OP]");
		}

		std::array<std::string, 2> getChildren() {
			return this->branches;
		}


}; // END Binary(Operation) class

class Unary : public Operation {

	private:
		int _id_children_a;
		std::array<std::string, 1> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		void getString() {
			printf("[UNARY OP]");
		}

		std::array<std::string, 1> getChildren() {
			return this->branches;
		}

		std::array<int, 1> getIDchildren() {
			std::array<int, 1> children;
			children[0] = this->_id_children_a;
			return children;
		}

		void setIDchildren(std::array<int, 1> c) {
			this->_id_children_a = c[0];
		}


}; // END Unary(Operation) class

class Add : public Binary {


	void getString() {
		printf("[%d] + [%d]", this->getIDchildren()[0], this->getIDchildren()[1]);
	}

	void Derive() {
        float dthis_da = 1; //(this->_id_children_a)->getValue();
		auto current_partial_a = 1;  //getIDchildren()[0]->getPartial();
		setPartial(current_partial_a + dthis_da * this->getPartial());
        //setChildren(getChildren()[0]->Derive(), getIDchildren()[1]);  // when set up pointers to objects
		std::array<int, 2> children;
		children[0] = 1;
		children[1] = 2;
        setIDchildren(children);
        //setIDchildren(getIDchildren()[0]->Derive(), getIDchildren()[1]);

		// this->children[0]->getPartial();
		// this->children[0]->partial; // -> is for pointer of sorts
    }

}; // END Add(Binary) class

class Subtract : public Binary {
	void getString() {
		printf("[%d] - [%d]", this->getIDchildren()[0], this->getIDchildren()[1]);
	}
}; // END Subtract(Binary) class

class Multiply : public Binary {
	void getString() {
		printf("[%d] * [%d]", this->getIDchildren()[0], this->getIDchildren()[1]);
	}
}; // END Multiply(Binary) class

class Divide : public Binary {
	void getString() {
		printf("[%d] / [%d]", this->getIDchildren()[0], this->getIDchildren()[1]);
	}
}; // END Divide(Binary) class

class Sin : public Unary {
	void getString() {
		printf("sin([%d])", this->getIDchildren()[0]);
	}
}; // END Sin(Unary) class

class Cos : public Unary {
	void getString() {
		printf("cos([%d])", this->getIDchildren()[0]);
	}
}; // END Cos(Unary) class

class Exponential : public Unary {
	void getString() {
		printf("exp([%d])", this->getIDchildren()[0]);
	}
}; // END Exponential(Unary) class

class NaturalLog : public Unary {
	void getString() {
		printf("ln([%d])", this->getIDchildren()[0]);
	}
}; // END NaturalLog(Unary) class


// ------------------------------ EXPRESSIONS --------------------------------------
class Expression : public BaseNode {

	private:
		float value;

	public:
		std::array<int, 2> Evaluate() {
			// evaluate children, returns ids of children objects
			return {0, 0};
		};


}; // END Expression class

class Symbol : public Expression { // x, y, ... single characters

	private:
		std::string _s;
		std::array<std::string, 1> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		void getString() {
			printf(" %s ", this->_s);
		}

		std::array<std::string, 1> getChildren() { // TODO(Otis) check return type
			return this->branches;
		}


}; // END Symbol(Expression) class

class Number : public Expression { // literal number eg. the 2 in (x+2)

	private:
		std::string _s;
		std::array<std::string, 1> branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		void getString() {
			printf(" %s ", this->_s);
		}

		std::array<std::string, 1> getChildren() {
			return this->branches;
		}

}; // END Number(Expression) class

//class X : public Symbol { // x
//}; // END X(Symbol) class

// syntax to define instance
//new = Symbol();
//new.setStringAndValue("x", 10);

