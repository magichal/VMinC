CC=gcc
LDFLAG=
LPFLAG=-g
NAME=../src
ARCHIVE_NAME=eval_4.6_rigaud_neau.zip

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TEST=testU/test_unitaire.c

EXE=vm
EXE2=test

all: mrpropre vm

vm:
	@$(CC) -g -Wall -o $(EXE) $(SRC)
	@echo "operation terminee.\nl application a ete creer."

test: mrpropre vm
	@$(CC) -g -Wall -o $(EXE2) $(TEST)
	@echo "operation terminee.\nl application a ete creer."
	@./$(EXE2) 2> /dev/null

%.o: %.c
	@$(CC) $(LPFLAG) -o $@ -c $<

#########################################

run:
	./$(EXE)


#########################################


clean:
	@rm -rf *.o *~

mrpropre: clean
	@rm -rf $(EXE)
	@rm -rf $(EXE2)




##########################################

zip:
	zip -9 -r $(ARCHIVE_NAME) $(NAME)
