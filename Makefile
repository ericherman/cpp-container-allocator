
default: demo

demo: arg-allocator.cpp
	g++ -o demo arg-allocator.cpp
	./demo


sad: arg-allocator.cpp
	g++ -DARG_ALLOCATOR_DEFAULT_CTR -o sad arg-allocator.cpp
	./sad

clean:
	rm -fv sad demo *.o
