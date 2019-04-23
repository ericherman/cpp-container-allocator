
default: fix

demo: arg-allocator.cpp
	g++ -o demo arg-allocator.cpp
	./demo

fix: arg-allocator.cpp
	g++ -o fix \
		-I ./include/c++/8 \
		arg-allocator.cpp
	./fix

sad: arg-allocator.cpp
	g++ -DARG_ALLOCATOR_DEFAULT_CTR -o sad arg-allocator.cpp
	./sad

clean:
	rm -fv sad demo fix *.o
