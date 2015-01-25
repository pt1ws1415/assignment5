PROGRAMS = task2 task3 task4 generate transpose
CFLAGS = -I../include

all: $(PROGRAMS:%=$(OUTDIR)/%)

$(OUTDIR)/%:
	@mkdir -p $(OUTDIR)
	$(CC) $(LOADLIBES) $(LDFLAGS) $^ -o $@

.PHONY: all clean

#----------------------------------------------------------------
# 1.I   Finds all source files in that folder and below
# 1.II  Detect all dependencies of your source files automatically
# 1.III Add a clean rule, that deletes all temporary files and the output directory
# 1.IV  Build one rule for each program like the one of task2
#       (do that when you solve the corresponding tasks)

$(OUTDIR)/task2: test/task2.o lib/lower_upper.o

#----------------------------------------------------------------
