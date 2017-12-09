#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Key
{
	public:
		Key(string name, int keycode) : m_name(name), m_keycode(keycode) {}

		string get_name()
		{
			return this -> m_name;
		}

		int get_keycode()
		{
			return this -> m_keycode;
		}

	private:
		string m_name;
		int m_keycode;
};

class MediaKeys
{
	public:
		MediaKeys()
		{
			Key stop("Stop", 174);
			Key back("Back", 173);
			Key pause("Play/Pause", 172);
			Key forward("Forward", 171);

			all_media_keys.push_back(stop);
			all_media_keys.push_back(back);
			all_media_keys.push_back(pause);
			all_media_keys.push_back(forward);
		}

		vector<Key> get_media_keys()
		{
			return this -> all_media_keys;
		}

		Key get_key(int search_keycode)
		{
			for(vector<Key>::iterator it = all_media_keys.begin(); it != all_media_keys.end(); it++)
			{
				Key next_key = *it;
				if(next_key.get_keycode() == search_keycode)
				{
					return next_key;
				}
			}

			throw;
		}

		void print_keys()
		{
			for(vector<Key>::iterator it = all_media_keys.begin(); it != all_media_keys.end(); it++)
			{
				Key next_key = *it;
				cout << next_key.get_name() << endl;
			}
		}

	private:
		vector<Key> all_media_keys;
};
