LD_FLAGS+=-lX11

default:
	gcc whatsthiscolor.c -o whatsthiscolor $(LD_FLAGS)

