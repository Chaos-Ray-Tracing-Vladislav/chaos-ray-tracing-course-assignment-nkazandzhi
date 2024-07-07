#include <fstream>
#include "CRTVector.h"
#include <vector>
#include <iostream>
#include "CRTTriangle.h"

int main()
{
	//Task 2
	//Task 2.1
	CRTVector A(3.5, 0, 0);
	CRTVector B(1.75, 3.5, 0);

	//cross(A,B)
	CRTVector C=A.cross(B);
	std::cout << "A: " << A.to_string() <<"B: " <<B.to_string() << "cross(A,B)=" << C.to_string();
	std::cout << "\n";

	//Task 2.2
	CRTVector F(3, -3, 1);
	CRTVector D(4, 9, 3);
	//cross(F,D)
	CRTVector E = F.cross(D);
	std::cout << "F: " << F.to_string() << "D: " << D.to_string() << "cross(F,D)=" << E.to_string();
	std::cout << "\n";

	//Task 2.3
	//area of the parallelogram==cross product
	//area of the parallelogram(F, D)==||cross(F,D)||

	std::cout << "F: " << F.to_string() << "D: " << D.to_string() << "Area of the parallelogram(F,D)=" << E.length() << "\n";
	std::cout << "\n";
	//Task 2.4
	//area of the parallelogram(F, D)
	CRTVector H(-12, 12, -4);
	//cross(G,V)
	CRTVector I = F.cross(H);
	std::cout << "F: " << F.to_string() << "H: " << H.to_string() << "Area of the parallelogram(F,H)=" << I.to_string();
	std::cout << "\n";

	//Task 3
	//Task 3.1
	CRTTriangle triangleA({ -1.75,-1.75,-3 }, { 1.75,-1.75,-3 }, { 0,1.75,-3 });
	std::cout << "Triangle A: " << triangleA.to_string();

	std::cout << "Triangle A normal: " << triangleA.get_normal();
	std::cout << "\n";

	//Task 3.2
	CRTTriangle triangleB({ 0,0,-1 }, { 1,0,1 }, { -1,0,1 });
	std::cout << "Triangle B: " << triangleB.to_string();

	std::cout << "Triangle B normal: " << triangleB.get_normal();
	std::cout << "\n";

	//Task 3.3
	CRTTriangle triangleC({ 0.56,1.11,1.23}, { 0.44,-2.368,-0.54 }, { -1.56,0.15,-1.92 });
	std::cout << "Triangle C: " << triangleC.to_string();

	std::cout << "Triangle C normal: " << triangleC.get_normal();
	std::cout << "\n";

	//Task 3.4 calculate areas:
	std::cout << "Areas: " << "\n";
	std::cout << "Triangle A: " << triangleA.get_area() << std::endl;
	std::cout << "Triangle B: " << triangleB.get_area() << std::endl;
	std::cout << "Triangle C: " << triangleC.get_area() << std::endl;

	return 0;
}