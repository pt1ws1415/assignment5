# Define the output directory for the programs
OUTDIR = bin

# Command to pass variables into make in folder src
RUN_REC_MAKE = $(MAKE) OUTDIR=../$(OUTDIR) -C src

# Our default target, we need to state this explicitly
all:
	$(RUN_REC_MAKE) all

# All targets in OUTDIR are prepended with ../ for our sub-make
$(OUTDIR)/%:
	$(RUN_REC_MAKE) ../$@

# All other targets are just passed on
%:
	$(RUN_REC_MAKE) $@	
