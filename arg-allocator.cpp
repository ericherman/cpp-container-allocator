/* foo.cpp
   Copyright (C) 2018 Eric Herman <eric@freesa.org>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

	https://www.gnu.org/licenses/lgpl-3.0.txt
	https://www.gnu.org/licenses/gpl-3.0.txt
 */
#include <limits>
#include <list>
#include <iostream>

template <typename T> class ArgAllocator {
	char my_c;

      public:
	typedef T value_type;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template <typename U> struct rebind { typedef ArgAllocator<U> other; };

#ifdef ARG_ALLOCATOR_DEFAULT_CTR
	ArgAllocator() { my_c = '\0'; }
#endif
	inline explicit ArgAllocator(char c) { my_c = c; }
	inline ~ArgAllocator() {}
	inline ArgAllocator(ArgAllocator const &other) { my_c = other.my_c; }
	inline ArgAllocator(ArgAllocator &&other) { my_c = other.my_c; }

	template <typename U>
	inline ArgAllocator(ArgAllocator<U> const &) {}
	template <typename U>
	inline ArgAllocator(ArgAllocator<U>&&) {}

	inline pointer address(reference r) const { return &r; }
	inline const_pointer address(const_reference r) const { return &r; }

	inline pointer
	allocate(size_type cnt,
		 typename std::allocator<void>::const_pointer = 0) {
		return reinterpret_cast<pointer>(
			::operator new(cnt * sizeof(T)));
	}

	inline void deallocate(pointer p, size_type) { ::operator delete(p); }

	inline size_type max_size() const {
		return std::numeric_limits<size_type>::max() / sizeof(T);
	}

	inline void construct(pointer p, const T &t) { new (p) T(t); }
	inline void destroy(pointer p) { p->~T(); }

	inline bool operator==(ArgAllocator const &) const { return true; }
	inline bool operator!=(ArgAllocator const &a) const { return false; }

	ArgAllocator& operator =(ArgAllocator const& other) { my_c = other.my_c; return *this; }
	ArgAllocator& operator =(ArgAllocator&& other) { my_c = other.my_c; return *this; }
}; //    end of class ArgAllocator

typedef std::list<int, ArgAllocator<int>> Intlist;

int main(void) {
	ArgAllocator<int> foo('a');
	Intlist l(foo);
	l.push_back(3);
	l.push_back(1);
	l.push_back(4);
	l.sort();

	for (auto i = l.begin(); i != l.end(); ++i) {
		std::cout << *i << ",";
	}
	std::cout << "\n";
}
