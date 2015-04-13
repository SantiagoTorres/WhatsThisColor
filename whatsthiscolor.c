#include <stdio.h>
#include <X11/Xlib.h>



/* Taken from http://rosettacode.org/wiki/Color_of_a_screen_pixel#C */
void get_pixel_color (Display *d, int x, int y, XColor *color)
{

  XImage *image;
  image = XGetImage (d, RootWindow (d, DefaultScreen (d)), x, y, 1, 1,
                        AllPlanes, XYPixmap);
  color->pixel = XGetPixel (image, 0, 0);
  XFree (image);
  XQueryColor (d, DefaultColormap(d, DefaultScreen (d)), color);

}


int main(int argc, char **argv)
{

    Display *display;
    XEvent xevent;
    Window window;
    int pixel;
    XColor c;


    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;
    window = DefaultRootWindow(display);
    XAllowEvents(display, AsyncBoth, CurrentTime);

    /* Get mouse pointer */
    XGrabPointer(display, window, 1, PointerMotionMask, GrabModeAsync,
                 GrabModeAsync, None, None, CurrentTime);

    /* query the mouse position and find which color is the pixel in it */
    while(1) {

        XNextEvent(display, &xevent);

        switch (xevent.type) {
            case MotionNotify:
                //pixel = vga_getpixel(xevent.xmotion.x_root, xevent.xmotion.y_root);
                get_pixel_color (display, xevent.xmotion.x_root,
                                 xevent.xmotion.y_root, &c);
                printf("Color in cursor %04x, %04x, %04x\n", c.red, c.green,
                                                            c.blue);
                break;
        }
    }

    return 0;
}
