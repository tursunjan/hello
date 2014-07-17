objects = main.o  read_sam.o sure_bp.o  read_sam_ins.o sure_bp_ins.o
cc = gcc
CFLAGS = -Wall -O2 -g
sure_bp : $(objects)
	$(cc) $(CFLAGS) -o SAM2SV $(objects)  
.PHONY : clean  
clean :  
	rm SAM2SV $(objects) 
