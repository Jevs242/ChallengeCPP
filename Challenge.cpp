#include "Challenge.h"

#include <array> 
#include <chrono>
#include <algorithm>
#include <vector>

int main()
{

	auto t1 = std::chrono::high_resolution_clock::now();

	Challenge Challenge;
	//Challenge.day1();
	//Challenge.day2_1();
	//Challenge.day3_1();
	//Challenge.day4();
	//Challenge.day4_2();
	Challenge.day5();
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "test function took "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n";

	return 0;
}

#pragma region Day 2

void Challenge::day1()
{
	std::ifstream file("day1.txt");
	std::string str;
	std::vector<int> p;

	int number = 0;
	while (std::getline(file, str))
	{
		if (str == "")
		{
			p.push_back(number);
			number = 0;
		}
		else
		{
			number += std::stoi(str);
		}
	}
	std::sort(p.begin(), p.end(), [](int& a, int& b) { return a > b; });
	std::cout << p[0] << std::endl;

	int total = 0;

	for (int i = 0; i < 3; i++)
	{
		total += p[i];
	}

	std::cout << total << std::endl;

}

void Challenge::day2_1()
{
	std::ifstream file("day2.txt");
	std::string str;
	int points = 0;

	while (std::getline(file, str))
	{
		int player = ConvertChatToInt(str[2]);
		int oponent = ConvertChatToInt(str[0]);

		player = FixPlay(player, oponent, points);

		if (player == 2)
		{
			points += 3;
		}
		else if (player == 3)
		{
			points += 6;

		}

		points += player;
	}

	std::cout << points << std::endl;
}

void Challenge::day2_2()
{
	std::ifstream file("day2.txt");
	std::string str;
	int points = 0;

	while (std::getline(file, str))
	{
		int player = ConvertChatToInt(str[2]);
		int oponent = ConvertChatToInt(str[0]);

		player = FixPlay(player, oponent, points);

		points += player;
	}

	std::cout << points << std::endl;
}

int Challenge::ConvertChatToInt(char letter)
{
	if (letter == 'A' || letter == 'X')
		return 1;
	else if (letter == 'B' || letter == 'Y')
		return 2;
	else if (letter == 'C' || letter == 'Z')
		return 3;
	else
		return 0;
}

int Challenge::FixPlay(int player, int oponent, int& points)
{
	int fix = 0;
	if (player == 1)
	{
		if (oponent == 1)
		{
			fix = 3;
		}
		else if (oponent == 2)
		{
			fix = 1;
		}
		else if (oponent == 3)
		{
			fix = 2;
		}
	}
	else if (player == 2)
	{
		fix = oponent;
		points += 3;
	}
	else if (player == 3)
	{
		if (oponent == 1)
		{
			fix = 2;
		}
		else if (oponent == 2)
		{
			fix = 3;
		}
		else if (oponent == 3)
		{
			fix = 1;
		}
		points += 6;
	}
	return fix;
}

#pragma endregion

#pragma region Day 3

void Challenge::day3()
{
	std::ifstream file("day3.txt");
	std::string str;
	int point = 0;

	while (std::getline(file, str))
	{
		std::string line1 = "";
		std::string line2 = "";
		for (int i = 0; i < str.size(); i++)
		{
			if (i < str.size() / 2)
			{
				line1 += str[i];
			}
			else
			{
				line2 += str[i];
			}
		}
		RepeatLettle(line1, line2, point);
	}

	std::cout << point << std::endl;
}

void Challenge::day3_2()
{
	std::ifstream file("day3.txt");
	std::string str;
	int point = 0;
	std::string lines[3] = { "" };
	int index = 0;

	while (std::getline(file, str))
	{
		lines[index] = str;
		index++;
		if (3 == index)
		{
			RepeatLettle(lines[0], lines[1], lines[2], point);
			index = 0;
		}
	}

	std::cout << point << std::endl;
}

void Challenge::RepeatLettle(std::string line, std::string line2, int& point)
{
	bool isUpper = false;
	for (int i = 0; i < line.size(); i++)
	{
		for (int j = 0; j < line2.size(); j++)
		{
			if (line[i] == line2[j])
			{
				isUpper = isupper(line[i]);

				point += isUpper ? (int(toupper(line[i])) - 64) + 26 : int(toupper(line[i])) - 64;
				return;
			}
		}
	}
}

void Challenge::RepeatLettle(std::string line, std::string line2, std::string line3, int& point)
{
	bool isUpper = false;
	for (int i = 0; i < line.size(); i++)
	{
		for (int j = 0; j < line2.size(); j++)
		{
			for (int k = 0; k < line3.size(); k++)
			{
				if (line[i] == line2[j] && line2[j] == line3[k])
				{
					isUpper = isupper(line[i]);
					point += isUpper ? (int(toupper(line[i])) - 64) + 26 : int(toupper(line[i])) - 64;
					return;
				}
			}
		}
	}
}

#pragma endregion

#pragma region Day 4

void Challenge::day4()
{
	std::ifstream file("day4.txt");
	std::string str;
	int points = 0;
	int index = 0;

	std::array<std::string, 2> line;
	std::array<int, 4> number;

	while (std::getline(file, str))
	{
		std::string separate = "";
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ',')
			{
				separate += "-";
				line[0] = separate;
				separate = "";
				continue;
			}

			separate += str[i];
			if (i == str.size() - 1)
			{
				separate += "-";
				line[1] = separate;
				separate = "";
			}
		}

		index = 0;
		for (int i = 0; i < line.size(); i++)
		{
			for (int j = 0; j < line[i].size(); j++)
			{
				//std::cout << line[i][j] << std::endl;
				if (line[i][j] == '-')
				{
					try {
						number[index] = stoi(separate);
							separate = "";
							index++;
							continue;
					}
					catch (...) {

					}
				}
				separate += line[i][j];


			}
			

		}

		if (number[0] <= number[2] && number[1] >= number[3] || number[0] >= number[2] && number[1] <= number[3])
		{
			std::cout << number[0] << std::endl;
			points++;
		}
	}

	std::cout << points << std::endl;
}

void Challenge::day4_2()
{
	std::ifstream file("day4.txt");
	std::string str;
	int points = 0;
	int index = 0;

	std::array<std::string, 2> line;
	std::array<int, 4> number;

	while (std::getline(file, str))
	{
		std::string separate = "";
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ',')
			{
				separate += "-";
				line[0] = separate;
				separate = "";
				continue;
			}

			separate += str[i];
			if (i == str.size() - 1)
			{
				separate += "-";
				line[1] = separate;
				separate = "";
			}
		}

		index = 0;
		for (int i = 0; i < line.size(); i++)
		{
			for (int j = 0; j < line[i].size(); j++)
			{
				//std::cout << line[i][j] << std::endl;
				if (line[i][j] == '-')
				{
					try {
						number[index] = stoi(separate);
						separate = "";
						index++;
						continue;
					}
					catch (...) {

					}
				}
				separate += line[i][j];


			}


		}

		if (inRange(number[0] , number[1] , number[2]) || inRange(number[0], number[1], number[3])|| inRange(number[2], number[3], number[1])|| inRange(number[2], number[3], number[0]))
		{
			points++;
		}
	}
	
	std::cout << points << std::endl;
}


#pragma endregion

void Challenge::day5()
{
	std::ifstream file("day5Table.txt");
	std::string str;
	int points = 0;

	std::array<std::string, 8> arr;
	std::array<std::string, 9> FixArr;
	int index = 0;


	while (std::getline(file, str))
	{
		if (str[1] != '1')
		{
			arr[index] = str;
			std::cout << str << std::endl;
			index++;
		}
	}

	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[i].size(); j++)
		{
			if (j % 2 == 0)
			{
				arr[i][j] = ' ';
			}
		}
	}

	std::cout << "===================================" << std::endl;

	for (int i = 0; i < arr.size(); i++)
	{
		FixArr[0] += arr[i][1];
		FixArr[1] += arr[i][5];
		FixArr[2] += arr[i][9];
		FixArr[3] += arr[i][13];
		FixArr[4] += arr[i][17];
		FixArr[5] += arr[i][21];
		FixArr[6] += arr[i][25];
		FixArr[7] += arr[i][29];
		FixArr[8] += arr[i][33];
	}

	for (int i = 0; i < FixArr.size(); i++)
		reverseStr(FixArr[i]);
	
	for(auto line: FixArr)
		std::cout << line << std::endl;

}