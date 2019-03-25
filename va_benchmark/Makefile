GENERATED_CODE_DIR	:=va_benchmark_CODE
CXXFLAGS 		+=-std=c++11 -Wall -Wpedantic -Wextra

.PHONY: all clean generated_code

all: va_benchmark

va_benchmark: simulator.cc generated_code
	$(CXX) $(CXXFLAGS)  simulator.cc -o va_benchmark -L$(GENERATED_CODE_DIR) -lrunner -Wl,-rpath=$(GENERATED_CODE_DIR)

generated_code:
	$(MAKE) -C $(GENERATED_CODE_DIR)
