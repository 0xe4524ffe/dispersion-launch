DEBUG = -g3 -O0
CFLAGS = -Wall -Werror -Wextra -Wpedantic -Wshadow -std=gnu11 $(shell pkg-config --cflags gtk+-3.0 gio-unix-2.0)
LFLAGS = -lmagic $(shell pkg-config --libs gtk+-3.0 gio-unix-2.0)

release: main.c
	cc $(CFLAGS) -march=native -Os $(LFLAGS) -o dispersion-launch main.c
	strip -s dispersion-launch
	objcopy --strip-all -R .comment -R .note.gnu.build-id -R .note.ABI-tag dispersion-launch dispersion-launch

debug: main.c
	cc $(CFLAGS) $(DEBUG) $(LFLAGS) -o dispersion-launch main.c

clean:
	rm ./dispersion-launch
