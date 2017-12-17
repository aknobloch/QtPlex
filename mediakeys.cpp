#include <QString>
#include <QDebug>
#include <mediakeys.h>

Key::Key(QString name, int keycode) : m_name(name), m_keycode(keycode) {}

Key::Key(const Key &copy)
{
	this -> m_name = copy.getName();
	this -> m_keycode = copy.getKeyCode();
}

Key::Key()
{
	this -> m_name = "Default Key";
	this -> m_keycode = 0;
}

Key::~Key()
{

}

QString Key::getName() const
{
	return this -> m_name;
}

int Key::getKeyCode() const
{
	return this -> m_keycode;
}

MediaKeys::MediaKeys()
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

vector<Key> MediaKeys::getMediaKeys()
{
	return this -> all_media_keys;
}

Key MediaKeys::getKey(int searchKeyCode)
{
	for(vector<Key>::iterator it = all_media_keys.begin(); it != all_media_keys.end(); it++)
	{
		Key next_key = *it;
		if(next_key.getKeyCode() == searchKeyCode)
		{
			return next_key;
		}
	}

	throw;
}

void MediaKeys::printKeys()
{
	for(vector<Key>::iterator it = all_media_keys.begin(); it != all_media_keys.end(); it++)
	{
		Key next_key = *it;
		qInfo() << next_key.getName();
	}
}
