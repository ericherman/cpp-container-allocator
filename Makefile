ifeq ($(CXX),)
CXX := g++
#CXX := clang++
endif

default: patched

native: arg-allocator.cpp
	$(CXX) -o native arg-allocator.cpp
	./native

patched: arg-allocator.cpp
	$(CXX) -o patched \
		-I ./include/c++/8 \
		arg-allocator.cpp
	./patched

clean:
	rm -fv native patched
