#ifndef _CIRCULAR_QUE_H_
#define _CIRCULAR_QUE_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct CircularQue {
	int32_t			 HeadCntr;
	int32_t			 TailCntr;

	void**			 QuePtr;			
	uint32_t		 Size;

	bool			 IsFull;
}CircularQue_Typedef;

typedef struct {
	CircularQue_Typedef*		(*Init_CircularQue)		(uint16_t capacity);
	bool						(*UpdateCapacity)		(CircularQue_Typedef*  quePtr, uint16_t capacity);

	void						(*Push)					(CircularQue_Typedef*  quePtr, void* data);
	void*						(*Pop)					(CircularQue_Typedef*  quePtr);
	bool						(*Free)					(CircularQue_Typedef*  quePtr);

	bool						(*IsFull)				(CircularQue_Typedef*  quePtr);
	void						(*Clear)				(CircularQue_Typedef** quePtr);
}CircularQueFunctions_Typedef;

bool Initialize_CircularQueLib(CircularQueFunctions_Typedef** ptr);

#endif

