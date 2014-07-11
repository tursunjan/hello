objects = main.o  read_sam.o sure_bp.o list.o chr.o mutation_type.o merge_pos.o quick_sort.o Remove_redundant.o merge_pos_ins.o Remove_redundant_ins.o read_sam_ins.o quick_sort_ins.o
cc = gcc
CFLAGS = -Wall -O2 -g
sure_bp : $(objects)
	$(cc) $(CFLAGS) -o SAM2SV $(objects)  
.PHONY : clean  
clean :  
	rm SAM2SV $(objects) 
