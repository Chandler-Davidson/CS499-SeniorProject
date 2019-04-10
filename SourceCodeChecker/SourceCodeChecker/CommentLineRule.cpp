//Count number of comment lines
#include<iostream>
#include<string>
#include<regex>
#include "CommentLineRule.h"

CommentLineRule::CommentLineRule()
{

	string name = "CommentLineRule"; // Name of the rule
	int count = 0; // A storeage var for any rule that just has a count
	string data = ""; // A var to send finialized data back to rule manager

}

// Return the name of the rule. Used to initialize
string CommentLineRule::getName()
{
	return name;
}

// Receive the line from RuleManager here and split
// the line up and send to checkLine to check
void CommentLineRule::run(string l)
{
	//Count comment lines beginning with"//"
	regex comment_count("^.*//.*$");                

	if (regex_match(l, comment_count))
		count += 1;
}

// Called after the file has finished being read
// used to send collected metrics back to the
// rule manager. 
// ~~Be sure to add this to your class and customize as needed.
string CommentLineRule::finished()
{
	data = count;                      


	cout << "\n" << count << "\n";
	// Return count to 0
	count = 0;
	// Put data in a string and return it to the Rule Manager
	return data;
}