#Makefile

ROOTPATH   =     .
SRC        =     $(ROOTPATH)/src
HEAD       =     $(ROOTPATH)/head
COM        =     $(ROOTPATH)/obj
BIN        =     $(ROOTPATH)/bin
TEST       =     $(ROOTPATH)/test

OBJLIST    =     $(COM)/dlist.o
OBJTOOL    =     $(COM)/tools.o
MAIN       =     $(COM)/main.o

TARGET     =     $(BIN)/dlist

all : com 

$(OBJLIST):
	$(CC) -c $(SRC)/dlist.c -o $(OBJLIST) -I $(HEAD)
	$(CC) -c $(SRC)/tools.c -o $(OBJTOOL) -I $(HEAD)

com:$(OBJLIST)
	@echo "-objects-"

test:$(OBJLIST)
	@echo "-test-"
	$(CC) -c $(TEST)/main.c -o $(MAIN) -I $(HEAD)
	$(CC)  $(OBJLIST) $(OBJTOOL) $(MAIN) -o $(TARGET)
	@echo "---------"
	@date

.PHONE:
clean:
	rm -f $(OBJLIST) $(OBJTOOL) $(MAIN) $(TARGET) 
