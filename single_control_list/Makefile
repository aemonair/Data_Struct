#Makefile

ROOTPATH   =     .
SRC        =     $(ROOTPATH)/src
HEAD       =     $(ROOTPATH)/head
COM        =     $(ROOTPATH)/obj
BIN        =     $(ROOTPATH)/bin
TEST       =     $(ROOTPATH)/test

OBJ        =     $(COM)/list.o
MAIN       =     $(COM)/main.o

TARGET     =     $(BIN)/list

all : com 

$(OBJ):
	$(CC) -c $(SRC)/list.c -o $(OBJ) -I $(HEAD)

com:$(OBJ)
	@echo "-objects-"

test:$(OBJ)
	@echo "-test-"
	$(CC) -c $(TEST)/main.c -o $(MAIN) -I $(HEAD)
	$(CC)  $(OBJ) $(MAIN) -o $(TARGET)
	@echo "---------"
	@date

.PHONE:
clean:
	rm -f $(OBJ) $(MAIN) $(TARGET) 
