#include<stdio.h>
#include<stdlib.h>   // exit 함수를 사용하기 위해 include 
#include<ctype.h>    // isdigit 함수를 사용하기 위해 include 
#include<string.h>

#define SIZE 100    // 배열의 크기를 100으로 고정하기 위한 정의 

char stack[SIZE];
int top = -1;

void push(char item ) // 스택의 푸쉬 함수 
{
	if(top >= SIZE-1) //예외처리: 스택이 가득 차게 된  상태의 push 방지 
	{
		printf("\n오버 플로우입니다.");
	}
	else
	{
		top = top+1;
		stack[top] = item;
	}
}

char pop()  //스택의 팝 함수 
{
	char item ;

	if(top <0) //예외처리: 스택이 적재되지 않은 상태의 pop 방지 
	{
		printf("언더 플로우입니다. ");
		getchar();

		exit(1);
	}
	else
	{
		item = stack[top];
		top = top-1;
		return(item);
	}
}

int is_operator(char symbol) // 연산자를 구분해 주는 함수 
{
	if(symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-' || symbol =='%')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}

char calculate(int a, int b, char symbol ) // 두개의 값을 할당받아  
{											//정수형으로 계산 후 다시 문자형으로 
	switch(symbol){							//반환해준다. 
		case '+': return ((b-48) + (a-48))+'0';
		case '-': return ((b-48) - (a-48))+'0';
		case '*': return ((b-48) * (a-48))+'0';
		case '/': return ((b-48) / (a-48))+'0';
		case '%': return ((b-48) % (a-48))+'0';
	}
}

int precedence(char symbol) // 연산자의 우선순위를 정해주는 함수 
{
	if(symbol == '*' || symbol == '/' || symbol == '%')// *, /, %라면 2를 
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')     // +, -라면 1을 반환    
	{
		return(1);  
	}
	else // 예외처리: 만약 연산자가 아닌 값이 들어왔을 경우를 방지한 0 반환 
	{
		return(0);
	}
}

void InfixToPostfix(char infix_exp[], char postfix_exp[]) // 후위 표기법 변환 함수 
{ 
	int i, j;
	char item;
	char x;

	i=0;
	j=0;
	item=infix_exp[i];        
		printf(" 토큰\t스택\tpostfix\t\n");
		printf("--------------------------------\n\n");
	while(item != '\0')  // 토큰이 null일 때까지 반봅   
	{
		printf(" %c\t%s\t%s\n",infix_exp[i], stack,postfix_exp );
		if(item == '(') // 여는 괄호라면 
		{
			push(item);
		}
		else if( isdigit(item)) //숫자라면 
		{	

			postfix_exp[j] = item;            
			j++;
		}
		else if(is_operator(item) == 1)    //연산자라면  
		{
			if (top == -1){
			
			push(item);
			i++;
			item = infix_exp[i];
			printf(" \t%s\t%s\n", stack,postfix_exp );
			continue;
			}
			x=pop();
			if(is_operator(x) == 1 && precedence(x)>= precedence(item)) // 연산자의 우선순위에 따른 
			{															// 적재 알고리즘 

				postfix_exp[j] = x;                
				j++;                      
			}else{
				push(x);
			}
			push(item);     
			        
		}
		else if(item == ')')      //닫는 괄호라면 
		{
			x = pop();                   
			while(x != '(')                
			{
				printf(" \t%s\t%s\n", stack,postfix_exp );
				postfix_exp[j] = x;
				j++;
				x = pop();
			}
		}
		else // 예외처리: 이상한 값이 들어와 시스템이 다운되는 것을 방지 
		{ 
			printf("이상한 값을 넣었습니다. \n");     
			getchar();
			exit(1);
		}
		
		i++;
		item = infix_exp[i]; 
		
	}
	if(item == '\0') //item이 null이라면  
		{
			              
			while(top != -1)     //스택에 적재된 모든 연산자를 차례재로 pop           
			{

				x = pop();
				postfix_exp[j] = x;
				j++;
	
			}
		}
	printf(" \t%s\t%s\n", stack,postfix_exp );
	if(top>0) // 예외처리: 스택에 값이 남아있어 시스템에 문제가 생기는 것을 막아줌. 
	{
		printf("스택 안에 아직 값이 남아있습니다.\n");     
		getchar();
		exit(1);
	}
	postfix_exp[j] = '\0'; 
}

char Calculator(char postfix_exp[]) // 후위 연산식을 계산하는 함수
{
 	int i;
	char item;
	i = 0;
	
	item = postfix_exp[i];
	printf(" postfix\t스택\t출력\t\n");
	printf("--------------------------------\n\n");
	while(postfix_exp[i] != '\0') // 하나씩 후위 연산식의 토큰을 가져옴 
	{	
		printf(" %s\t\t%c\t%c\n",postfix_exp, stack[top], item);
		if(is_operator(postfix_exp[i]) == 1){ // 연산자라면 두 값을 pop하여 연산 후 다시 push 
			
			int a = pop();
			int b = pop();
			item = calculate(a,b,postfix_exp[i]);
			push(item);
			}
		else if(isdigit(item)) //피연산자라면 스택에 바로 푸쉬 
		{ 
			push(postfix_exp[i]);  
		}
		else // 예외처리: 이상한 값이 postfix에 있을 경우를 방지 
		{ 
			printf("이상한 값을 넣었습니다. \n");     
			getchar();
			exit(1);
		}
    i++;	
	item = postfix_exp[i]; 	
	}
	return pop(); // while문이 끝났다면 스택의 마지막으로 적재된 값을 pop 
}
int main() 
{
	char infix[SIZE], postfix[SIZE]; //중위 표기식과 후위 표기식의 배열 정의    
	char  x ;
	printf("중위 표기법을 후기 표기법으로 바꾸겠습니다.\n");
	printf("\n식을 넣어주세요 : ");
	gets(infix); 
	InfixToPostfix(infix,postfix);                
	printf("후위 표기법은 : ");
	puts(postfix); 
	printf("입니다.\n\n");    
	printf("후위 표기법으로 작성된 %s 는\n" , postfix);
	x = Calculator(postfix) - '0';
	printf("\n%d입니다.", x);
	return 0;
}
