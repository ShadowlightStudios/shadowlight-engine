#include "stdafx.h"

void RaiseErrorA(ErrorCode err, const char* fname, int line)
{
	switch (err)
	{
	case FILE_LOAD_FAIL:
	{
		printf("File does not exist");
		break;
	}
	case TEXTURE_FORMAT_FAIL:
	{
		printf("Failed to load texture, wrong format");
		break;
	}
	case TEXTURE_GEN_FAIL:
	{
		printf("Failed to load texture, failed to generate texture");
		break;
	}
	case ALLOCATION_ERROR:
	{
		printf("Failed to allocate (out of memory?)");
		break;
	}
	case SHADER_GEN_FAIL:
	{
		printf("Failed to create a shader object");
		break;
	}
	case SHADER_COMPILE_FAIL:
	{
		printf("Failed to compile shader");
		break;
	}
	case PROGRAM_CREATE_FAIL:
	{
		printf("Failed to create shader program");
		break;
	}
	case PROGRAM_LINK_FAIL:
	{
		printf("Failed to link shader");
		break;
	}
	case OUT_OF_MEMORY:
	{
		printf("Failed to allocate data; out of memory");
		break;
	}
	case LUMP_TYPE_ERROR:
	{
		printf("Lump type is not recognized");
		break;
	}
	case SCRIPT_NONEXISTENT:
	{
		printf("Attempt to load a nonexistent script");
		break;
	}
	default: return;
	}
	printf(" at %s:%i\n", fname, line);
}
