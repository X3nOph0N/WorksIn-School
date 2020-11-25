#include<iostream>
#include<sstream>
#include<string>
#include<stack>
#include<cstdlib>
using namespace std;

void standardize(string&);
string infix2posfix(string);
double calculatePosfix(string);
double calculateExpression(string);
bool checkIfInNumber(char);
bool checkBalance(const string&);
bool checkAndPop(stack<char>&);
bool checkIfMatch(char,char);
bool checkIfLeftParenthesis(char);
bool checkIfRightParenthesis(char);
int operaCharPriority(char);
bool checkIsNumber(const string&);
double calculateBinary(double,double,char);

int main(){
    string expression;
    getline(cin, expression);
    standardize(expression);
    if(checkBalance(expression)){
    cout<<infix2posfix(expression)<<endl;
    cout<<calculatePosfix(infix2posfix(expression))<<endl;
    cout<<calculateExpression(expression)<<endl;
    }
    else {
        cout<<"Unbalanced expression"<<endl;
    }
    system("pause");
    return 0;
}

void standardize( string& inputExpression){
    int pos=0;
    while(pos<inputExpression.length()){
        if(inputExpression[pos]==32){
            inputExpression.erase(pos,1);
            continue;
            }
            pos++;
    }
    return ;
};

string infix2posfix(string expression){
    string result;
    string tempNum;
    stack<char>operaChars;
    operaChars.emplace('$');
    for(string::const_iterator curr = expression.begin();curr!=expression.end();curr++){
        if(checkIfInNumber(*curr)){
            tempNum+=(char)*curr;
            continue;
        }
        else{
            if(checkIfLeftParenthesis(*curr)){
                operaChars.push(*curr);
                continue;
            }
            if(checkIfRightParenthesis(*curr)){
                if(checkIsNumber(tempNum)){
                tempNum+=(char)32;
                result.append(tempNum);
                tempNum.clear();
                }
                else{
                    cout << "Syntax error,please check the expression";
                    return expression;
                }
                while(!checkIfMatch(operaChars.top(),*curr)){
                    string tempOpera;
                    tempOpera+=operaChars.top();
                    tempOpera += (char)32;
                    result.append(tempOpera);
                    operaChars.pop();
                }
                operaChars.pop();
                continue;
            }
            if(tempNum.size()==0){
                if(checkIfRightParenthesis(*(curr-1))){
                    if(operaCharPriority(*curr)>operaCharPriority(operaChars.top())){
                        operaChars.push(*curr);
                        continue;
                    }
                    else{
                        while(operaCharPriority(operaChars.top())>=operaCharPriority(*curr)){
                            string tempOpera;
                            tempOpera+=operaChars.top();
                            tempOpera+=(char)32;
                            result.append(tempOpera);
                            operaChars.pop();
                        }
                        operaChars.push(*curr); 
                        continue;
                    }                   
                }
                if(*curr=='+'){
                    continue;
                }
                if(*curr=='-'){
                    tempNum+=(char)*curr;
                    continue;
                }
                cout<<"Syntax error,please check the expression";
                return expression;
            }
            else{
                if(checkIsNumber(tempNum)){
                    tempNum+=(char)32;
                    result.append(tempNum);
                    tempNum.clear();
                }
                else{
                    cout<<"Syntax error,please check the expression";
                    return expression;
                }
                
            

            if(operaCharPriority(*curr)>operaCharPriority(operaChars.top())){
                operaChars.push(*curr);
                continue;
            }
            else{
                while(operaCharPriority(operaChars.top())>=operaCharPriority(*curr)){
                    string tempOpera;
                    tempOpera+=operaChars.top();
                    tempOpera+=(char)32;
                    result.append(tempOpera);
                    operaChars.pop();
                }
                operaChars.push(*curr); 
                continue;
            }
            }
            
        }
    }
    if(tempNum.size()!=0){
        tempNum+=(char)32;
        result.append(tempNum);
    }
    while(operaChars.top()!='$'){
        string tempOpera ;
        tempOpera+=(char)operaChars.top();
        tempOpera+=(char)32;
        result.append(tempOpera);
        operaChars.pop();
    }
    result+="\0";
    return result;

}

double calculatePosfix(string expression){
    stack<double>result;
    string tempNum;
    for(unsigned int i=0; i<expression.length();i++){
        if(expression[i]==32){
            if(tempNum.length()>0){
            result.push(stod(tempNum));
            tempNum.clear();
            }
            continue;
        }
        if(checkIfInNumber(expression[i])){
            tempNum+=(char)expression[i];
        }
        else if(expression[i]=='-'&&expression[i+1]!=32){
            tempNum+=(char)'-';
        }
        else{
            double rvalue=result.top();
            result.pop(); 
            double lvalue=result.top();
            result.pop();
            result.push(calculateBinary(lvalue,rvalue,expression[i]));
        }
        
    }
    return result.top();
}

double calculateExpression(string expression){
    stack<double>result;
    stack<char> operaChars;
    string tempNum;
    operaChars.emplace('$');
    for(string::const_iterator curr = expression.begin();curr!=expression.end();curr++){
        if(checkIfInNumber(*curr)){
            tempNum+=(char)*curr;
            continue;
        }
        else{
            if(checkIfLeftParenthesis(*curr)){
                operaChars.push(*curr);
                continue;
            }
            if(checkIfRightParenthesis(*curr)){
                if(checkIsNumber(tempNum)){
             result.push(stod(tempNum));
                tempNum.clear();
                }
                else{
                    cout << "Syntax error,please check the expression";
                    return 0.0;
                }
                while(!checkIfMatch(operaChars.top(),*curr)){
                  double rvalue= result.top();
                  result.pop();
                  double lvalue= result.top();
                  result.pop();
                  result.push(calculateBinary(lvalue,rvalue,operaChars.top()));
                  operaChars.pop();
                }
                operaChars.pop();
                continue;
            }
            if(tempNum.size()==0){
                if(checkIfRightParenthesis(*(curr-1))){
                    if(operaCharPriority(*curr)>operaCharPriority(operaChars.top())){
                        operaChars.push(*curr);
                        continue;
                    }
                    else{
                        while(operaCharPriority(operaChars.top())>=operaCharPriority(*curr)){
                          double rvalue= result.top();
                          result.pop();
                          double lvalue= result.top();
                          result.pop();
                          result.push(calculateBinary(lvalue,rvalue,operaChars.top()));
                            operaChars.pop();
                        }
                        operaChars.push(*curr); 
                        continue;
                    }                   
                }
                if(*curr=='+'){
                    continue;
                }
                if(*curr=='-'){
                    tempNum+=(char)*curr;
                    continue;
                }
                cout<<"Syntax error,please check the expression";
                return 0.0;
            }
            else{
                if(checkIsNumber(tempNum)){
                    result.push(stod(tempNum));
                    tempNum.clear();
                }
                else{
                    cout<<"Syntax error,please check the expression";
                    return 0.0;
                }
                
            

            if(operaCharPriority(*curr)>operaCharPriority(operaChars.top())){
                operaChars.push(*curr);
                continue;
            }
            else{
                while(operaCharPriority(operaChars.top())>=operaCharPriority(*curr)){
                    double rvalue= result.top();
                    result.pop();
                    double lvalue= result.top();
                    result.pop();
                    result.push(calculateBinary(lvalue,rvalue,operaChars.top()));
                    operaChars.pop();
                }
                operaChars.push(*curr); 
                continue;
            }
            }
            
        }
    }
    if(tempNum.size()!=0){
      result.push(stod(tempNum));
    }
    while(operaChars.top()!='$'){
        double rvalue= result.top();
        result.pop();
        double lvalue= result.top();
        result.pop();
        result.push(calculateBinary(lvalue,rvalue,operaChars.top()));
        operaChars.pop();
    }
    if(result.size()==1){
        return result.top();
    }
    cout<<"Syntax error,please check if the expression is valid"<<endl;
    return 0;
}

bool checkIfInNumber(char c){
    return ((c==46||(c>47&&c<58))?true:false);
}

bool checkBalance(const string&inputExpression){
    stack<char>sln{};
    unsigned int size = inputExpression.size();
        for(unsigned int i = 0; i < size; i++){
            if(inputExpression[i]=='('||inputExpression[i]=='['||inputExpression[i]=='{'){
                sln.emplace(inputExpression[i]);
                continue;
            }
            if(inputExpression[i]==')'||inputExpression[i]==']'||inputExpression[i]=='}'){
                sln.emplace(inputExpression[i]);
                checkAndPop(sln);
                
            }
}
    if(sln.empty()){
        return true;
    }
    else{
        return false;
    }
}

bool checkAndPop(stack<char>&inputStack) {
    if(inputStack.size()<2)
        return false;
    char c1=inputStack.top();
    inputStack.pop();
    char c2=inputStack.top();
    inputStack.pop();
    if(checkIfMatch(c2,c1))
        return true;
    else
    {
        inputStack.push(c2);
        inputStack.push(c1);
        return false;
    }
};

bool checkIfMatch(char c1,char c2) {
    if((c1=='('&&c2==')')||(c1=='['&&c2==']')||(c1=='{'&&c2=='}'))
        return true;
    return false;

}

int operaCharPriority(char c){
    if(c=='+'||c=='-'){
        return 1;
    }
    if(c=='*'||c=='/'){
        return 2;
    }
    return -1;
}

bool checkIsNumber(const string& expression){
    bool flag = true;
    int dotCnt = 0;
    for(string::const_iterator curr = expression.begin(); curr != expression.end();curr++){
        if(curr==expression.begin()){
            if(*curr=='-'){
                continue;
            }
            else if(*curr=='.'||!checkIfInNumber(*curr)){
            flag = false;
            break;
            }
        }
        if(checkIfInNumber(*curr)){
            if(*curr=='.'){
                dotCnt++;
                if(dotCnt>1){
                    flag = false;
                    break;
                }
            }
            continue;
        }
        else{
            cout<<(int)*curr;
            if(*curr==0){
                continue;
            }
            flag = false;
            break;
        }
    }
    return flag;
}

bool checkIfLeftParenthesis(char c){
    return (c=='(' || c=='['|| c=='{');
}

bool checkIfRightParenthesis(char c){
    return (c==')' || c==']' || c=='}');
}

double calculateBinary(double lvalue,double rvalue,char operaChar){
    double result = 0;
           switch(operaChar){
                case '+':
                result=(lvalue+rvalue);
                break;
                case '-':
                result=(lvalue-rvalue);
                break;
                case '*':
                result=(lvalue*rvalue);
                break;
                case '/':
                result=(lvalue/rvalue);
                break;
                default:
                break;
            }              
    return result;
}