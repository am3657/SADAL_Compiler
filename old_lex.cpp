#include <iostream>
#include <map>
#include <algorithm>
#include "lex.h"
using namespace std;

map<string, Token> keywordMap = {
  {"procedure", PROCEDURE},
  {"string", STRING},
  {"else", ELSE},
  {"if", IF},
  {"integer", INT},
  {"float", FLOAT},
  {"character", CHAR},
  {"put", PUT},
  {"putline", PUTLN},
  {"get", GET},
  {"boolean", BOOL},
  {"true", TRUE},
  {"false", FALSE},
  {"elsif", ELSIF},
  {"is", IS},
  {"end", END},
  {"begin", BEGIN},
  {"then", THEN},
  {"constant", CONST},
  {"mod", MOD},
  {"and", AND},
  {"or", OR},
  {"not", NOT}
};

  map<string, Token> delimiterMap = {
    {",", COMMA}, {";", SEMICOL}, {"(", LPAREN},
    {")", RPAREN}, {".", DOT}, {":", COLON}
  };

  map<string, Token> operatorMap = {
    {"+", PLUS}, {"-", MINUS}, {"*", MULT}, {"/", DIV},
    {":=", ASSOP}, {"=", EQ}, {"/=", NEQ}, {"<", LTHAN},
    {">", GTHAN}, {"<=", LTE}, {">=", GTE}, {"mod", MOD},
    {"&", CONCAT}, {"and", AND}, {"or", OR}, {"not", NOT}, {"**", EXP}
};


LexItem id_or_kw(const string& lexeme, int linenum){
  string lex = lexeme;
  transform(lex.begin(), lex.end(), lex.begin(), ::tolower);

    for(auto i : keywordMap){
      if(i.first == lex){
        if(i.second == TRUE || i.second == FALSE){
          return LexItem(BCONST, lexeme, linenum);
        }
        return LexItem(i.second, lexeme, linenum);
      }
    }
    return LexItem(IDENT, lexeme, linenum);
  }

LexItem getNextToken (istream& in, int& linenum){

  char c;
  string lexeme;
  string tempLex;
  enum State {
    START, INID, INSTRING, ININT, INREAL, INEXP, INCHAR
  }
  lexState = START;

  while(in.get(c)){
    switch (lexState){
      case START:
        if(isspace(c)){
          if (c == '\n'){
            linenum++;
        }
        continue;
      }
        if(isalpha(c)){
          lexState = INID;
          lexeme += c;
          continue;
        }
        else{
          if(c == '_'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(ERR, tempLex, linenum);
          }
          if(c == '?'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(ERR, tempLex, linenum);
          }
          if(c == '!'){
            
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(ERR, tempLex, linenum);
          }
          if(isdigit(c)){
            lexState = ININT;
            lexeme += c;
            continue;
          }
          if (c == '\"'){
            lexState = INSTRING;
            lexeme += c;
            continue;
          }
          if( c== '\''){
            lexState = INCHAR;
            lexeme += c;
            continue;
          }
          if(c == '+'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(PLUS, tempLex, linenum);
          }
          if(c == '-'){
            if(in.peek() == '-'){
              while (in.get(c)){
                if(c == '\n'){
                  linenum++;
                  break;
                }
              }
              continue;
            }
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(MINUS, tempLex, linenum);
          }
          else if(c == '*'){
            lexeme += c;
            char next = in.peek();
            if(next == '*'){
              in.get(c);
              lexeme += next;
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(EXP, tempLex, linenum);
            }
            else{
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(MULT, tempLex, linenum);
            }
          }
          if(c == '/'){
            if (in.peek() == '='){
              lexeme += c;
              in.get(c);
              lexeme += c;
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(NEQ, tempLex, linenum);
            }
            else{
              lexeme += c;
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(DIV, tempLex, linenum);
            }
          }
          if(c == ':'){
            lexeme += c;
            char next = in.peek();
            if (next == '='){
              in.get(c);
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(ASSOP, tempLex, linenum);
            }
            else{
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(COLON, tempLex, linenum);
            }

          }
          if(c == '<'){
            lexeme += c;
            char next = in.peek();
            if(next == '='){
              in.get(c);
              lexeme += c;
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(LTE, tempLex, linenum);
            }
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(LTHAN, tempLex, linenum);
          }
          if(c == '>'){
            lexeme += c;
            char next = in.peek();
            if(next == '='){
              in.get(c);
              lexeme += c;
              tempLex = lexeme;
              lexeme.clear();
              return LexItem(GTE, tempLex, linenum);
            }
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(GTHAN, tempLex, linenum);
          }
          if(c == ','){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(COMMA, tempLex, linenum);
          }
          if(c == ';'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(SEMICOL, tempLex, linenum);
          }
          if(c == '('){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(LPAREN, tempLex, linenum);
          }
          if(c == ')'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(RPAREN, tempLex, linenum);
          }
          if(c == ':'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(COLON, tempLex, linenum);
          }
          if(c == '.'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(DOT, tempLex, linenum);
          }
          if(c == '&'){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(CONCAT, tempLex, linenum);
          }
          if(c == '='){
            lexeme += c;
            tempLex = lexeme;
            lexeme.clear();
            return LexItem(EQ, tempLex, linenum);
          }
          
          break;
        case INID:
            if(isalnum(c)){
                lexeme += c;
                if(lexeme.length() == 1 && !isdigit(in.peek())){
                  tempLex = lexeme;
                  lexeme.clear();
                  lexState = START;
                  transform(tempLex.begin(), tempLex.end(), tempLex.begin(), ::tolower);
                  return LexItem(IDENT, tempLex, linenum);
                }
              }
            else if(c == '_'){
              lexeme += c;
              if(in.peek() == '_'){
                tempLex = lexeme;
                lexeme.clear();
                lexState = START;
                return id_or_kw(tempLex, linenum);
              }
            }
            else{
              in.unget();
              tempLex = lexeme;
              lexeme.clear();
              lexState = START;
              return id_or_kw(tempLex, linenum);
            }
            break;
      case INSTRING:
        if(c == '\n' || c == '\t'){
          tempLex = lexeme;
          lexeme.clear();
          lexState = START;
          return LexItem(ERR, " Invalid string constant " + tempLex , linenum);
        }
        else if(c == '\"'){
          tempLex = lexeme.substr(1, lexeme.length()-1);
          lexeme.clear();
          return LexItem(SCONST, tempLex, linenum);
        }
        else{
          lexeme += c;
        }
        break;
      case INCHAR:
        if(c == '\n'){
          tempLex = lexeme;
          lexeme.clear();
          lexState = START;
          return LexItem(ERR, "New line is an invalid character constant.", linenum);
        }
        else if(c == '\''){
          tempLex = lexeme.substr(1);
          lexeme.clear();
          lexState = START;
          return LexItem(CCONST, tempLex, linenum);
        }
        else{
          lexeme += c;
          if(lexeme.length() > 2){
            tempLex = lexeme;
            lexeme.clear();
            lexState = START;
            return LexItem(ERR, " Invalid character constant " + tempLex +"\'", linenum);
          }
        }
        break;
      case ININT:
          if(isdigit(c)){
            lexeme += c;
          }
          else if (c == 'E'|| c == 'e'){
            lexeme += c;
            lexState = INEXP;
            
          }
          else if(c == '.'){
              lexeme += c;
              if(isdigit(in.peek())){
                lexState = INREAL;
                continue;
            }
          }
          else{
              in.unget();
              tempLex = lexeme;
              lexeme.clear();
              lexState = START;
              return LexItem(ICONST, tempLex, linenum);
          }
          break;
      case INREAL:
        if(isdigit(c)){
          lexeme += c;
        }
        else if(c == 'E' || c == 'e'){
          if(isspace(in.peek())){
            in.unget();
            tempLex = lexeme;
            lexeme.clear();
            lexState = START;
            return LexItem(FCONST, tempLex, linenum);
          }
          lexeme += c;
          lexState = INEXP;
          
        }
        else if(c == '.'){
          lexeme += c;
          tempLex = lexeme;
          lexeme.clear();
          lexState = START;
          return LexItem(ERR, tempLex, linenum);
        }
        else{
          in.unget();
            tempLex = lexeme;
            lexeme.clear();
            lexState = START;
            return LexItem(FCONST, tempLex, linenum);
          }
        }
        break;
      case INEXP:
        if((c == '+' || c == '-')){
          if(isdigit(in.peek()))
            lexeme += c;
          else{
            in.unget();
            tempLex = lexeme;
            lexeme.clear();
            lexState = START;
            return LexItem(ERR, tempLex, linenum);
          }
        }
        else if(isdigit(c)){
          lexeme += c;
        }

        else if(c == '.'){
          in.unget();
          tempLex = lexeme;
          lexeme.clear();
          lexState = START;
          return LexItem(ERR, tempLex, linenum);
        }
        else{
          in.unget();
          tempLex = lexeme;
          lexeme.clear();
          lexState = START;
          if(tempLex.find('.') != string::npos){
            return LexItem(FCONST, tempLex, linenum);
          }
          else{
            return LexItem(ICONST, tempLex, linenum);
          }
        }
        break;
      }
    }
  
  if(in.eof()){
    return LexItem(DONE, "", linenum);
  }
  else{
    return LexItem(ERR, lexeme, linenum);
  }
}
ostream& operator<< (ostream& out, const LexItem& tok){
  Token token = tok.GetToken();
  string lexeme = tok.GetLexeme();
  //int linenum = tok.GetLinenum();

  switch(token){
    case ICONST:
      out << "ICONST" <<": (" <<lexeme<<")" << endl;
      break;
    case FCONST: 
      out << "FCONST" <<": (" <<lexeme<<")" << endl;
      break;
    case BCONST: 
      out << "BCONST" <<": (" <<lexeme<<")" << endl;
      break;
    case IDENT:
      out << "IDENT" <<": <"<<lexeme<<">" <<endl;
      break;
    case SCONST:
      out << "SCONST" <<": \"" <<lexeme<<"\"" <<endl;
      break;
    case CCONST:
      out << "CCONST" <<": \'"<<lexeme<<"\'" << endl;
      break;
    case ERR:
      out << "ERR: In line " << tok.GetLinenum() << ", Error Message {" << tok.GetLexeme() << "}" <<endl;
      break;
    case PLUS: 
        out << "PLUS" <<endl; 
        break;
    case MINUS: 
        out << "MINUS" <<endl; 
        break;
    case MULT: 
        out << "MULT" <<endl; 
        break;
    case DIV: 
        out << "DIV" <<endl; 
        break;
    case COMMA: 
        out << "COMMA" <<endl;
        break;
    case DOT: 
        out << "DOT" <<endl; 
        break;
    case COLON: 
        out << "COLON" <<endl; 
        break;
    case ASSOP: 
        out << "ASSOP" <<endl; 
        break;
    case LPAREN: 
        out << "LPAREN" <<endl; 
        break;
    case RPAREN: 
        out << "RPAREN" <<endl; 
        break;
    case SEMICOL: 
        out << "SEMICOL" <<endl; 
        break;
    case IF: 
        out << "IF" <<endl; 
        break;
    case ELSE: 
        out << "ELSE" <<endl; 
        break;
    case ELSIF: 
        out << "ELSIF" <<endl; 
        break;
    case INT: 
        out << "INT" <<endl; 
        break;
    case FLOAT: 
        out << "FLOAT" <<endl; 
        break;
    case BOOL: 
        out << "BOOL" <<endl; 
        break;
    case PROCEDURE: 
        out << "PROCEDURE" <<endl; 
        break;
    case END: 
        out << "END" <<endl; 
        break;
    case BEGIN: 
        out << "BEGIN" <<endl; 
        break;
    case CHAR: 
        out << "CHAR" <<endl; 
        break;
    case STRING: 
        out << "STRING" <<endl; 
        break;
    case CONST: 
        out << "CONST" <<endl; 
        break;
    case AND: 
        out << "AND" <<endl; 
        break;
    case OR: 
        out << "OR" <<endl; 
        break;
    case NOT: 
        out << "NOT" <<endl; 
        break;
    case THEN: 
        out << "THEN" <<endl; 
        break;
    case GTE: 
        out << "GTE"<<endl; 
        break;
    case LTE: 
        out << "LTE" <<endl; 
        break;
    case MOD: 
        out << "MOD" <<endl; 
        break;
    case GTHAN:
        out << "GTHAN" <<endl; 
        break;
    case LTHAN:
        out << "LTHAN" <<endl; 
        break;
    case NEQ: 
        out << "NEQ" <<endl; 
        break;
    case EXP: 
        out << "EXP" <<endl; 
        break;
    case CONCAT: 
        out << "CONCAT" <<endl; 
        break;
    case EQ: 
        out << "EQ" <<endl; 
        break;
    default:
      
      out << token << endl;
      break;
    
  }
  return out;
}
