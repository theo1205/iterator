.PHONY: all archive clean distclean doc

NAME ?= $(shell basename $(shell pwd))
LDLIBS ?= -lm
CFLAGS ?= -O3 -march=native -g3 -ggdb
override CFLAGS += -std=gnu11 -pedantic -pedantic-errors \
		-Wall -Wextra \
		-Wdouble-promotion -Wformat=2 -Winit-self -Wswitch-default \
		-Wswitch-enum -Wunused-parameter -Wuninitialized -Wfloat-equal \
		-Wshadow -Wundef -Wbad-function-cast \
		-Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
		-Wjump-misses-init -Wlogical-op -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes -Wmissing-declarations \
		-Wredundant-decls -Wnested-externs
# D'autres warnings intéressants (en général, certains sont inutiles dans ce
# cas particulier) mais pas encore reconnus par la version de GCC disponible
# sur une Ubuntu 14.04... :
#
# -Wmissing-include-dirs -Wnull-dereference -Wswitch-bool -Wduplicated-cond
# -Wdate-time

EXEC = test_liste test_tableau test_ensemble test_iterateur
all: $(EXEC)
test_liste: test_liste.o liste.o iterateur.o
test_tableau: test_tableau.o tableau.o iterateur.o
test_ensemble: test_ensemble.o ensemble.o iterateur.o
test_iterateur: test_iterateur.o iterateur.o liste.o tableau.o ensemble.o
%: %.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)

# Documentation
doc:
	doxygen Doxyfile

# Archive
archive:
	tar -czf $(NAME).tar.gz --transform="s,^,$(NAME)/," \
		*.c *.h Makefile Doxyfile

# Nettoyage
clean:
	$(RM) -r $(EXEC) *.o doc
distclean: clean
	$(RM) *.tar.gz

# Dépendances avec les en-têtes
tableau.o: tableau.c tableau.h sorte.h
liste.o: liste.c liste.h sorte.h
tableau.o: tableau.c tableau.h sorte.h
ensemble.o: ensemble.c ensemble.h sorte.h
iterateur.o: iterateur.c iterateur.h sorte.h liste.h tableau.h
test_liste.o: test_liste.c liste.h sorte.h
test_tableau.o: test_tableau.c tableau.h sorte.h
test_ensemble.o: test_ensemble.c ensemble.h sorte.h
test_iterateur.o: test_iterateur.c iterateur.h sorte.h liste.h tableau.h
