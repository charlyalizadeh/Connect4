#include "minmax.hpp"

using namespace std;

int main()
{
	/*for (int i = 3; i < 7; i++) 
	{
		std::vector<uint8_t> moveOrder = { 0,1,2,3,4,5,6,7,8,9,10,11 };
		std::cout << "-----TESTING DEPTH = " << i << "-----" << endl;
		std::cout << "NO ORDER : ...";
		for (int j = 0; j < 15; j++)
		{
			std::string filename = "test_" + to_string(i) + ".txt";
			Connect4AI ai(filename, moveOrder, i);
			ai.gameAlone();
		}
		std::cout << "done !" << endl;
		std::cout << "ORDER : ...";
		moveOrder = { 6,5,7,4,8,3,9,2,10,1,0,11 };
		for (int j = 0; j < 5; j++)
		{
			std::string filename = "test_" + to_string(i) + "_Ordered.txt";
			Connect4AI ai(filename, moveOrder, i);
			ai.gameAlone();
		}
		std::cout << "done !" << endl;
	}*/
	Connect4AI* ai = new Connect4AI();
	ai->game();
	return 0;
}
