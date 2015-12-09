#ifndef NAUGHTTYPES_H
#define NAUGHTTYPES_H
#include <map>
// maps naught types to c types.
static std::map<string,string> naughtToC = {
	{"string", "char*"},
	{"int", "int32_t"},
	{"pointer", "int*"}
};	
#endif

#ifndef TABS
#define TABS(x,y) \
	for(int temp__ = 0; temp__ < (y); temp__++) { \
        (x) << "  "; \
      }
#endif
