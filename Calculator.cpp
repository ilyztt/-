#include<string.h>      
#include<math.h>     
#include"LinkStack.h"
#include"Calculator.h"
int main(void)
{
	cal<double> s;
	char ifcontinue='Y';
	while(ifcontinue=='Y'||ifcontinue=='y')
	{
		cout<<"������ʽ,��'='����:"<<endl;
		s.Run();
		cout<<"�Ƿ����?������Y��y�����������˳���"<<endl;
		cin>>ifcontinue;
	}
	return 0;
}
