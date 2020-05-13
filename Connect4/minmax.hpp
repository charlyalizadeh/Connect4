#include "bitboard72.hpp"
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <future>

/*Links that helped me : 
http://www.informatik.uni-trier.de/~fernau/DSL0607/Masterthesis-Viergewinnt.pdf
http://fabpedigree.com/james/connect4.htm
https://roadtolarissa.com/connect-4-ai-how-it-works/
https://towardsdatascience.com/creating-the-perfect-connect-four-ai-bot-c165115557b0
http://blog.gamesolver.org/
https://www.chessprogramming.org/Main_Page
*/


class Connect4AI
{
public:
	Connect4AI(int _depth = 6, std::string _filename = "trash.txt", std::vector<uint8_t> _moveOrder = { 6,5,7,4,8,3,9,2,10,1,0,11 }) :m_depth(_depth), m_filename(_filename), m_moveOrder(_moveOrder) {	}
	
	//AI vs Human
	void gameMT()
	{
		//char winner = ' ';
		m_possibleCoord = { 5,5,5,5,5,5,5,5,5,5,5,5 };
		bitboard72 board_AI(0, 0);
		bitboard72 board_Opp(0, 0);
		std::wcout << L"Voulez vous commencer ? [y/n]\n";
		wchar_t choiceStart;
		std::wcin >> choiceStart;
		if (choiceStart == 'n')
		{
			board_AI = results(board_AI, bestMoveMT(board_AI, board_Opp, m_depth, m_possibleCoord));
		}
		int choice = -1;
		displayGameConsole(board_AI, board_Opp);
		while (!isTerminal(board_AI) && !isTerminal(board_Opp))
		{
			do
			{
				std::wcout << L"Saisissez un coup : \n";
				std::wcin >> choice;
			} while (choice < 1 || choice >12  && getRow(board_AI & board_Opp, 0));
			board_Opp = results(board_Opp, choice - 1);
			if (isTerminal(board_Opp)) {
				std::wcout << "X Won";
				/*winner = 'X';*/
				break;
			}
			displayGameConsole(board_AI, board_Opp);
			board_AI = results(board_AI, bestMoveMT(board_AI, board_Opp, m_depth, m_possibleCoord));
			displayGameConsole(board_AI, board_Opp);
			if (isTerminal(board_AI))
			{
				std::wcout << "O Won";
				/*winner = 'O';*/
				break;
			}
		}
	}
	void game()
	{
		//char winner = ' ';
		m_possibleCoord = { 5,5,5,5,5,5,5,5,5,5,5,5 };
		bitboard72 board_AI(0, 0);
		bitboard72 board_Opp(0, 0);
		std::wcout << L"Voulez vous commencer ? [y/n]\n";
		wchar_t choiceStart;
		std::wcin >> choiceStart;
		if (choiceStart == 'n')
		{
			board_AI = results(board_AI, bestMove(board_AI, board_Opp, m_depth));
		}
		int choice = -1;
		displayGameConsole(board_AI, board_Opp);
		while (!isTerminal(board_AI) && !isTerminal(board_Opp))
		{
			do
			{
				std::wcout << L"Saisissez un coup : \n";
				std::wcin >> choice;
			} while (choice < 1 || choice >12 && getRow(board_AI & board_Opp, 0));
			board_Opp = results(board_Opp, choice - 1);
			if (isTerminal(board_Opp)) {
				std::wcout << "X Won";
				/*winner = 'X';*/
				break;
			}
			displayGameConsole(board_AI, board_Opp);
			board_AI = results(board_AI, bestMove(board_AI, board_Opp, m_depth));
			displayGameConsole(board_AI, board_Opp);
			if (isTerminal(board_AI))
			{
				std::wcout << "O Won";
				/*winner = 'O';*/
				break;
			}
		}
	}

	//AI vs AI (vs itself)
	void gameAlone(int depth1 = 6, int depth2 = 6,bool display = true)
	{
		m_possibleCoord = { 5,5,5,5,5,5,5,5,5,5,5,5 };
		bitboard72 board_AI(0, 0);
		bitboard72 board_Opp(0, 0);
		m_movesSequences.clear();
		m_times.clear();
		uint8_t move;
		char winner = '.';
		while (!isTerminal(board_AI) && !isTerminal(board_Opp))
		{
			move = bestMoveMT(board_Opp, board_AI, depth1, m_possibleCoord);
			m_movesSequences.push_back(move);
			board_Opp = results(board_Opp, move);
			if (display)
				displayGameConsole(board_AI, board_Opp);
			if (isTerminal(board_Opp)) {
				//td::wcout << "X Won";
				winner = 'X';
				break;
			}
			move = bestMoveMT(board_AI, board_Opp, depth2, m_possibleCoord);
			m_movesSequences.push_back(move);
			board_AI = results(board_AI, move);
			if (display)
				displayGameConsole(board_AI, board_Opp);
			if (isTerminal(board_AI)) {
				//std::wcout << "O Won";
				winner = 'O';
				break;
			}
		}
		savePartyData(winner);
	}

	//Simulate party of AI vs AI from depth 1 to depth 6
    void simulateGames()
    {
       for(int i = 1;i<7;i++)
       {
         for(int j = 1;j<7;j++)
         {
           std::cout<<"------TESTING DEPTH : " + std::to_string(i) + " vs " + std::to_string(j) + "------------"<<std::endl;
           std::cout<<"No order : ";
           for(int k = 0;k<3;k++)
           {
             m_moveOrder = std::vector<uint8_t>{0,1,2,3,4,5,6,7,8,9,10,11};
             m_filename = "test_" +  std::to_string(i) + "." + std::to_string(j) + ".txt";
             gameAlone(i,j,false);
             std::cout<<std::to_string(k);
           }
           std::cout<<std::endl<<"Ordered : ";
           for(int k = 0;k<3;k++)
           {
             m_moveOrder = std::vector<uint8_t>{6,5,7,4,8,3,9,2,10,1,0,11};
             m_filename = "test_" +  std::to_string(i) + "." + std::to_string(j) + "_Ordered" + ".txt";
             gameAlone(i,j,false);
             std::cout<< std::to_string(k);
           }
           std::cout<<std::endl;
         }
       }
    }



private:
	//--------------------VARIABLES--------------------------
	std::vector<int> m_possibleCoord;//We store the possible coordinates by row so we don't need to calculate each time we want to make move
	std::vector<uint8_t> m_moveOrder;//Order of the move check
	std::vector<int> m_times;
	std::chrono::time_point<std::chrono::system_clock>m_start, m_end;
	std::string m_filename;
	std::vector<uint8_t> m_movesSequences;
	int m_depth;

	//--------------------METHODS--------------------------
	//Return a value corresponding to the quality of the board for the player which own the *board1*. 
	int heuristic(bitboard72 board1, bitboard72 board2, int depth, int coeff3 = 5,int coeff2 = 1)
	{
		if (isTerminal(board1))
			return 900000 + depth;
		if (isTerminal(board2))
			return -900010 - depth;
		else
		{
			return ((hasFollow3(board1, board2)) * coeff3 + hasFollow2(board1, board2)) * coeff2 - ((hasFollow3(board2, board1) * coeff3 + hasFollow2(board2, board1) * coeff2));
		}

	}
	//Check if *board* has four 1 in a row,column or diagonal
	bool isTerminal(bitboard72 board)
	{
		int directions[4] = { 1,13,12,14 };
		for (int i = 0; i < 4; i++)
		{
			if (board & board >> directions[i] & board >> directions[i] * 2 &  board>>directions[i] * 3)
				return true;
		}
		return false;
	}
	//The two following methods are little bit messy. They search the number of sequences that aren't blocked by the opponent. 
	//Return the number of good three 1 in a row,column and diagonal
	int hasFollow3(bitboard72 board1,bitboard72 board2)
	{
		int directions[4] = { 1,13,12,14 };
		int count = 0;
		bitboard128 preventBord(0xFFFFFFFFFFFFE001, 0x8004002001000);//This bitboard prevent for value not in the in the board to be count as valid
		for (int i = 0; i < 4; i++)
		{
			bitboard72 test1 = ~board2 & (board1 >> directions[i])& (board1 >> directions[i] * 2)& (board1 >> directions[i] * 3) & ~preventBord;                    // |   | O | O | O |
			bitboard72 test2 = board1 & (~(board2 >> directions[i]))& (board1 >> directions[i] * 2)& (board1 >> directions[i] * 3)& ~(preventBord>>directions[i]);  // | O |   | O | O |
			bitboard72 test3 = board1 & (board1 >> directions[i])& (~(board2 >> directions[i] * 2))& (board1 >> directions[i] * 3)& ~(preventBord>>directions[i]*2);// | O | O |   | O |
			bitboard72 test4 = board1 & (board1 >> directions[i])& (board1 >> directions[i] * 2)& (~(board2 >> directions[i] * 3))& ~(preventBord>>directions[i]*3);// | O | O | O |   |
			count += countCell(test1 | test2 | test3 | test4);
		}
		return count;
	}
	//Return the number of good two 1 in a row, column, and diagonal
	int hasFollow2(bitboard72 board1, bitboard72 board2)
	{
		int directions[4] = { 1,13,12,14 };
		int count = 0;
		bitboard128 preventBord(0xFFFFFFFFFFFFE001, 0x8004002001000);//This bitboard prevent for value not in the int he board to be count has valid
		for (int i = 0; i < 4; i++)
		{
				bitboard72 test1 = (board1 & (board1 >> directions[i]))& (~((board2 >> directions[i] * 2) | (board2 >> directions[i] * 3))) & ~((preventBord >> directions[i] * 2) | (preventBord >> directions[i] * 3));   // | O | O |   |   |
				bitboard72 test2 = ((board1 >> directions[i])& (board1 >> directions[i] * 2))& (~((board2) | (board2 >> directions[i] * 3))) & ~((preventBord) | (preventBord >> directions[i] * 3));						// |   | O | O |   |
				bitboard72 test3 = (~(board2 | (board2 >> directions[i])))& ((board1 >> directions[i] * 2)& (board1 >> directions[i] * 3)) & ~((preventBord) | (preventBord >> directions[i]));                             // |   |   | O | O |
				bitboard72 test4 = ((board1 & (board1 >> directions[i] * 3))& (~((board2 >> directions[i]) | (board2 << directions[i] * 2)))) & ~((preventBord >> directions[i]) | (preventBord >> directions[i] * 2));     // | O |   |   | O |
				bitboard72 test5 = ((board1 >> directions[i])& (board1 >> directions[i] * 3))& (~(board2 | (board2 >> directions[i] * 2))) & ~((preventBord) | (preventBord >> directions[i] * 2));						    // | O |   | O |   |
				bitboard72 test6 = ((board1) & (board1 >> directions[i] * 2))& (~((board2 >> directions[i]) | (board2 >> directions[i] * 3))) & ~((preventBord >> directions[i]) | (preventBord >> directions[i] * 3));		// |   | O |   | O |
				count += countCell(test1 | test2 | test3 | test4 | test5 | test6);
		}
		return count;
	}

	//-----WITHOUT MULTI THREADING-------
	//Return a bitboard equal to board with a 1 in the highest coordinates of the column *col*
	bitboard72 results(bitboard72 board, uint8_t col)
	{
		uint8_t temp = m_possibleCoord[col];
		m_possibleCoord[col]--;
		return setCellState(board, temp, col);
	}
	//The minmax algorithm
	int minmax(bitboard72 board_AI, bitboard72 board_Opp, int depth, int alpha, int beta, bool player)
	{
		//displayConsole(to_wstring(board_AI | board_Opp));
		if (depth == 0 || isTerminal(board_AI) || isTerminal(board_Opp) || countCell(board_AI | board_Opp)>=42)
			return heuristic(board_AI, board_Opp,depth); 

		if (player)
		{
			int value = -1000000;
			uint16_t childs = getRow(board_AI | board_Opp, 0);
			for (uint8_t i = 0; i < 12; i++)
			{
				if (!((1 << m_moveOrder[i]) & childs))
				{
					value = std::max(value, minmax(results(board_AI, m_moveOrder[i]), board_Opp, depth - 1, alpha, beta, !player));
					m_possibleCoord[m_moveOrder[i]]++;
					if (value >= beta)
						return value;
					alpha = std::max(alpha, value);
				}
			}
			return value;
		}
		else
		{
			int value = 1000000;
			uint16_t childs = getRow(board_AI | board_Opp, 0);
			for (uint8_t i = 0; i < 12; i++)
			{
				if (!((1 << m_moveOrder[i]) & childs))
				{
					value = std::min(value, minmax(board_AI, results(board_Opp, m_moveOrder[i]), depth - 1, alpha, beta, !player));
					m_possibleCoord[m_moveOrder[i]]++;
					if (value <= alpha)
						return value;
					beta = std::min(beta, value);
				}
			}
			return value;
		}



	}
	//Return the best move for the player who own *board_AI* against the player who owns *board_opp*
	uint8_t bestMove(bitboard72 board_AI, bitboard72 board_Opp,int depth)
	{
		m_start = std::chrono::system_clock::now();
		int bestMove = -1, bestValue = -1000000; 
		uint16_t childs = getRow(board_AI | board_Opp, 0);
		for (int i = 0; i < 12; i++)
		{
			if (!((1 << m_moveOrder[i]) & childs))
			{
				int value = minmax(results(board_AI, m_moveOrder[i]), board_Opp, depth, -1000000, 1000000, false);
				std::wcout << L"Move : " << m_moveOrder[i] << L" Value " << value << std::endl;
				m_possibleCoord[m_moveOrder[i]]++;
				if (value > bestValue)
				{
					bestMove = m_moveOrder[i];
					bestValue = value;
				}
			}
		}
		m_end = std::chrono::system_clock::now();
		std::wcout << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() << std::endl;
		m_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count());
		std::wcout << "Coup : " << std::to_wstring(bestMove + 1) << std::endl;
		return bestMove;
	}


	//-----MULTI THREADING-------
	//Return a bitboard equal to board with a 1 in the highest coordinates of the column *col*
	bitboard72 resultsMT(bitboard72 board, uint8_t col, std::vector<int>& possibleCoord)
	{
		uint8_t temp = possibleCoord[col];
		possibleCoord[col]--;
		return setCellState(board, temp, col);
	}
	//The minmax algorithm
	int minmaxMT(bitboard72 board_AI, bitboard72 board_Opp, int depth, int alpha, int beta, bool player, std::vector<int>& possibleCoord)
	{
		if (depth == 0 || isTerminal(board_AI) || isTerminal(board_Opp) || countCell(board_AI | board_Opp) >= 42)
			return heuristic(board_AI, board_Opp, depth);

		if (player)
		{
			int value = -1000000;
			uint16_t childs = getRow(board_AI | board_Opp, 0);
			for (uint8_t i = 0; i < 12; i++)
			{
				if (!((1 << m_moveOrder[i]) & childs))
				{
					value = std::max(value, minmaxMT(resultsMT(board_AI, m_moveOrder[i], possibleCoord), board_Opp, depth - 1, alpha, beta, !player, possibleCoord));
					possibleCoord[m_moveOrder[i]]++;
					if (value >= beta)
						return value;
					alpha = std::max(alpha, value);
				}
			}
			return value;
		}
		else
		{
			int value = 1000000;
			uint16_t childs = getRow(board_AI | board_Opp, 0);
			for (uint8_t i = 0; i < 12; i++)
			{
				if (!((1 << m_moveOrder[i]) & childs))
				{
					value = std::min(value, minmaxMT(board_AI, resultsMT(board_Opp, m_moveOrder[i], possibleCoord), depth - 1, alpha, beta, !player, possibleCoord));
					possibleCoord[m_moveOrder[i]]++;
					if (value <= alpha)
						return value;
					beta = std::min(beta, value);
				}
			}
			return value;
		}



	}
	//Return the best move for the player who own *board_AI* against the player who owns *board_opp*
	uint8_t bestMoveMT(bitboard72 board_AI, bitboard72 board_Opp, int depth, std::vector<int> possibleCoord)
	{
		m_start = std::chrono::system_clock::now();
		int bestMove = -1, bestValue = -1000000;
		uint16_t childs = getRow(board_AI | board_Opp, 0);
		std::vector<std::future<int>> futures;
		std::vector<int> index;
		for (int i = 0; i < 12; i++)
		{
			if (!((1 << m_moveOrder[i]) & childs))
			{
				std::vector<int> possibleCoordTemp = possibleCoord;
				futures.push_back(std::async(std::launch::async, 
					[this](bitboard72 board_AI, bitboard72 board_Opp, int depth, int alpha, int beta, bool player, std::vector <int> possibleCoord)
					{return minmaxMT(board_AI, board_Opp, depth, alpha, beta, player, possibleCoord); },
						resultsMT(board_AI, m_moveOrder[i], possibleCoordTemp), board_Opp, depth, -1000000, 1000000, false, possibleCoordTemp));
				index.push_back(m_moveOrder[i]);
			}
		}
		int i = 0;
		for (auto &a : futures)
		{
			int temp = a.get();
			std::wcout << L"Move : " << index[i] << L" Value : " << temp << std::endl;
			if (temp > bestValue) {
				bestMove = index[i];
				bestValue = temp;
			}
			i++;
			std::chrono::time_point<std::chrono::system_clock>m_temp = std::chrono::system_clock::now();
			if (std::chrono::duration_cast<std::chrono::milliseconds>(m_temp - m_start).count() > 8500)
			{
				if (bestValue < -900000)//Kind of a hopeless situation here
					bestMove = index[i];
				break;
			}
		}
		m_end = std::chrono::system_clock::now();
		std::wcout << std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() << std::endl;
		m_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count());
		std::wcout << "Coup : " << std::to_wstring(bestMove + 1) << std::endl;
		return bestMove;
	}

	//Save times, moves and winner of the party in a txt/csv file
	void savePartyData(char winner)
	{
		std::ofstream wStream(m_filename.c_str(), std::ios::app);
		if (wStream)
		{
			for (int i = 0; i < m_times.size(); i++)
				wStream << std::to_string(m_times[i]) << ';';

			wStream << std::endl;

			for (int i = 0; i < m_movesSequences.size(); i++)
				wStream << std::to_string(m_movesSequences[i]) << ';';

			wStream << std::endl << winner << ';' << std::endl;
		}
	}
	//Display the game in the console. AI = O, Opponent = X
	void displayGameConsole(bitboard72 board_AI, bitboard72 board_Opp)
	{
		std::wstring str = L" 1  2  3  4  5  6  7  8  9  10  11 12\n";
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (getCellState(board_AI, i, j))
					str += L" O ";
				else if (getCellState(board_Opp, i, j))
					str += L" X ";
				else
					str += L" . ";
			}
			str += L"\n";
		}
		str += L"\n";
		displayConsole(str);
	}

	
};




