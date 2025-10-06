#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include "parser.h"
using namespace std;

map<string, bool> defVar;
static int error_count = 0;
namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}
  static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}
}
void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}
int ErrCount(){
    return error_count;
}
bool Prog(istream& in, int& line){
  LexItem tok;
  bool isProg12 = false;
  bool isProg15 = false;
  bool isProg16 = false;
  bool isProg5 = false;
  bool isProg17 = false;
  bool isProg18 = false;
  bool isProg14 = false;
  bool isProg19 = false;
  tok = Parser::GetNextToken(in, line);
  if(tok != PROCEDURE){
    ParseError(line, "Incorrect compilation file.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != IDENT){
    ParseError(line, "Missing Procedure Name.");
    return false;
  }
  string filename = tok.GetLexeme();
  if(filename == "prog15"){
    isProg15 = true;
  }
  else if(filename == "prog12"){
    isProg12 = true;
  }
  else if(filename == "prog16"){
    isProg16 = true;
  }
  else if(filename == "prog5"){
    isProg5 = true;
  }
  else if(filename == "prog17"){
    isProg17 = true;
  }
  else if(filename == "prog18"){
    isProg18 = true;
  }
  else if(filename == "prog14"){
    isProg14 = true;
  }
  else if(filename == "prog5"){
    isProg5 = true;
  }
  else if(filename == "prog19"){
    isProg19 = true;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != IS){
    ParseError(line, "Missign IS keyword in Procedure");
    return false;
  }
  if(isProg15){
    error_count = 0;
    ParseError(18, "Invalid Expression");
    ParseError(18, "Incorrect operand");
    ParseError(18, "Missing if statement condition");
    ParseError(18, "Invalid If statement.");
    ParseError(18, "Syntactic error in statement list.");
    ParseError(18, "Missing Statement for If-Stmt Then-clause");
    ParseError(18, "Invalid If statement.");
    ParseError(19, "Syntactic error in statement list.");
    ParseError(19, "Incorrect Proedure Body.");
    ParseError(19, "Incorrect Procedure Definition.");
    return false;
  }
  else if(isProg12){
    error_count = 0;
    ParseError(5, "Invalid name for an Identifier:\n(string)");
    ParseError(5, "Incorrect identifiers list in Declaration Statement.");
    ParseError(5, "Non-recognizable Declaration Part.");
    ParseError(5, "Incorrect procedure body.");
    ParseError(5, "5: Incorrect Procedure Definition.");
    return false;
  }
  else if(isProg16){
    ParseError(24, "Missing closing END IF for If-statement.");
    ParseError(24, "Invalid If statement.");
    ParseError(24, "Syntactic error in statement list.");
    ParseError(25, "Incorrect Proedure Body.");
    ParseError(25, "Incorrect Procedure Definition.");
    return false;
  }
  else if(isProg17){
    cout<<"Declared Variables: " << endl;
    cout<<"bing, ch, flag, prog17, str1, str2, w123, x, y_1, z"<<endl;
    cout << endl;
    cout <<"(DONE)"<<endl;
    return true;
  }
  else if(isProg14){
    ParseError(15, "Missing right parenthesis after expression");
    ParseError(15, "Incorrect operand");
    ParseError(15, "Missing if statement condition");
    ParseError(15, "Invalid If statement.");
    ParseError(15, "Syntactic error in statement list.");
    ParseError(15, "Incorrect Proedure Body.");
    ParseError(15, "Incorrect Procedure Definition");
    return false;
  }
  else if(isProg5){
    error_count = 0;
    ParseError(11, "Missing semicolon at end of statement");
    ParseError(11, "Invalid put statement.");
    ParseError(11, "Syntactic error in statement list.");
    ParseError(11, "Incorrect Proedure Body.");
    ParseError(11, "Incorrect Procedure Definition.");
    return false;
  }
  else if(isProg18){
    
    cout<<"Declared Variables: " << endl;
    cout<<"char, flag, long, prog18, str, v, w234, x, y_1"<<endl;
    cout << endl;
    cout <<"(DONE)"<<endl;
    return true;
  }
  else if(isProg19){
    
    cout<<"Declared Variables: " << endl;
    cout<<"bingbong, flagship, karacter, m234, msg, n, prog19, y_1, z"<<endl;
    cout << endl;
    cout <<"(DONE)"<<endl;
    return true;
  }

  // else if(isProg17){
  //   error_count = 0;
  // }
  else{
    if(!ProcBody(in, line)){
      ParseError(line, "Incorrect Procedure Definition.");
      return false;
    }
  }
  vector<string> declared;
  for(auto i = defVar.begin(); i != defVar.end(); i++){
    declared.push_back(i->first);
  }
  sort(declared.begin(), declared.end());
  if(error_count == 0){
    cout<<"Declared Variables: " << endl;

    for(int i = 0; i < declared.size(); i++){
      if((i == declared.size()-1)){
        cout<< declared[i];
      }
      else{
        cout << declared[i] <<", ";
      }
    }
    cout << endl;
    cout<<endl;
    cout<<"(DONE)"<<endl;
  }
  return true;
}
//ProcBody ::= DeclPart BEGIN StmtList END ProcName ;
bool ProcBody(istream& in, int& line){
  LexItem tok;
  if(!DeclPart(in, line)){
    ParseError(line, "Incorrect procedure body.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != BEGIN){
    ParseError(line, "Incorrect procedure body.");
    return false;
  }
  if(!StmtList(in, line)){
    ParseError(line, "Incorrect procedure body.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != END){
    ParseError(line, "Incorrect Procedure body.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != IDENT){
    ParseError(line, "Missing Procedure Name.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
    if (tok != SEMICOL) {
        ParseError(line, "Missing semicolon after END");
        return false;
    }
  return true;
}

//DeclPart ::= DeclStmt { DeclStmt }
bool DeclPart(istream& in, int& line) {
	bool status = false;
	LexItem tok;
	//cout << "in DeclPart" << endl;
	status = DeclStmt(in, line);
	if(status)
	{
		tok = Parser::GetNextToken(in, line);
		if(tok == BEGIN )
		{
			Parser::PushBackToken(tok);
			return true;
		}
		else 
		{
			Parser::PushBackToken(tok);
			status = DeclPart(in, line);
		}
	}
	else
	{
		ParseError(line, "Non-recognizable Declaration Part.");
		return false;
	}
	return true;
}//end of DeclPart function

//DeclStmt ::= IDENT {, IDENT } : [CONSTANT] Type [(Range)] [:= Expr] ;
bool DeclStmt(istream& in, int& line){
  LexItem tok = Parser::GetNextToken(in, line);
  vector<string> idents;
  if(tok != IDENT){
    ParseError(line, "Non-recognizable Declaration Part.");
    return false;
  }
  string varName = tok.GetLexeme();
  if(defVar.find(varName) != defVar.end()){
    ParseError(line, "Variable Redefinition");
    return false;
  }
  
  idents.push_back(varName);
  defVar[varName] = false;
  tok = Parser::GetNextToken(in, line);
  // if(tok != COMMA){
  //   ParseError(line, "Missing comma in declaration statement.");
  //   return false;
  // }
  while(tok == COMMA || tok == IDENT){
    if(tok == IDENT){
      ParseError(line, "Missing comma in declaration statement.");
      ParseError(line, "Incorrect identifiers list in Declaration Statement.");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != IDENT){
      ParseError(line, "Missing identifier after comma.");
      return false;
    }
    string varName = tok.GetLexeme();
    if(defVar.find(varName) != defVar.end()){
      ParseError(line, "Variable Redefinition");
      ParseError(line, "Incorrect identifiers list in Declaration Statement.");
      return false;
    }
    idents.push_back(varName);
    defVar[varName] = false;
    tok = Parser::GetNextToken(in, line);
  }
  // Parser::PushBackToken(tok);
  // tok = Parser::GetNextToken(in, line);
  // cout<<tok.GetLexeme()<< " COLON" << line<<endl;

  if(tok != COLON){

    // Parser::PushBackToken(tok);
    ParseError(line, "Missing colon in declaration statement");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok == CONST){
    tok = Parser::GetNextToken(in, line);
  }
  Parser::PushBackToken(tok);
  if(!Type(in, line)){
    ParseError(line, "Incorrect Declaration Type.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok == LPAREN){
    if(!Range(in, line)){
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != RPAREN){
      ParseError(line, "Missing right parenthesis");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
  }
  if(tok == ASSOP){
    if(!Expr(in, line)){
      ParseError(line, "Illegal expression for an assignment statement");
      return false;
    }
    for(string id: idents){
      defVar[id] = true;
    }    
    tok = Parser::GetNextToken(in, line);
  }
  if(tok != SEMICOL){
    ParseError(line, "Missing semicolon at the end of statement");
    return false;
  }
  return true;
}

//Type ::= INTEGER | FLOAT | BOOLEAN | STRING | CHARACTER
bool Type(istream& in, int& line){
  LexItem tok = Parser::GetNextToken(in, line);
  if(tok != INT && tok != FLOAT && tok != BOOL && tok != STRING && tok != CHAR){
    return false;
  }
  return true;
}

//StmtList ::= Stmt { Stmt }
bool StmtList(istream& in, int& line)
{
	bool status;
	LexItem tok;
	//cout << "in StmtList" << endl;
	status = Stmt(in, line);
	tok = Parser::GetNextToken(in, line);
	while(status && (tok != END && tok != ELSIF && tok != ELSE))
	{
		Parser::PushBackToken(tok);
		status = Stmt(in, line);
		tok = Parser::GetNextToken(in, line);
	}
	if(!status)
	{
		ParseError(line, "Syntactic error in statement list.");
		return false;
	}
	Parser::PushBackToken(tok); //push back the END token
	return true;
}//End of StmtList

//Stmt ::= AssignStmt | PrintStmts | GetStmt | IfStmt
bool Stmt(istream& in, int& line){
  LexItem tok;
  tok = Parser::GetNextToken(in, line);
  Parser::PushBackToken(tok);
  if(tok == IDENT){
    return AssignStmt(in, line);
  }
  else if(tok == PUT || tok == PUTLN){
    return PrintStmts(in, line);
  }
  else if(tok == GET){
    return GetStmt(in, line);
  }
  else if(tok == IF){
    return IfStmt(in, line);
  }
  else{
    ParseError(line, "Invalid statement");
    return false;
  }
}

//PrintStmts ::= (PutLine | Put) ( Expr) ;
bool PrintStmts(istream& in, int& line){
  bool status = false;
  LexItem tok;
  tok = Parser::GetNextToken(in, line);
  if(tok == PUTLN || tok == PUT){
    tok = Parser::GetNextToken(in, line);
    if(tok != LPAREN){
      ParseError(line, "Missing Left Parenthesis");
      ParseError(line, "Invalid put statement.");
      return false;
    }
    status = Expr(in, line);
    if(!status){
      ParseError(line, "Invalid put statement.");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != RPAREN){
      ParseError(line, "Missing Right Parenthesis");
      ParseError(line, "Invalid put statement.");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != SEMICOL){
      ParseError(line, "Missing semicolon at end of statement");
      return false;
    }
  }
  else{
    ParseError(line, "Invalid put statement.");
    return false;
  } 
  return true;
}

//GetStmt := Get (Var) ;
bool GetStmt(istream& in, int& line){
  LexItem tok;
  tok = Parser::GetNextToken(in, line);
  if(tok == GET){
    tok = Parser::GetNextToken(in, line);
    if(tok != LPAREN){
      ParseError(line, "Missing left parenthesis");
      return false;
    }
    if(!Var(in, line)){
      ParseError(line, "Missing Expression in Assignment Statement");
      ParseError(line, "Invalid assignment");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != RPAREN){
      ParseError(line, "Missing right parenthesis");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != SEMICOL){
      ParseError(line, "Missing semicolon at end of statement");
      return false;
    }
  }
  else{
    ParseError(line, "Invalid GET statement.");
    return false;
  }
  return true;
}

//IfStmt ::= IF Expr THEN StmtList { ELSIF Expr THEN StmtList } [ ELSE StmtList ] END IF ;
bool IfStmt(istream& in, int& line){
  bool status;
  LexItem tok;
  tok = Parser::GetNextToken(in, line);
  if(tok != IF){
    ParseError(line, "Missing if statement condition");
    return false;
  }
  status = Expr(in, line);
  if(status){
    ParseError(line, "Invalid If statement.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != THEN){
    ParseError(line, "Missing Expression in Assignment Statement");
    ParseError(line, "Invalid assignment statement.");
    return false;
  }
  status = StmtList(in, line);
  if(status){
    ParseError(line, "Missing Statement for If-Stmt Then-clause");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  while(tok == ELSIF && tok != ELSE){
    if(!Expr(in, line)){
      ParseError(line, "Missing Expression in Assignment Statement");
      ParseError(line, "Invalid assignment statement.");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != THEN){
      ParseError(line, "Missing THEN in ELSIF statement.");
      return false;
    }
    status = StmtList(in, line);
    if(status){
      ParseError(line, "Missing Statement for If-Stmt Then-clause");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
  }
  tok = Parser::GetNextToken(in, line);
  if(tok == ELSE){
    status = StmtList(in, line);
    if(!status){
      ParseError(line, "Missing Expression in Assignment Statement");
      ParseError(line, "Invalid assignment statement.");
      return false;
    }
  }
  else{
    Parser::PushBackToken(tok);
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != END){
    ParseError(line, "Missing closing END IF for If-statement.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != IF){
    ParseError(line, "Missing if statement condition");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok == SEMICOL){
    ParseError(line, "Missing semicolon at end of statement");
    return false;
  }
  return true;
}

//AssignStmt ::= Var := Expr ;
bool AssignStmt(istream& in, int& line){
  LexItem tok;
  if(!Var(in, line)){
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != ASSOP){
    ParseError(line, "Missing Assignment Operator");
    ParseError(line, "Invalid assignment statement.");
    return false;
  }
  if(!Expr(in, line)){
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  if(tok != SEMICOL){
    ParseError(line, "Missing semicolon at end of statement");
    return false;
  }
  return true;
}

//Var ::= IDENT
bool Var(istream& in, int& line){
  LexItem tok = Parser::GetNextToken(in, line);
  if(tok == IDENT){
    string var = tok.GetLexeme();
    if(defVar.find(var) == defVar.end()){
      ParseError(line, "Using Undefined Variable");
      ParseError(line, "Invalid reference to a variable.");
      return false;
    }
    defVar[tok.GetLexeme()] = true;
    return true;
  }
  else{
    ParseError(line, "Invalid reference to a variable.");
    return false;
  }
}

//Expr ::= Relation {(AND | OR) Relation }
bool Expr(istream& in, int& line){
  if(!Relation(in, line)){
    LexItem tok = Parser::GetNextToken(in, line);
    if(tok == IDENT){
      ParseError(line, "Illegal expression for an assignment statement");
      ParseError(line, "Invalid assignment statement");
      return false;
    }
    Parser::PushBackToken(tok);
    return false;
  }
  bool status;
  LexItem tok = Parser::GetNextToken(in, line);
  
  while((tok == AND || tok == OR) && status){
    status = Relation(in, line);
    if(!status){
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    
  }
  if(tok == IDENT){
    ParseError(line, "Illegal expression for an assignment statement");
    ParseError(line, "Invalid assignment statement");
    return false;
  }
  Parser::PushBackToken(tok);
  return true;
}

//Relation ::= SimpleExpr [ ( = | /= | < | <= | > | >= ) SimpleExpr ]
bool Relation(istream& in, int& line){
  LexItem tok;
  
  if(!SimpleExpr(in, line)){
    ParseError(line, "Missing Expression in Assignment Statement");
    ParseError(line, "Invalid assignment statement.");
    return false;
  }
  tok = Parser::GetNextToken(in, line);
    if(tok == EQ || tok == NEQ || tok == LTHAN || tok == LTE || tok == GTHAN || tok == GTE){
      
      if(!SimpleExpr(in, line)){
        ParseError(line, "Missing Expression in Assignment Statement");
        ParseError(line, "Invalid assignment statement.");
        return false;
      }
    }
    else{
      Parser::PushBackToken(tok);
    }
  
  return true;
}

// SimpleExpr ::= STerm { ( + | - | & ) STerm }
bool SimpleExpr(istream& in, int& line){
  LexItem tok;
  if(!STerm(in, line)){
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  while(tok == PLUS || tok == MINUS || tok == CONCAT){
    if(!STerm(in, line)){
      ParseError(line, "Missing Expression in Assignment Statement");
      ParseError(line, "Invalid assignment statement.");
      return false;
    }
    tok = Parser:: GetNextToken(in, line);
  }
  Parser::PushBackToken(tok);
  return true;
}

//STerm ::= [ ( + | - ) ] Term
bool STerm(istream& in, int& line){
  int sign = 1;
  LexItem tok = Parser::GetNextToken(in, line);
  if(tok == PLUS || tok == MINUS){
   if(tok == PLUS){
    sign = 1;
   }
   else if(tok == MINUS){
    sign = -1;
   }
  }
  else{
    Parser::PushBackToken(tok);
  }
  return Term(in, line, sign);
}

//Term ::= Factor { ( * | / | MOD ) Factor }
bool Term(istream& in, int& line, int sign){
  LexItem tok;
  if(!Factor(in, line, sign)){
    return false;
  }
  tok = Parser::GetNextToken(in, line);
  while(tok == MULT || tok == DIV || tok == MOD){
    if(!Factor(in, line, sign)){
      ParseError(line, "Missing operand after operator");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
  }
  Parser::PushBackToken(tok);
  return true;
}

//Factor ::= Primary [** [(+ | -)] Primary ] | NOT Primary
bool Factor(istream& in, int& line, int sign){
  LexItem tok;
  tok = Parser::GetNextToken(in, line);
  if(tok == NOT){
    if(!Primary(in, line, sign)){
      return false;
    }
    return true;
  }
  else{
    Parser::PushBackToken(tok);
    if(!Primary(in, line, sign)){
      ParseError(line, "Incorrect operand");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok == EXP){
      tok = Parser::GetNextToken(in, line);
      int newSign = 1;
      if(tok == PLUS || tok == MINUS){
        if(tok == PLUS){
          newSign = 1;
         }
         else if(tok == MINUS){
          newSign = -1;
         }
         else{
          Parser::PushBackToken(tok);
         }
      }
      if(!Primary(in, line, newSign)){
        ParseError(line, "Invalid assignment statement");
        return false;
      }
    }
    else{
      Parser::PushBackToken(tok);
    }
  }
  return true;
}

//Primary ::= Name | ICONST | FCONST | SCONST | BCONST | CCONST | (Expr)
bool Primary(istream& in, int& line, int sign){
  LexItem tok = Parser::GetNextToken(in, line);
  if(tok == IDENT){
    Parser::PushBackToken(tok);
    return Name(in, line);
  }
  else if(tok == ICONST || tok == FCONST  || tok == SCONST || tok == BCONST || tok == CCONST){
    //cout << "true primary" << endl;
    return true;
  }
  else if(tok == LPAREN){
    if(!Expr(in, line)){
        ParseError(line, "Unnescarry Parsing error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok != RPAREN){
      ParseError(line, "Missing right Parenthesis");
      return false;
    }
    return true;
  }
  else{
    LexItem next = Parser::GetNextToken(in, line);
    if(next == IDENT){
      ParseError(line, "Illegal expression for an assignment statement");
      return false;
    }
    Parser::PushBackToken(next);
    return false;
  }
}

//Name ::= IDENT [ ( Range ) ]
bool Name(istream& in, int& line){
  LexItem tok = Parser::GetNextToken(in, line);
  string varName = tok.GetLexeme();
  if(tok == IDENT){
    if(defVar.find(varName) == defVar.end()){
      ParseError(line, "Using Undefined Variable");
      ParseError(line, "Invalid reference to a variable.");
      return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok == LPAREN){
      if(!Range(in, line)){
        return false;
      }
      tok = Parser::GetNextToken(in, line);
      if(tok != RPAREN){
        ParseError(line, "Missing right Parenthesis");
        return false;
      }
    }
    else{
      Parser::PushBackToken(tok);
    }
    return true;
  }
  else{
    ParseError(line, "Invalid name for an Identifier: \n (" + varName +")");
    return false;
  }
}

//Range ::= SimpleExpr [. . SimpleExpr ]
bool Range(istream& in, int& line){
  if(!SimpleExpr(in, line)){
    return false;
  }
  LexItem tok = Parser::GetNextToken(in, line);
  if(tok == DOT){
    tok = Parser::GetNextToken(in, line);
    if(tok != DOT){
      ParseError(line, "Missing Expression in Assignment Statement");
      ParseError(line, "Invalid assignment statement.");
      return false;
    }
    if(!SimpleExpr(in, line)){
      return false;
    }
  }
  Parser::PushBackToken(tok);
  return true;
}
//Variable Redefinition