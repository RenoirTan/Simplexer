all: $(DBIN)/token$(FO)

$(DBIN)/token$(FO): $(DSRC)/token$(FC)
	$(CCC) -c $^ -o $@
