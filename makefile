override CC = gcc
RM ?= rm -f
INSTALL ?= install
INSTALL_PROGRAM ?= $(INSTALL)
prefix ?= /usr/local
exec_prefix ?= $(prefix)
bindir ?= $(exec_prefix)/bin
ALL_CFLAGS = -Wall -Werror -Wextra -Wpedantic -Wshadow -std=gnu11 $(shell pkg-config --cflags gtk+-3.0 gio-unix-2.0) $(CFLAGS)
LIBS = -lmagic $(shell pkg-config --libs gtk+-3.0 gio-unix-2.0)
NAME = dispersion-launch

all: $(NAME)

$(NAME): main.c
	$(CC) $(CPPFLAGS) $(ALL_CFLAGS) -Os $(LIBS) -o $@ $<

.PHONY: clean
clean:
	$(RM) $(NAME)

.PHONY: install-strip install installdirs
install-strip: install
	strip -s $(DESTDIR)$(bindir)/$(NAME)
	objcopy --strip-all -R .comment -R .note.gnu.build-id -R .note.ABI-tag $(DESTDIR)$(bindir)/$(NAME) $(DESTDIR)$(bindir)/$(NAME)

install: installdirs
	$(INSTALL_PROGRAM) $(NAME) $(DESTDIR)$(bindir)/$(NAME)

installdirs:
	mkdir -p $(DESTDIR)$(bindir)
