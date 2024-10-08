#pragma once
#include <string> 

class Button;

class DemoObject
{
private: 
	int mNumberOfPeople;
	int* pNumberOfPeoples; // p in front of peoples means Pointer
	std::string& rName; //r in front of Name stands for reference
public:
	Button* btnSaveNumberOfPeople;
	void setNumberOfPeople(int numberOfPeople) {
		mNumberOfPeople = numberOfPeople;
	}
	//int getNumberOfPeople();

	//void onSavePeopleButtonClick();

	//bool hasName();


};

