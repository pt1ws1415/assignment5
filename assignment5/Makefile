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

# Added by @TimNN
# These rules are required because otherwise $OUTDIR/* will be assumed
# up to date as long as the file exists
# As make does not allow implicit rules to be .PHONY we define an
# explict rule for each file in $OUTDIR.

TARGETS = $(shell find $(OUTDIR) -type f)

.PHONY: $(TARGETS)

$(TARGETS):
	$(RUN_REC_MAKE) ../$@
