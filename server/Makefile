ROOT_PATH=$(shell pwd)
DATA_POOL_PATH=$(ROOT_PATH)/../data_pool
COMM_PATH=$(ROOT_PATH)/../comm
JSON_PATH=$(ROOT_PATH)/../json_lib
INCLUDE=-I$(COMM_PATH) -I$(JSON_PATH)/include -I$(DATA_POOL_PATH)
LIB_PATH=-L$(JSON_PATH)/lib -L/usr/lib/
LIB=-ljson -static -lpthread  
BIN=udp_server
CC=g++
SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(DATA_POOL_PATH); ls *.cpp)
SRC+=$(shell cd $(COMM_PATH); ls *.cpp)
OBJ=$(SRC:.cpp=.o)

$(BIN):$(OBJ)
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB) 
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMM_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(DATA_POOL_PATH)/%.cpp
	$(CC) -c $< 



.PHONY:clean
clean:
	rm -f $(BIN) *.o

.PHONY:debug
debug:
	@echo $(SRC)
	@echo $(OBJ)


