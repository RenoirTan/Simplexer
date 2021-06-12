all: $(DBIN)/token$(FO)

$(DBIN)/token$(FO): $(DSRC)/token$(FCXX)
	$(CCXXC) -c $^ -o $@
