#include "mx/mx_file.h"

int mx_read_file(const char* path, size_t* size, void* buffer) {
	FILE* fptr;
	fptr = fopen(path, "rb");

	if(fptr == NULL) {
		return -1;
	}

	fseek(fptr, 0, SEEK_END);
	*size = ftell(fptr);

	if(buffer == NULL) {
		fclose(fptr);
		return MX_SUCCESS;
	}

	rewind(fptr);
	fread(buffer, 1, *size, fptr);

	fclose(fptr);
	return MX_SUCCESS;
}
