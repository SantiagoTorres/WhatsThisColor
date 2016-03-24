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


/* Find the point with the least error */
const char *reverse_lookup_color(XColor color)
{ 
    int i;
    int found = -1;
    int error, min_error, rerror, gerror, berror;


    min_error = 10000;
    for (i = 0; i < NUMBER_OF_COLORS; i++) {

        rerror = (color.red & 0xff) - COLOR_VALUES[i][0];
        rerror *= rerror;

        gerror = (color.green & 0xff) - COLOR_VALUES[i][1];
        gerror *= gerror;

        berror = (color.blue & 0xff) - COLOR_VALUES[i][2];
        berror *= berror;

        error = rerror + gerror + berror;
        if (error < min_error) {
            min_error = error;
            found = i;
        }

    }

    if (found != -1)
        return COLOR_NAMES[found];
    return NULL;

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

    printf("%s\n", reverse_lookup_color(c));

    return 0;
}
