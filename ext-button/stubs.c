/*
 * *      stubs.c
 * *
 * *      Copyright (C) 2012 Jiri Pittner <jiri@pittnerovi.com>
 * *
 * *      This program is free software: you can redistribute it and/or modify
 * *      it under the terms of the GNU General Public License as published by
 * *      the Free Software Foundation, either version 3 of the License, or
 * *      (at your option) any later version.
 * *
 * *      This program is distributed in the hope that it will be useful,
 * *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 * *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * *      GNU General Public License for more details.
 * *      You should have received a copy of the GNU General Public License
 * *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * *
 * *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//these are just dummies except _sbrk which is essential for malloc

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
	__attribute__((weak)) void _kill(void) {}
	__attribute__((weak)) void _getpid(void) {}
	__attribute__((weak)) void _fstat(void) {}
	__attribute__((weak)) void _lseek(void) {}
	__attribute__((weak)) int _isatty(int i) {return 0;}
	__attribute__((weak)) void _close(void) {}
	__attribute__((weak)) void _exit(int i) {}

	/*appropriate definition of _heap and _heap_end has to be done in the linker script*/ 
	extern int _heap;
	extern int _heap_end;

	caddr_t  _sbrk ( int incr )
	{
		static unsigned char *heap = NULL;
		void *prev_heap;
		void *heap_end = &_heap_end;

		if (heap == NULL)  prev_heap = heap = (unsigned char *)&_heap; 

		if ((prev_heap + incr) < heap_end)
		{
			prev_heap = heap;
			heap += incr;
		}
		else return NULL;
		return (caddr_t) prev_heap;
	}

	//this gets overwritten by usartxxx.c
	__attribute__((weak)) 
		int _open(const char *pathname, int flags, mode_t mode) 
		{
			return -1;
		}


#pragma weak _write
	ssize_t _write(int fd, const void *buf, size_t count) {return -1;} 

	//#pragma weak _read
	__attribute__((weak))
		ssize_t _read(int fd, const void *buf, size_t count) {return -1;}


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
