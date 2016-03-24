LD_FLAGS+=-lX11 -lm
#CFLAGS := -g

default:
	gcc whatsthiscolor.c -o whatsthiscolor $(CFLAGS) $(LD_FLAGS)

