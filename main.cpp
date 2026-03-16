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
		string filename = "data.db";
	public:
		int findKey(const string &key) // Searches the in memory index for a key using linear search and returns the index position if found, otherwise -1.
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

			ofstream file(filename, ios::app);
			file << "SET " << key << " " << value << endl;
			file.close();
		}

		void get(const string &key)
		{
			int pos = findKey(key);

			if(pos == -1)
			{
				cout << endl;
			}
			else
			{
				cout << index[pos].value << endl;
			}
		}

		// Loads the append only log from disk and rebuilds the index by replaying each SET command.
		void load()
		{
			ifstream file(filename);

			if(!file.is_open())
			{
				return;
			}

			string line;

			while(getline(file, line))
			{
				stringstream ss(line);
				string command;
				string key;
				string value;

				ss >> command >> key >> value;

				if(command == "SET")
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
			}
			file.close();
		}
};

int main()
{
	KeyValueStore db;
	db.load();
	string line;

	while (getline(cin, line))
	{
		if(line.empty())
		{
			continue;
		}
		stringstream ss(line);
		string command;

		ss >> command;

		if(command == "SET")
		{
			string key;
			string value;

			ss >> key >> value;
			db.set(key, value);
		}
		else if(command == "GET")
		{
			string key;
			
			ss >> key;
			db.get(key);
		}
		else if(command == "EXIT")
		{
			break;
		}
	}

	return 0;
}
