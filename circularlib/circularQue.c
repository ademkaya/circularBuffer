#include "circularQue.h"

static CircularQue_Typedef* Init_CircularQue(uint16_t capacity);
static bool					UpdateCapacity(CircularQue_Typedef* ptr, uint16_t capacity);
static void					Clear(CircularQue_Typedef* quePtr);
static bool					IsFull(CircularQue_Typedef* quePtr);
static void*				Pop(CircularQue_Typedef* quePtr);
static void					Push(CircularQue_Typedef* quePtr, void* data);
static bool					Free(CircularQue_Typedef** ptr);

/**/
bool Initialize_CircularQueLib(CircularQueFunctions_Typedef** ptr)
{
	/* Once initialized it doesn't accept further initialization calls*/
	if (*ptr != NULL)
		return	false;

		(*ptr) = (CircularQueFunctions_Typedef*)calloc(1, sizeof(CircularQueFunctions_Typedef));
		if (!(*ptr))
			return false;
	
	/* ptr is expected to be initialized properly */
	(*ptr)->Init_CircularQue = &Init_CircularQue;
	(*ptr)->UpdateCapacity	 = &UpdateCapacity;
	(*ptr)->Clear			 = &Clear;
	(*ptr)->IsFull			 = &IsFull;
	(*ptr)->Pop				 = &Pop;
	(*ptr)->Push			 = &Push;
	(*ptr)->Free			 = &Free;

	return true;
}

static bool Free(CircularQue_Typedef** ptr) {

	if ((ptr == NULL)||(*ptr== NULL))
		return false;

	free((void**)((*ptr)->QuePtr));
	(*ptr)->QuePtr = 0;

	free((void*)*ptr);
	*ptr = 0;

	return true;
}

static CircularQue_Typedef* Init_CircularQue(uint16_t capacity) {

	CircularQue_Typedef* retVal = NULL;

	retVal = (CircularQue_Typedef*)calloc(1, sizeof(CircularQue_Typedef));
	if (retVal == NULL)
		return NULL;

	retVal->QuePtr = (void**)calloc(capacity, sizeof(void*));
	if (retVal->QuePtr == NULL)
		return NULL;

	retVal->Size	 = capacity;
	retVal->IsFull   = false;

	retVal->TailCntr = -1;
	retVal->HeadCntr = 0;

	return retVal;
}

static bool UpdateCapacity(CircularQue_Typedef* ptr, uint16_t capacity) {
	bool retVal = false;

	if ((!ptr->QuePtr)||(ptr == NULL))				/* if not initialized previously */
		return retVal;

	ptr->QuePtr = (void**)realloc(ptr->QuePtr, (capacity * sizeof(void*)));
	if (ptr->QuePtr == NULL) {
		/* assign previous size back again */
		ptr->QuePtr = (void**)realloc(ptr->QuePtr, (ptr->Size * sizeof(void*)));
		return retVal;
	}

	/* clear rest of the array */
	if (((int)(capacity - ptr->Size)) > 0) {
		memset(ptr->QuePtr + ptr->Size, 0, (capacity - ptr->Size) * sizeof(void*));
	}

	ptr->Size = capacity;

	return true;
}

static void Clear(CircularQue_Typedef* quePtr) {

	if (quePtr == NULL)
		return;

	quePtr->IsFull = false;
	quePtr->TailCntr = -1;
	quePtr->HeadCntr = 0;

	memset(quePtr->QuePtr, 0, (quePtr->Size)*sizeof(void*));
}

static void* Pop(CircularQue_Typedef* quePtr) {
	CircularQue_Typedef* retVal = NULL;

	if (quePtr == NULL)
		return retVal;

	retVal = quePtr->QuePtr[quePtr->HeadCntr];

	quePtr->QuePtr[quePtr->HeadCntr] = 0;

	quePtr->HeadCntr = ((quePtr->HeadCntr + 1) % quePtr->Size);

	/* update IsFull var */
	IsFull(quePtr);

	return retVal;
}

static bool IsFull(CircularQue_Typedef* quePtr) {
	bool retVal = false;

	if (quePtr == NULL)
			return retVal;

	if (quePtr->HeadCntr == ((quePtr->TailCntr + 1) % quePtr->Size))
	{
		retVal = true;
		quePtr->IsFull = true;
	}
	else {
		quePtr->IsFull = false;
	}

	return retVal;
}

static void Push(CircularQue_Typedef* quePtr, void* data) {

	if (quePtr == NULL)
			return;

	/* increase the pointer // new place to written */
	quePtr->TailCntr = ((quePtr->TailCntr + 1) % quePtr->Size);
	/* 0 1 2 3 4 ..... n-1 */
	quePtr->QuePtr[quePtr->TailCntr] = data;	

	if (quePtr->IsFull)
		quePtr->HeadCntr = ((quePtr->HeadCntr + 1) % quePtr->Size);

	IsFull(quePtr);
}
