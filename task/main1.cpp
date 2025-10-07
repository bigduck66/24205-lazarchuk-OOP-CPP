#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout <<  "Hello world!" << "\n";
	
	std::cout << Modulel::getMyName() << "\n";
	std::cout << Module2::getMyName() << "\n";

	using namespace Modulel;
	std::cout << getMyName() << "\n"; // (A)
	std::cout << Module2::getMyName() << "\n";

	//using namespace Module2; // (B)
	//std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

	using Module2::getMyName;//нет ошибки потому что в заголовочном файле нет строки namespace Module2 мы берем именно эту функцию
	std::cout << getMyName() << "\n"; // (D)

	std::cout << Module3::getMyName() << "\n";
}