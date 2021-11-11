#ifndef _AST_H_
#define _AST_H_

#include <list>
#include <string>

using namespace std;

class Expr;
class Statement;
class Declaration;
class Parameter;
typedef list<Expr *> ParameterList;
typedef list<Statement *> StatementList;
typedef list<Expr *> ArgumentList;

class Statement{
    public:
        int line;
        virtual void printResult() = 0;
};

class Expr{
    public:
        int line;
        virtual float getResult() = 0;
};


class Declarator : public Statement{
    public:
        Declarator(const char * id, Expr* arrayDeclaration,  int line){
            this->id = id;
            this->line = line;
            this->arrayDeclaration = arrayDeclaration;
        }
        const char * id;
        int line;
        Expr * arrayDeclaration;
        void printResult();
};

class MethodDefinition : public Statement{
    public:
        MethodDefinition(const char * id, ParameterList params, StatementList statement, int line){
            this->id = id;
            this->params = params;
            this->statement = statement;
            this->line = line;
        }

        const char * id;
        ParameterList params;
        StatementList statement;
        int line;
        void printResult();
};

class FloatExpr : public Expr{
    public:
        FloatExpr(float value, int line){
            this->value = value;
            this->line = line;
        }
        float value;
        float getResult();
};

class BinaryExpr : public Expr{
    public:
        BinaryExpr(char symbol ,Expr * expr1, Expr *expr2, int line){
            this->expr1 = expr1;
            this->expr2 = expr2;
            this->line = line;
            this->symbol = symbol;
        }
        Expr * expr1;
        Expr *expr2;
        char symbol;
        int line;
        float getResult();
        bool evaluate();
};

class IdExpr : public Expr{
    public:
        IdExpr(const char * id, int line){
            this->id = id;
            this->line = line;
        }
        const char * id;
        int line;
        float getResult();
};

class MethodInvocationStmt : public Statement{
    public:
        MethodInvocationStmt(const char * id, ArgumentList args, int line){
            this->id = id;
            this->args = args;
            this->line = line;
        }
        const char * id;
        ArgumentList args;
        int line;
        void printResult();
};

class WhileStatement: public Statement{
    public:
        WhileStatement(Expr * expr, StatementList stmt, int line){
            this->expr = expr;
            this->stmt = stmt;
            this->line = line;
        }
        Expr* expr;
        StatementList  stmt;
        int line;
        void printResult();
};

class ExprStatement : public Statement{
    public:
        ExprStatement(Expr * expr, int line){
            this->expr = expr;
            this->line = line;
        }
        Expr * expr;
        void printResult();
};
#endif