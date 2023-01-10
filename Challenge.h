#pragma once
#include <iostream>
#include <fstream>
#include <string>


class Challenge
{
	
private:
	int ConvertChatToInt(char letter);
	int FixPlay(int player, int oponent , int &points);

	void RepeatLettle(std::string line, std::string line2 , int& point);
	void RepeatLettle(std::string line, std::string line2, std::string line3, int& point);


public:

	void day1();

	void day2_1();
	void day2_2();

	void day3();
	void day3_2();

	void day4();
	void day4_2();

	void day5();

protected:

	bool inRange(unsigned low, unsigned high, unsigned x)
	{
		return (low <= x && x <= high);
	}
	void reverseStr(std::string& str)
	{
		int n = str.length();

		for (int i = 0; i < n / 2; i++)
			std::swap(str[i], str[n - i - 1]);
	}
};