/*
*	Last worked on 3/19/2019
*	RuleManager.cpp
*/

#include<filesystem>
#include<iostream>
#include<string>
#include<vector>
#include "RuleManager.h"

RuleManager* RuleManager::instance = 0;

// Constructior for RuleManager
RuleManager::RuleManager()
{
	int i = 0;
	// Get list of rules on creation
	for (std::filesystem::directory_entry p : std::filesystem::directory_iterator("Rules"))
	{
		string ruleName = p.path().string();
		int end = ruleName.find(".cpp");
		if (end != string::npos)
		{
			// Start at the end of the directory name
			// and substract directory name and .cpp
			// from the total length.
			ruleName = ruleName.substr(6, ruleName.size() - 10);
			// Add rule to list of callable rules
			//rules[i] = callFacotry(ruleName);
		}
	}

	static IntCountRule* p = new IntCountRule();

	// Temp till the rule factory can be setup
	rules.emplace_back(p);

	fileName = "";
}

// Will return the instance of the RuleManager
RuleManager* RuleManager::getInstance()
{
	if (instance == 0)
	{
		instance = new RuleManager();
	}

	return instance;
}

// For receiving the active rules. Return false if
// there is any errors setting up the rules.
// Create using the rule name?
bool RuleManager::setActiveRules(vector<string> active)
{
	// Check names in given vector with names of
	// rules found in directory.
	
	// As found create an array of active rules
	// to iterate over.

	//temp for testing
	activeRules.push_back(0);

	return true;
}

// For receiving the file name. Return false if
// there is any errors setting the name.
void RuleManager::setName(string filePath)
{
	fileName = filePath;
}

// Used by parser to send the string
void RuleManager::run(string input)
{
	// Run rules that are active
	// Send line to each rule
	for(int i = 0; i < activeRules.size(); i++)
		rules[activeRules[i]]->run(input);
}

// Will be called at the end of a file and retreive the
// final metrics from the rules then push them to storage
void RuleManager::finished()
{
	string data; // Temp string to hold metrics

	// Loop all active rules to tell them the
	// parser is finished
	for (int i = 0; i < activeRules.size(); ++i)
	{
		data = rules[activeRules[i]]->finished();

		cout << "Stored data for: " << rules[activeRules[i]]->getName() << "\n";
	}

	fileName = "";
}
