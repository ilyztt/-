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
		cout<<"输入表达式,以'='结束:"<<endl;
		s.Run();
		cout<<"是否继续?（输入Y或y继续，其他退出）"<<endl;
		cin>>ifcontinue;
	}
	return 0;
}
