/*
 * MemLib.c
 *
 * Created: 15/03/2022 20:53:24
 * Author : blue
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

uint8_t mem_write_string(Region* region, char* string){
	const uint8_t len = (uint8_t)strlen_P(string) + 1;	//	store lenght of the string with the null-byte

	while(((region->element_count + len) * sizeof(uint8_t)) > region->size){
		if(!mem_resize_region(region)){return 0;}
	}

	for(uint8_t index = 0; index < len; index++){
		*(region->ptr + (region->element_count++)) = *(string + index);
	}

	region->size += (len * sizeof(uint8_t));
	return 1;
}

uint8_t mem_write_byte(Region* region, uint8_t byte){
	if(((region->element_count + 1) * sizeof(uint8_t)) > region->size){	//	check if byte fits in currently allocated space
		if(!mem_resize_region(region)){return 0;}	//	try allocating more space
	}

	*(region->ptr + (++region->element_count)) = byte;	//	increment element_count, and assign byte to correct space
	region->size += sizeof(uint8_t);	//	update size
	return 1;	//	return success	

}


Region* mem_alloc_region(uint8_t elements){
	Region* region = (Region*) malloc(sizeof(Region));	//	allocate space for the struct

	if(!region){return NULL;}	//	return NULL pointer if malloc failed
	region->element_count = 0;
	region->size = 0;
	region->ptr = (uint8_t*)malloc(((elements)?elements:MEM_MALLOC_AMOUNT) * sizeof(uint8_t));	//	if elements is 0, use MEM_MALLOC_AMOUNT
	
	if(region->ptr == NULL){return NULL;}	//	if allocating heap space failed, return NULL pointer

	return region;
}

void mem_free_region(Region* region){
	//	release all the resources used by the region
	free(region->ptr);
	free(region);
}
