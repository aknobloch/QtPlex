#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "mediakeys.h"
using namespace std;

MediaKeys all_keys;

void grab_keys(Display *display, Window &grab_window);

int main()
{
     
	Display*    dpy     = XOpenDisplay(0);
    Window      root    = DefaultRootWindow(dpy);
    XEvent      event;

    // initial grab for media keys
    grab_keys(dpy, root);

    while(true)
    {
        XNextEvent(dpy, &event);

        // grab again for future events
        // TODO: is this neccessary? No other examples do this
        grab_keys(dpy, root);

        switch(event.type)
        {
            case KeyPress:
            
            	Key pressed_key = all_keys.get_key(event.xkey.keycode);
                cout << pressed_key.get_name() << " pressed!" << endl;
        }
    }

    XCloseDisplay(dpy);
    return 0;
}

void grab_keys(Display *display, Window &grab_window)
{
	unsigned int    modifiers       = AnyModifier;
	Bool            owner_events    = False;
	int             pointer_mode    = GrabModeAsync;
	int             keyboard_mode   = GrabModeAsync;
	
	vector<Key> keys = all_keys.get_media_keys();

	for(vector<Key>::iterator it = keys.begin(); it < keys.end(); it++)
	{
		Key next_key = *it;
	 	XGrabKey(display, next_key.get_keycode(), modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
 	}
}