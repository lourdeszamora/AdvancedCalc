#ifndef _AST_H_
#define _AST_H_

#include <list>
#include <string>

using namespace std;

class Expr;
class InitDeclarator;
class Statement;
class Declaration;
class Parameter;
typedef list<Expr *> InitializerElementList;
typedef list<InitDeclarator *> InitDeclaratorList;
typedef list<Expr *> ParameterList;
typedef list<Statement *> StatementList;
typedef list<Expr *> ArgumentList;
typedef list<Declaration *> DeclarationList;

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

class Initializer{
    public:
        Initializer(InitializerElementList expressions, int line){
            this->expressions = expressions;
            this->line = line;
        }
        InitializerElementList expressions;
        int line;
};

class Declarator{
    public:
        Declarator(string id, Expr* arrayDeclaration,  int line){
            this->id = id;
            this->line = line;
            this->arrayDeclaration = arrayDeclaration;
        }
        string id;
        int line;
        Expr * arrayDeclaration;
};

class InitDeclarator{
    public:
        InitDeclarator(Declarator * declarator, Initializer * initializer, int line){
            this->declarator = declarator;
            this->initializer = initializer;
            this->line = line;
        }
        Declarator * declarator;
        Initializer * initializer;
        int line;
};

class Declaration{
    public:
        Declaration( InitDeclaratorList declarations, int line){
            this->declarations = declarations;
            this->line = line;
        }
        InitDeclaratorList declarations;
        int line;
        int evaluateSemantic();
};

class BlockStatement : public Statement{
    public:
        BlockStatement(StatementList statements, DeclarationList declarations, int line){
            this->statements = statements;
            this->declarations = declarations;
            this->line = line;
        }
        StatementList statements;
        DeclarationList declarations;
        int line;
        void printResult();
};

class MethodDefinition : public Statement{
    public:
        MethodDefinition(string id, ParameterList params, Statement * statement, int line){
            this->id = id;
            this->params = params;
            this->statement = statement;
            this->line = line;
        }

        string id;
        ParameterList params;
        Statement * statement;
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
};

class IdExpr : public Expr{
    public:
        IdExpr(string id, int line){
            this->id = id;
            this->line = line;
        }
        string id;
        int line;
        float getResult();
};

class MethodInvocationStmt : public Statement{
    public:
        MethodInvocationStmt(string id, ParameterList args, int line){
            this->id = id;
            this->args = args;
            this->line = line;
        }
        string id;
        ArgumentList args;
        int line;
        void printResult();
};

class WhileStatement: public Statement{
    public:
        WhileStatement(Expr * expr, Statement * stmt, int line){
            this->expr = expr;
            this->stmt = stmt;
            this->line = line;
        }
        Expr* expr;
        Statement * stmt;
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