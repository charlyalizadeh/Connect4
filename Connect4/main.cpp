#define OLC_PGE_APPLICATION
#include "minmax.hpp"

int main()
{

    std::wcout << "Saisissez la profondeur : ";
    int profondeur;
    std::wcin >> profondeur;
    Connect4AI* game = new Connect4AI(profondeur);
    std::wcout << "1.AI vs HUMAN\n2.AI vs AI\n3.Simulate games\n";
    int choice;
    std::wcin >> choice;
    switch(choice)
    {
        case 1:
            game->gameMT();
            break;
        case 2:
            std::wcout << "Profondeur AI 1 : ";
            int p1;
            std::wcin >> p1;
            std::wcout << "Profondeur AI 1 : ";
            int p2;
            std::wcin >> p2;
            game->gameAlone(p1,p2);
            break;
        case 3:
            game->simulateGames();
            break;
    }
	game->simulateGames();
	return 0;
}
