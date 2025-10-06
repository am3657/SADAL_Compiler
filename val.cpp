#include <iostream>
#include "val.h"
#include <string>
#include <cmath>
using namespace std;

// numeric overloaded add this to op
Value Value::operator+(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    int sumInt = this->GetInt() + op.GetInt();
    return Value(sumInt);
  }
  else if(this->IsReal() && op.IsReal()){
    double sumReal = this->GetReal() + op.GetReal();
    return Value(sumReal);
  }
  else{
    cout<<"Illegal mixed operands for + operator"<<endl;
    return Value();
  }
}
// numeric overloaded subtract op from this
Value Value::operator-(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    int sumInt = this->GetInt() - op.GetInt();
    return Value(sumInt);
  }
  else if(this->IsReal() + op.IsReal()){
    double sumReal = this->GetReal() + op.GetReal();
    return Value(sumReal);
  }
  else{
    cout<<"Illegal mixed operands for - operator"<<endl;
    return Value();
  }
}

// numeric overloaded multiply this by op
Value Value::operator*(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    return Value(this->GetInt() * op.GetInt());
  }
  else if(this->IsReal() && op.IsReal()){
    return Value(this->GetReal() * op.GetReal());
  }
  // cout<<"Illegal operand type for the operation" <<endl;
  cerr << "Illegal operand type for the operation" <<endl;
  return Value();
}

// numeric overloaded divide this by oper
Value Value::operator/(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    if(op.GetInt() == 0){
      cout<< "Run-Time Error-Illegal division by Zero" <<endl;
      return Value();
    }
    return Value(this->GetInt() / op.GetInt());
  }
  else if(this->IsReal() && op.IsReal()){
    if(op.GetReal() == 0){
      cout<< "Run-Time Error-Illegal division by Zero" <<endl;
      return Value();
    }
    return Value(this->GetReal() / op.GetReal());
  }
  return Value();
}

//numeric MOD: overloaded Remainder this by op
Value Value::operator%(const Value & op) const{
  if(this->IsInt() == op.IsInt()){
    if(op.GetInt() == 0){
      cout<<"Illegal modulus by 0" << endl;
    }
    return Value(this->GetInt() % op.GetInt());
  }
  //Show error
  cout<<"Illegal operand types for MOD operator"<<endl;
  return Value();
}
     
//(Relational = (Equal): overloaded equality operator of this with op
Value Value::operator==(const Value& op) const{
  if(this->GetType()!= op.GetType()){
    cout<<"Illegal mixed operands for =="<<endl;
    return Value();
  }
  if(op.IsInt()){
    return Value(this->GetInt() == op.GetInt());
  }
  else if(op.IsReal()){
    return Value(this->GetReal() == op.GetReal());
  }
  else if(op.IsString()){
    return Value(this->GetString() == op.GetString());
  }
  else if(op.IsChar()){
    return Value(this->GetChar() == op.GetChar());
  }
  return Value();
}

//Relational /= (Not equal): overloaded inequality operator of this with op
Value Value::operator!=(const Value& op) const{
  if(this->GetType() != op.GetType()){
    cout<<"Illegal mixed operands for !="<<endl;
    return Value();
  }
  else{
    if(this->IsInt() == op.IsInt()){
      return Value(this->GetInt() != op.GetInt());
    }
    else if(this->IsReal() == op.IsReal()){
      return Value(this->GetReal() != op.GetReal());
    }
    else if(this->IsString() == op.IsString()){
      return Value(this->GetString() != op.GetString());
    }
    else if(this->IsChar() == op.IsChar()){
      return Value(this->GetChar() != op.GetChar());
    }
  }
  return Value();
}

//overloaded greater than operator of this with op
Value Value::operator>(const Value& op) const{
  if(this->GetType() != op.GetType()){
    cout<<"Illegal mixed operands for >"<<endl;
    return Value();
  }
  else{
    if(this->IsInt() && op.IsInt()){
      return Value(this->GetInt() > op.GetInt());
    }
    else if(this->IsReal() && op.IsReal()){
      return Value(this->GetReal() > op.GetReal());
    }
    else if(this->IsString() == op.IsString()){
      return Value(this->GetString() > op.GetString());
    }
    else if(this->IsChar() == op.IsChar()){
      return Value(this->GetChar() > op.GetChar());
    }
  }
  return Value();
}

//overloaded less than operator of this with op
Value Value::operator<(const Value& op) const{
  if(this->GetType() != op.GetType()){
    cout<<"Illegal mixed operands for <"<<endl;
    return Value();
  }
  else{
    if(this->IsInt() == op.IsInt()){
      return Value(this->GetInt() < op.GetInt());
    }
    else if(this->IsReal() == op.IsReal()){
      return Value(this->GetReal() < op.GetReal());
    }
    else if(this->IsString() == op.IsString()){
      return Value(this->GetString() < op.GetString());
    }
    else if(this->IsChar() == op.IsChar()){
      return Value(this->GetChar() < op.GetChar());
    }
  }
  return Value();
}

//Relational <= (less than or equal): overloaded less than or equal operator of this with op
Value Value::operator<=(const Value& op) const{
  if(this->GetType() != op.GetType()){
    cout<<"Illegal mixed operands for <="<<endl;
    return Value();
  }
  else{
    if(this->IsInt() == op.IsInt()){
      return Value(this->GetInt() <= op.GetInt());
    }
    else if(this->IsReal() == op.IsReal()){
      return Value(this->GetReal() <= op.GetReal());
    }
    else if(this->IsString() == op.IsString()){
      return Value(this->GetString() <= op.GetString());
    }
    else if(this->IsReal() == op.IsReal()){
      return Value(this->GetReal() <= op.GetReal());
    }
    else if(this->IsChar() == op.IsChar()){
      return Value(this->GetChar() <= op.GetChar());
    }
  }
  return Value();
}

//Relational >= (Greater than or equal): overloaded Greater than or equal operator of this with op
Value Value::operator>=(const Value& op) const{
  if(this->GetType() != op.GetType()){
    cout<<"Illegal mixed operands for >="<<endl;
    return Value();
  }
  else{
    if(this->IsInt() == op.IsInt()){
      return Value(this->GetInt() >= op.GetInt());
    }
    else if(this->IsReal() == op.IsReal()){
      return Value(this->GetReal() >= op.GetReal());
    }
    else if(this->IsString() == op.IsString()){
      return Value(this->GetString() >= op.GetString());
    }
    else if(this->IsChar() == op.IsChar()){
      return Value(this->GetChar() >= op.GetChar());
    }
  }
  return Value();
}

//Logical and: overloaded logical Anding operator of this with op
Value Value::operator&&(const Value& op) const{
  if(this->IsBool() && op.IsBool()){
    return Value(this->GetBool() && op.GetBool());
  }
  //Show Error Statement
  return Value();
}

//Logical or: overloaded logical Oring operator of this with op
Value Value::operator||(const Value& op) const{
  if(this->IsBool() && op.IsBool()){
    return Value(this->GetBool() || op.GetBool());
  }
  return Value();
}

//Logical not: overloaded logical Complement operator of this object
Value Value::operator!(void) const{
  if(this->IsBool()){
    bool val = this->GetBool();
    return Value(!val);
  }
  return Value();
}

//Concatenation &: Concatenate this with op
Value Value::Concat(const Value & op) const{
  if(this->IsString() && op.IsString()){
    return Value(this->GetString() + op.GetString());
  }
  else if(this->IsString() && op.IsChar()){
    return Value(this->GetString() + op.GetChar());
  }
  else if(this->IsChar() && op.IsString()){
    return Value(this->GetChar() + op.GetString());
  }
  else if(this->IsChar() && op.IsChar()){
    return Value(this->GetChar() + op.GetChar());
  }
  return Value();
}

//Exponentiation **: raise this to the power of op
Value Value::Exp(const Value & op) const{
  if(this->IsInt() && op.IsInt()){
    return Value(pow(this->GetInt(), op.GetInt()));
  }
  if(this->IsReal() && op.IsReal()){
    return Value(pow(this->GetReal(), op.GetReal()));
  }
  return Value();
}