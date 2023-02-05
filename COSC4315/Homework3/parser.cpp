#include <string>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <map>
 //uses older version of c++, before c++17
 //https://github.com/uliwitness/simpleparser was used to help make code 
 //time complexity of O(n^2) or greater
 //can not do if else statements 

 //line number counter 
int totalLineNum = 1;
 

//structure for variables that are either ints or lists
struct varInfo {
  int value;
  std::vector<int> values;
  bool isList;
};
 //token types for the tokenizer
enum TokenType {
  WHITESPACE, // No token ever has this type.
  IDENTIFIER,
  INTEGER_LITERAL,
  STRING_LITERAL,
  OPERATOR,
  POTENTIAL_TAB,
  TABED
};
 

 //strings to label the tokes
static const char *sTokenTypeStrings[] = {
  "WHITESPACE",
  "IDENTIFIER",
  "INTEGER_LITERAL",
  "STRING_LITERAL",
  "OPERATOR",
  "POTENTIAL_TAB",
  "TABED"
};
 
 //token class to hold the info we need
class Token {
public:
  enum TokenType mType {
    WHITESPACE
  };
  std::string mText;
  int mLineNumber = 0;
  bool isTabed = false;
  int tabNum = 0;
  void debugPrint() const;
};
 // class for tokenizer 
class Tokenizer{
public:
  std::vector<Token>parse(const std::string &inProgram);
private:
  void endToken(Token &token, std::vector<Token> &tokens);
};
 
 //tokenizer function  goes through each character of the string
std::vector<Token> Tokenizer::parse(const std::string &inProgram) {
  std::vector<Token> tokens;
  Token currentToken;
  currentToken.mLineNumber = 1;
  for (char currCh : inProgram) {
    switch (currCh) {
      // Integers
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (currentToken.mType == WHITESPACE) {
        currentToken.mType = INTEGER_LITERAL;
        currentToken.mText.append(1, currCh);
      }
      else {
        currentToken.mText.append(1, currCh);
      }
      break;
      // operators
    case '(':
    case ')':
    case '{':
    case '}':
    case '=':
    case '+':
    case '-':
    case '*':
    case '<':
    case ',':
    case '#':
    case '[':
    case ']':
    // case '"':
    case ':':
      if (currentToken.mType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = OPERATOR;
        currentToken.mText.append(1, currCh);
        endToken(currentToken, tokens);
      }
      else {
        currentToken.mText.append(1, currCh);
      }
      break;
    // whitespace and tabs
    case ' ':
      if (currentToken.mType != POTENTIAL_TAB && currentToken.mType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = POTENTIAL_TAB;
        currentToken.mText.append(1, currCh);
        endToken(currentToken, tokens);
      }
      else if (currentToken.mType == POTENTIAL_TAB) {
        endToken(currentToken, tokens);
        currentToken.mType = TABED;
        currentToken.mText.append(1, currCh);
        endToken(currentToken, tokens);
      }
      else if (currentToken.mType == STRING_LITERAL) {
        currentToken.mText.append(1, currCh);
      }
      else {
        endToken(currentToken, tokens);
      }
      break;
    case '\t':
      if (currentToken.mType == STRING_LITERAL) {
        currentToken.mText.append(1, currCh);
      }
      else {
        endToken(currentToken, tokens);
      }
      break;
    case '\n':
      // newlines and keeps track of line number
      endToken(currentToken, tokens);
      ++currentToken.mLineNumber;
      totalLineNum++;
      break;
    case '\r':
      endToken(currentToken, tokens);
      break;
    case '"':
      if (currentToken.mType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = STRING_LITERAL;
      }
      else if (currentToken.mType == STRING_LITERAL) {
        endToken(currentToken, tokens);
      }
      break;
    default:
      // identifiers
      if (currentToken.mType == WHITESPACE || currentToken.mType == INTEGER_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.mType = IDENTIFIER;
        currentToken.mText.append(1, currCh);
      }
      else {
        currentToken.mText.append(1, currCh);
      }
      break;
    }
  }

  endToken(currentToken, tokens);

  return tokens;
}
//map function for the variables
//binding C++ data structure/class
 
std::map<std::string, varInfo> variables;
struct Func{
//std::string FuncName;
std::vector<Token>Params;
std::vector<std::vector<Token>>LocVar;
std::vector<Token>ReturnVar;
bool hasreturn=false;
};
 
void printMap() {
  std::map<std::string, varInfo>::iterator it = variables.begin();
  while(it != variables.end()) {
    std::cout << "Variable = " << it->first << "\tValue = " << it->second.value << "\t" << " List = ";
    for(int i = 0; i < it->second.values.size(); i++) {
      std::cout << it->second.values[i] << " ";
    }
    std::cout << "\tisList = " << it->second.isList << std::endl;
    it++;
  }
}

void printBody(std::vector<Token> body) {
  for(int i = 0; i < body.size(); i++) {
    std::cout << body[i].mText << " ";
  }
}

 //parser class to parse tokens
class Parser {
public:
  void parse(std::vector<Token> &tokens);
private:
  std::vector<Token>::iterator mCurrTok;
  std::vector<Token>::iterator mEndTok;

  bool isIdentifier(const std::string &name = std::string());
  bool isOperator(const std::string &name = std::string());
  bool isString(const std::string &name = std::string());
  bool isAssignment();
  bool isPrintCall();
  bool isPrintForList();
  bool isCommentedLine();
  bool isListAssignment();
  bool isListConcatAssignment();
  bool isListUpdate();
  bool isIfElse();
  bool isDef();
  bool isAssignFuncCall();
  bool isFuncCall();
  bool isLen();
  void funcBody(std::vector<varInfo> &funccall, varInfo &returnAns, std::string funckey);

  std::map<std::string, Func> FuncVars;
  bool isAssignmentFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  bool isPrintCallFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  bool isPrintForListFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  bool isCommentedLineFunc(std::vector<Token> &line);
  bool isListAssignmentFunc(std::vector<Token> &line);
  bool isListConcatAssignmentFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  bool isLenFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  bool isListUpdateFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  bool isReturnStatement(std::vector<Token> &line, std::map<std::string, varInfo> funcmap);
  varInfo funcBody2(std::vector<Token> &funccall);
};

bool Parser::isIdentifier(const std::string &name){
  if(mCurrTok == mEndTok){return false;}
  if(mCurrTok->mType != IDENTIFIER){return false;}
  if(!name.empty() && mCurrTok->mText != name){return false;}

  ++mCurrTok;
  return true;
}

bool Parser::isOperator(const std::string &name){
  if(mCurrTok == mEndTok){return false;}
  if(mCurrTok->mType != OPERATOR){return false;}
  if(!name.empty() && mCurrTok->mText != name){return false;}

  ++mCurrTok;
  return true;
  
}

bool Parser::isString(const std::string &name){
  if(mCurrTok == mEndTok){return false;}
  if(mCurrTok->mType != STRING_LITERAL){return false;}
  if(!name.empty() && mCurrTok->mText != name){return false;}

  ++mCurrTok;
  return true;
}

bool Parser::isAssignment() {
  if(isListAssignment()==true){

    return false;
  }
  if(isLen() == true) {
    return false;
  }
  if(isListConcatAssignment()==true){
   
 
    return false;
  }
  if(isCommentedLine()==true){
    
    return false;
  }
  if(isAssignFuncCall()==true){
    
    return false;
  }
  if(isIdentifier()==true){
    if(isOperator("=")==true){
      --mCurrTok;
      --mCurrTok;
      return true;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isPrintCall() {
    std::map<std::string, varInfo>::iterator it;
    if (isIdentifier("print") == true) {
        if (isOperator("(") == true) {
            if (isString() == true) {
                if (isOperator(",") == true) {
                    it = variables.find(mCurrTok->mText);
                    if (it != variables.end() && it->second.isList == false) {
                        --mCurrTok;
                        --mCurrTok;
                        --mCurrTok;
                        --mCurrTok;
                        return true;
                    }
                }
                else {
                    std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
                    exit(0);
                }
                --mCurrTok;
                --mCurrTok;
            }
            it = variables.find(mCurrTok->mText);
            if (it != variables.end() && it->second.isList == false) {
                --mCurrTok;
                --mCurrTok;
                return true;
            }
            --mCurrTok;
        }
        --mCurrTok;
    }
    return false;
}

bool Parser::isPrintForList() {
  std::map<std::string, varInfo>::iterator it;
  if (isIdentifier("print") == true) {
    if (isOperator("(") == true) {
      if (isString() == true) {
        if (isOperator(",") == true) {
          it = variables.find(mCurrTok->mText);
          if (it != variables.end() && it->second.isList == true) {
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            return true;
          }
        }
        else {
          std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
          exit(0);
        }
        --mCurrTok;
        --mCurrTok;
      }
      it = variables.find(mCurrTok->mText);
      if (it != variables.end() && it->second.isList == true) {
        --mCurrTok;
        --mCurrTok;
        return true;
      }
      --mCurrTok;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isCommentedLine() {
  if(isOperator("#")==true) {
    --mCurrTok;
    return true;
  }
  return false;
}

bool Parser::isListAssignment() {
  if (isIdentifier() == true) {
    if (isOperator("=") == true) {
      if (isOperator("[") == true) {
        --mCurrTok;
        --mCurrTok;
        --mCurrTok;
        return true;
      }
      if(isIdentifier() == true) {
        if(isOperator("[") == true) {
          if(mCurrTok->mText == ":") {
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            return true;
          }
          ++mCurrTok;
          if(mCurrTok->mText == "]") {
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            return false;
          }
          else {
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            --mCurrTok;
            return true;           
          }
        }
        --mCurrTok;
      }
      --mCurrTok;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isListConcatAssignment() {
  std::map<std::string, varInfo>::iterator it = variables.begin();
  if (isIdentifier() == true) {
    if (isOperator("=") == true) {
      it = variables.find(mCurrTok->mText);
      if (it->second.isList == true && isIdentifier() == true) {
        if(isOperator("[")) {
          --mCurrTok;
          --mCurrTok;
        }
        else {
          --mCurrTok;
          --mCurrTok;
          --mCurrTok;
          return true;
        }
      }
      --mCurrTok;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isListUpdate() {
  std::map<std::string, varInfo>::iterator it = variables.begin();
  it = variables.find(mCurrTok->mText);
  if (it == variables.end()) {
    return false;
  }
  ++mCurrTok;
  if (isOperator("[") == true && it->second.isList == true) {
    --mCurrTok;
    --mCurrTok;
    return true;
  }
  --mCurrTok;
  return false;
}

bool Parser::isIfElse() {
  std::map<std::string, varInfo>::iterator it;
  if (isIdentifier("if") == true) {
    --mCurrTok;
    return true;
  }
  if(isIdentifier("else") == true) {
    --mCurrTok;
    return true;
  }
  return false;
}

bool Parser::isDef() {
  if (isIdentifier("def") == true) {
    if (isIdentifier() == true) {
      if (isOperator("(")) {
        --mCurrTok;
        --mCurrTok;
        --mCurrTok;
        return true;
      }
      --mCurrTok;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isLen(){
  std::map<std::string, varInfo>::iterator it;
  if(isIdentifier()==true){
    if(isOperator("=")==true){
      if(isIdentifier("len")==true){
        if(isOperator("(")==true){
      --mCurrTok;
      --mCurrTok;
      --mCurrTok;
      --mCurrTok;
      return true;
          }
        --mCurrTok;
        }
      --mCurrTok;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isAssignFuncCall() {
  std::map<std::string, Func>::iterator fit;
  if (isIdentifier() == true) {
    if (isOperator("=") == true) {
      fit = FuncVars.find(mCurrTok->mText);
      if (mCurrTok->mType == IDENTIFIER && fit != FuncVars.end() && mCurrTok->mText != "print" && fit->second.hasreturn == true) {
        ++mCurrTok;
        if (isOperator("(") == true) {
          --mCurrTok;
          --mCurrTok;
          --mCurrTok;
          --mCurrTok;
          return true;
        }
        --mCurrTok;
      }
      --mCurrTok;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isFuncCall() {
  std::map<std::string, Func>::iterator fit;
  fit = FuncVars.find(mCurrTok->mText);
  if (mCurrTok->mType == IDENTIFIER && fit != FuncVars.end() && fit->second.hasreturn == false){
    ++mCurrTok;
    if (isOperator("(") == true){
      --mCurrTok;
      --mCurrTok;
      return true;
    }
    --mCurrTok;
  }
  return false;
}

bool Parser::isLenFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap) {
  if (line[0].mType == true) {
    if (line[1].mType == OPERATOR && line[1].mText == "=") {
      if (line[2].mType == IDENTIFIER && line[2].mText == "len") {
        if (line[3].mType == OPERATOR && line[3].mText == "(") {
          return true;
        }
      }
    }
  }
  return false;
}

bool Parser::isAssignmentFunc(std::vector<Token> &line,std::map<std::string,varInfo> funcmap){
  if(isListAssignmentFunc(line) || isListConcatAssignmentFunc(line,funcmap) || isCommentedLineFunc(line) || isLenFunc(line, funcmap)) {
    return false;
  }
  return true;
}

bool Parser::isPrintCallFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap) {
  std::map<std::string, varInfo>::iterator it;
  if (line[0].mText == "print" && line[1].mText == "(") {
    if (line[2].mType == STRING_LITERAL) {
      if (line[3].mText != ",") {
        std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
        exit(0);
      }
      it = funcmap.find(line[4].mText);
      if (it != funcmap.end() && it->second.isList == false) {
        return true;
      }
    }
    else {
      it = funcmap.find(line[2].mText);
      if (it != funcmap.end() && it->second.isList == false) {
        return true;
      }
    }
  }
  return false;
}

bool Parser::isPrintForListFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap) {
  std::map<std::string, varInfo>::iterator it;
  if (line[0].mText == "print" && line[1].mText == "(") {
    if (line[2].mType == STRING_LITERAL) {
      if (line[3].mText != ",") {
        std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
        exit(0);
      }
      it = funcmap.find(line[4].mText);
      if (it != funcmap.end() && it->second.isList == true) {
        return true;
      }
    }
    else {
      it = funcmap.find(line[2].mText);
      if (it != funcmap.end() && it->second.isList == true) {
        return true;
      }
    }
  }
  return false;
}

bool Parser::isCommentedLineFunc(std::vector<Token> &line){
  if(line[0].mText == "#") {
    return true;
  }
  return false;
  
}

bool Parser::isListAssignmentFunc(std::vector<Token> &line){
  if(line[1].mText == "=") {
    if(line[2].mText == "[") {
      return true;
    }
  }
  return false;
}

bool Parser::isListConcatAssignmentFunc(std::vector<Token> &line,std::map<std::string,varInfo> funcmap){
  std::map<std::string, varInfo>::iterator it = funcmap.begin();
  it = funcmap.find(line[2].mText);
  if(line[0].mType == IDENTIFIER && line[1].mText == "=") {
    if(it != funcmap.end() && it->second.isList == true) {
      if(line[3].mText == "[") {
        return false;
      }
      return true;
    }
  }
  return false;
}

bool Parser::isListUpdateFunc(std::vector<Token> &line, std::map<std::string, varInfo> funcmap) {
  std::map<std::string, varInfo>::iterator it = funcmap.begin();
  it = funcmap.find(line[0].mText);
  if (it == funcmap.end()) {
    return false;
  }
  if (line[1].mText == "[" && it->second.isList == true) {
    return true;
  }
  return false;
}

bool Parser::isReturnStatement(std::vector<Token> &line,std::map<std::string,varInfo> funcmap){
  if(line[0].mType==IDENTIFIER && line[0].mText=="return"){
    return true;
  }
  return false;
}

void Parser::funcBody(std::vector<varInfo> &funccall, varInfo &returnAns, std::string funckey) {
  std::map<std::string, Func>::iterator fit;
  fit = FuncVars.find(funckey);
  bool hr = fit->second.hasreturn;
  std::map<std::string, varInfo> funcVariables;
  std::vector<std::vector<Token>> line;
  std::vector<Token> rt;
  for (int i = 0; i < fit->second.LocVar.size(); i++) {
    std::vector<Token> temp;
    for (int j = 0; j < fit->second.LocVar[i].size(); j++) {
      if (hr == true && i == fit->second.LocVar.size() - 1) {
        rt.push_back(fit->second.LocVar[i][j]);
        continue;
      }
      else {
        temp.push_back(fit->second.LocVar[i][j]);
        continue;
      }
    }
    line.push_back(temp);
  }
  if (hr == true && line[line.size() - 1].size() == 0) {
    line.pop_back();
  }
  for (int i = 0; i < funccall.size(); i++) {
    funcVariables.insert({fit->second.Params[i].mText, funccall[i]});
  }
  for (int i = 0; i < line.size(); i++) {
    
    if (isAssignmentFunc(line[i], funcVariables)) {
      std::map<std::string, varInfo>::iterator it,itCurr,itInd;
      std::string currVarName;
      if (funcVariables.find(line[i][0].mText) == funcVariables.end()) {
        varInfo currVar = (varInfo){.value = 0, .values = {}, .isList = false};
        funcVariables.insert({line[i][0].mText, currVar});
        currVarName = line[i][0].mText;
      }
      else {
        it = funcVariables.find(line[i][0].mText);
        currVarName = it->first;
      }
      std::stack<std::string> expStack;
      std::vector<int> output;
      for (int j = 2; j < line[i].size(); j++) {
        if (line[i][j].mType == IDENTIFIER) {
          it = funcVariables.find(line[i][j].mText);
          itCurr = funcVariables.find(line[i][j].mText);
          if (it == funcVariables.end()) {
            std::cout << "Variable " << line[i][j].mText << " not defined" << std::endl;
            exit(0);
          }
            if(j+1 >= line[i].size()) {
            output.push_back(itCurr->second.value);
            if (output.size() > 1 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
          }
          else {
            if(line[i][j+1].mText == "[") {
              if(line[i][j+2].mType == IDENTIFIER) {
                
                itInd = funcVariables.find(line[i][j+2].mText);
                
                
                if(itInd == funcVariables.end()) {
                  std::cout << "No such variable " << line[i][j+2].mText << std::endl;
                  exit(0);
                }
                
                if(itInd->second.isList) {
                  std::cout << "Variable " << itInd->first << " is a list, not a value" << std::endl;
                  exit(0);
                }
                
                if(itInd->second.value > itCurr->second.values.size()) {
                  std::cout << "Index out of range for variable " << it->first << std::endl;
                  exit(0);
                }
                
                output.push_back(itCurr->second.values[itInd->second.value]);
                if (output.size() > 1 && !expStack.empty()){
                  if (expStack.top() == "+"){
                    output.end()[-2] = output.end()[-1] + output.end()[-2];
                    output.pop_back();
                    expStack.pop();
                  }
                }
                j++; j++; j++;
                continue;
              }
              else {
                if(stoi(line[i][j+2].mText) > itCurr->second.values.size()) {
                  std::cout << "Index out of range for variable " << itCurr->first << std::endl;
                  exit(0);
                }
                else {
                  output.push_back(itCurr->second.values[stoi(line[i][j+2].mText)]);
                  if (output.size() > 1 && !expStack.empty()){
                    if (expStack.top() == "+"){
                      output.end()[-2] = output.end()[-1] + output.end()[-2];
                      output.pop_back();
                      expStack.pop();
                    }
                  }
                  j++; j++; j++;
                  continue;
                }
              }
            }
            output.push_back(itCurr->second.value);
            if (output.size() > 1 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
          }
        }
        if (line[i][j].mType == INTEGER_LITERAL) {
          output.push_back(std::stoi(line[i][j].mText));
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (line[i][j].mType == OPERATOR) {
          expStack.push(line[i][j].mText);
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (output.size() >= 2 && !expStack.empty()) {
          if (expStack.top() == "+") {
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
      }
      it = funcVariables.find(currVarName);
      it->second.value = output[0];
    }

    if(isLenFunc(line[i], funcVariables)){
      std::map<std::string, varInfo>::iterator it,itlist;
      std::string currVarName;
      if (funcVariables.find(line[i][0].mText) == funcVariables.end()) {
        varInfo currVar = (varInfo){.value = 0, .values = {}, .isList = false};
        funcVariables.insert({line[i][0].mText, currVar});
        currVarName = line[i][0].mText;
      }
      else {
        it = funcVariables.find(line[i][0].mText);
        currVarName = it->first;
      }
      it = funcVariables.find(line[i][0].mText);
      itlist=funcVariables.find(line[i][4].mText);
      if(itlist==funcVariables.end()){
         std::cout << "Error: variables doesnt exist"<< std::endl;
              exit(0);
      }
      if(itlist->second.isList==false){
         std::cout << "Error: variable is not a list"<< std::endl;
              exit(0);
      }
      it->second.value=itlist->second.values.size();

      
    }

    if (isPrintCallFunc(line[i], funcVariables)) {
      std::map<std::string, varInfo>::iterator it;
      std::stack<std::string> expStack;
      std::vector<int> output;
      int ind;
      if (line[i][2].mType == STRING_LITERAL) {
        std::cout << line[i][2].mText;
        if (line[i][3].mText != ",") {
          std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
          exit(0);
        }
        int j = 4;
        while (line[i][j].mText != ")") {
          if (line[i][j].mType == IDENTIFIER) {
            it = funcVariables.find(line[i][j].mText);
            if (it == funcVariables.end()) {
              std::cout << "Variable " << line[i][j].mText << " not defined" << std::endl;
              exit(0);
            }
            output.push_back(it->second.value);
          }
          if (line[i][j].mType == INTEGER_LITERAL) {
            output.push_back(std::stoi(line[i][j].mText));
          }
          if (line[i][j].mType == OPERATOR) {
            expStack.push(line[i][j].mText);
          }
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
            }
          }
          j++;
        }
        std::cout << output[0] << std::endl;
      }
      else {
        int j = 2;
        while (line[i][j].mText != ")") {
          if (line[i][j].mType == IDENTIFIER) {
            it = funcVariables.find(line[i][j].mText);
            if (it == funcVariables.end()) {
              std::cout << "Variable " << line[i][j].mText << " not defined" << std::endl;
              exit(0);
            }
            output.push_back(it->second.value);
          }
          if (line[i][j].mType == INTEGER_LITERAL) {
            output.push_back(std::stoi(line[i][j].mText));
          }
          if (line[i][j].mType == OPERATOR) {
            expStack.push(line[i][j].mText);
          }
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
            }
          }
          j++;
        }
        std::cout << output[0] << std::endl;
      }
      continue;
    }
    
    if (isPrintForListFunc(line[i], funcVariables)) {
      std::map<std::string, varInfo>::iterator it;
      if (line[i][2].mType == STRING_LITERAL) {
        std::cout << line[i][2].mText;
        if (line[i][3].mText != ",") {
          std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
          exit(0);
        }
        it = funcVariables.find(line[i][4].mText);
        std::cout << " [";
        for (int k = 0; k < it->second.values.size(); k++) {
          if (k == it->second.values.size() - 1) {
            std::cout << it->second.values[k];
            continue;
          }
          std::cout << it->second.values[k] << ", ";
        }
      }
      else {
        it = funcVariables.find(line[i][2].mText);
        if (it == funcVariables.end()) {
          std::cout << "ERROR: Variable " << line[i][0].mText << " not defined" << std::endl;
          exit(0);
        }
        std::cout << "[";
        for (int k = 0; k < it->second.values.size(); k++) {
          if (k == it->second.values.size() - 1) {
            std::cout << it->second.values[k];
            continue;
          }
          std::cout << it->second.values[k] << ", ";
        }
      }
      std::cout << "]" << std::endl;
      continue;
    }

    if (isCommentedLineFunc(line[i])) {
      continue;
    }
    
    if (isListAssignmentFunc(line[i])) {
      std::map<std::string, varInfo>::iterator it, varit;
      std::string currVarName;
      if (funcVariables.find(line[i][0].mText) == funcVariables.end()) {
        varInfo currVar = (varInfo){.value = 0, .values = {}, .isList = true};
        funcVariables.insert({line[i][0].mText, currVar});
        currVarName = line[i][0].mText;
      }
      else {
        currVarName = line[i][0].mText;
      }
      it = funcVariables.find(currVarName);
      if (it == funcVariables.end()) {
        std::cout << "ERROR: Variable does not exist" << std::endl;
        exit(0);
      }
      int ind = 3;
      while (line[i][ind].mText != "]") {
        if (line[i][ind].mText == ",") {
          ind++;
          continue;
        }
        else {
          if (line[i][ind].mType == INTEGER_LITERAL) {
            it->second.values.push_back(std::stoi(line[i][ind].mText));
            ind++;
          }
          if (line[i][ind].mType == IDENTIFIER) {
            if (funcVariables.find(line[i][ind].mText) == funcVariables.end()) {
              std::cout << "ERROR: Variable " << line[i][ind].mText << " does not exist" << std::endl;
              exit(0);
            }
            varit = funcVariables.find(line[i][ind].mText);
            it->second.values.push_back(varit->second.value);
            ind++;
          }
        }
      }
    }

    if (isListConcatAssignmentFunc(line[i], funcVariables)) {
      std::map<std::string, varInfo>::iterator itVar, itCurrVar;
      std::string currVarName = line[i][0].mText;
      if (funcVariables.find(currVarName) == funcVariables.end()) {
        varInfo currVar = (varInfo){.value = 0, .isList = true};
        funcVariables.insert({currVarName, currVar});
      }
      itVar = funcVariables.find(currVarName);
      for (int j = 2; j < line[i].size(); j++) {
        if (line[i][j].mType == OPERATOR && line[i][j].mText == "+") {
          continue;
        }
        itCurrVar = funcVariables.find(line[i][j].mText);
        if (itCurrVar == funcVariables.end()) {
          std::cout << "ERROR: Value does not exist" << std::endl;
          exit(0);
        }
        if (itCurrVar->second.isList == false) {
          std::cout << "ERROR: Can only concatenate list(not \"int\")" << std::endl;
          exit(0);
        }
        for (int k = 0; k < itCurrVar->second.values.size(); k++) {
          itVar->second.values.push_back(itCurrVar->second.values[k]);
        }
      }
    }

    if (isListUpdateFunc(line[i], funcVariables)) {
      int listIndex = std::stoi(line[i][2].mText);
      std::map<std::string, varInfo>::iterator it;
      it = funcVariables.find(line[i][0].mText);
      if (it == funcVariables.end()) {
        std::cout << "ERROR: No such variable defined" << std::endl;
        exit(0);
      }
      if (it->second.values.size() < listIndex) {
        std::cout << "ERROR: List assignment index out of range" << std::endl;
        exit(0);
      }
      std::stack<std::string> expStack;
      std::vector<int> output;
      for (int j = 5; j < line[i].size(); j++) {
        if (line[i][j].mType == IDENTIFIER) {
          it = funcVariables.find(line[i][j].mText);
          if (it == funcVariables.end()) {
            std::cout << "Variable " << line[i][j].mText << " not defined" << std::endl;
            exit(0);
          }
          output.push_back(it->second.value);
          if (output.size() > 1 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (line[i][j].mType == INTEGER_LITERAL) {
          output.push_back(std::stoi(line[i][j].mText));
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (line[i][j].mType == OPERATOR) {
          expStack.push(line[i][j].mText);
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (output.size() >= 2 && !expStack.empty()) {
          if (expStack.top() == "+") {
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
      }
      it->second.values[listIndex] = output[0];
    }
  }

  if (rt.size() > 0 && hr == true) {
    if (isReturnStatement(rt, funcVariables)) {
      std::map<std::string, varInfo>::iterator it, lit;
      std::stack<std::string> expStack;
      std::vector<int> output;
      std::vector<int> arr;
      if (rt[1].mType == IDENTIFIER) {
        lit = funcVariables.find(rt[1].mText);
        if (lit == funcVariables.end()) {
          std::cout << "Variable " << rt[1].mText << " not defined" << std::endl;
          exit(0);
        }
        if (lit->second.isList == true) {
          returnAns.isList = true;
          returnAns.value = 0;
          for (int j = 0; j < lit->second.values.size(); j++) {
            arr.push_back(lit->second.values[j]);
          }
        }
      }
      for (int j = 1; j < rt.size(); j++) {
        if (rt[j].mType == IDENTIFIER) {
          // std::cout<<"test 2"<<std::endl;
          it = funcVariables.find(rt[j].mText);
          if (it == funcVariables.end()) {
            std::cout << "Variable " << rt[j].mText << " not defined" << std::endl;
            exit(0);
          }
          if (it->second.isList == true) {

          }
          else if (it->second.isList == false) {
            returnAns.isList = false;
            returnAns.values = {};
            output.push_back(it->second.value);
            if (output.size() > 1 && !expStack.empty()) {
              if (expStack.top() == "+") {
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
          }
          continue;
        }
        if (rt[j].mType == INTEGER_LITERAL) {
          returnAns.isList = false;
          returnAns.values = {};
          output.push_back(std::stoi(rt[j].mText));
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (rt[j].mType == OPERATOR) {
          expStack.push(rt[j].mText);
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (output.size() >= 2 && !expStack.empty()) {
          if (expStack.top() == "+") {
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
      }
      if (returnAns.isList == false) {
        returnAns.value = output[0];
      }
      if (returnAns.isList == true) {
        for (int j = 0; j < arr.size(); j++) {
          returnAns.values.push_back(arr[j]);
        }
      }
    }
  }
}

varInfo Parser::funcBody2(std::vector<Token> &funccall)
{

  std::map<std::string, Func>::iterator fit;
  std::map<std::string, varInfo>::iterator it;
  fit = FuncVars.find(funccall[0].mText);
  if (fit->second.hasreturn == false)
  {
    std::cout << "Function has no return " << std::endl;
    exit(0);
  }

  int ind = 2;
  int paramcount = 0;

  std::vector<varInfo> args;

  for (int i = ind; i < funccall.size(); i++)
  {

    if ((funccall[i].mText == ")" || funccall[i].mText == ",") && funccall.size() != 3)
    {
      paramcount++;
    }
  }

  int psize = fit->second.Params.size();

  if (paramcount > psize)
  {
    std::cout << "There are more arguments than parameters "
              << "Arguments: " << paramcount << "Parameters: " << psize << std::endl;
    exit(0);
  }
  if (paramcount < fit->second.Params.size())
  {
    std::cout << "There are more parameters than arguments  "
              << "Arguments: " << paramcount << "Parameters: " << psize << std::endl;
    exit(0);
  }

  std::stack<std::string> expStack;
  std::vector<int> output;
  varInfo temp;
  if (paramcount > 0)
  {
    for (int i = 2; i < funccall.size(); i++)
    {

      if (funccall[i].mType == IDENTIFIER)
      {
        it = variables.find(funccall[i].mText);
        if (it == variables.end())
        {
          std::cout << "Variable " << funccall[i].mText << " not defined"
                    << " line 1860" << std::endl;
          exit(0);
        }
        if (it->second.isList == true)
        {
          temp.isList = true;
          temp.value = 0;
          for (int j = 0; j < it->second.values.size(); j++)
          {
            temp.values.push_back(it->second.values[j]);
          }
        }
        else if (it->second.isList == false)
        {
          temp.isList = false;
          temp.values = {};
          // temp.value=it->second.value;
          output.push_back(it->second.value);
          if (output.size() > 1 && !expStack.empty())
          {
            if (expStack.top() == "+")
            {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
        }
        // ind++;
        continue;
      }
      if (funccall[i].mType == INTEGER_LITERAL)
      {
        temp.isList = false;
        temp.values = {};
        output.push_back(std::stoi(funccall[i].mText));
        if (output.size() >= 2 && !expStack.empty())
        {
          if (expStack.top() == "+")
          {
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
        // ind++;
        continue;
      }
      if (funccall[i].mType == OPERATOR && funccall[i].mText == "+")
      {
        expStack.push(funccall[i].mText);
        if (output.size() >= 2 && !expStack.empty())
        {
          if (expStack.top() == "+")
          {
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
        // ind++;
        continue;
      }
      if (output.size() >= 2 && !expStack.empty())
      {
        if (expStack.top() == "+")
        {
          output.end()[-2] = output.end()[-1] + output.end()[-2];
          output.pop_back();
          expStack.pop();
        }
        // ind++;
      }

      if (funccall[i].mText == "," || funccall[i].mText == ")")
      {

        if (temp.isList == false)
        {
          temp.value = output[0];
          args.push_back(temp);

          while (!expStack.empty())
          {
            expStack.pop();
          }
          output.clear();
          temp.value = 0;
          temp.values = {};
        }
        else if (temp.isList == true)
        {
          args.push_back(temp);
          while (!expStack.empty())
          {
            expStack.pop();
          }
          output.clear();
          temp.value = 0;
          temp.values = {};
        }

        continue;
      }
    }
  }

  varInfo returnstmnt;

  funcBody(args, returnstmnt, funccall[0].mText);

  return returnstmnt;
}
// parsing function that will test booleans to see what kind of statement is given
void Parser::parse(std::vector<Token> &tokens){
  mCurrTok = tokens.begin();
  mEndTok = tokens.end();
  // Parsing line by line
  while (mCurrTok != mEndTok){

    if (isDef() == true) {
      Func curFunc;
      int ln = mCurrTok->mLineNumber;
      std::vector<Token> line;
      std::vector<Token> line2;
      ++mCurrTok;
      std::string funcname = mCurrTok->mText;
      ++mCurrTok;
      while (mCurrTok->mText != ":" && mCurrTok != mEndTok) {
        if(mCurrTok->mLineNumber != ln) {
          std::cout << "SyntaxError: expected ':' on line " << ln << std::endl;
          exit(0);
        }
        Token ct = *mCurrTok;
        line2.push_back(ct);
        ++mCurrTok;
      }
      ++mCurrTok; 
      for (int i = 0; i < line2.size(); i++) {
        if (line2[i].mText == "," || line2[i].mText == "(" || line2[i].mText == ")") {
          continue;
        }
        curFunc.Params.push_back(line2[i]);
      }
      while (mCurrTok->isTabed == true && mCurrTok != mEndTok) {
        Token ct2 = *mCurrTok;
        line.push_back(ct2);
        ++mCurrTok;
      }
      std::vector<int> linenum;
      int returnln;
      int cl = 0;
      for (int i = 0; i < line.size(); i++) {
        if (line[i].mText == "return") {
          returnln = line[i].mLineNumber;
          curFunc.hasreturn = true;
        }
        if (line[i].mLineNumber > cl) {
          linenum.push_back(line[i].mLineNumber);
          cl = line[i].mLineNumber;
        }
      }
      for (int i = 0; i < linenum.size(); i++) {
        std::vector<Token> tempTok;
        for (int j = 0; j < line.size(); j++) {
          if (line[j].mLineNumber == linenum[i]) {
            tempTok.push_back(line[j]);
          }
        }
        curFunc.LocVar.push_back(tempTok);
      }
      FuncVars.insert({funcname, curFunc});
    }

    else if (isAssignment() == true){
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::map<std::string, varInfo>::iterator it, itInd, itCurr;
      std::map<std::string,Func>::iterator fit;
      if (variables.find(line[0].mText) == variables.end()){
        varInfo currVar = (varInfo){.value = 0, .values = {}, .isList = false};
        variables.insert({line[0].mText, currVar});
      }
      it = variables.find(line[0].mText);
      std::stack<std::string> expStack;
      std::vector<int> output;
      for (int j = 2; j < line.size(); j++){
        if (line[j].mType == IDENTIFIER){
          itCurr = variables.find(line[j].mText);
          if(itCurr->second.isList == true && line[j+1].mText != "[") {
            std::cout << "TypeError: unsupported operand type(s) for +: 'int' and 'list'" << std::endl;
            exit(0);
          }
          fit = FuncVars.find(line[j].mText);
          if (itCurr == variables.end() && (fit == FuncVars.end() && line[j+1].mText != "(")){
            std::cout << "Variable " << line[j].mText << " not defined" << std::endl;
            exit(0);
          }
          if(j+1 >= line.size()) {
            output.push_back(itCurr->second.value);
            if (output.size() > 1 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
          }
          else {
            if(line[j+1].mText=="("){
              int index=j;
              varInfo ans;
              std::vector<Token> nline;
              while(line[index].mText!=")"){
                nline.push_back(line[index]);
                index++;
              }
              nline.push_back(line[index]);
              ans=funcBody2(nline);
              if(ans.isList==true){
                std::cout << "Error: cannot concatenate list to int"<< std::endl;
              exit(0);
                
              }
              output.push_back(ans.value);
              if (output.size() > 1 && !expStack.empty()){
                  if (expStack.top() == "+"){
                    output.end()[-2] = output.end()[-1] + output.end()[-2];
                    output.pop_back();
                    expStack.pop();
                  }
                }
                j = index;
                continue;
            }
            if(line[j+1].mText == "[") {
              if(line[j+2].mType == IDENTIFIER) {
                itInd = variables.find(line[j+2].mText);
                if(itInd == variables.end()) {
                  std::cout << "No such variable " << line[j+2].mText << std::endl;
                  exit(0);
                }
                if(itInd->second.isList) {
                  std::cout << "Variable " << itInd->first << " is a list, not a value" << std::endl;
                  exit(0);
                }
                if(itInd->second.value >= itCurr->second.values.size()) {
                  std::cout << "Index out of range for variable " << it->first << std::endl;
                  exit(0);
                }
                output.push_back(itCurr->second.values[itInd->second.value]);
                if (output.size() > 1 && !expStack.empty()){
                  if (expStack.top() == "+"){
                    output.end()[-2] = output.end()[-1] + output.end()[-2];
                    output.pop_back();
                    expStack.pop();
                  }
                }
                j++; j++; j++;
                continue;
              }
              else {
                if(stoi(line[j+2].mText) >= itCurr->second.values.size()) {
                  std::cout << "Index out of range for variable " << itCurr->first << std::endl;
                  exit(0);
                }
                else {
                  output.push_back(itCurr->second.values[stoi(line[j+2].mText)]);
                  if (output.size() > 1 && !expStack.empty()){
                    if (expStack.top() == "+"){
                      output.end()[-2] = output.end()[-1] + output.end()[-2];
                      output.pop_back();
                      expStack.pop();
                    }
                  }
                  j++; j++; j++;
                  continue;
                }
              }
            }
            output.push_back(itCurr->second.value);
            if (output.size() > 1 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
          }
        }
        if (line[j].mType == INTEGER_LITERAL){
          output.push_back(std::stoi(line[j].mText));
          if (output.size() >= 2 && !expStack.empty()){
            if (expStack.top() == "+"){
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (line[j].mType == OPERATOR){
          expStack.push(line[j].mText);
          if (output.size() >= 2 && !expStack.empty()){
            if (expStack.top() == "+"){
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (output.size() >= 2 && !expStack.empty()){
          if (expStack.top() == "+"){
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
      }
      it->second.value = output[0];
    }

    else if (isPrintCall() == true){
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::map<std::string, varInfo>::iterator it;
      std::stack<std::string> expStack;
      std::vector<int> output;

      if (line[2].mType == STRING_LITERAL){
        int ind = 3;
        std::cout << line[2].mText;
        if (line[3].mText != ","){
          std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
          exit(0);
        }
        int j = 4;
        while (line[j].mText != ")"){
          if (line[j].mType == IDENTIFIER){
            it = variables.find(line[j].mText);
            if (it == variables.end()){
              std::cout << "Variable " << line[j].mText << " not defined" << std::endl;
              exit(0);
            }
            output.push_back(it->second.value);
          }
          if (line[j].mType == INTEGER_LITERAL){
            output.push_back(std::stoi(line[j].mText));
          }
          if (line[j].mType == OPERATOR){
            expStack.push(line[j].mText);
          }
          if (output.size() >= 2 && !expStack.empty()){
            if (expStack.top() == "+"){
              output.end()[-2] = output.end()[-1] + output.end()[-2];
            }
          }
          j++;
        }
        std::cout << " " << output[0] << std::endl;
      }
      else{
        int j = 2;
        while (line[j].mText != ")"){
          if (line[j].mType == IDENTIFIER){
            it = variables.find(line[j].mText);
            if (it == variables.end()){
              std::cout << "Variable " << line[j].mText << " not defined" << std::endl;
              exit(0);
            }
            output.push_back(it->second.value);
          }
          if (line[j].mType == INTEGER_LITERAL){
            output.push_back(std::stoi(line[j].mText));
          }
          if (line[j].mType == OPERATOR){
            expStack.push(line[j].mText);
          }
          if (output.size() >= 2 && !expStack.empty()){
            if (expStack.top() == "+"){
              output.end()[-2] = output.end()[-1] + output.end()[-2];
            }
          }
          j++;
        }
        std::cout << output[0] << std::endl;
      }
      continue;
    }

    else if (isCommentedLine() == true){
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
    }

    else if (isListAssignment() == true){
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::map<std::string, varInfo>::iterator it, itCurr, itVar;
      std::string currVarName;
      if (variables.find(line[0].mText) == variables.end()){
        varInfo currVar = (varInfo){.value = 0, .values = {}, .isList = true};
        variables.insert({line[0].mText, currVar});
        currVarName = line[0].mText;
      }
      else{
        currVarName = line[0].mText;
      }
      it = variables.find(currVarName);
      if (it == variables.end()){
        std::cout << "ERROR: Variable does not exist" << std::endl;
        exit(0);
      }
      if(line[2].mType == IDENTIFIER) {
        int beg, end;
        itCurr = variables.find(line[2].mText);
        if(itCurr == variables.end()) {
          std::cout << "Variable " << line[2].mText << " does not exist" << std::endl;
          exit(0);
        }
        if(line[4].mType == INTEGER_LITERAL) {
          beg = stoi(line[4].mText);
          if(line[5].mText == ":") {
            end = itCurr->second.values.size();
          }
        }
        if(line[4].mText == ":") {
          beg = 0;
          if(line[5].mType == INTEGER_LITERAL) {
            end = stoi(line[5].mText);
          }
          else if(line[5].mText == "]") {
            end = itCurr->second.values.size();
          }
        }
        for(int i = 0; i < (end-beg); i++) {
          it->second.values.push_back(itCurr->second.values[beg+i]);
        }
      }
      else {
        int ind = 3;
        while (line[ind].mText != "]"){
          if (line[ind].mText == ","){
            ind++;
            continue;
          }
          else{
            if (line[ind].mType == INTEGER_LITERAL){
              it->second.values.push_back(std::stoi(line[ind].mText));
              ind++;
            }
            if (line[ind].mType == IDENTIFIER) {
              if (variables.find(line[ind].mText) == variables.end()) {
                std::cout << "ERROR: Variable " << line[ind].mText << " does not exist" << std::endl;
                exit(0);
              }
              itVar = variables.find(line[ind].mText);
              it->second.values.push_back(itVar->second.value);
              ind++;
            }            
          }
        }
      }
    }

    else if (isListConcatAssignment() == true){
      std::vector<Token> line;
      std::vector<int> newList;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::map<std::string, varInfo>::iterator itVar, itCurrVar;
      std::string currVarName = line[0].mText;
      if (variables.find(currVarName) == variables.end()){
        varInfo currVar = (varInfo){.value = 0, .isList = true};
        variables.insert({currVarName, currVar});
      }
      itVar = variables.find(currVarName);
      for (int j = 2; j < line.size(); j++){
        if (line[j].mText == "+"){
          continue;
        }
        itCurrVar = variables.find(line[j].mText);
        if (itCurrVar == variables.end()){
          std::cout << "ERROR: Value does not exist" << std::endl;
          exit(0);
        }
        if(itCurrVar->second.isList == false) {
          std::cout << "ERROR: Can only concatenate list(not \"int\")" << std::endl;
          exit(0);         
        }
        else {
          int len = itCurrVar->second.values.size();
          for (int k = 0; k < len; k++){
            newList.push_back(itCurrVar->second.values[k]);
          }
        }
      }
      itVar->second.values.clear();
      for(int i = 0; i < newList.size(); i++) {
        itVar->second.values.push_back(newList[i]);
      }
    }

    else if (isListUpdate() == true){
      int sizeOfSplice = 0;
      std::map<std::string, varInfo>::iterator it, itInd, itCurr;
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      it = variables.find(line[0].mText);
      if(it == variables.end()) {
        std::cout << "Variable " << line[0].mText << " does not exist" << std::endl;
        exit(0);
      }
      if(line[2].mText == ":" || line[3].mText == ":") {
        int begVar1, endVar1, begVar2, endVar2;
        if(line[2].mText == ":") {
          begVar1 = 0;
          if(line[3].mType == INTEGER_LITERAL) {
            endVar1 = stoi(line[3].mText);
          }
          else if(line[3].mText == "]") {
            endVar1 = it->second.values.size();
            sizeOfSplice = endVar1 - begVar1;
          }
        }
        if(line[2].mType == INTEGER_LITERAL) {
          begVar1 = stoi(line[2].mText);
          if(line[3].mText == ":") {
            endVar1 = it->second.values.size();
            sizeOfSplice = endVar1 - begVar1;

          }
        }
        if(line[6].mType == IDENTIFIER) {
          itCurr = variables.find(line[6].mText);
          if(itCurr == variables.end()) {
            std::cout << "Variable " << line[6].mText << " does not exist" << std::endl;
            exit(0);
          }
          if(line[8].mType == INTEGER_LITERAL) {
            begVar2 = stoi(line[8].mText);
            if(line[9].mText == ":") {
              endVar2 = itCurr->second.values.size();
            }
          }
          if(line[8].mText == ":") {
            begVar2 = 0;
            if(line[9].mType == INTEGER_LITERAL) {
              endVar2 = stoi(line[9].mText);
            }
            else if(line[9].mText == "]") {
              endVar2 = itCurr->second.values.size();
            }
          }
          if(sizeOfSplice == (endVar2 - begVar2)) {
            for(int i = 0; i < sizeOfSplice; i++) {
              it->second.values[begVar1+i] = itCurr->second.values[begVar2+i];
            }
          }
          else {
            std::cout << "Splicing Failed" << std::endl;
            exit(0);
          }
        }
      }
      else {
        int listIndex;
        if(line[2].mType == IDENTIFIER) {
          itInd = variables.find(line[2].mText);
          if(itInd == variables.end()) {
            std::cout << "Variable " << line[2].mText << " does not exist" << std::endl;
            exit(0);
          }
          listIndex = itInd->second.value;
        }
        else {
          listIndex = std::stoi(line[2].mText);
        }
        it = variables.find(line[0].mText);
        if (it == variables.end()){
          std::cout << "ERROR: No such variable defined" << std::endl;
          exit(0);
        }
        if (it->second.values.size() <= listIndex){
          std::cout << "IndexError: list assignment index out of range for line " << line[0].mLineNumber << std::endl;
          exit(0);
        }
        std::stack<std::string> expStack;
        std::vector<int> output;
        for (int j = 5; j < line.size(); j++){
          if (line[j].mType == IDENTIFIER){
            itCurr = variables.find(line[j].mText);
            if (itCurr == variables.end()){
              std::cout << "Variable " << line[j].mText << " not defined" << std::endl;
              exit(0);
            }
            if(j+1 < line.size()) {
              if(line[j+1].mText == "[") {
                if(itCurr->second.isList == false) {
                  std::cout << "TypeError: 'int' cannot have an index" << std::endl;
                  exit(0);
                }
                if(line[j+2].mType == IDENTIFIER) {
                  itInd = variables.find(line[j+2].mText);
                  if(itInd == variables.end()) {
                    std::cout << "No such variable " << line[j+2].mText << std::endl;
                    exit(0);
                  }
                  if(itInd->second.isList) {
                    std::cout << "Variable " << itInd->first << " is a list, not a value" << std::endl;
                    exit(0);
                  }
                  if(itInd->second.value >= itCurr->second.values.size()) {
                    std::cout << "Index out of range for variable " << itCurr->first << std::endl;
                    exit(0);
                  }
                  output.push_back(itCurr->second.values[itInd->second.value]);
                  if (output.size() > 1 && !expStack.empty()){
                    if (expStack.top() == "+"){
                      output.end()[-2] = output.end()[-1] + output.end()[-2];
                      output.pop_back();
                      expStack.pop();
                    }
                  }
                  j++; j++; j++;
                  continue;
                }
                else {
                  if(stoi(line[j+2].mText) >= itCurr->second.values.size()) {
                    std::cout << "Index out of range for variable " << itCurr->first << std::endl;
                    exit(0);
                  }
                  else {
                    output.push_back(itCurr->second.values[stoi(line[j+2].mText)]);
                    if (output.size() > 1 && !expStack.empty()){
                      if (expStack.top() == "+"){
                        output.end()[-2] = output.end()[-1] + output.end()[-2];
                        output.pop_back();
                        expStack.pop();
                      }
                    }
                    j++; j++; j++;
                    continue;
                  }
                }
              }
            }
            output.push_back(itCurr->second.value);
            if (output.size() > 1 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
            continue;
          }
          if (line[j].mType == INTEGER_LITERAL){
            output.push_back(std::stoi(line[j].mText));
            if (output.size() >= 2 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
            continue;
          }
          if (line[j].mType == OPERATOR){
            expStack.push(line[j].mText);
            if (output.size() >= 2 && !expStack.empty()){
              if (expStack.top() == "+"){
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
            continue;
          }
          if (output.size() >= 2 && !expStack.empty()){
            if (expStack.top() == "+"){
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
        }
        it->second.values[listIndex] = output[0];
      }
    }

    else if (isPrintForList() == true){
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::map<std::string, varInfo>::iterator it;
      if (line[2].mType == STRING_LITERAL){
        std::cout << line[2].mText;
        if (line[3].mText != ","){
          std::cout << "ERROR: No comma seperating print statement from variables" << std::endl;
          exit(0);
        }
        it = variables.find(line[4].mText);
        if (it == variables.end()){
          std::cout << "ERROR: Variable " << line[0].mText << " not defined" << std::endl;
          exit(0);
        }
        std::cout << "[";
        for (int k = 0; k < it->second.values.size(); k++){
          if (k == it->second.values.size() - 1){
            std::cout << it->second.values[k];
            continue;
          }
          std::cout << it->second.values[k] << ", ";
        }
      }
      else{
        it = variables.find(line[2].mText);
        if (it == variables.end()){
          std::cout << "ERROR: Variable " << line[2].mText << " not defined" << std::endl;
          exit(0);
        }
        std::cout << "[";
        for (int k = 0; k < it->second.values.size(); k++){
          if (k == it->second.values.size() - 1){
            std::cout << it->second.values[k];
            continue;
          }
          std::cout << it->second.values[k] << ", ";
        }
      }
      std::cout << "]" << std::endl;
    }

    else if (isAssignFuncCall() == true) {
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok) {
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::vector<int> answer;
      std::map<std::string, Func>::iterator fit;
      std::map<std::string, varInfo>::iterator it;
      fit = FuncVars.find(line[2].mText);
      int ind = 4;
      int paramcount = 0;
      std::vector<varInfo> args;
      for (int i = ind; i < line.size(); i++) {
        if ((line[i].mText == ")" || line[i].mText == ",") && line.size() != 5) {
          paramcount++;
        }
      }
      int psize = fit->second.Params.size();
      if (paramcount > psize) {
        std::cout << "There are more arguments than parameters "
                  << "Arguments: " << paramcount << "Parameters: " << psize << std::endl;
        exit(0);
      }
      if (paramcount < fit->second.Params.size()) {
        std::cout << "There are more parameters than arguments  "
                  << "Arguments: " << paramcount << "Parameters: " << psize << std::endl;
        exit(0);
      }
      std::stack<std::string> expStack;
      std::vector<int> output;
      varInfo temp;
      if (paramcount > 0) {
        for (int i = 4; i < line.size(); i++) {
          if (line[i].mType == IDENTIFIER) {
            it = variables.find(line[i].mText);
            if (it == variables.end()) {
              std::cout << "Variable " << line[i].mText << " not defined"
                        << " line 1860" << std::endl;
              exit(0);
            }
            if (it->second.isList == true) {
              temp.isList = true;
              temp.value = 0;
              for (int j = 0; j < it->second.values.size(); j++) {
                temp.values.push_back(it->second.values[j]);
              }
            }
            else if (it->second.isList == false) {
              temp.isList = false;
              temp.values = {};
              output.push_back(it->second.value);
              if (output.size() > 1 && !expStack.empty()) {
                if (expStack.top() == "+") {
                  output.end()[-2] = output.end()[-1] + output.end()[-2];
                  output.pop_back();
                  expStack.pop();
                }
              }
            }
            continue;
          }
          if (line[i].mType == INTEGER_LITERAL) {
            temp.isList = false;
            temp.values = {};
            output.push_back(std::stoi(line[i].mText));
            if (output.size() >= 2 && !expStack.empty()) {
              if (expStack.top() == "+") {
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
            continue;
          }
          if (line[i].mType == OPERATOR && line[i].mText == "+") {
            expStack.push(line[i].mText);
            if (output.size() >= 2 && !expStack.empty()) {
              if (expStack.top() == "+") {
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
            continue;
          }
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          if (line[i].mText == "," || line[i].mText == ")") {
            if (temp.isList == false) {
              temp.value = output[0];
              args.push_back(temp);
              while (!expStack.empty()) {
                expStack.pop();
              }
              output.clear();
              temp.value = 0;
              temp.values = {};
            }
            else if (temp.isList == true) {
              args.push_back(temp);
              while (!expStack.empty()) {
                expStack.pop();
              }
              output.clear();
              temp.value = 0;
              temp.values = {};
            }
            continue;
          }
        }
      }
      varInfo returnstmnt;
      funcBody(args, returnstmnt, line[2].mText);
      std::string currVarName = line[0].mText;
      if (variables.find(currVarName) == variables.end()) {
        variables.insert({currVarName, returnstmnt});
      }
      else {
        variables.erase(currVarName);
        variables.insert({currVarName, returnstmnt});
      }
    }

    else if(isLen() == true){
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok){
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      
      
      std::map<std::string, varInfo>::iterator it,itlist;
      if (variables.find(line[0].mText) == variables.end()){
        varInfo currVar = (varInfo){.value = 0, .values = {}, .isList = false};
        variables.insert({line[0].mText, currVar});
      }
      it = variables.find(line[0].mText);
      itlist=variables.find(line[4].mText);
      if(itlist==variables.end()){
         std::cout << "Error: variables doesnt exist"<< std::endl;
              exit(0);
      }
      if(itlist->second.isList==false){
         std::cout << "Error: variable is not a list"<< std::endl;
              exit(0);
      }
      it->second.value=itlist->second.values.size();
      
      
    }

    else if (isFuncCall() == true) {
      std::vector<Token> line;
      int ln = mCurrTok->mLineNumber;
      while (mCurrTok->mLineNumber == ln && mCurrTok != mEndTok) {
        Token ct = *mCurrTok;
        line.push_back(ct);
        ++mCurrTok;
      }
      std::map<std::string, Func>::iterator fit;
      std::map<std::string, varInfo>::iterator it;
      fit = FuncVars.find(line[0].mText);
      int ind = 2;
      int paramcount = 0;
      std::vector<varInfo> args;
      for (int i = ind; i < line.size(); i++) {
        if ((line[i].mText == ")" || line[i].mText == ",") && line.size() != 3) {
          paramcount++;
        }
      }
      if (paramcount > fit->second.Params.size()) {
        std::cout << "There are more arguments than parameters " << std::endl;
        exit(0);
      }
      if (paramcount < fit->second.Params.size()) {
        std::cout << "There are more parameters than arguments  " << std::endl;
        exit(0);
      }
      std::stack<std::string> expStack;
      std::vector<int> output;
      varInfo temp;
      if(paramcount>0){
        for (int i = 2; i < line.size(); i++) {
        if (line[i].mType == IDENTIFIER) {
          it = variables.find(line[i].mText);
          if (it == variables.end()) {
            std::cout << "Variable " << line[i].mText << " not defined"
                      << " line 2224" << std::endl;
            exit(0);
          }
          if (it->second.isList == true) {
            temp.isList = true;
            temp.value = 0;
            for (int j = 0; j < it->second.values.size(); j++) {
              temp.values.push_back(it->second.values[j]);
            }
          }
          else if (it->second.isList == false) {
            temp.isList = false;
            temp.values = {};
            output.push_back(it->second.value);
            if (output.size() > 1 && !expStack.empty()) {
              if (expStack.top() == "+") {
                output.end()[-2] = output.end()[-1] + output.end()[-2];
                output.pop_back();
                expStack.pop();
              }
            }
          }
          continue;
        }
        if (line[i].mType == INTEGER_LITERAL) {
          temp.isList = false;
          temp.values = {};
          output.push_back(std::stoi(line[i].mText));
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (line[i].mType == OPERATOR && line[i].mText == "+") {
          expStack.push(line[i].mText);
          if (output.size() >= 2 && !expStack.empty()) {
            if (expStack.top() == "+") {
              output.end()[-2] = output.end()[-1] + output.end()[-2];
              output.pop_back();
              expStack.pop();
            }
          }
          continue;
        }
        if (output.size() >= 2 && !expStack.empty()) {
          if (expStack.top() == "+") {
            output.end()[-2] = output.end()[-1] + output.end()[-2];
            output.pop_back();
            expStack.pop();
          }
        }
        if (line[i].mText == "," || line[i].mText == ")") {
          if (temp.isList == false) {
            temp.value = output[0];
            args.push_back(temp);
            while (!expStack.empty()) {
              expStack.pop();
            }
            output.clear();
            temp.value = 0;
            temp.values = {};
          }
          else if (temp.isList == true) {
            args.push_back(temp);
            while (!expStack.empty()) {
              expStack.pop();
            }
            output.clear();
            temp.value = 0;
            temp.values = {};
          }
          continue;
        }
      }
        }
      
      varInfo returnstmnt;
      funcBody(args, returnstmnt, line[0].mText);
    }

    else if (isIfElse() == true) {
      std::vector<Token> ifbody;
      std::vector<Token> elsebody;
      std::map<std::string, varInfo>::iterator it;
      bool ifTrue = false, isList = false;
      int currTab = mCurrTok->tabNum;
      int currVecLine = 0, currTokLine, listInd, listVal;
      while (mCurrTok->tabNum == currTab && mCurrTok != mEndTok) {
        if(mCurrTok->mText == "if") {
          ++mCurrTok;
          if(mCurrTok->mText == "(") {
            ++mCurrTok;
          }
          it = variables.find(mCurrTok->mText);
          ++mCurrTok;
          if(mCurrTok->mText == "[") {
            isList = true;
            ++mCurrTok;
            listInd = stoi(mCurrTok->mText);
            listVal = it->second.values[listInd];
            ++mCurrTok;
            ++mCurrTok;
          }
        }
        if(mCurrTok->mText == "=") {
          ++mCurrTok;
          if(mCurrTok->mText == "=") {
            ++mCurrTok;
            if(isList == true) {
              if(listVal == stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
            else {
              if(it->second.value == stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
          }
          else {
            std::cout << "Invalid syntax in if statement" << std::endl;
          }
        }
        if(mCurrTok->mText == "!") {
          ++mCurrTok;
          if(mCurrTok->mText == "=") {
            ++mCurrTok;
            if(isList == true) {
              if(listVal != stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
            else {
              if(it->second.value != stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
          }
          else {
            std::cout << "Invalid syntax in if statement" << std::endl;
          }
        }
        else if(mCurrTok->mText == ">") {
          ++mCurrTok;
          if(mCurrTok->mText == "=") {
            ++mCurrTok;
            if(isList == true) {
              if(listVal == stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
            else {
              if(it->second.value == stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
              else {
                --mCurrTok;
              }
            }
          }
          else {
            if(isList == true) {
              if(listVal > stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
            else {
              if(it->second.value > stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
          }
        }
        else if(mCurrTok->mText == "<") {
          ++mCurrTok;
          if(mCurrTok->mText == "=") {
            ++mCurrTok;
            if(isList == true) {
              if(listVal <= stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
            else {
              if(it->second.value <= stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
              else {
                --mCurrTok;
              }
            }
          }
          else {
            if(isList == true) {
              if(listVal < stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
            else {
              if(it->second.value < stoi(mCurrTok->mText)) {
                ifTrue = true;
              }
            }
          }
        }
        ++mCurrTok;
        if(mCurrTok->mText == ")") {
          ++mCurrTok;
        }
        ++mCurrTok;
      }
      currTab = mCurrTok->tabNum;
      currTokLine = mCurrTok->mLineNumber;
      while(mCurrTok->tabNum >= currTab && mCurrTok != mEndTok) {
        Token ct = *mCurrTok;
        ifbody.push_back(ct);
        ++mCurrTok;
      }
      if(mCurrTok->mText == "else") {
        ++mCurrTok;
        ++mCurrTok;
        currTab = mCurrTok->tabNum;
        currTokLine = mCurrTok->mLineNumber;
        while(mCurrTok->tabNum >= currTab && mCurrTok != mEndTok) {
          Token ct = *mCurrTok;
          elsebody.push_back(ct);
          ++mCurrTok;
        }
        if(ifTrue == true) {
          Parser ifElseParse;
          ifElseParse.parse(ifbody);
        }
        else {
          Parser ifElseParse;
          ifElseParse.parse(elsebody);
        }
      }
      else {
        if(ifTrue == true) {
          Parser ifElseParse;
          ifElseParse.parse(ifbody);
        }
      }
    }

    else{
      mCurrTok = tokens.end();
    }
  }
}
//part of Tokenizer, ends the token 
 
void Tokenizer::endToken(Token &token, std::vector<Token> &tokens) {
    if (token.mType != WHITESPACE) {
        tokens.push_back(token);
    }
    token.mType = WHITESPACE;
    token.mText.erase();
}
 
 
void Token::debugPrint() const {
  std::cout << "Token(" << sTokenTypeStrings[mType] << ", \"" << mText << "\", " << mLineNumber <<" , "<< isTabed << " , " << tabNum << ")" << std::endl;
}
 
int main(int argc, char* argv[]){

std::string cmdarg = argv[1];

std::ifstream t(cmdarg);
std::stringstream buffer;
buffer << t.rdbuf();

Tokenizer tokenizer;

std::vector<Token> tokens = tokenizer.parse(buffer.str());
std::vector<std::vector<Token>> lines;
int count = 0, currTok = 0;

for(int i = 0; i < totalLineNum; i++) {
  lines.push_back(std::vector<Token>());
  while(tokens[currTok].mLineNumber == i) {
    lines[i].push_back(tokens[currTok]);
    currTok++;
  }
}

for(int i = 0; i < lines.size(); i++) {
  for(int j = 0; j < lines[i].size(); j++) {
    if(j == 0) {
      while(lines[i][j].mText == " ") {
        count++;
        j++;
      }
    }
  }
  if(count >= 1) {
    for(int k = 0; k < lines[i].size(); k++) {
      lines[i][k].isTabed = true;
      lines[i][k].tabNum = count;
    }
  }
  count = 0;
}

std::vector<Token> tokens2;
for(int i = 0; i < lines.size(); i++) {
  for(int j = 0; j < lines[i].size(); j++) {
    if(lines[i][j].mText != " ") {
      tokens2.push_back(lines[i][j]);
    }
  }
}


// for(Token currTok:tokens2) {
//   currTok.debugPrint();
// }

  Parser parser;
  parser.parse(tokens2);
 
//   printMap();
}
