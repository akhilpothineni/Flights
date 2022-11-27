EXE = run #Things to type to run code
TEST = test

EXE_OBJ = main.o #object files
OBJS = main.o Airports.o Routes.o Calculate.o 

#message output
$(info $(shell echo -e "\033[0;30;42m")************  MAKING PROJECT  (USE ./run TO RUN || USE make test && ./test TO TEST) ************ $(shell echo -e "\033[0m"))


# Use the CS 225 Makefile template
include cs225/make/cs225.mk