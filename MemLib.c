/*
 * MemLib.c
 *
 * Created: 15/03/2022 20:53:24
 * Author : arthu
 */ 

 #include "MemLib.h"

uint8_t mem_resize_region(Region* region){
	if((region->size + (sizeof(uint8_t) * MEM_MALLOC_AMOUNT)) > MEM_MAX_REGION_SIZE){	//	check if the realloc would fit withing MEM_MAX_REGION_SIZE boundary
		return 0;	//	return failure
	} else {
		region->size += sizeof(uint8_t) * MEM_MALLOC_AMOUNT;	//	recalculate size	
		realloc(region->ptr, region->size);	//	realloc the block
		return 1;	//	return success
	}
}

uint8_t mem_write_byte(Region* region, uint8_t byte){
	if((region->element_count * sizeof(uint8_t)) >= region->size){	//	check if byte fits in currently allocated space
		if(!mem_resize_region(region)){return 0;}	//	try allocating more space
	} else {

		(region->ptr + (++region->element_count)) = byte;
		region->size += sizeof(uint8_t);
	}
}


Region* mem_alloc_region(uint8_t elements){
	Region* region = (Region*) malloc(sizeof(Region));	//	allocate space for the struct

	if(region){return NULL;}	//	return NULL pointer if malloc failed
	region->element_count = 0;
	region->size = 0;
	region->ptr = (uint8_t*)malloc((elements)?elements:MEM_MALLOC_AMOUNT);	//	if elements is 0, use MEM_MALLOC_AMOUNT
	
	if(region->ptr == NULL){return NULL;}	//	if allocating heap space failed, return NULL pointer

	return region;
}

void mem_free_region(Region* region){
	//	release all the resources used by the region
	free(region->ptr);
	free(region);
}
