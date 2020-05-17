# QtPlex
QtPlex provides a cross-platform, Linux-first solution for streaming Plex media. The application is a shallow wrapper into the standard web interface, with the added benefits of native media keyboard shortcuts.

![QtPlex GUI Example](https://i.imgur.com/6xfr4Sb.png)

## Installation and Setup

### Prerequisites
* Accessible server running Plex. 
* QtCreator software.

1. Install the libraries needed for QtPlex: `sudo apt-get install qtwebengine5-dev qtdeclarative5-dev libqt5x11extras5-dev libfontconfig1-dev libfreetype6-dev libx11-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libx11-xcb-dev libxcb-glx0-dev libxkbcommon-x11-dev`
2. Open the QtPlex.pro file in QtCreator, then build/run.
3. [Optional] Add a desktop file for launching:
```
[Desktop Entry]
Type=Application
Name=QtPlex
Keywords=audio;plex;qt
Icon=/path/to/build-QtPlex-Desktop-Release/res/icon256.png
Exec=/path/to/build-QtPlex-Desktop-Release/QtPlex
Terminal=false
StartupWMClass=QtPlex
```

## Known Issues
### GNOME Intercepts (Issue #14)
If you notice the application no longer responding to media keys, and instead a pop-up shown indicating there are no media applications present, you can disable GNOME from intercepting X keys. You can read more [here](https://askubuntu.com/questions/990284/media-keys-not-working-on-ubuntu-17-10).

Workaround:
1. Install `dconf-editor`
2. Open `dconf-editor` and navigate to `org.gnome.settings-daemon.plugins.media-keys`.
3. Remove the `previous-static` binding by changing the value to nothing (`['']`).
4. Repeat the above for `pause-static`, `play-static`, `stop-static` and `next-static`. 
5. If problems persist, look through the settings in step two and validate nothing is bound to suspicious `XF86Audio*`keys.

### Proprietary Codecs
In order to enable full functionality of the Plex web app (video and particular audio), some proprietary codecs need to be available to the QtWebEngine. Unfortunately, due to licensing, these cannot be packaged with the Qt libraries, or through this application. As such, you'll need to build the QtWebEngine from source. You can find more information on building QtWebEngine from source [here](http://wiki.qt.io/QtWebEngine/How_to_Try). Before running the `qmake` command in that guide, you'll need to enable the proprietary codecs using the `--webengine-proprietary-codecs` flag. More information on that can be found [here](https://doc.qt.io/qt-5.11/qtwebengine-features.html). 

------
## Acknowledgments
This project is dependent on Plex and Qt, and the hard-working developers there who build and maintain the core features that QtPlex relies on. Additionally, [QHotKey](https://github.com/Skycoder42/QHotkey) enabled the base framework for cross-platform keyboard hooks. 
