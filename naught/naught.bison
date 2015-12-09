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
#include "astnodes/VariableDeclarationNode.h"
#include "astnodes/VariableDeclarationAssignNode.h"
#include "astnodes/StatementNode.h"
#include "astnodes/BlockNode.h"
#include "astnodes/ParameterNode.h"
#include "astnodes/ExpressionNode.h"
#include "astnodes/BinaryExpressionNode.h"
#include "astnodes/TermLiteralNode.h"
#include "astnodes/TermNode.h"
#include "astnodes/Types.h"

using namespace std;

extern int _WANT_DEBUG;
extern ModuleNode *AST;

%}

%code requires {
  #include "StrUtil.h"
  #include "astnodes/ModuleNode.h"
  #include "astnodes/VariableDeclarationNode.h"
  #include "astnodes/FunctionDefinitionNode.h"
  #include "astnodes/FunctionDeclarationNode.h"
  #include "astnodes/ParameterNode.h"
  #include "astnodes/Types.h"
  #include "astnodes/BlockNode.h"
  #include "astnodes/VariableDeclarationNode.h"
  #include "astnodes/VariableDeclarationAssignNode.h"
  #include "astnodes/StatementNode.h"
  #include "astnodes/ExpressionNode.h"
  #include "astnodes/BinaryExpressionNode.h"
  #include "astnodes/TermLiteralNode.h"
  #include "astnodes/TermNode.h"

}

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
  VariableDeclarationAssignNode* variabledeclarationassign;
  FunctionDefinitionNode*  functiondefinition;
  ParameterNode* parameter;
  string* str;
  BlockNode* blocknode;
  StatementNode* stat;
  TermNode* termnode;
  ExpressionNode* exp;

  vector<StatementNode*>* statementlist;
  vector<ParameterNode*>* parameterlist;
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

%token <str> TYPE
%token <str> STRING_LITERAL
%token <str> INT_LITERAL
%token <str> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module> module
%type <functiondefinition> funcdef
%type <blocknode> block
%type <variabledeclaration> vardecl
%type <functiondeclaration> funcdecl
%type <exp> expr
%type <termnode> term
%type <stat> stmt

%type <statementlist> stmt_list
%type <variabledeclarationlist> vardecl_list
%type <functiondeclarationlist> funcdecl_list
%type <parameter> param;
%type <parameterlist> param_list;
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
          }
        | funcdecl SEMI
          { $$ = new vector<FunctionDeclarationNode*>();
            $$->push_back($1);
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new FunctionDeclarationNode($2, false,$4);
          }
        | FUNCTION ID LPAREN  RPAREN
          { 
            $$ = new FunctionDeclarationNode($2, false, new vector<ParameterNode*>());
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { 
            $$ = new FunctionDeclarationNode($2, true, $4);
          }
        | SFUNCTION ID LPAREN  RPAREN
          { 
            $$ = new FunctionDeclarationNode($2, true, new vector<ParameterNode*>());
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
          { $$ = new VariableDeclarationNode();//$1, $2, false);
          }
       | TYPE ID ASSIGN expr
          { $$ = new VariableDeclarationAssignNode();//$1, $2, false, $4);
          }
       | EXTERN TYPE ID  /* extern variable */
          { $$ = new VariableDeclarationNode();//$1, $2, true);
          }
       ;


funcdef_list :
         funcdef 
         {
          $$ = new vector<FunctionDefinitionNode*>();
          $$->push_back($1);
         }
       | funcdef_list funcdef
         {
          $1->push_back($2);
          $$ = $1;
         }
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { $$ = new FunctionDefinitionNode($2, false, $4, $6);
          }
        | FUNCTION ID LPAREN RPAREN block
          { $$ = new FunctionDefinitionNode($2, false, new vector<ParameterNode*>(), $5);
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new FunctionDefinitionNode($2, true, $4, $6);
          }
        | SFUNCTION ID LPAREN RPAREN block
          { $$ = new FunctionDefinitionNode($2, true, new vector<ParameterNode*>(), $5);
          }
        ;

param_list : 
          param_list COMMA param
          { $1->push_back($3);
          }
        | param
          { $$ = new vector<ParameterNode*>();
            $$->push_back($1);
          }
        ;

param :
         TYPE ID
          { $$ = new ParameterNode($1, $2);
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new BlockNode($2, $3);
          }
	| LCBRACE              stmt_list RCBRACE
          { $$ = new BlockNode(new vector<VariableDeclarationNode*>(), $2);
          }
	| LCBRACE vardecl_list           RCBRACE
          { $$ = new BlockNode($2, new vector<StatementNode*>());
          }
        | LCBRACE RCBRACE
          { $$ = new BlockNode(new vector<VariableDeclarationNode*>(), new vector<StatementNode*>());
          }
        ;

stmt_list :
          stmt_list stmt
          { $1->push_back($2);
            $$ = $1;
          }
        | stmt
          { $$ = new vector<StatementNode*>();
            $$->push_back($1);
          }
       ;

stmt : 
         expr SEMI
          { $$ = new StatementNode(false, $1);
          }
       | RETURN expr SEMI
          { $$ = new StatementNode(true, $2);
          }
     ;

expr : 
        expr ADD expr
        { $$ = new BinaryExpressionNode(new string("+"), $1, $3);
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
        { $$ = new TermLiteralNode($1, new string("string"));
        }
      | INT_LITERAL
        { $$ = new TermLiteralNode($1, new string("int"));
        }
      | ID
        { //
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
