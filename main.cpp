#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

struct Entry {
	string key;
	string value;
};

class KeyValueStore
{
	private:
		vector<Entry> index;
	public:
		int findKey(const string &key) 
		{
			for(int i=0; i < index.size(); i++)
			{
				if(index[i].key == key){
					return i;
				}
			}
			return -1;
		}

		void set(const string &key, const string &value)
		{
			int pos = findKey(key);

			if(pos == -1)
			{
				Entry e;
				e.key = key;
				e.value = value;
				index.push_back(e);
			}
			else
			{
				index[pos].value = value;
			}
		}
};

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
