all: $(DBIN)/token$(FO) $(DBIN)/utils$(FO)

$(DBIN)/utils$(FO): $(DSRC)/utils$(FC)
	$(CCC) -c $^ -o $@

$(DBIN)/token$(FO): $(DSRC)/token$(FC) $(DBIN)/utils$(FO)
	$(CCC) -c $^ -o $@
