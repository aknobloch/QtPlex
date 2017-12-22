# QtPlex
=====
## About
QtPlex is a cross-platform media player, based on [Plex](https://www.plex.tv/) home server and the [Qt](https://www.qt.io/) framework. The main motivation behind QtPlex was to provide a stable, modern interface into Plex without sacrificing functionality. Most notable, existing solutions for Plex interfaces lack support for media playback keys. Additionally, the support for any Plex interface on Linux machines is sorely lacking, both in features and support. With this in mind, QtPlex was created as an interface into the Plex web client. This allows for low-level control over things such as keyboard shortcuts, while taking advantage of the officially maintained web interface.

## Prerequisites
In order to use QtPlex, you must have an accessible server running Plex. In the current development status, you must also need the Qt software installed to build and run the project.

## Getting Started
Currently, QtPlex is stable with core functionality, but still in development. I hope to have a packaged release shortly, but for now you must download QtCreator and run the project through the build button. Alternatively, you should be able to use qmake from the command line, via `qmake QtPlex.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug`. **In order to access your server, you will need to change the IP address, located in the main.cpp file.**

## Goals
Moving forward, the first steps are to abstract the IP address for the server into a proper setting, which should be cached by the application. Cross-platform testing needs to be done, as well as adding support for Windows media key shortcuts. After that, an officially packaged distributable will be made.  
=====

## Acknowledgments
Obviously, this project is dependent on Plex and Qt, and the hard-working developers there who build and maintain the core features that QtPlex relies on. Additionally, [QHotKey](https://github.com/Skycoder42/QHotkey) enabled the base framework for cross-platform keyboard hooks. 
