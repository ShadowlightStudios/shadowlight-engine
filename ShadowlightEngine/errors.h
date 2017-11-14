#pragma once

#define RaiseError(err) { \
RaiseErrorA(err, __FILE__, __LINE__); \
};
enum ErrorCode { TEXTURE_FORMAT_FAIL, TEXTURE_GEN_FAIL, FILE_LOAD_FAIL, ALLOCATION_ERROR, SHADER_GEN_FAIL, SHADER_COMPILE_FAIL, PROGRAM_LINK_FAIL, PROGRAM_CREATE_FAIL, OUT_OF_MEMORY, LUMP_TYPE_ERROR, SCRIPT_NONEXISTENT};
void RaiseErrorA(ErrorCode, const char*, int);

const char * GetOpenALErrorString(int errID);
void CheckOpenALError(const char* stmt, const char* fname, int line);
const char * GetOpenGLErrorString(int errID);
void CheckOpenGLError(const char* stmt, const char* fname, int line);