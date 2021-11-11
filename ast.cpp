#include "ast.h"
#include <map>
#include <iostream>

map<string, float> globalVariables = {};
map<string, int> methods;

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
  int cont = 0;
  while (itd != this->params.end())
  {
      IdExpr * dec = dynamic_cast<IdExpr*>(*itd);
      if(dec != NULL){
        globalVariables.insert(pair<string,float>(string(dec->id),dec->getResult()));
        cont++;
      }

      itd++;
  }
  methods.insert(pair<string,int>(string(this->id),cont));
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

