#include "ast.h"
#include <map>
#include <iostream>

map<string, float> globalVariables = {};
map<string, pair<ParameterList,StatementList>> methods;

float getVariableValue(string id){
    if(!globalVariables.empty())
        return globalVariables[id];
    return -1;
}

bool variableExists(string id){
  float value;
  value = getVariableValue(id);
  if(value != -1)
    return true;
  
  return false;
}

void Declarator::printResult(){
  globalVariables.insert(pair<string,float>(string(this->id),this->arrayDeclaration->getResult()));
  printf ("Variable %s declarada \n", this->id);
}

void MethodDefinition::printResult(){
  list<Expr *>::iterator itd = this->params.begin();
  while (itd != this->params.end())
  {
      IdExpr * dec = dynamic_cast<IdExpr*>(*itd);
      if(dec != NULL ){
        if(globalVariables.find(string(dec->id))!= globalVariables.end()){
          globalVariables.insert(pair<string,float>(string(dec->id),dec->getResult()));
        }
        else {
          printf ("ERROR! ya existe una variable con nombre %s \n", this->id);
        }
      }

      itd++;
  }
  pair<ParameterList,StatementList> p = pair<ParameterList,StatementList>(this->params,this->statement);
  methods.insert(pair<string,pair<ParameterList,StatementList>>(string(this->id), p));
  printf ("Metodo %s agregado \n", this->id);
}

float FloatExpr::getResult(){
  return this->value;
}

float BinaryExpr::getResult(){
  
  float result = 0;
  switch (this->symbol)
  {
  case '+':
    result = this->expr1->getResult() + this->expr2->getResult();
    break;

  case '-':
   result = this->expr1->getResult() - this->expr2->getResult();
   break;
  
  case '*':
   result = this->expr1->getResult() * this->expr2->getResult();
   break;
  
  case '/':
   result = this->expr1->getResult() / this->expr2->getResult();
   break;
  
  default:
    printf ("ERROR! Se quiere convertir una expresion bool a float  \n");
    break;
  }
  return result;
}

bool BinaryExpr::evaluate(){

  switch (this->symbol)
  {
  case '>':
    return this ->expr1->getResult() > this->expr2->getResult();
  
  case '<':
    return this ->expr1->getResult() < this->expr2->getResult();

  default:
    printf ("ERROR! Se quiere convertir una expresion float a bool  \n");
    break;
  }

}

float IdExpr::getResult(){
  string i = string(this->id);
  if(getVariableValue(i)!=-1){
    return getVariableValue(i);
  }
}

void MethodInvocationStmt::printResult(){

  map<string, pair<ParameterList,StatementList>>::iterator p = methods.find(string(this->id));
  ParameterList params = p->second.first;
  StatementList stmts = p->second.second;
  if(params.size()!= this->args.size()){
    printf ("ERROR! Se requiere que complete los parametros de acuerdo a la declaracion del metodo  \n");
    return;
  }
  list<Expr *>::iterator itd = params.begin();
  list<Expr *>::iterator itdargs = this->args.begin();
  while (itd != params.end())
  {
      IdExpr * dec = dynamic_cast<IdExpr*>(*itd);
      Expr * val = *itdargs;
      if(dec != NULL){
        globalVariables.find(string(dec->id))->second = val->getResult();
      }

      itd++;
      itdargs++;
  }
  StatementList::iterator stm = stmts.begin();
  while(stm!=stmts.end()){
    stm.printResult();
  }

}
