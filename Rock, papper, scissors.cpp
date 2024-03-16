using namespace std;
#include <iostream>
#include <string>
#include <cstdlib>

enum enChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };
struct stRoundInfo
{
	short RoundNumber = 1;
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = " ";
};
struct stGameInfo
{
	short GameRounds = 0;
	short PLayerWinTimes = 0;
	short ComputerWinTimes = 0;
	int DrawTimes = 0;
	enWinner GameWinner;
	string GameWinnerName = " ";
};

short ReadHowManyRounds()
{
	short HowManyRounds = 1;
	do
	{
		cout << "How many rounds 1 to 10 " << endl;
		cin >> HowManyRounds;

		while (!cin) {
			cin.clear(); 
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "How many rounds 1 to 10 " << endl;
			cin >> HowManyRounds;
		}

	} while (HowManyRounds < 0);

	return HowManyRounds;
}

int RandomNumber(int From, int To)
{
	int Random = rand() % (To - From + 1) + From;

	return Random;
}

enChoice GetComputerChoice()
{
	return (enChoice)RandomNumber(1, 3);
}

enChoice ReadPLayerChoice()
{
	short Choice = 1;

	do
	{
		cout << "\nEnter your choice : Rock[1], Paper[2], Scissors[3] ?\n";
		cin >> Choice;

		while (!cin) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Please enter a valid choice: " << endl;
			cin >> Choice;
		}

	} while (Choice < 1 || Choice > 3);

	return (enChoice)Choice;
}

string NameWinner(enWinner Winner)
{
	string arrWinnerNames[3] = { "Player", "Computer", "Draw" };

	return arrWinnerNames[Winner - 1];
}

string NameChoices(enChoice Choices)
{
	string arrChoicesName[3] = { "Rock", "Paper", "Scissors" };

	return arrChoicesName[Choices - 1];
}

enWinner WhoWonTheRound(stRoundInfo Roundinfo)
{
	if (Roundinfo.PlayerChoice == Roundinfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (Roundinfo.PlayerChoice)
	{
	case enChoice::Paper:
		if (Roundinfo.ComputerChoice == enChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enChoice::Rock:
		if (Roundinfo.ComputerChoice == enChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enChoice::Scissors:
		if (Roundinfo.ComputerChoice == enChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}
	// if you reached here then the player won
	return enWinner::Player;
}

void SetScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Computer:
		system("color 4F");    // red screen
		cout << "\a";
		break;

	case enWinner::Player:
		system("color 2F");  // green screen
		break;

	case enWinner::Draw:
		system("color 6F");  // yellow screen
	}
}

void PrintRoundResult(stRoundInfo Roundinfo)
{
	cout << "\nRound [" << Roundinfo.RoundNumber << "]" << endl;
	cout << "Player choice : " << NameChoices(Roundinfo.PlayerChoice) << endl;
	cout << "Computer choice : " << NameChoices(Roundinfo.ComputerChoice) << endl;
	cout << "Round winner : " << NameWinner(Roundinfo.Winner) << endl;
	cout << "------------------------------------------------------------------" << endl;

	SetScreenColor(Roundinfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (PlayerWinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameInfo FillGameResults(int HowManyRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameInfo Gameinfo;

	Gameinfo.GameRounds = HowManyRounds;
	Gameinfo.PLayerWinTimes = PlayerWinTimes;
	Gameinfo.ComputerWinTimes = ComputerWinTimes;
	Gameinfo.DrawTimes = DrawTimes;
	Gameinfo.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes, DrawTimes);
	Gameinfo.GameWinnerName = NameWinner(Gameinfo.GameWinner);

	return Gameinfo;
}

stGameInfo PlayGame(int HowManyRounds)
{
	stRoundInfo Roundinfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (int Round = 1; Round <= HowManyRounds; Round++)
	{
		cout << "\nRound [" << Round << "] begins ";
		Roundinfo.RoundNumber = Round;
		Roundinfo.PlayerChoice = ReadPLayerChoice();
		Roundinfo.ComputerChoice = GetComputerChoice();
		Roundinfo.Winner = WhoWonTheRound(Roundinfo);
		Roundinfo.WinnerName = NameWinner(Roundinfo.Winner);

		// increasw The won times for : player/computer/draw
		if (Roundinfo.Winner == enWinner::Player)
		{
			PlayerWinTimes++;
		}
		else if (Roundinfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
			DrawTimes++;

		PrintRoundResult(Roundinfo);
	}

	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = " ";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}

	return t;
}

void ShowFinalGameResult(stGameInfo Gameinfo)
{
	cout << endl;
	cout << Tabs(2) << "------------[ GAME RESULTS ]-----------------------" << endl;
	cout << Tabs(2) << "Game rounds : " << Gameinfo.GameRounds << endl;
	cout << Tabs(2) << "Player won times : " << Gameinfo.PLayerWinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << Gameinfo.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times : " << Gameinfo.DrawTimes << endl;
	cout << Tabs(2) << "Game winner : " << Gameinfo.GameWinnerName << endl;
	cout << Tabs(2) << "---------------------------------------------------" << endl;
}

void ShowGameover()
{
	cout << endl;
	cout << Tabs(2) << "--------------------------------------------------------------------" << endl;
	cout << Tabs(2) << "                      +++ Game Over +++                             " << endl;
	cout << Tabs(2) << "--------------------------------------------------------------------" << endl;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameInfo Gameinfo = PlayGame(ReadHowManyRounds());
		ShowGameover();
		ShowFinalGameResult(Gameinfo);

		cout << "\nDo you want to play again ? , (Y) for yes / (N) for no ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	StartGame();
}