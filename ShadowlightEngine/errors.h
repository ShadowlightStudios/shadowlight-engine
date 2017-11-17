#pragma once

#define RaiseError(err, message) { \
RaiseErrorA(err, message, __FILE__, __LINE__); \
};
void RaiseErrorA(const char*, const char*, const char*, int);