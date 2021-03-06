/*
 * MemLib.h
 *
 * Created: 15/03/2022 20:55:20
 *  Author: blue
 */ 

 #include <stdint-gcc.h>
 #include <stdlib.h>
 #include <avr/pgmspace.h>

#ifndef MEMLIB_H_
#define MEMLIB_H_

typedef struct MemoryRegion{
	uint8_t* ptr;
	uint8_t element_count;
	uint32_t size;
}Region;

#ifndef MEM_MAX_REGION_SIZE	//	max size of one allocated block in bits
#define MEM_MAX_REGION_SIZE 540 //	== 60 * uint8_t	
#endif

#ifndef MEM_MALLOC_AMOUNT	//	multiple of 8 bits that gets allocated with each malloc or realloc
#define MEM_MALLOC_AMOUNT 10	//	10 * uint8_t = 80 bits per realloc
#endif

#ifndef NULL
#define NULL 0
#endif

#endif /* MEMLIB_H_ */

extern uint8_t mem_resize_region(Region* region);
extern uint8_t mem_write_string(Region* region, char* string);
extern uint8_t mem_write_byte(Region* region, uint8_t byte);
extern Region* mem_alloc_region(uint8_t elements);
extern void mem_free_region(Region* region);
