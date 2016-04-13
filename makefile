SHELL = /bin/sh
override CC = gcc
RM = rm -r
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
prefix = /usr/local
exec_prefix = ($prefix)
bindir = $(exec_prefix)/bin
sbindir = $(exec_prefix)/sbin
libexecdir = $(exec_prefix)/libexec
datarootdir = $(prefix)/share
datadir = $(datarootdir)
sysconfdir = $(prefix)/etc
sharedstatedir = $(prefix)/com
localstatedir = $(prefix)/var
runstatedir = $(localstatedir)/run
includedir = $(prefix)/include
oldincludedir = /usr/include
docdir = $(datarootdir)/doc/yourpkg
infodir = $(datarootdir)/info
htmldir = $(docdir)
dvidir = $(docdir)
pdfdir = $(docdir)
psdir = $(docdir)
libdir = $(exec_prefix)/lib
lispdir = $(datarootdir)/emacs/site-lisp
localedir = $(datarootdir)/locale
mandir = $(datarootdir)/man
ALL_CFLAGS = -Wall -Werror -Wextra -Wpedantic -Wshadow -std=gnu11 $(shell pkg-config --cflags gtk+-3.0 gio-unix-2.0) $(CFLAGS)
LDLIBS = -lmagic $(shell pkg-config --libs gtk+-3.0 gio-unix-2.0)
NAME = dispersion-launch

all: $(NAME)

$(NAME): main.c
	$(CC) $(CPPFLAGS) $(ALL_CFLAGS) -Os $(LDFLAGS) $(LDLIBS) -o $@ $<

.PHONY: clean
clean:
	$(RM) ./$(NAME)

.PHONY: install-strip install installdirs
install-strip:
	strip -s $(DESTDIR)$(bindir)/$(NAME)
	objcopy --strip-all -R .comment -R .note.gnu.build-id -R .note.ABI-tag $(NAME) $(NAME)

install: installdirs
	$(INSTALL_PROGRAM) $(NAME) $(DESTDIR)$(bindir)

installdirs:
	mkdir -p $(DESTDIR)$(bindir)
