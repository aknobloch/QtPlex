#ifndef MEDIAKEYS_H
#define MEDIAKEYS_H

#include <QString>
#include <vector>
using namespace std;

class Key
{
	public:
		Key(QString name, int keycode);

		QString getName() const;
		int getKeyCode() const;

	private:
		const QString m_name;
		const int m_keycode;
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
