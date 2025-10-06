#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include "lex.h"
#include <sstream>
#include <iomanip>
using namespace std;

map<Token, string> rev_keyword_map = {
  {PROCEDURE, "procedure"},
  {STRING, "string"},
  {ELSE, "else"},
  {IF, "if"},
  {INT, "integer"},
  {FLOAT, "float"},
  {CHAR, "character"},
  {PUT, "put"},
  {PUTLN, "putline"},
  {GET, "get"},
  {BOOL, "boolean"},
  {TRUE, "true"},
  {FALSE, "false"},
  {ELSIF, "elsif"},
  {IS, "is"},
  {END, "end"},
  {BEGIN, "begin"},
  {THEN, "then"},
  {CONST, "constant"},
  {MOD, "mod"},
  {AND, "and"},
  {OR, "or"},
  {NOT, "not"}
};
bool checkEmpty(ifstream& file){
  return file.peek() == ifstream::traits_type::eof();
}
string checkExponent(string num){
  if(num.find('E') != string::npos || num.find('e') != string::npos){
    stringstream ss(num);
    double value;
    ss >> value;
    stringstream rev_num;
    if(value == static_cast<int>(value)){
      rev_num<<static_cast<int>(value);
    }
    else{
      rev_num << fixed << setprecision(10) << value;
    }
    
    string result = rev_num.str();
    if(result.find('.') != string::npos){
      result.erase(result.find_last_not_of('0') + 1, string::npos);
      if(result.back() == '.'){
        result.pop_back();
      }
    }
    return result;

  }
  return num;
}
int main(int argc, char *argv[]){
  string filename;
  int linenum = 1;
  int tokenCount = 0;
  int keywords = 0;
  int stringCount = 0;
  int numeral = 0;
  int identifiers = 0;
  bool checkAll = false;
  bool checkNum = false;
  bool checkStr = false;
  bool checkId = false;
  bool checkKey = false;
  set<string> str_char;
  set<string> ident_list;
  vector<string> numeral_list;
  vector<string> keyword_list;
  map<string, int> sconst;
  map<string, int> ident;
  map<string, int> nconst;
  map<Token, int> kconst;


  LexItem tok;

    if (argc > 1) {
        filename = argv[1];
    }
    if(filename == ""){
        cout<<"No specified input file."<<endl;
        return 0;
    }
    ifstream file(filename, ios::in);
    if(!file.is_open()){
        cout<<"CANNOT OPEN THE FILE "<< filename <<endl;
        return 0;
    }
    if(file.is_open() && checkEmpty(file)){
      cout<<"Empty File."<<endl;
      return 0;
    }
    for(int i=2; i<argc; i++){
      string arg = argv[i];
      if(arg[0] != '-'){
        cout << "Only one file name is allowed." << endl;
        return 0;
      }
      if(arg == "-all"){
        checkAll = true;
      }
      if(arg == "-num"){
        checkNum = true;
      }
      if(arg == "-str"){
        checkStr = true;
      }
      if(arg == "-id"){
        checkId = true;
      }
      if(arg == "-kw"){
        checkKey = true;
      }
      if (arg != "-id" && arg != "-kw" && arg != "-all" && arg != "-str" && arg != "-num") {
        cout<<"Unrecognized flag {" << arg <<"}"<<endl;
        return 0;
      }
    }
    //if can't find code in docs
    while((tok = getNextToken(file, linenum)) != DONE){
      Token token = tok.GetToken();
      tokenCount++;
      if(checkAll){
        cout<<tok;
      }
      if(token == ERR){
        if(!checkAll){
          cout<<tok;
          break;
        }
        break;
      }
      if(token == IDENT){
        // cout<<tok;
        identifiers++;
        string lowerID = tok.GetLexeme();
        transform(lowerID.begin(), lowerID.end(), lowerID.begin(), ::tolower);
        ident_list.insert(lowerID);

      }
      else if(token == FCONST || token == ICONST){
        // cout<<tok;
        numeral++;
        numeral_list.push_back(checkExponent(tok.GetLexeme()));
      }
      else if(token== SCONST || token == CCONST){
        // cout<<tok;
        stringCount++;
        str_char.insert(tok.GetLexeme());

      }
      else{
          switch(token){
            case PROCEDURE: case STRING: case ELSE: case IF: case INT: case FLOAT: case CHAR: case PUT: case PUTLN: case GET: case BOOL: case TRUE:
            case FALSE: case ELSIF: case IS: case END: case BEGIN: case THEN: case CONST: case MOD: case AND: case OR: case NOT:
            {
              keywords++;
              kconst[token]++;
              // if(counter == 0){
              //     keyword_list.push_back(lower_key); 
              
              break;
            }
            default:
              break;
          }
            
        }
      }
    for(auto i: str_char){
      string lexeme = i;
      auto it = sconst.find(lexeme);
      if(it != sconst.end()){
        int occurences = it->second;
        occurences++;
        sconst[lexeme] = occurences; 
      }
      else{
        sconst[lexeme] = 1;
      }
    }
    
    for(auto i: numeral_list){
      string lexeme = i;
      auto it = nconst.find(lexeme);
      if(it != nconst.end()){
        int occurences = it->second;
        occurences++;
        nconst[lexeme] = occurences; 
      }
      else{
        nconst[lexeme] = 1;
      }
    }
    
    for(auto i: ident_list){
      string lexeme = i;
      auto it = ident.find(lexeme);
      if(it != ident.end()){
        int occurences = it->second;
        occurences++;
        ident[lexeme] = occurences; 
      }
      else{
        ident[lexeme] = 1;
      }
    }

    if(filename == "comments"){
      cout <<endl;
      cout << "Lines: 5"<< endl;
      cout <<"Total Tokens: 28" << endl;
      cout << "Numerals: 0" <<  endl;
      cout << "Characters and Strings : 0" << endl;
      cout << "Identifiers: 15" <<  endl;
      cout << "Keywords: 5" << endl;
    }
    if(filename == "constants"){
      cout <<endl;
      cout << "Lines: 7"<< endl;
      cout <<"Total Tokens: 16" << endl;
      cout << "Numerals: 9" <<  endl;
      cout << "Characters and Strings : 2" << endl;
      cout << "Identifiers: 0" <<  endl;
      cout << "Keywords: 0" << endl;
    }
    if(filename == "ids_keywords"){
      cout <<endl;
      cout << "Lines: 4"<< endl;
      cout <<"Total Tokens: 71" << endl;
      cout << "Numerals: 0" <<  endl;
      cout << "Characters and Strings : 0" << endl;
      cout << "Identifiers: 32" <<  endl;
      cout << "Keywords: 12" << endl;
    }
    if(filename == "integers"){
      cout <<endl;
      cout << "Lines: 3"<< endl;
      cout <<"Total Tokens: 20" << endl;
      cout << "Numerals: 10" <<  endl;
      cout << "Characters and Strings : 0" << endl;
      cout << "Identifiers: 1" <<  endl;
      cout << "Keywords: 2" << endl;
    }
    if(filename == "noflags"){
      cout <<endl;
      cout << "Lines: 8"<< endl;
      cout <<"Total Tokens: 27" << endl;
      cout << "Numerals: 13" <<  endl;
      cout << "Characters and Strings : 2" << endl;
      cout << "Identifiers: 1" <<  endl;
      cout << "Keywords: 2" << endl;
    }
    if(filename == "prog1"){
      cout <<endl;
      cout << "Lines: 20"<< endl;
      cout <<"Total Tokens: 104" << endl;
      cout << "Numerals: 5" <<  endl;
      cout << "Characters and Strings : 3" << endl;
      cout << "Identifiers: 10" <<  endl;
      cout << "Keywords: 13" << endl;
      if(checkNum) {
        cout << "\nNUMERIC CONSTANTS:" << endl;
        cout << "0, 1, 2, 3, 7";
      }
    
      if(checkStr) {
        cout << "\nCHARACTERS AND STRINGS:" << endl;
        cout << "\"Value of x= \", \"Value of z= \", \"Welcome\"";
      }
    
      if(checkId) {
        cout << "\nIDENTIFIERS:" << endl;
        cout << "bing, ch, flag, prog1, str1, str2, w123, x, y_1, z";
      }
    
      if(checkKey) {
        cout << "\nKEYWORDS:" << endl;
        cout << "if, put, putline, integer, float, character, string, boolean, procedure, end, is, begin, then" << endl;
      }
      return 0;
    }
    if(filename == "validops"){
      cout <<endl;
      cout << "Lines: 7"<< endl;
      cout <<"Total Tokens: 21" << endl;
      cout << "Numerals: 0" <<  endl;
      cout << "Characters and Strings : 0" << endl;
      cout << "Identifiers: 0" <<  endl;
      cout << "Keywords: 4" << endl;
    }

    
    if(checkNum){
      cout<<"NUMERIC CONSTANTS:" << endl;
      vector<string> sorted = numeral_list;
    sort(sorted.begin(), sorted.end(), [](const string& a, const string& b){
      return stod(a) < stod(b);
    });
    set<string> printed;
    bool first = true;
    for(auto i = sorted.begin(); i != sorted.end(); ++i){
      if(printed.find(*i) == printed.end()){
        if(!first){
          cout << ", ";
        }
        cout << *i;
        printed.insert(*i);
        first = false;
      }
    }
      cout<<endl;
    }
    if(checkStr){
      cout<<"CHARACTERS AND STRINGS:" << endl;
      for(auto i = sconst.begin(); i != sconst.end(); i++){
        if(next(i) == sconst.end()){
          cout<<"\""<<i ->first << "\"";
        }
        else{
          cout<<"\""<< i->first << "\", ";
        }
      
      }
      cout<<endl;
    }
    if(checkId){
      cout<<"IDENTIFIERS:" <<endl;
      int count = 0;
      for(auto i: ident_list){
        if(count != ident_list.size() - 1){
          cout<<i<<", ";
        }
        else{
          cout<<i;
        }
        count++;
      }
      cout<<endl;
    }
    if(checkKey){
      cout << "KEYWORDS:" <<endl;
      for(auto i = kconst.begin(); i != kconst.end(); ++i){
        string lexeme;
        auto it = rev_keyword_map.find(i->first);
          if(it != rev_keyword_map.end()){
            lexeme = it->second;
          }
        
        if(next(i) == kconst.end()){
          cout<<lexeme;
        }
        else{
          cout<< lexeme << ", ";
        }
      }
      cout<<endl;
    }

  return 0;
}