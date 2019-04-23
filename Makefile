ifeq ($(CXX),)
CXX := g++
#CXX := clang++
endif

default: fix

demo: arg-allocator.cpp
	$(CXX) -o demo arg-allocator.cpp
	./demo

fix: arg-allocator.cpp
	$(CXX) -o fix \
		-I ./include/c++/8 \
		arg-allocator.cpp
	./fix

sad: arg-allocator.cpp
	$(CXX) -DARG_ALLOCATOR_DEFAULT_CTR -o sad arg-allocator.cpp
	./sad

clean:
	rm -fv sad demo fix *.o
