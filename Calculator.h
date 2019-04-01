#include<iostream>
#include<ctype.h>
using namespace std;
template<class datatype>
class cal
{
 private :
    Stack<datatype> opnd ;     //建立操作数栈
	Stack<char>  optr ;         //建立操作符栈
	bool gettwoope(double &left ,double &right) ; 	//取出操作数栈两个数字
	bool doope(char op) ;  	//操作函数 
	bool isope(char ch) ;	//判断传入字符是否为操作符 
	void getChar(char &ch) ; 	//从输入流中读入字符
    int isp(char op); //栈外优先数
    int icp(char op); //栈内优先数
	public :
		void Run() ;  //运行函数 	
};
template<class datatype>
void cal<datatype>::Run()
{
   	optr.clear() ;    // 清空操作符栈
	opnd.clear() ;    //清空 操作数栈
	optr.push('=') ;  // 操作符栈传入一个'='，当读入字符是'='且栈顶符号是'='时，运算结束
	char ch ;         // 临时字符
	char prichar ;  // 上一个字符
	char optrtop ;    // 操作符栈顶元素
	datatype operand ;  // 需要被操作数 
    char op = '0';          //定义操作数为'0'，用于小数运算
    getChar(ch);            //得到一个字符
	optr.gettop(optrtop);      //操作符栈栈顶元素
	if(optr.gettop(optrtop)==fail )//如果操作符栈为空，提示错误
	{
		cout<<"表达式有错!"<<endl;
		return;
	} 
	while(optrtop!='='||ch!='=')	//当前字符和栈顶的字符其中一个不为"="，运算未结束，进一步操作 
	{
		if((ch>='0'&&ch<='9')||ch=='.')	//字符是数字或者小数点，放回，操作数读入，放到操作数栈中，前一个字符赋0
		{
			cin.putback(ch); 
			cin>>operand;
			opnd.push(operand);
			prichar='0';
			getChar(ch);
		}
		else if(!isope(ch))	//除了数字只有操作符，判断，不是数字，小数点或操作符，输入有误，输出错误，继续读入， 
		{
			cout<<"表达式有错!"<<endl;		
			while(cin>>ch,ch!='=');
		}
		else
		{
			if((prichar=='='||prichar=='(')&&(ch=='+'||ch=='-'))
			opnd.push (0);
			if(isp(optrtop)<icp(ch))//操作符栈顶元素的优先级别小于操作符号，放回操作符栈，当前字符赋给前一个字符，读入下一个 
			{
				optr.push(ch);
			    prichar=ch;
				getChar(ch);    
			}
			else if(isp(optrtop)>icp(ch))//操作符栈顶元素的优先级别大于当前操作符号，删除操作符栈顶元素，判断OP是否操作符号，不是则返回
			{
				optr.gettop(op);
				optr.pop();
				if(!doope(op))
				return ;
			}
			else if(isp(optrtop)==icp(ch)&&ch==')')//栈内操作符和栈外操作符的优先级别一样的操作 
			{
				optr.pop();
			    prichar=')';
			    getChar(ch);
			};
		}
		if(optr.gettop(optrtop)==fail)  //操作符栈为空，输出错误
		{
			cout<<"表达式有错!"<<endl;
		}; 
	}
	if(opnd.gettop(operand)==fail || optr.pop() == fail)//操作数栈为空或操作符号删除，栈顶元素空，输出错误
	{
		cout<<"表达式有错!"<<endl;	
	} 
	else //删除操作数栈栈顶元素，再成功删除则输出错误
	{
		opnd.pop();
		if (opnd.pop()==success || optr.pop()==success)
		{
			cout<<"表达式有错!"<<endl;
		}
		cout<<operand<<endl;
	}
};
template<class datatype>
int cal<datatype>::isp(char op)//栈外优先级判断
{
	int back;
	switch(op)
	{
		case '=':
			back=0;
			break;
		case '(':
			back=1;
			break;
		case '+':
		case '-':
			back=3;
			break;
		case '*':
		case '/':
		case '%':
			back=5;
			break;
		case '^':
			back=7;
			break;
		case ')':
			back=8;
	}
	return back;
};
template<class datatype>//栈内优先级判断
int cal<datatype>::icp(char op)
{
	int back;
	switch(op)
	{
		case '=':
			back=0;
			break;
		case ')':
			back=1;
			break;
		case '+':
		case '-':
			back=2;
			break; 
		case '*':
		case '/':
		case '%':
			back=4;
			break;
		case '^':
			back=6;
			break;
		case '(':
			back=8;
			break;
	}
	return back;
};
template<class datatype>
bool cal<datatype>::gettwoope(double &x,double &y)//从操作数栈中得到两个数字，如果操作数栈或者操作符栈的元素少于两个，输出错误
{
	if(opnd.isempty())
	{
		cout<<"表达式有错!"<<endl;
		return false;
	}
	opnd.gettop(y);
	opnd.pop();
	if(opnd.isempty())
	{
		cout<<"表达式有错!"<<endl;
		return false;
	}
	opnd.gettop(x);
	opnd.pop();
	return true;
};
template<class datatype>
bool cal<datatype>::doope(char op)//判断符号，进行相应操作 
{
	datatype x,y;
	bool back=gettwoope(x,y); 
    if(back==true)
	{
		switch(op)
		{
			case '+':
				opnd.push(x+y);
				break;
			case '-':
				opnd.push(x-y);
				break;
			case '*':
			    opnd.push(x*y);
				break;
			case '/':
				if(y==0)
				{
					cout<<"表达式有错!"<<endl;
					return false;
				}
				opnd.push(x/y);
				break;
			case '%':
				if((long)y==0)
				{
					cout<<"表达式有错!"<<endl;
					return false;
				}
				opnd.push((long)x % (long)y);
				break;
			case '^':
				opnd.push(pow(x,y));
		}
		return true;
	}
	else return false;
};
template<class elemtype>
void cal<elemtype>::getChar(char &ch)//从输入流中读入字符
{
	cin>>ch;
	while(ch==' '||ch=='\n')  //非运算符继续读取 
		cin>>ch;
};
template<class datatype>
bool cal<datatype>::isope(char ch)//判断输入字符是否操作符
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^'||ch=='='||ch=='('||ch==')')
		return true;
	else 
		return false;
};
