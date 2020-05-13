#include <cstdint>
#include <string>
#include <iostream>

//This is a mess but I'll try to comment in a way that it's undersandable

//This bitboard is only use in order to not take count of unvalid value when we check 3 in a row or 2 in a row. 
struct bitboard128
{
	uint64_t part1, part2;
	bitboard128(uint64_t p1,uint64_t p2) : part1(p1),part2(p2){}
	operator bool()
	{
		return part1 != 0L || part2 != 0L;
	}
};
bitboard128 operator<<(const bitboard128& lhs, int rhs)
{
	bitboard128 results = lhs;
	while (rhs != 0)
	{
		results.part1 = results.part1 << 1;
		if (results.part2 & 0x8000000000000000)
			results.part1 |= 1;
		results.part2 = results.part2 << 1;
		rhs--;
	}
	return results;
}
bitboard128 operator>>(const bitboard128& lhs, int rhs)
{
	bitboard128 result = lhs;
	while (rhs != 0)
	{
		result.part2 = result.part2 >> 1;
		if (result.part1 & 0x1)
			result.part2 |= 0x8000000000000000;
		result.part1 = result.part1 >> 1;
		rhs--;
	}
	return result;
}

//bitboard128 operators
bitboard128 operator|(const bitboard128& lhs, const bitboard128& rhs)
{
	bitboard128 result = lhs;
	result.part2 |= rhs.part2;
	result.part1 |= rhs.part1;
	return result;
}
bitboard128 operator&(const bitboard128& lhs, const bitboard128& rhs)
{
	bitboard128 result = lhs;
	result.part2 &= rhs.part2;
	result.part1 &= rhs.part1;
	return result;
}
bitboard128 operator^(const bitboard128& lhs, const bitboard128& rhs)
{
	bitboard128 result = lhs;
	result.part2 ^= rhs.part2;
	result.part1 ^= rhs.part1;
	return result;
}
bitboard128 operator~(const bitboard128& rhs)
{
	bitboard128 result = rhs;
	result.part1 = ~result.part1;
	result.part2 = ~result.part2;
	return result;
}


//The actual bitboard where we put the move of the IA and its opponent. It's acutally a 80 bits data structure but in the game we use it as a 72 bits data structure
struct bitboard72 
{
	bitboard72( uint16_t s16 = 0, uint64_t s64 = 0) :part16bit(s16), part64bit(s64)
	{
	}
	uint16_t part16bit;
	uint64_t part64bit;
	

	operator bool()
	{
		return part64bit != 0L || part16bit != 0L;
	}
	void operator|=(const bitboard72& rhs)
	{
		this->part16bit |= rhs.part16bit;
		this->part64bit |= rhs.part64bit;
	}
	void operator&=(const bitboard72& rhs)
	{
		this->part16bit &= rhs.part16bit;
		this->part64bit &= rhs.part64bit;
	}
	void operator^=(const bitboard72& rhs)
	{
		this->part16bit ^= rhs.part16bit;
		this->part64bit ^= rhs.part64bit;
	}
};

//bitboard72 operators
bitboard72 operator<<(const bitboard72& lhs,int rhs)
{
	bitboard72 results = lhs;
	while (rhs != 0)
	{
		results.part16bit = results.part16bit << 1;
		if (results.part64bit & 0x8000000000000000)
			results.part16bit |= 1;
		results.part64bit = results.part64bit << 1;
		rhs--;
	}
	return results;
}
bitboard72 operator>>(const bitboard72& lhs,int rhs)
{
	bitboard72 result = lhs;
	while (rhs != 0)
	{
		result.part64bit = result.part64bit >> 1;
		if (result.part16bit & 0x1)
			result.part64bit |= 0x8000000000000000;
		result.part16bit = result.part16bit >> 1;
		rhs--;
	}
	return result;

}
bitboard72 operator|(const bitboard72& lhs,const bitboard72& rhs)
{
	bitboard72 result = lhs;
	result.part64bit |= rhs.part64bit;
	result.part16bit |= rhs.part16bit;
	return result;
}
bitboard72 operator&(const bitboard72& lhs,const bitboard72& rhs)
{
	bitboard72 result = lhs;
	result.part64bit &= rhs.part64bit;
	result.part16bit &= rhs.part16bit;
	return result;
}
bitboard72 operator^(const bitboard72& lhs, const bitboard72& rhs)
{
	bitboard72 result = lhs;
	result.part64bit^= rhs.part64bit;
	result.part16bit^= rhs.part16bit;
	return result;
}
bitboard72 operator~(const bitboard72& rhs)
{
	bitboard72 result = rhs;
	result.part16bit = ~result.part16bit;
	result.part64bit = ~result.part64bit;
	return result;
}


//Operator between bitboard72 and bitboard128
bitboard72 operator|(const bitboard72& lhs, const bitboard128& rhs)
{
	bitboard72 result = lhs;
	result.part64bit |= rhs.part2;
	result.part16bit |= rhs.part1;
	return result;
}
bitboard72 operator&(const bitboard72& lhs, const bitboard128& rhs)
{
	bitboard72 result = lhs;
	result.part64bit &= rhs.part2;
	result.part16bit &= rhs.part1;
	return result;
}
bitboard72 operator^(const bitboard72& lhs, const bitboard128& rhs)
{
	bitboard72 result = lhs;
	result.part64bit ^= rhs.part2;
	result.part16bit ^= rhs.part1;
	return result;
}



//Set the cell (row,col) of board to 1.
bitboard72 setCellState(bitboard72& board, uint8_t row, uint8_t col)
{
	bitboard72 newBit = bitboard72(0,1) << (row * 13 + col);
	return board | newBit;
}

/*
 Get the state of the cell (row,col) of board. 
 True if board(row,col) == 1 
 False if board(row,col) == 0
*/
bool getCellState(const bitboard72& board,uint8_t row, uint8_t col)
{
	bitboard72 isBit = bitboard72(0, 1) << (row * 13 + col);
	return isBit & board;
}

// Get the number of 1 in board
int countCell(const bitboard72& board)
{
	bitboard72 buffer = board;
	int count = 0;
	while (buffer.part64bit)
	{
		buffer.part64bit &= (buffer.part64bit - 1);
		count++;
	}
	while (buffer.part16bit)
	{
		buffer.part16bit &= (buffer.part16bit - 1);
		count++;
	}
	return count;
}

/* Return a 16 bits integer which contains the state of the *row* of *board*. 
If the state of *row* is | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 
getRow will return 0000100001000110. 
The 4 most significants bits are useless
*/
uint16_t getRow(const bitboard72& board, uint8_t row)
{
	if(row==5)
	{
		return board.part16bit;
	}
	else
	{
		return 0xFFF & board.part64bit >> 13 * row;
	}
}

//Display Method, not a good one, it's for the development 
std::wstring to_wstring(const bitboard72& board)
{
	std::wstring str = L"    1   2   3   4   5   6   7   8   9   10  11  12  \n";
	str += L"  +---+---+---+---+---+---+---+---+---+---+---+---+\n";
	for (int i = 0; i < 6; i++)
	{
		str += (std::to_wstring(i) + L" │");
		for (int j = 0; j < 12; j++)
		{
			if (getCellState(board, i, j))
				str += L" 1 │";
			else
				str += L" 0 │";
		}
		if (i == 5)
			str += L"\n  +---+---+---+---+---+---+---+---+---+---+---+---+\n";
		else
			str += L"\n  +---+---+---+---+---+---+---+---+---+---+---+---+\n";
	}
	str += L"\n";
	return str;
}
void displayConsole(std::wstring str)
{
	std::wcout<<str;
}

//Just a test for when I change some stuff, there are better way to test but I didn't want to focus on it right now
void displayTest()
{
	bitboard128 temp(0, 1);
	temp = temp << 1;
	std::cout << "2 = " << temp.part2 << std::endl;
	temp = bitboard128(1,0);
	temp = temp >> 1;
	std::cout << "9223372036854775808 = " << temp.part2 << std::endl;
	temp = bitboard128(1, 0);
	temp = temp >> 1;
	std::cout << "0 = " << temp.part1 << std::endl;
} 
