#include <iostream>
#include "RMQ.h"

int main()
{
	RMQ myRMQ = RMQ(100000);
	myRMQ.preProcess();
	std::cout << "V1 min from index 0 to 50000 is: " << myRMQ.queryV1(0, 50000) << std::endl;
	std::cout << "V2 min from index 0 to 50000 is: " << myRMQ.queryV2(0, 50000) << std::endl;
	std::cout << "V3 min from index 0 to 50000 is: " << myRMQ.queryV3(0, 50000) << std::endl;
	std::cout << "V4 min from index 0 to 50000 is: " << myRMQ.queryV4(0, 50000) << std::endl;

	std::cout << "V1 min from index 50001 to 99999 is: " << myRMQ.queryV1(50001, 99999) << std::endl;
	std::cout << "V2 min from index 50001 to 99999 is: " << myRMQ.queryV2(50001, 99999) << std::endl;
	std::cout << "V3 min from index 50001 to 99999 is: " << myRMQ.queryV3(50001, 99999) << std::endl;
	std::cout << "V4 min from index 50001 to 99999 is: " << myRMQ.queryV4(50001, 99999) << std::endl;
	return 0;
}