CP := cp -f -u
MKDIR_P := mkdir -p
BIN_DIR := ./bin
RES_DIR := ./res

CXXFLAGS := -Wall -Wextra -Wpedantic --std=c++17

# NO USER SERVICEABLE PARTS BELOW THIS LINE
# ----------------------------------------------------------------------------
SRC := $(wildcard *.cc)
OBJ := $(SRC:.cc=.o)

.PRECIOUS: %.o

all: directories test

directories:
	${MKDIR_P} ${BIN_DIR}
	${CP} ${RES_DIR}/* ${BIN_DIR} || true

test: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o ${BIN_DIR}/test
	cd ${BIN_DIR} ; ./test ; cd ..

.phony:
clean:
	$(RM) $(OBJ) *~ ${BIN_DIR}/* ../*~
