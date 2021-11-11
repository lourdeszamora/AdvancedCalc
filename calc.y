%code requires{
    #include "ast.h"
}

%{

    #include <cstdio>
    using namespace std;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
        fprintf(stderr, "Line: %d, error: %s\n", yylineno, s);
    }

    #define YYERROR_VERBOSE 1
%}

%union{
    const char * string_t;
    float float_t;
    Expr * expr_t;
    Statement * statement_t;
}

%token EOL
%token ADD SUB MUL DIV IF THEN ENDIF WHILE DO DONE ELSE LET
%token<string_t> TK_ID
%token<float_t>  TK_LIT_FLOAT

%type <statement_t> while_stmt
%type<expr_t> term

%%
start: input{
    list<Statement *>::iterator it = $1->begin();
    while(it != $1->end()){
        printf("semantic result: %d \n",(*it)->printResult());
        it++;
    }
}

input: /* empty */ 
    | input method_decl
    | input variable_decl
    | input expr_stmt
    | input while_stmt
    | input method_invoc;
    ;

method_decl: LET TK_ID '(' param_list ')' '=' statements ';' { 
                    $$ = new MethodDefinition( $2, *$4, $6, yylineno );
                    delete $4;
                    };

param_list: param_list ',' TK_ID {$$ = $1; $$->push_back(new IdExpr($3, yylineo));}
            | TK_ID  { $$ = new ParameterList; $$->push_back(new IdExpr($1, yylineno)); }
            ;

statements:  statement { $$ = new StatementList; $$->push_back($1); }
    | statements statement ';'  { $$ = $1; $$->push_back($2); }
    ;

statement: variable_decl {$$ = $1;}
    |expr_stmt {$$ = $1;}
    | while_stmt {$$ = $1;}
    | method_invoc {$$ = $1;}
    ;

method_invoc: TK_ID '(' param_list ')' { $$ = new MethodInvocationStmt($1, *$3, yylineo); }

variable_decl: LET TK_ID '=' expr_stmt { $$ = new Declarator($1,$3,yylineno); }

expr_stmt:  expr_stmt ADD factor { $$ = new BinaryExpr( $2, $1, $3, yylineno); }
    | expr_stmt SUB factor { $$ = new BinaryExpr( $2, $1, $3, yylineno); }
    | factor { $$ = $1 }
    ;

factor: factor MUL term { $$ = new BinaryExpr( $2, $1, $3, yylineno); }
    | factor DIV term { $$ = new BinaryExpr( $2, $1, $3, yylineno); }
    | term { $$ = $1 }
    ;

term: TK_LIT_FLOAT {$$ = new FloatExpr($1, yylineo); }
    | TK_ID { $$ = new IdExpr($1, yylineno); }
    ;

while_stmt: WHILE '(' rel_expr ')' DO statements DONE { $$ = new WhileStatement( $3, $6, yylineno); }

rel_expr: term '>' term { $$ = new BinaryExpr( $2, $1, $3, yylineno); }
        | term '<' term { $$ = new BinaryExpr( $2, $1, $3, yylineno); }
        ;

%%
