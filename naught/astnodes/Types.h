#ifndef NAUGHTTYPES_H
#define NAUGHTTYPES_H
#include <map>

// maps naught types to c types.
static std::map<string,string> naughtToC = {
	{"string", "char*"},
	{"int", "int32_t"}
};	

enum NodeTypes {
	// NODE ,
 //    MODULE = 2,
 //    FUNDEC_LIST = 3,
 //    FUNCDECL = 4,
 //    VARDEC_LIST = 283,
 //    VARDEC = 284,
 //    FUNCDEF_LIST = 285,
 //    FUNCDEF = 286,
 //    PARAM_LIST = 287,
 //    PARAM = 288,
 //    BLOCK = 289,
 //    STMT_LIST = 290,
 //    STMT = 291,
 //    EXPR = 292,
 //    TERM = 293,
 //    ARGLIST = 294,
 //    EXPR_ADD = 295,
 //    EXPR_ASSIGN = 296,
 //    EXPR_DIV = 297,
 //    EXPR_STAR = 298,
 //    EXPR_SUB = 299,
 //    EXPR_TERNARY = 300,
 //    TERM_EXPR = 301,
 //    TERM_FUNCCALL = 302,
 //    TERM_ID = 303,
 //    TERM_LIT = 304,
 //    TERM_UNARY = 305
};

#endif //NAUGHTTYPES_H