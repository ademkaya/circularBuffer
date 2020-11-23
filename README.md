# Circular Buffer

Simple circular buffer library written in C language.


### Usage
```sh
	#define		CBSize		8
	CircularQueFunctions_Typedef* CQue = NULL;
	CircularQue_Typedef*		  ptr  = NULL;
	int main(){
		Initialize_CircularQueLib(&CQue);
		ptr = CQue->Init_CircularQue(CBSize);
		CQue->Clear(ptr);

		CQue->Push(ptr, (void*)5);
		int g = CQue->Pop(ptr);

		CQue->Free(&ptr);

		return 0;
	}
```


### Note
Data taken as void pointer (void*) and used as it is. If the data pointer is changed also circular buffer includings will be altered.
