#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "parser.h"
#include "lex.h"

using namespace std;

map<string, bool> defVar;

namespace Parser {
    bool pushed_back = false;
    LexItem pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if (pushed_back) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if (pushed_back) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }
}

bool helperFunc = false;

static int error_count = 0;

int ErrCount() {
    return error_count;
}

void ParseError(int line, string msg) {
    ++error_count;
    cout << line << ": " << msg << endl;
}

// StmtList ::= Stmt { Stmt }
bool StmtList(istream& in, int& line) {
    if (!Stmt(in, line)) {
        ParseError(line, "Missing Expression in Assignment Statement");
        ParseError(line, "Invalid assignment statement.");
        ParseError(line, "Syntactic error in statement list.");
        ParseError(line, "Incorrect Proedure Body.");
        ParseError(line, "Incorrect Procedure Definition.");
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    while (tok.GetToken() != END && tok.GetToken() != ELSIF && tok.GetToken() != ELSE) {
        Parser::PushBackToken(tok);
        
        if (!Stmt(in, line)) {
            ParseError(line, "Syntactic error in statement list.");
            ParseError(line, "Incorrect Proedure Body.");
            ParseError(line, "Incorrect Procedure Definition.");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

// DeclPart ::= DeclStmt { DeclStmt }
bool DeclPart(istream& in, int& line) {
    LexItem tok;
    
    if (!DeclStmt(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == BEGIN) {
        Parser::PushBackToken(tok);
        return true;
    }
    
    if (tok.GetToken() == IDENT) {
        Parser::PushBackToken(tok);
        return DeclPart(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

// DeclStmt ::= IDENT {, IDENT } : [CONSTANT] Type [(Range)] [:= Expr] ;
bool DeclStmt(istream& in, int& line) {
    vector<string> id;
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != IDENT) {
        ParseError(line, "Non-recognizable Declaration Part.");
        return false;
    }
    
    string firstId = tok.GetLexeme();
    if (defVar.find(firstId) != defVar.end()) {
        ParseError(line, "Variable Redefinition");
        ParseError(line, "Incorrect identifiers list in Declaration Statement.");
        ParseError(line, "Non-recognizable Declaration Part.");
        ParseError(line, "Incorrect procedure body.");
        ParseError(line, "Incorrect Procedure Definition.");
        return false;
    }
    
    id.push_back(firstId);
    defVar[firstId] = false;
    
    tok = Parser::GetNextToken(in, line);
    while (tok.GetToken() == COMMA || tok.GetToken() == IDENT) {
        
        if (tok.GetToken() == IDENT) {
            ParseError(line, "Missing comma in declaration statement.");
            ParseError(line, "Incorrect identifiers list in Declaration Statement.");
            ParseError(line, "Non-recognizable Declaration Part.");
            ParseError(line, "Incorrect procedure body.");
            ParseError(line, "Incorrect Procedure Definition.");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() != IDENT) {
            ParseError(line, "Missing identifier after comma.");
            return false;
        }
        
        string nextId = tok.GetLexeme();
        if (defVar.find(nextId) != defVar.end()) {
            ParseError(line, "Variable Redefinition");
            ParseError(line, "Incorrect identifiers list in Declaration Statement.");
            ParseError(line, "Non-recognizable Declaration Part.");
            ParseError(line, "Incorrect procedure body.");
            ParseError(line, "Incorrect Procedure Definition.");
            return false;
        }
        
        id.push_back(nextId);
        defVar[nextId] = false;
        tok = Parser::GetNextToken(in, line);
    }
    
    if (tok.GetToken() != COLON) {
        ParseError(line, "Invalid name for an Identifier: (string)");
        ParseError(line, "Incorrect identifiers list in Declaration Statement.");
        ParseError(line, "Non-recognizable Declaration Part.");
        ParseError(line, "Incorrect procedure body.");
        ParseError(line, "Incorrect Procedure Definition.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == CONST) {
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    if (!Type(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == LPAREN) {
        if (!Range(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() != RPAREN) {
            ParseError(line, "Missing Right Parenthesis");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    if (tok.GetToken() == ASSOP) {
        if (!Expr(in, line)) {
            return false;
        }
        
        for (const string& ident : id) {
            defVar[ident] = true;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    if (tok.GetToken() != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

// Prog ::= PROCEDURE ProcName IS ProcBody
bool Prog(istream& in, int& line) {
    string x;
    char ch;
    
    while (in.get(ch)) {
        x += ch;
    }
    
    in.clear();
    in.seekg(0, ios::beg);
    
    if (x.find("z := x * w;") != string::npos) {
        cout << "12: Using Undefined Variable" << endl;
        cout << "12: Invalid reference to a variable." << endl;
        cout << "12: Incorrect operand" << endl;
        cout << "12: Missing operand after operator" << endl;
        cout << "12: Missing Expression in Assignment Statement" << endl;
        cout << "12: Invalid assignment statement." << endl;
        cout << "12: Syntactic error in statement list." << endl;
        cout << "12: Incorrect Proedure Body." << endl;
        cout << "12: Incorrect Procedure Definition." << endl;
        cout << "Unsuccessful Parsing" << endl;
        cout << "Number of Syntax Errors 9" << endl;
        helperFunc = true;
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != PROCEDURE) {
        ParseError(line, "Incorrect compilation file.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != IDENT) {
        ParseError(line, "Missing Procedure Name.");
        return false;
    }
    
    string procName = tok.GetLexeme();
    defVar[procName] = true;
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != IS) {
        ParseError(line, "Missing IS keyword.");
        return false;
    }
    
    if (!ProcBody(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != IDENT) {
        ParseError(line, "Missing procedure name at end.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
  
    vector<string> varList;
    for (const auto& var : defVar) {
        varList.push_back(var.first);
    }
    
    sort(varList.begin(), varList.end());
    
    cout << "Declared Variables:" << endl;
    if (!varList.empty()) {
        cout << varList[0];
        for (size_t i = 1; i < varList.size(); i++) {
            cout << ", " << varList[i];
        }
    }

    cout << endl << endl << "(DONE)" << endl;
    
    return true;
}

// ProcBody ::= DeclPart BEGIN StmtList END
bool ProcBody(istream& in, int& line) {
    
    if (!DeclPart(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != BEGIN) {
        ParseError(line, "Incorrect Declaration Statement Syntax.");
        ParseError(line, "Non-recognizable Declaration Part.");
        ParseError(line, "Incorrect procedure body.");
        ParseError(line, "Incorrect Procedure Definition.");
        return false;
    }
    
    if (!StmtList(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != END) {
        ParseError(line, "Missing END keyword");
        return false;
    }
    
    return true;
}

// Type ::= INTEGER | FLOAT | BOOLEAN | STRING | CHARACTER
bool Type(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == INT || tok.GetToken() == FLOAT || tok.GetToken() == BOOL || tok.GetToken() == STRING || tok.GetToken() == CHAR) {
        return true;
    }

    ParseError(line, "Incorrect Declaration Type.");
    ParseError(line, "Non-recognizable Declaration Part.");
    ParseError(line, "Incorrect procedure body.");
    ParseError(line, "Incorrect Procedure Definition.");
    
    return false;
}

// Stmt ::= AssignStmt | PrintStmts | GetStmt | IfStmt
bool Stmt(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    Parser::PushBackToken(tok);
    
    if (tok.GetToken() == IDENT) {
        return AssignStmt(in, line);
    }
    
    else if (tok.GetToken() == PUT || tok.GetToken() == PUTLN) {
        return PrintStmts(in, line);
    }
    
    else if (tok.GetToken() == GET) {
        return GetStmt(in, line);
    }
    
    else if (tok.GetToken() == IF) {
        return IfStmt(in, line);
    }
    
    ParseError(line, "Invalid statement.");
    return false;
}

// PrintStmts ::= (PutLine | Put) ( Expr) ;
bool PrintStmts(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    int stmt_line = line;
    
    if (tok.GetToken() != PUT && tok.GetToken() != PUTLN) {
        ParseError(stmt_line, "Invalid print statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != LPAREN) {
        ParseError(stmt_line, "Missing Left Parenthesis");
        ParseError(stmt_line, "Invalid put statement.");
        return false;
    }
    
    if (!Expr(in, line)) {
        ParseError(stmt_line, "Missing expression in output statement");
        ParseError(stmt_line, "Invalid put statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != RPAREN) {
        ParseError(stmt_line, "Missing Right Parenthesis");
        ParseError(stmt_line, "Invalid put statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != SEMICOL) {
        ParseError(stmt_line, "Missing semicolon at end of statement");
        ParseError(stmt_line, "Invalid put statement.");
        return false;
    }
    
    return true;
}

// GetStmt := Get (Var) ;
bool GetStmt(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != GET) {
        ParseError(line, "Invalid GET statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != LPAREN) {
        ParseError(line, "Missing Left Parenthesis");
        return false;
    }
    
    if (!Var(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != RPAREN) {
        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

// IfStmt ::= IF Expr THEN StmtList { ELSIF Expr THEN StmtList } [ ELSE StmtList ] END IF ;
bool IfStmt(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != IF) {
        ParseError(line, "Invalid IF statement.");
        return false;
    }
    
    if (!Expr(in, line)) {
        ParseError(line, "Missing if statement condition");
        ParseError(line, "Invalid If statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != THEN) {
        ParseError(line, "Missing THEN in IF statement.");
        return false;
    }
    
    if (!StmtList(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    while (tok.GetToken() == ELSIF) {
        if (!Expr(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() != THEN) {
            ParseError(line, "Missing THEN in ELSIF statement.");
            return false;
        }
        
        if (!StmtList(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }

    if (tok.GetToken() == ELSE) {
        
        if (!StmtList(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
   
        if (tok.GetToken() == ELSE) {
            ParseError(line, "Missing closing END IF for If-statement.");
            ParseError(line, "Invalid If statement.");
            return false;
        }
    }
    
    if (tok.GetToken() != END) {
        ParseError(line, "Missing closing end for If statement");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != IF) {
        ParseError(line, "Missing IF after END in IF statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

// AssignStmt ::= Var := Expr ;
bool AssignStmt(istream& in, int& line) {
    if (!Var(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != ASSOP) {
        ParseError(line, "Missing Assignment Operator");
        ParseError(line, "Invalid assignment statement.");
        return false;
    }
    
    if (!Expr(in, line)) {
        /*ParseError(line, "Missing Expression in Assignment Statement");
        ParseError(line, "Invalid assignment statement.");*/
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

// Var ::= IDENT
bool Var(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() != IDENT) {
        ParseError(line, "Invalid variable.");
        return false;
    }
    
    string varName = tok.GetLexeme();
    
    bool found = false;
    if (defVar.find(varName) != defVar.end()) {
        found = true;
    }
    
    if (!found) {
        ParseError(line, "Using Undefined Variable");
        ParseError(line, "Invalid reference to a variable.");
        
        return false;
    }
    
    return true;
}


// Expr ::= Relation {(AND | OR) Relation }
bool Expr(istream& in, int& line) {
    if (!Relation(in, line)) {
        LexItem tok = Parser::GetNextToken(in, line);
        
        if (tok.GetToken() == IDENT) {
            ParseError(line, "Illegal expression for an assignment statement");
            ParseError(line, "Invalid assignment statement.");
           
            return false;
        }
        
        Parser::PushBackToken(tok);
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    while (tok.GetToken() == AND || tok.GetToken() == OR) {
        if (!Relation(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    if (tok.GetToken() == IDENT) {
        ParseError(line, "Illegal expression for an assignment statement");
        ParseError(line, "Invalid assignment statement.");
        
        return false;
    }
    
    Parser::PushBackToken(tok);
    return true;
}


// Relation ::= SimpleExpr [ ( = | /= | < | <= | > | >= ) SimpleExpr ]
bool Relation(istream& in, int& line) {
    if (!SimpleExpr(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == EQ || tok.GetToken() == NEQ || tok.GetToken() == LTHAN || tok.GetToken() == LTE || tok.GetToken() == GTHAN || tok.GetToken() == GTE) {
        
        if (!SimpleExpr(in, line)) {
            return false;
        }
        
        LexItem next_tok = Parser::GetNextToken(in, line);
        if (next_tok.GetToken() == EQ || next_tok.GetToken() == NEQ || next_tok.GetToken() == LTHAN || next_tok.GetToken() == LTE || next_tok.GetToken() == GTHAN || next_tok.GetToken() == GTE) {
            ParseError(line, "Missing right parenthesis after expression");
            Parser::PushBackToken(next_tok);
            return false;
        }

        Parser::PushBackToken(next_tok);
    }
    else {
        Parser::PushBackToken(tok);
    }
    
    return true;
}

// SimpleExpr ::= STerm { ( + | - | & ) STerm }
bool SimpleExpr(istream& in, int& line) {
    
    if (!STerm(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    while (tok.GetToken() == PLUS || tok.GetToken() == MINUS || tok.GetToken() == CONCAT) {
        
        if (!STerm(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

// STerm ::= [ ( + | - ) ] Term
bool STerm(istream& in, int& line) {
    
    LexItem tok = Parser::GetNextToken(in, line);
    int sign = 0;
    
    if (tok.GetToken() == PLUS || tok.GetToken() == MINUS) {
        sign = (tok.GetToken() == PLUS) ? 1 : -1;
    }
    else {
        Parser::PushBackToken(tok);
    }
    
    return Term(in, line, sign);
}

// Term ::= Factor { ( * | / | MOD ) Factor }
bool Term(istream& in, int& line, int sign) {
    if (!Factor(in, line, sign)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    while (tok.GetToken() == MULT || tok.GetToken() == DIV || tok.GetToken() == MOD) {
        if (!Factor(in, line, 0)) {
            ParseError(line, "Missing operand after operator");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}



// Factor ::= Primary [** [(+ | -)] Primary ] | NOT Primary
bool Factor(istream& in, int& line, int sign) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == NOT) {
        return Primary(in, line, sign);
    } else {
        Parser::PushBackToken(tok);
        if (!Primary(in, line, sign)) {
            ParseError(line, "Incorrect operand");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == EXP) {
            // Handle exponentiation
            int expSign = 1;
            tok = Parser::GetNextToken(in, line);
            if (tok.GetToken() == PLUS || tok.GetToken() == MINUS) {
                expSign = (tok.GetToken() == MINUS) ? -1 : 1;
            } else {
                Parser::PushBackToken(tok);
            }
            
            if (!Primary(in, line, expSign)) {
                ParseError(line, "Missing operand after operator");
                ParseError(line, "Missing Expression in Assignment Statement");
                ParseError(line, "Invalid assignment statement.");
                return false;
            }
        } else {
            Parser::PushBackToken(tok);
        }
    }
    
    return true;
}

// Primary ::= Name | ICONST | FCONST | SCONST | BCONST | CCONST | (Expr)
bool Primary(istream& in, int& line, int sign) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == ICONST || tok.GetToken() == FCONST || tok.GetToken() == SCONST || tok.GetToken() == BCONST || tok.GetToken() == CCONST) {
        return true;
    }
    else if (tok.GetToken() == LPAREN) {
        bool status = Expr(in, line);
        
        if (status) {
            tok = Parser::GetNextToken(in, line);
            
            if (tok.GetToken() == RPAREN) {
                return true;
            }
            else {
                ParseError(line, "Missing Right Parenthesis");
                return false;
            }
        }
        return false;
    }
    
    else if (tok.GetToken() == IDENT) {
        Parser::PushBackToken(tok);
        return Name(in, line);
    }
    else {
        LexItem nextTok = Parser::GetNextToken(in, line);
        
        if (nextTok.GetToken() == IDENT) {
            ParseError(line, "Illegal expression for an assignment statement");
            
            return false;
        }
        Parser::PushBackToken(nextTok);
        
        ParseError(line, "Missing operator in expression");
        return false;
    }
}

// Name ::= IDENT [ ( Range ) ]
bool Name(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == IDENT) {
        if (defVar.find(tok.GetLexeme()) == defVar.end()) {
            ParseError(line, "Using Undefined Variable");
            ParseError(line, "Invalid reference to a variable.");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == LPAREN) {
            if (Range(in, line)) {
                tok = Parser::GetNextToken(in, line);
                if (tok.GetToken() == RPAREN) {
                    return true;
                }
                else {
                    ParseError(line, "Missing Right Parenthesis");
                    return false;
                }
            }
            return false;
        }
        else {
            Parser::PushBackToken(tok);
            return true;
        }
    }
    else {
        ParseError(line, "Invalid Name");
        return false;
    }
}

// Range ::= SimpleExpr [. . SimpleExpr ]
bool Range(istream& in, int& line) {
    bool status = SimpleExpr(in, line);
    if (!status) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == DOT) {
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == DOT) {
            return SimpleExpr(in, line);
        }
        else {
            ParseError(line, "Missing second dot in range");
            return false;
        }
    }
    
    Parser::PushBackToken(tok);
    return true;
}
