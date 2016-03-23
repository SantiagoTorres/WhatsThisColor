#include "whatsthiscolor.h"

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
    Window window, root_return, child_return;
    int pixel;
    XColor c, exact, screen;
    int done = 0;
    int rootx, rooty, winx, winy;
    unsigned int mask;
    int ret;
    char *color_string;
    Colormap colormap;


    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;
    window = DefaultRootWindow(display);

    /* Get mouse pointer coordinates */
    ret = XQueryPointer(display, window, &root_return, &child_return, &rootx,
            &rooty, &winx, &winy, &mask);
    get_pixel_color (display, rootx, rooty, &c);
    printf("[%x] r:%x g:%x b:%x\n", ret, c.red, c.green, c.blue);

    return 0;
}
