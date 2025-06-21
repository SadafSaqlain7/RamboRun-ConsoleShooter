
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<iomanip>
#include<string>

using namespace std;

constintmap_height = 50;
constintmap_width = 50;

char map[map_height][map_width];
intramboheight;
intrambowidth;
intramboOnemove = 2;

int obstacles[30][2];
int bullets[10][2] = { { -1, -1 } };
intbulletCount = 0;

intgameSpeed = 1;
stringplayerName;
int score = 0;
int lives = 3;

stringgame_file = "game_scores.txt";

voidgamemenu();
void instructions();
voidhighScores();
voiddrawMap(intplayerscore, intplayerlives);
voiduserinput();
voidcreateObstacles();
voidgameprocess();
voidobstaclesmovement();
voidbulletsmovement();
void collision();
voidsaveScore(stringplayerName, intscore);

int main() {
	srand(time(0));
	ramboheight = map_height - 2;
	rambowidth = map_width / 2;
	charch;

	cout << "**********       JOHN RAMBO GAME        ***********" << endl;

	do {
		gamemenu();

		int choice;
		cout << "Enter Your Choice: ";
		cin >> choice;

		if (choice == 1) {

			system("cls");
			cout << endl << endl;
			cout << "Enter your name: ";
			cin >> playerName;

			while (lives > 0) {
				drawMap(score, lives);
				userinput();
				createObstacles();
				gameprocess();
				Sleep(100);
			}

			cout << "Game Over! Your scores are: " << score << endl;
			saveScore(playerName, score);
			exit(0);
		}
		elseif(choice == 2) {
			Sleep(750);
			system("cls");
			cout << endl << endl;
			highScores();
		}
		elseif(choice == 3) {
			Sleep(750);
			system("cls");
			instructions();
		}
		elseif(choice == 4) {

			Sleep(750);
			cout << "\n\nExit Successfully" << endl;
			exit(0);
		}
		else {
			cout << "Invalid Input" << endl;
		}

		cout << "Press 0 to Return to Menu: ";
		cin >> ch;
		Sleep(750);
		system("cls");
	} while (ch == '0');

	system("Pause");
	return 0;
}

voidgamemenu() {
	cout << " You Have got the following choices " << endl;
	cout << setw(19) << "1. Play" << endl;
	cout << setw(26) << "2. High scores" << endl;
	cout << setw(27) << "3. Instructions" << endl;
	cout << setw(19) << "5. Exit" << endl;
}

voidhighScores() {
	string highest1 = " ", highest2 = " ", highest3 = " ";
	int score1 = 0, score2 = 0, score3 = 0;
	int Score = 0;
	string Name;
	ifstreaminData;
	inData.open(game_file);
	if (inData.is_open()) {
		while (!inData.eof()) {
			inData >> Name >> Score;
			if (Score > score1) {
				score3 = score2;
				score2 = score1;
				score1 = Score;
				highest3 = highest2;
				highest2 = highest1;
				highest1 = Name;
			}
			elseif(Score < score1 && Score > score2) {
				score3 = score2;
				score2 = Score;
				highest3 = highest2;
				highest2 = Name;
			}
			elseif(Score < score1 && Score < score2 && Score > score3) {
				score3 = Score;
				highest3 = Name;
			}
		}
	}
	cout << "First Highest Score:    " << highest1 << "   " << score1 << endl;
	cout << "Second Highest Score:   " << highest2 << "   " << score2 << endl;
	cout << "Third Highest Score:    " << highest3 << "   " << score3 << endl << endl;
	cout << endl;
}

void instructions() {
	system("cls");
	cout << "Instructions: " << endl << endl;
	cout << "1. You have got 3 Lives." << endl;
	cout << "2. You will lose one life whenever you get hit by an obstacle. " << endl;
	cout << "3. Press S for shoot" << endl;
	cout << "4. Press '<' for left Movement." << endl;
	cout << "5. Press '>' for Right Movement." << endl;
	cout << endl;
}

voiddrawMap(intplayerscore, intplayerlives) {
	for (int i = 0; i <map_height; ++i) {
		for (int j = 0; j <map_width; ++j) {
			map[i][j] = ' ';
		}
	}

	for (int i = 0; i <map_height; ++i) {
		map[0][i] = '-';
		map[map_height - 1][i] = '-';
		map[i][0] = '*';
		map[i][map_width - 1] = '*';
	}

	if (ramboheight >= 1 && rambowidth<map_height - 1 && rambowidth >= 1 && rambowidth<map_width - 1) {
		map[ramboheight][rambowidth] = 'R';
	}

	for (int i = 0; i < 30; ++i) {
		if (obstacles[i][0] != -1) {
			for (int j = obstacles[i][1]; j < obstacles[i][1] + 10; ++j) {
				if (obstacles[i][0] >= 1 && obstacles[i][0] <map_height - 1 && j >= 1 && j <map_width - 1) {
					map[obstacles[i][0]][j] = '&';
				}
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		if (bullets[i][0] != -1) {
			if (bullets[i][0] >= 1 && bullets[i][0] <map_height - 1 && bullets[i][1] >= 1 && bullets[i][1] <map_width - 1) {
				map[bullets[i][0]][bullets[i][1]] = 'o';
			}
		}
	}

	system("cls");
	for (int i = 0; i <map_height; ++i) {
		for (int j = 0; j <map_width; ++j) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Score: " << playerscore << endl;
	cout << "Lives: " << playerlives << endl;
}

voiduserinput() {
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case'<':
			if (rambowidth> 1)
				rambowidth -= ramboOnemove;
			break;
		case'>':
			if (rambowidth<map_width - 3)
				rambowidth += ramboOnemove;
			break;
		case's':
			bullets[bulletCount % 10][0] = ramboheight;
			bullets[bulletCount % 10][1] = rambowidth;
			bulletCount++;
			break;
		}
	}
}

voidcreateObstacles() {
	if (rand() % 10 == 0) {
		intrandomobstacle = rand() % (map_width - 10) + 1;
		for (int i = 0; i < 30; ++i) {
			if (obstacles[i][0] == -1) {
				obstacles[i][0] = 1;
				obstacles[i][1] = randomobstacle;
				break;
			}
		}
	}
}

voidgameprocess() {
	obstaclesmovement();
	bulletsmovement();
	collision();
}

voidobstaclesmovement() {
	for (int i = 0; i < 30; ++i) {
		if (obstacles[i][0] != -1) {
			obstacles[i][0]++;
			if (obstacles[i][0] == map_height - 1) {
				obstacles[i][0] = -1;
				obstacles[i][1] = -1;
			}
		}
	}
}

voidbulletsmovement() {
	for (int i = 0; i < 10; ++i) {
		if (bullets[i][0] != -1) {
			bullets[i][0]--;
			if (bullets[i][0] == 0) {
				bullets[i][0] = -1;
				bullets[i][1] = -1;
			}
		}
	}
}

void collision() {
	for (int i = 0; i < 30; ++i) {
		if (obstacles[i][0] != -1 && obstacles[i][0] == ramboheight&&rambowidth >= obstacles[i][1] && rambowidth <= obstacles[i][1] + 9) {
			lives--;
			if (lives <= 0) {
				cout << "Game Over! Your scores are: " << score << endl;
				saveScore(playerName, score);
				exit(0);
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		if (bullets[i][0] != -1) {
			for (int j = 0; j < 30; ++j) {
				if (obstacles[j][0] != -1 && obstacles[j][0] == bullets[i][0] && bullets[i][1] >= obstacles[j][1] && bullets[i][1] <= obstacles[j][1] + 9) {
					obstacles[j][0] = -1;
					obstacles[j][1] = -1;
					bullets[i][0] = -1;
					bullets[i][1] = -1;
					score += 10;
				}
			}
		}
	}
}

voidsaveScore(stringplayerName, intscore) {
	ofstream file(game_file, ios::app);
	if (file.is_open()) {
		file << playerName << " " << score << endl;
		file.close();
	}
}
T




