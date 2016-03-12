#ifndef NAUGHTTYPES_H
#define NAUGHTTYPES_H
#include <map>
// maps naught types to c types.
static std::map<string,string> naughtToC = {
	{"string", "char*"},
	{"int", "int32_t"},
	{"pointer", "int*"},
	{"", "int"}
};	
#endif

#ifndef TABS
#define TABS(x,y) \
	for(int temp__ = 0; temp__ < (y); temp__++) { \
        (x) << "  "; \
      }
#endif

#ifndef NAUGHT_ERR
#define NAUGHT_ERR
static void err(string msg) {
	cerr << "Error: " << msg << endl << "Exiting naughtyc...";
	exit(2);
}

static void wrn(string msg) {
	cerr << "Warning: " << msg << endl;
}
#endif