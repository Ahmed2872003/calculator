#include <iostream>
#include<stack>
#include<string>
#include<math.h>
using namespace std;
 bool isoperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;
    return false;
}
bool lore(char exp , char top)  // less or equal (priority)
{
    if(((exp == '+' || exp == '-') && (top == '*' || top == '/' || top == '^')))   // less order
        return true;
    else if(((exp == '+' || exp == '-') && ((top == '-' || top == '+'))))  // equal order (+,-)
        return true;   
    else if(((exp == '*' || exp == '/') && ((top == '*' || top == '/'))))   // equal order (*,/)
        return true;
    else if((exp == '^' && top == '^') || (exp!= top && top == '^'))
        return true;
    return false;
}
void swap(stack<char>& st,string& exp , int index)
{
    char temp = exp[index];
    exp[index] = st.top();
    st.pop();
    st.push(temp);
}
int evaluate (int op1 , int op2 , char sign)
{
    auto result = 0;
    switch(sign)
    {
        case '+' : 
            result = op1 + op2;
            break;
        case '-' : 
            result = op1 - op2;
            break;
        case '*' : 
            result = op1 * op2;
            break;
        case '/' : 
            result = op1 / op2;
            break;
        case '^' :
            result = pow(op1 , op2);
            break;
    }
    return result;
}
int to_int (string& exp , int& i)
{
    int number = 0;
    while(exp[i] >= '0' && exp[i] <= '9')
    {
        number = number * 10 + (exp[i] - '0');
        i++;
    }
    i--;
    return number;
}
int main() {
 
    string exp;
    auto result = 0;
    stack<char>modify;
    stack<int>eval;
    cout << "Enter your expression : ";
    getline(cin,exp);
    for(int j = 0 ; j < exp.size() ; j++)
    {
        if(exp[j] == ' ' || exp[j] == '(' || exp[j] == ')')
        {
            if(exp[j] == '(' || exp[j] == ')')
                {
                    modify.push(exp[j]);
                    if(exp[j] == ')')
                    {
                        modify.pop();
                        string signs;
                        int c = 0;
                        while(modify.top()!='(')
                        {
                            c++;
                            signs+=modify.top();
                            modify.pop();
                        }
                        modify.pop();
                        exp.insert(j , signs);
                        j+=c;
                    }
                }
                    exp.erase(j , 1);
                    j--;

        }
        else if(isoperator(exp[j]))
        {
            if(modify.empty())
            {
                modify.push(exp[j]);
                exp[j] = ' ';
            }
            else if(lore(exp[j] , modify.top()))
            {
                swap(modify , exp , j);
            }
            else
            {
                modify.push(exp[j]);
                exp[j] = ' ';

            }
        }
    }
    while(!modify.empty()) 
    {
        exp+=modify.top();
        modify.pop();
    }
    cout << exp << endl;
        // evaluate expression
for(int i = 0 ; i < exp.size() ; i++)
{
    if(exp[i] == ' ')
        continue;
    if(isoperator(exp[i]))
    {
        int operand2 = eval.top();
        eval.pop();
        int operand1 = eval.top();
        eval.pop();
        result = evaluate(operand1 , operand2 , exp[i]);
        eval.push(result);
    }
    else
    {
        eval.push(to_int(exp , i));
    }
}
cout << "Answer = " << result << endl;
    return 0;       
    }
