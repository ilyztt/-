#include<iostream>
#include<ctype.h>
using namespace std;
template<class datatype>
class cal
{
 private :
    Stack<datatype> opnd ;     //����������ջ
	Stack<char>  optr ;         //����������ջ
	bool gettwoope(double &left ,double &right) ; 	//ȡ��������ջ��������
	bool doope(char op) ;  	//�������� 
	bool isope(char ch) ;	//�жϴ����ַ��Ƿ�Ϊ������ 
	void getChar(char &ch) ; 	//���������ж����ַ�
    int isp(char op); //ջ��������
    int icp(char op); //ջ��������
	public :
		void Run() ;  //���к��� 	
};
template<class datatype>
void cal<datatype>::Run()
{
   	optr.clear() ;    // ��ղ�����ջ
	opnd.clear() ;    //��� ������ջ
	optr.push('=') ;  // ������ջ����һ��'='���������ַ���'='��ջ��������'='ʱ���������
	char ch ;         // ��ʱ�ַ�
	char prichar ;  // ��һ���ַ�
	char optrtop ;    // ������ջ��Ԫ��
	datatype operand ;  // ��Ҫ�������� 
    char op = '0';          //���������Ϊ'0'������С������
    getChar(ch);            //�õ�һ���ַ�
	optr.gettop(optrtop);      //������ջջ��Ԫ��
	if(optr.gettop(optrtop)==fail )//���������ջΪ�գ���ʾ����
	{
		cout<<"���ʽ�д�!"<<endl;
		return;
	} 
	while(optrtop!='='||ch!='=')	//��ǰ�ַ���ջ�����ַ�����һ����Ϊ"="������δ��������һ������ 
	{
		if((ch>='0'&&ch<='9')||ch=='.')	//�ַ������ֻ���С���㣬�Żأ����������룬�ŵ�������ջ�У�ǰһ���ַ���0
		{
			cin.putback(ch); 
			cin>>operand;
			opnd.push(operand);
			prichar='0';
			getChar(ch);
		}
		else if(!isope(ch))	//��������ֻ�в��������жϣ��������֣�С��������������������������󣬼������룬 
		{
			cout<<"���ʽ�д�!"<<endl;		
			while(cin>>ch,ch!='=');
		}
		else
		{
			if((prichar=='='||prichar=='(')&&(ch=='+'||ch=='-'))
			opnd.push (0);
			if(isp(optrtop)<icp(ch))//������ջ��Ԫ�ص����ȼ���С�ڲ������ţ��Żز�����ջ����ǰ�ַ�����ǰһ���ַ���������һ�� 
			{
				optr.push(ch);
			    prichar=ch;
				getChar(ch);    
			}
			else if(isp(optrtop)>icp(ch))//������ջ��Ԫ�ص����ȼ�����ڵ�ǰ�������ţ�ɾ��������ջ��Ԫ�أ��ж�OP�Ƿ�������ţ������򷵻�
			{
				optr.gettop(op);
				optr.pop();
				if(!doope(op))
				return ;
			}
			else if(isp(optrtop)==icp(ch)&&ch==')')//ջ�ڲ�������ջ������������ȼ���һ���Ĳ��� 
			{
				optr.pop();
			    prichar=')';
			    getChar(ch);
			};
		}
		if(optr.gettop(optrtop)==fail)  //������ջΪ�գ��������
		{
			cout<<"���ʽ�д�!"<<endl;
		}; 
	}
	if(opnd.gettop(operand)==fail || optr.pop() == fail)//������ջΪ�ջ��������ɾ����ջ��Ԫ�ؿգ��������
	{
		cout<<"���ʽ�д�!"<<endl;	
	} 
	else //ɾ��������ջջ��Ԫ�أ��ٳɹ�ɾ�����������
	{
		opnd.pop();
		if (opnd.pop()==success || optr.pop()==success)
		{
			cout<<"���ʽ�д�!"<<endl;
		}
		cout<<operand<<endl;
	}
};
template<class datatype>
int cal<datatype>::isp(char op)//ջ�����ȼ��ж�
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
template<class datatype>//ջ�����ȼ��ж�
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
bool cal<datatype>::gettwoope(double &x,double &y)//�Ӳ�����ջ�еõ��������֣����������ջ���߲�����ջ��Ԫ�������������������
{
	if(opnd.isempty())
	{
		cout<<"���ʽ�д�!"<<endl;
		return false;
	}
	opnd.gettop(y);
	opnd.pop();
	if(opnd.isempty())
	{
		cout<<"���ʽ�д�!"<<endl;
		return false;
	}
	opnd.gettop(x);
	opnd.pop();
	return true;
};
template<class datatype>
bool cal<datatype>::doope(char op)//�жϷ��ţ�������Ӧ���� 
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
					cout<<"���ʽ�д�!"<<endl;
					return false;
				}
				opnd.push(x/y);
				break;
			case '%':
				if((long)y==0)
				{
					cout<<"���ʽ�д�!"<<endl;
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
void cal<elemtype>::getChar(char &ch)//���������ж����ַ�
{
	cin>>ch;
	while(ch==' '||ch=='\n')  //�������������ȡ 
		cin>>ch;
};
template<class datatype>
bool cal<datatype>::isope(char ch)//�ж������ַ��Ƿ������
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^'||ch=='='||ch=='('||ch==')')
		return true;
	else 
		return false;
};
