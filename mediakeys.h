#ifndef MEDIAKEYS_H
#define MEDIAKEYS_H

#include <QString>
#include <vector>
using namespace std;

class Key
{
	public:
		Key();
		~Key();
		Key(QString name, int keycode);
		Key(const Key &copy);

		QString getName() const;
		int getKeyCode() const;

	private:
		QString m_name;
		int m_keycode;
};

enum MediaKeyCodes
{
	STOP = 174,
	BACK = 173,
	PLAY_PAUSE = 172,
	FORWARD = 171
};

class MediaKeys
{
	public:
		MediaKeys();

		vector<Key> getMediaKeys();
		Key getKey(int searchKeyCode);
		void printKeys();

	private:
		vector<Key> all_media_keys;
};

#endif // MEDIAKEYS_H
