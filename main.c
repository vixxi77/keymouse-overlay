#include <stdio.h>
#include <time.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

#define W_WIDTH 400
#define W_HEIGHT 400

void main(){
	Display *display = XOpenDisplay(0);
	Window   root 	 = DefaultRootWindow(display);
	GC gc;
/*
 * THIS CODE OF SETTING TRANSPARENT WINDOW IS NOT MINE!!!
 */
 	XVisualInfo vinfo; 
	XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

    	XSetWindowAttributes attr;
    	attr.colormap = XCreateColormap(display, root, vinfo.visual, AllocNone);
    	attr.border_pixel = 0;
    	attr.background_pixel = 0;
/*CODE THATS NOT MINE ENDS HERE */

    	Window window = XCreateWindow(display, root, 0, 0, W_WIDTH, W_HEIGHT, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);

/*TEST CODE */	
	/*
	cairo_surface_t *surface = cairo_xlib_surface_create(display, window, vinfo.visual, 1000, 800);
	cairo_t *cr = cairo_create(surface);
	cairo_surface_t *png = cairo_image_surface_create_from_png("keyboard60he.png");
	*/
/*TEST CODE */


	XMapWindow(display, window);
	XIEventMask emask;
	
	unsigned char mask[XIMaskLen(XI_LASTEVENT)] = {0};
    	emask.deviceid = XIAllMasterDevices;
        emask.mask = mask;
        emask.mask_len = sizeof(mask);

        XISetMask(emask.mask, XI_RawKeyPress);
        XISetMask(emask.mask, XI_RawKeyRelease);

	XISelectEvents(display, root, &emask, 1);\

	XSync(display, False);

	gc = XCreateGC(display, window, 0, 0);
    	XSetForeground( display, gc, WhitePixel(display, 0));


	while(true){
		XEvent event;
		XNextEvent(display, &event);


		if(XGetEventData(display, &event.xcookie) && event.xcookie.type == GenericEvent){
				XIRawEvent *raw = (XIRawEvent *)event.xcookie.data;


				switch(event.xcookie.evtype){
					case XI_RawKeyPress:
						printf("pressed, keycode: %d \n", raw->detail);
						switch(raw->detail){
							case 24: 
								XFillRectangle(display, window, gc, 0, 0, 25, 25);
								break;
							case 25:
								XFillRectangle(display, window, gc, 30, 0, 25, 25);
								break;
							case 26:
								XFillRectangle(display, window, gc, 60, 0, 25, 25);
								break;

						}
					break;
					case XI_RawKeyRelease:
						printf("released, keycode: %d \n", raw->detail);
						switch(raw->detail){
							case 24: 
								XClearArea(display, window, 0, 0, 25, 25, False);
								break;
							case 25:
								XClearArea(display, window, 30, 0, 25, 25, False);
								break;
							case 26:
								XClearArea(display, window, 60, 0, 25, 25, False);
								break;

						}
					break;
				}	
		}

		XFreeEventData(display, &event.xcookie);		
		
		/*
		cairo_set_source_surface(cr, png, 0, 0);
		cairo_paint(cr);
		cairo_surface_flush(surface);
		*/

	}

	XCloseDisplay(display);
}
