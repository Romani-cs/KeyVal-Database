#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

int main(){
	string line;

	while (getline(cin, line))
	{
		stringstream ss(line);
		string command;

		ss >> command;

		if(command == "SET")
		{
			cout << "SET command received" << endl;
		}
		else if(command == "GET")
		{
			cout << "GET command received" << endl;
		}
		else if(command == "EXIT")
		{
			break;
		}
	}

	return 0;
}
