%option noyywrap
%option yylineno

%{
    #include "tokens.h"
%}

%%
"+" { return ADD; }
"=" { return '='; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"(" { return '('; }
")" { return ')'; }
"," { return ','; }
";" { return ';'; }
">" { return '>'; }
">" { return '<'; }
"let" { return LET; }
"while" { return WHILE; }
"do" { return DO; }
"done" { return DONE; }
[\n] { return EOL; }
[ \t] { /* ignorar */ }
. { printf("invalido %c\n", yytext[0]); }
%%