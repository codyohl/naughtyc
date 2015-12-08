%{
#define YY_NO_UNPUT

#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <vector>

#include "yy.h"
#include "StrUtil.h"
#include "astnodes/ModuleNode.h"
#include "astnodes/VariableDeclarationNode.h"
#include "astnodes/FunctionDefinitionNode.h"
#include "astnodes/FunctionDeclarationNode.h"

using namespace std;

extern int _WANT_DEBUG;
extern ModuleNode *AST;

%}

/***************************************
 * These are the union of the data types
 * that are associated with AST nodes.
 * They should all be pointers.
 * The C++ type is the first entry.
 * The second entry is a symbolic
 * name used later in this file.
 ***************************************/
%union {
  StrUtil*    string_val;
  ModuleNode* module;
  FunctionDeclarationNode* functiondeclaration;
  VariableDeclarationNode* variabledeclaration; 
  FunctionDefinitionNode*  functiondefinition;
  std::vector<FunctionDeclarationNode*>* functiondeclarationlist;
  vector<VariableDeclarationNode*>* variabledeclarationlist;
  vector<FunctionDefinitionNode*>*  functiondefinitionlist;
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_val> ASSIGN
%right <string_val> COLON QUESTION
%left <string_val> ADD SUB
%left <string_val> STAR DIV
%right <string_val> UNARY_OP
/*********************************************************
 * Okay, that's it -- after this order doesn't matter
 *********************************************************/

/**********************************************************
 * Here (and in the precedence/associativity declarations 
 * above, we're defining symbols that can be returned by
 * the lexer. 
 **********************************************************/

%token <string_val> LCBRACE RCBRACE RPAREN LPAREN SEMI COMMA EXTERN FUNCTION SFUNCTION RETURN

%token <string_val> TYPE
%token <string_val> STRING_LITERAL
%token <string_val> INT_LITERAL
%token <string_val> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module> module
%type <functiondefinition> funcdef
%type <string_val> block
%type <variabledeclaration> vardecl
%type <functiondeclaration> funcdecl
%type <string_val> expr
%type <string_val> term
%type <string_val> stmt

%type <string_val> stmt_list
%type <variabledeclarationlist> vardecl_list
%type <functiondeclarationlist> funcdecl_list
%type <string_val> param;
%type <string_val> param_list;
%type <functiondefinitionlist> funcdef_list
%type <string_val> arglist;

/*********************************************
 * This is the terminal symbol.  The entire
 * naught program should be reducable to this
 * symbol.
 *********************************************/
%start module

%%

/********************************************************
 * It will take a bit of study, but these rules are
 * the easiest to understand explanation of the grammar.
 ********************************************************/

module :
         funcdecl_list vardecl_list funcdef_list
          { AST = new ModuleNode($1, $2, $3);
            $$ = AST;
          }
        |              vardecl_list funcdef_list
          { AST = new ModuleNode(new vector<FunctionDeclarationNode *>() ,$1, $2);
            $$ = AST;
          }
        | funcdecl_list             funcdef_list
          { AST = new ModuleNode($1, new vector<VariableDeclarationNode *>(), $2);
            $$ = AST;
          }
        |                            funcdef_list
          { AST = new ModuleNode(new vector<FunctionDeclarationNode *>(), new vector<VariableDeclarationNode *>(), $1);
            $$ = AST;
          }
        | funcdecl_list vardecl_list
          { AST = new ModuleNode($1, $2, new vector<FunctionDefinitionNode *>());
            $$ = AST;
          }
        |              vardecl_list
          { AST = new ModuleNode(new vector<FunctionDeclarationNode *>(), $1, new vector<FunctionDefinitionNode *>());
            $$ = AST;
          }
        | funcdecl_list             
          { AST = new ModuleNode($1, new vector<VariableDeclarationNode *>(), new vector<FunctionDefinitionNode *>());
            $$ = AST;
          }
        |
          { AST = new ModuleNode(new vector<FunctionDeclarationNode *>(), new vector<VariableDeclarationNode *>(), new vector<FunctionDefinitionNode *>());
            $$ = AST;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $1->push_back($2);
            $$ = $1;
            //$$ = new StrUtil(*$1 + *$2 + *$3);
            ////cout << *$$ << " -> funcdecl_list " << endl;
          }
        | funcdecl SEMI
          { $$ = new vector<FunctionDeclarationNode*>();
            $$->push_back($1);
            //$$ = new StrUtil(*$1 + *$2);
            ////cout << *$$ << " -> funcdecl_list " << endl;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new FunctionDeclarationNode();
          }
        | FUNCTION ID LPAREN  RPAREN
          { 
            $$ = new FunctionDeclarationNode();
            //$$ = new StrUtil(*$1 + *$2 +*$3 +*$4);
            //cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new FunctionDeclarationNode();
            //$$ = new StrUtil(*$1 + *$2 +*$3 +*$4 +*$5);
            //cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN  RPAREN
          { $$ = new FunctionDeclarationNode();
            //$$ = new StrUtil(*$1 + *$2 +*$3 +*$4);
            //cout << *$$ << " -> funcdecl " << endl;
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { $1->push_back($2);
            $$ = $1;
          }
        | vardecl SEMI
          { $$ = new vector<VariableDeclarationNode*>();
            $$->push_back($1);
          }
        ;

vardecl : 
         TYPE ID
          { //$$ = new StrUtil(*$1 + *$2);
            //cout << *$$ << " -> vardecl " << endl;
          }
       | TYPE ID ASSIGN expr
          { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4);
            //cout << *$$ << " -> vardecl " << endl;
          }
       | EXTERN TYPE ID  /* extern variable */
          { //$$ = new StrUtil(*$1 + *$2);
            //cout << *$$ << " -> vardecl " << endl;
          }
       ;


funcdef_list :
         funcdef
       | funcdef_list funcdef
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5 + *$6);
            //cout << *$$ << " -> funcdef " << endl;
          }
        | FUNCTION ID LPAREN RPAREN block
          { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5);
            //cout << *$$ << " -> funcdef " << endl;
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5 + *$6);
            //cout << *$$ << " -> funcdef " << endl;
          }
        | SFUNCTION ID LPAREN RPAREN block
          { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5);
            //cout << *$$ << " -> funcdef " << endl;
          }
        ;

param_list : 
          param_list COMMA param
          { //$$ = new StrUtil(*$1 + *$2 + *$3);
            //cout << *$$ << " -> param_list " << endl;
          }
        | param
          { //$$ = new StrUtil(*$1);
            //cout << *$$ << " -> param_list " << endl;
          }
        ;

param :
         TYPE ID
          { //$$ = new StrUtil(*$1 + *$2);
            //cout << *$$ << " -> param " << endl;
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4);
            //cout << *$$ << " -> block " << endl;
          }
	| LCBRACE              stmt_list RCBRACE
          { //$$ = new StrUtil(*$1 + *$2 + *$3);
            //cout << *$$ << " -> block " << endl;
          }
	| LCBRACE vardecl_list           RCBRACE
          { //$$ = new StrUtil(*$1 + *$2 + *$3);
            //cout << *$$ << " -> block " << endl;
          }
        | LCBRACE RCBRACE
          { //$$ = new StrUtil(*$1 + *$2);
            //cout << *$$ << " -> block " << endl;
          }
        ;

stmt_list :
          stmt_list stmt
          { //$$ = new StrUtil(*$1 + *$2);
            //cout << *$$ << " -> stmt_list " << endl;
          }
        | stmt
          { //$$ = new StrUtil(*$1);
            //cout << *$$ << " -> stmt_list " << endl;
          }
       ;

stmt : 
         expr SEMI
          { //$$ = new StrUtil(*$1 + *$2);
            //cout << *$$ << " -> stmt " << endl;
          }
       | RETURN expr SEMI
          { //$$ = new StrUtil(*$1 + *$2 + *$3);
            //cout << *$$ << " -> stmt " << endl;
          }
     ;

expr : 
        expr ADD expr
        { //$$ = new StrUtil(*$1 + *$2 + *$3);
          //cout << *$$ << " -> expr" << endl;
        }
      | expr SUB expr
        { //$$ = new StrUtil(*$1 + *$2 + *$3);
          //cout << *$$ << " -> expr" << endl;
        }
      | expr STAR expr
        { //$$ = new StrUtil(*$1 + *$2 + *$3);
          //cout << *$$ << " -> expr" << endl;
        }
      | expr DIV expr
        { //$$ = new StrUtil(*$1 + *$2 + *$3);
          //cout << *$$ << " -> expr" << endl;
        }
      | expr QUESTION expr COLON expr
        { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5);
          //cout << *$$ << " -> expr" << endl;
        }
      | term  ASSIGN expr
        { //$$ = new StrUtil(*$1 + *$2 + *$3);
          //cout << *$$ << " -> expr" << endl;
        }
      | term
        { //$$ = new StrUtil(*$1);
          //cout << *$$ << " -> expr" << endl;
        }
      ;

term :
        STRING_LITERAL
        { //$$ = new StrUtil(*$1);
          //cout << *$$ << " -> term" << endl;
        }
      | INT_LITERAL
        { //$$ = new StrUtil(*$1);
          //cout << *$$ << " -> term" << endl;
        }
      | ID
        { //$$ = new StrUtil(*$1);
          //cout << *$$ << " -> term" << endl;
        }
      | LPAREN expr RPAREN
       { //$$ = new StrUtil( *$1 + *$2 + *$3 );
         //cout << *$$ << " -> term" << endl;
        }
      | UNARY_OP term
        { //$$ = new StrUtil( *$1 + *$2);
          //cout << *$$ << " -> term" << endl;
        }
      | ID LPAREN arglist RPAREN  /* function call */
       { //$$ = new StrUtil(*$1 + *$2 + *$3 + *$4);
         //cout << *$$ << " -> term" << endl;
       }
      | ID LPAREN RPAREN  /* function call */
       { //$$ = new StrUtil(*$1 + *$2 + *$3);
         //cout << *$$ << " -> term" << endl;
       }
      ;

arglist :
        expr
        { //$$ = new StrUtil(*$1);
          //cout << *$$ << " -> arglist" << endl;
        }
      | arglist COMMA expr
        { //$$ = new StrUtil( *$1 + *$2 + *$3 );
        //cout << *$$ << " -> arglist" << endl;
        }
      ;

%%
