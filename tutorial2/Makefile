GENERATED_CODE_DIR	:=tutorial2_CODE
CXXFLAGS 		+=-std=c++11 -Wall -Wpedantic -Wextra

.PHONY: all clean generated_code

all: tutorial2

tutorial2: simulator.cc generated_code
	$(CXX) $(CXXFLAGS)  simulator.cc -o tutorial2 -L$(GENERATED_CODE_DIR) -lrunner -Wl,-rpath=$(GENERATED_CODE_DIR)

generated_code:
	$(MAKE) -C $(GENERATED_CODE_DIR)
