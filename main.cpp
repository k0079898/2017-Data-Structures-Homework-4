#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "function.h"

void tryTestCase(Implement &inst)
{
    std::string op;
	int label_1, label_2, weight, degree, degreePass, numCmp, numCmpPass;
	bool isExistPath, isExistPathPass;
	bool isExistCycle_ans;
	std::string input;
    while(getline(std::cin, input))
    {
		std::istringstream in(input);
		while(in >> op) {
			if( op == "addEdge" )
			{
				in >> label_1 >> label_2 >> weight;
				inst.addEdge(label_1, label_2, weight);
			}
			else if( op == "deleteEdge" )
			{
				in >> label_1 >> label_2;
				inst.deleteEdge(label_1, label_2);
			}
			else if( op == "deleteVertex" )
			{
				in >> label_1;
				inst.deleteVertex(label_1);
			}
			else if( op == "degree" )
			{
				in >> label_1;
				degree = inst.degree(label_1);
				std::cout << degree << std::endl;
			}
			else if( op == "isExistPath")
			{
				in >> label_1 >> label_2;
				isExistPath = inst.isExistPath(label_1, label_2);
				if(isExistPath) std::cout << "true" << std::endl;
				else std::cout << "false" << std::endl;
			}
			else if(op == "number_of_component")
			{
				numCmp = inst.number_of_component();
				std::cout << numCmp << std::endl;
			}
			else if(op == "deleteGraph")
			{
				inst.deleteGraph();
			}
			else if(op == "isExistCycle")
			{
				isExistCycle_ans = inst.isExistCycle();
				if(isExistCycle_ans) std::cout << "true" << std::endl;
				else std::cout << "false" << std::endl;
			}
		}
    }
}

int main(int argc, char *argv[])
{
    Implement inst;
    tryTestCase(inst);
    return 0;
}
