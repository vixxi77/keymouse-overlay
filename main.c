#include <stdio.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xlib.h>

#define WIDTH 400
#define HEIGHT 400

void main(){
	Display *display = XOpenDisplay(0);
	Window   root 	 = DefaultRootWindow(display);

	XIEventMask emask;
	
	unsigned char mask[XIMaskLen(XI_LASTEVENT)] = {0};
    	emask.deviceid = XIAllMasterDevices;
        emask.mask = mask;
        emask.mask_len = sizeof(mask);

        XISetMask(emask.mask, XI_RawKeyPress);
        XISetMask(emask.mask, XI_RawKeyRelease);

	XISelectEvents(display, root, &emask, 1);\

	XSync(display, False);

	while(true){
		XEvent event;
		XNextEvent(display, &event);

		if(XGetEventData(display, &event.xcookie) && event.xcookie.type == GenericEvent){
				XIRawEvent *raw = (XIRawEvent *)event.xcookie.data;

				switch(event.xcookie.evtype){
					case XI_RawKeyPress:
						printf("pressed, keycode: %d \n", raw->detail);
						break;
					case XI_RawKeyRelease:
						printf("released, keycode: %d \n", raw->detail);
						break;
				}	
		}

		XFreeEventData(display, &event.xcookie);		
	}

	XCloseDisplay(display);
}
