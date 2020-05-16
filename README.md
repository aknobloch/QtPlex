# QtPlex

### About
QtPlex is a cross-platform media player, based on [Plex](https://www.plex.tv/) home server and the [Qt](https://www.qt.io/) framework. The main motivation behind QtPlex was to provide a stable, modern interface into Plex without sacrificing functionality. Most notably, existing solutions for Plex interfaces lack support for media playback keys. Additionally, available Plex interfaces on Linux machines are sorely lacking, both in features and support. With this in mind, QtPlex was created as an interface into the Plex web client. This allows for low-level control over things such as keyboard shortcuts, while taking advantage of the officially maintained web interface, all while being cross-platform ready.

### Prerequisites
* Accessible server running Plex. 
* QtCreator software.
* The following packages installed:
    * sudo apt-get install qtwebengine5-dev qtdeclarative5-dev libqt5x11extras5-dev libfontconfig1-dev libfreetype6-dev libx11-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libx11-xcb-dev libxcb-glx0-dev libxkbcommon-x11-dev

### Getting Started
Currently, QtPlex is stable with core functionality, but still in development. I hope to have a packaged release shortly, but for now you must download QtCreator and run the project through the build button. Alternatively, you should be able to use qmake from the command line, via `qmake QtPlex.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug`. Make sure to have the prerequisite packages installed. 

##### Proprietary Codecs
In order to enable full functionality of the Plex web app (video and particular audio), some proprietary codecs need to be available to the QtWebEngine. Unfortunately, due to licensing, these cannot be packaged with the Qt libraries, or through this application. As such, you'll need to build the QtWebEngine from source. But, fear not! It's relatively painless. You can find more information on building QtWebEngine from source [here](http://wiki.qt.io/QtWebEngine/How_to_Try). Before running the `qmake` command in that guide, you'll need to enable the proprietary codecs using the `--webengine-proprietary-codecs` flag. More information on that can be found [here](https://doc.qt.io/qt-5.11/qtwebengine-features.html). 

------
### Acknowledgments
This project is dependent on Plex and Qt, and the hard-working developers there who build and maintain the core features that QtPlex relies on. Additionally, [QHotKey](https://github.com/Skycoder42/QHotkey) enabled the base framework for cross-platform keyboard hooks. 
