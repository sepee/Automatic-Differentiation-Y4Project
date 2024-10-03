// NODES
#include <string>

//#include <eigen3/Eigen>  // for working with vectors and matrices later

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

class Operation(BaseNode) {

	private:
		std::string[2] branches;  // branches to 2 children (always 2 children for simplicity)

	public:
		auto getChildren(this) {
			return branches;
		}


}; // END Operation class