#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>
#include "rgb.h"

typedef struct _colorname {
    char red;
    char green;
    char blue;
    char colorname[50];
} colorname;
