#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;

// Function to check if a given character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/'|| c=='^');
}

// Function to get the precedence of an operator
int getPrecedence(char c) {
	
	if (c == '^' ) {
        return 3;
    } 
    if (c == '*' || c == '/') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char infix[], char postfix[]) {
    char stack[100];
    int top = -1, i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[j] = c;
            j++;
        } else if (isOperator(c)) {
            while (top >= 0 && getPrecedence(stack[top]) >= getPrecedence(c)) {
                postfix[j] = stack[top];
                j++;
                top--;
            }
            top++;
            stack[top] = c;
        } else if (c == '(') {
            top++;
            stack[top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[j] = stack[top];
                j++;
                top--;
            }
            if (top >= 0 && stack[top] == '(') {
                top--;
            } else {
                cout << "Invalid expression: Unmatched ')'" << endl;
                return;
            }
        }
        i++;
    }

    while (top >= 0) {
        if (stack[top] == '(') {
            cout << "Invalid expression: Unmatched '('" << endl;
            return;
        }
        postfix[j] = stack[top];
        j++;
        top--;
    }

    postfix[j] = '\0';
}


double evaluatePostfix(char postfix[]){
	
	double stack[100];
	int top=-1, i=0, j=0;
	
	while(postfix[i]!='\0'){
		
		char ch=postfix[i];
		
		if(isalnum(ch)){
			
			stack[++top]=ch-'0';
		}
		
		else if(isOperator(ch)){
			
			double operator1 = stack[top];
			top--;
			
			double operator2 = stack[top];
			top--;
			
			double result;
			
			switch(ch){
				
				case '+':
					result = operator1+operator2;
					break;
				
					case '-':
					result = operator1-operator2;
					break;
					
			case '*':
					result = operator1*operator2;
					break;
			
				case '/':
					result = operator1/operator2;
					break;
			
				case '^':
					result = pow(operator1,operator2);	
					break;							
			}
			
			stack[++top]=result;
					}
		
		
		
		
		i++;
	}
	
	return stack[top];
}




int main(){
	
	char infix[100];
	char postfix[100];
	
	cout<<endl<<"Enter your infix: ";
	cin.getline(infix, 100);
	

	
	infixToPostfix(infix, postfix);
		cout<<endl<<"Postfix......  "<<postfix;
	
	cout<<endl<<"your answer is: "<<evaluatePostfix(postfix);
	
	
	
	
	
	
	return 0;
}