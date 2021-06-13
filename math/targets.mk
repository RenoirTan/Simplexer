all: $(DBIN)/utils$(FO) $(DBIN)/token$(FO) $(DBIN)/mathtok$(FX)

$(DBIN)/utils$(FO): $(DSRC)/utils$(FCXX)
	$(CCXXC) -c $^ -o $@

$(DBIN)/token$(FO): $(DSRC)/token$(FCXX) $(DBIN)/utils$(FO)
	$(CCXXC) -c $^ -o $@

$(DBIN)/mathtok$(FX): $(DSRC)/mathtok$(FCXX) $(DBIN)/token$(FO) $(DBIN)/utils$(FO)
	$(CCXXC) $^ -o $@
