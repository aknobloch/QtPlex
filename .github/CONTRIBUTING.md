## Style Guide
Use `clang-format` with Google style. A good article for configuring this in QtCreator can be found [here](https://www.vikingsoftware.com/using-clang-format-with-qtcreator/). All files should default to the respective public style guides by Google.

## Memory Usage
Use C++11 smart pointers, even though they can be awkward to hold in conjunction with Qt. Despite that fact, they handle implicit deletion if/when source code changes and solve a lot of memory issues. If constructing a pointer and immediately passing it to a Qt Parent, use `std::release` to pass the raw pointer along. For example:
```
std::unique_ptr<QMenu> file = std::make_unique<QMenu>("File");
file->addAction("Settings", this, &ApplicationWindow::showSettingsDialog);

menuBar()->setStyleSheet("background-color:rgb(244,244,244)");
menuBar()->addMenu(file.release());
```
Any pointers which are direct descendents of a custom object should be declared in the private member variables of the function. References to the pointer should be retrieved via `std::get()`.
