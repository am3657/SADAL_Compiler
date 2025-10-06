#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cctype>

#include <map>

using namespace std;
map<string, int> SPmap;
map<string, int> IDmap;
map<string, int> KWmap;
int keys = 0;
int specials = 0;
int iden = 0;
bool checkKey = false;
bool checkSpecial = false;
bool checkIdentifier = false;
string keywords[] = {"begin", "end", "if", "else", "while", "for", "break",
"continue", "case", "switch", "class", "public", "private", "abstract", "final"};
// vector<string> keyList;
// vector<string> specialList;
// vector<string> idenList;
bool checkEmpty(ifstream& file){
    return file.peek() == ifstream::traits_type::eof();
}
bool getKeyword(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for(string key: keywords){
      if(key == word){
        keys++;
        if(KWmap.find(word) == KWmap.end()) KWmap[word] = 1;
        else KWmap[word]++;
        return true;
      }
    }
    return false;
}

void getSpecialWord(string word){
  const char first = word[0];
  if(first != '$' && first != '@' && first != '%'){
    return;
  }
    
  for(int i = 1; i < word.size(); i++){
    if(!isalnum(word[i]) && word[i] != '_'){
       
      if(checkSpecial) cout<<"Invalid Special Word" << ": " <<word<<endl;
      return;
    }
  }
    if(SPmap.find(word) == SPmap.end()) SPmap[word] = 1;
    else SPmap[word]++;
    specials++;
  
}

void getIdentifier(string word){
  if(!isalpha(word[0])){return;}
  for(int i = 1; i < word.size(); i++){
    if(!isalnum(word[i])){
      if(checkIdentifier) cout<<"Invalid Identifier Word" << ": " <<word<<endl;
      
      return;
    }
  }
    
    if(getKeyword(word)) return;
    
    if(IDmap.find(word) == IDmap.end()) IDmap[word] = 1;
    else IDmap[word]++;
    iden++;
}
int main(int argc, char *argv[]){
    string filename;
    if (argc > 1) {
        filename = argv[1];
    }

    if(filename == ""){
        cout<<"NO SPECIFIED INPUT FILE NAME."<<endl;
        return 0;
    }
    ifstream file(filename, ios::in);
    if(!file.is_open()){
        cout<<"CANNOT OPEN THE FILE "<< filename <<endl;
        return 0;
    }


    for(int i=2; i<argc; i++){
      string arg = argv[i];
      if(arg == "-id"){
        checkIdentifier = true;
      }
      if(arg == "-kw"){
        checkKey = true;
      }
      if(arg == "-sp"){
        checkSpecial = true;
      }
      if (arg != "-id" && arg != "-kw" && arg != "-sp") {
        cout<<"UNRECOGNIZED FLAG " << arg <<endl;
        return 0;
      }
    }
        if(file.is_open() && checkEmpty(file)){
        cout<<"File is Empty."<<endl;
        return 0;
    }
    int totalWords = 0;
    string line = "";
    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        stringstream s(line);
        string word;
        while (s >> word) {
          totalWords++;
                    
          
          getSpecialWord(word);
          
          
          getIdentifier(word);
          
        }
    }
    cout<<"Total Number of Lines: "<< lineCount<<endl;
    cout<<"Number of Words: "<< totalWords<<endl;
    cout<<"Number of Special Words: "<< specials<<endl;
    cout<<"Number of Identifiers: "<< iden<<endl;
    cout<<"Number of Keywords: "<< keys<<endl;

  if(checkSpecial){
    cout<<endl;
    cout<<"List of Special Words and their number of occurrences:"<< endl;
    map<string, int>::iterator b = SPmap.begin();
    while (b != SPmap.end()) {
      cout<<b->first<<": "<<b->second<<endl;
      ++b;
    }
  }
    
  if(checkIdentifier){
    cout<<endl;
    cout<<"List of Identiers and their number of occurrences:"<< endl;
    map<string, int>::iterator c = IDmap.begin();
    while (c != IDmap.end()) {
      cout<<c->first<<": "<<c->second<<endl;
      ++c;
    }
  }
    
    
  if(checkKey){
        cout << endl;
      cout<<"List of Keywords and their number of occurrences:"<< endl;
      map<string, int>::iterator a = KWmap.begin();
      while (a != KWmap.end()) {
        cout<<a->first<<": "<<a->second<<endl;
        ++a;
      }
    }
    
  return 0;
}