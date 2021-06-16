all: $(DBIN)/token$(FO) $(DBIN)/utils$(FO) $(DBIN)/tokenizer$(FO) $(DBIN)/functok$(FX)

$(DBIN)/utils$(FO): $(DSRC)/utils$(FC)
	$(CCC) -c $^ -o $@

$(DBIN)/token$(FO): $(DSRC)/token$(FC) $(DBIN)/utils$(FO)
	$(CCC) -c $^ -o $@

$(DBIN)/tokenizer$(FO): $(DSRC)/tokenizer$(FC) $(DBIN)/token$(FO)
	$(CCC) -c $^ -o $@

$(DBIN)/functok$(FX): $(DSRC)/functok$(FC) $(DBIN)/token$(FO) $(DBIN)/utils$(FO) $(DBIN)/tokenizer$(FO)
	$(CCC) $^ -o $@
