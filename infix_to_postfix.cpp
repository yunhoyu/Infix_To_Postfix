#include<stdio.h>
#include<stdlib.h>   // exit �Լ��� ����ϱ� ���� include 
#include<ctype.h>    // isdigit �Լ��� ����ϱ� ���� include 
#include<string.h>

#define SIZE 100    // �迭�� ũ�⸦ 100���� �����ϱ� ���� ���� 

char stack[SIZE];
int top = -1;

void push(char item ) // ������ Ǫ�� �Լ� 
{
	if(top >= SIZE-1) //����ó��: ������ ���� ���� ��  ������ push ���� 
	{
		printf("\n���� �÷ο��Դϴ�.");
	}
	else
	{
		top = top+1;
		stack[top] = item;
	}
}

char pop()  //������ �� �Լ� 
{
	char item ;

	if(top <0) //����ó��: ������ ������� ���� ������ pop ���� 
	{
		printf("��� �÷ο��Դϴ�. ");
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

int is_operator(char symbol) // �����ڸ� ������ �ִ� �Լ� 
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

char calculate(int a, int b, char symbol ) // �ΰ��� ���� �Ҵ�޾�  
{											//���������� ��� �� �ٽ� ���������� 
	switch(symbol){							//��ȯ���ش�. 
		case '+': return ((b-48) + (a-48))+'0';
		case '-': return ((b-48) - (a-48))+'0';
		case '*': return ((b-48) * (a-48))+'0';
		case '/': return ((b-48) / (a-48))+'0';
		case '%': return ((b-48) % (a-48))+'0';
	}
}

int precedence(char symbol) // �������� �켱������ �����ִ� �Լ� 
{
	if(symbol == '*' || symbol == '/' || symbol == '%')// *, /, %��� 2�� 
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')     // +, -��� 1�� ��ȯ    
	{
		return(1);  
	}
	else // ����ó��: ���� �����ڰ� �ƴ� ���� ������ ��츦 ������ 0 ��ȯ 
	{
		return(0);
	}
}

void InfixToPostfix(char infix_exp[], char postfix_exp[]) // ���� ǥ��� ��ȯ �Լ� 
{ 
	int i, j;
	char item;
	char x;

	i=0;
	j=0;
	item=infix_exp[i];        
		printf(" ��ū\t����\tpostfix\t\n");
		printf("--------------------------------\n\n");
	while(item != '\0')  // ��ū�� null�� ������ �ݺ�   
	{
		printf(" %c\t%s\t%s\n",infix_exp[i], stack,postfix_exp );
		if(item == '(') // ���� ��ȣ��� 
		{
			push(item);
		}
		else if( isdigit(item)) //���ڶ�� 
		{	

			postfix_exp[j] = item;            
			j++;
		}
		else if(is_operator(item) == 1)    //�����ڶ��  
		{
			if (top == -1){
			
			push(item);
			i++;
			item = infix_exp[i];
			printf(" \t%s\t%s\n", stack,postfix_exp );
			continue;
			}
			x=pop();
			if(is_operator(x) == 1 && precedence(x)>= precedence(item)) // �������� �켱������ ���� 
			{															// ���� �˰��� 

				postfix_exp[j] = x;                
				j++;                      
			}else{
				push(x);
			}
			push(item);     
			        
		}
		else if(item == ')')      //�ݴ� ��ȣ��� 
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
		else // ����ó��: �̻��� ���� ���� �ý����� �ٿ�Ǵ� ���� ���� 
		{ 
			printf("�̻��� ���� �־����ϴ�. \n");     
			getchar();
			exit(1);
		}
		
		i++;
		item = infix_exp[i]; 
		
	}
	if(item == '\0') //item�� null�̶��  
		{
			              
			while(top != -1)     //���ÿ� ����� ��� �����ڸ� ������� pop           
			{

				x = pop();
				postfix_exp[j] = x;
				j++;
	
			}
		}
	printf(" \t%s\t%s\n", stack,postfix_exp );
	if(top>0) // ����ó��: ���ÿ� ���� �����־� �ý��ۿ� ������ ����� ���� ������. 
	{
		printf("���� �ȿ� ���� ���� �����ֽ��ϴ�.\n");     
		getchar();
		exit(1);
	}
	postfix_exp[j] = '\0'; 
}

char Calculator(char postfix_exp[]) // ���� ������� ����ϴ� �Լ�
{
 	int i;
	char item;
	i = 0;
	
	item = postfix_exp[i];
	printf(" postfix\t����\t���\t\n");
	printf("--------------------------------\n\n");
	while(postfix_exp[i] != '\0') // �ϳ��� ���� ������� ��ū�� ������ 
	{	
		printf(" %s\t\t%c\t%c\n",postfix_exp, stack[top], item);
		if(is_operator(postfix_exp[i]) == 1){ // �����ڶ�� �� ���� pop�Ͽ� ���� �� �ٽ� push 
			
			int a = pop();
			int b = pop();
			item = calculate(a,b,postfix_exp[i]);
			push(item);
			}
		else if(isdigit(item)) //�ǿ����ڶ�� ���ÿ� �ٷ� Ǫ�� 
		{ 
			push(postfix_exp[i]);  
		}
		else // ����ó��: �̻��� ���� postfix�� ���� ��츦 ���� 
		{ 
			printf("�̻��� ���� �־����ϴ�. \n");     
			getchar();
			exit(1);
		}
    i++;	
	item = postfix_exp[i]; 	
	}
	return pop(); // while���� �����ٸ� ������ ���������� ����� ���� pop 
}
int main() 
{
	char infix[SIZE], postfix[SIZE]; //���� ǥ��İ� ���� ǥ����� �迭 ����    
	char  x ;
	printf("���� ǥ����� �ı� ǥ������� �ٲٰڽ��ϴ�.\n");
	printf("\n���� �־��ּ��� : ");
	gets(infix); 
	InfixToPostfix(infix,postfix);                
	printf("���� ǥ����� : ");
	puts(postfix); 
	printf("�Դϴ�.\n\n");    
	printf("���� ǥ������� �ۼ��� %s ��\n" , postfix);
	x = Calculator(postfix) - '0';
	printf("\n%d�Դϴ�.", x);
	return 0;
}
