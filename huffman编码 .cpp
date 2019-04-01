#ifndef HUFFMAN
#define HUFFMAN
#include<iostream>
#include<string>
#include<algorithm>
#include<limits> 
#include<fstream>
using namespace std;
class HuffmanNode
{	
	public:
		double weight;//Ȩֵ
		unsigned int parent,lc,rc;//���ڵ㡢���ӡ��Һ���λ�� 
		HuffmanNode()
		{
			weight=0;
			parent=0,lc=0,rc=0;//�ڵ�����ĵ�0λ����ʹ�ã����������0�൱�ڡ�NULL���Ĺ��� 
		}
		HuffmanNode(double weight)
		{
			this->weight=weight;
			parent=0,lc=0,rc=0;
		}
}; 
class Huffman
{
	private:
		HuffmanNode *nodeArray;//�ڵ����飬��0λ���� 
		unsigned int nodeSum;//�ڵ��� 
		unsigned int leafSum;//Ҷ�ڵ��� 
		char *leafChars;//Ҷ�ڵ��ַ����飬��0λ����  
		string *leafCodes;//Ҷ�ڵ�������飬��0λ����  
	public:
		Huffman(char chars[],double weights[],unsigned int num);//���ַ������Ȩֵ�����Լ��ַ��������������������ɱ���
		string getCode(char c);//����ָ���ַ��ı���
		string deCode(string codes);//���� 
		void findMin(unsigned int x,unsigned int &a,unsigned int &b);//��nodeArray[1]��nodeArray[x]Ѱ���޸��ڵ���Ȩֵ��С�������ڵ�λ�� 
		unsigned int getNodeSum();
		unsigned int getLeafSum();
		char getChar(unsigned int index);
		string getCodeIndex(unsigned int index);
		double getWeight(unsigned int index);
};
#endif

Huffman::Huffman(char chars[],double weights[],unsigned int num) 
{
	leafSum=num;
	nodeSum=2*leafSum-1;
	nodeArray=new HuffmanNode[nodeSum+1];
	leafChars=new char[leafSum+1];
	leafCodes=new string[leafSum+1];
	unsigned int i;
	//����ַ���Ȩֵ 
	for(i=0;i<leafSum;i++)
	{
		leafChars[i+1]=chars[i];
		nodeArray[i+1].weight=weights[i];
	} 
	nodeArray[0].weight=numeric_limits<double>::max();//����findMin()��ʹ�� 
	//�����֧�ڵ�
	for(i=leafSum+1;i<=nodeSum;i++)
	{
		unsigned int a,b;
		findMin(i-1,a,b);
		nodeArray[i].weight=nodeArray[a].weight+nodeArray[b].weight;//nodeArray[i]��Ϊ���ڵ� 
		nodeArray[i].lc=a;
		nodeArray[i].rc=b;
		nodeArray[a].parent=i;
		nodeArray[b].parent=i;
	}
	//����� 
	for(i=1;i<=leafSum;i++)
	{
		string code="";
		unsigned int j=i;
		while(nodeArray[j].parent!=0)
		{
			if(nodeArray[nodeArray[j].parent].lc==j)
			{
				code+='0';//����������ĩβ��0 
			}
			else
			{
				code+='1';//����������ĩβ��1 
			}
			j=nodeArray[j].parent;
		}
		reverse(code.begin(),code.end());//��ת���� 
		leafCodes[i]=code; 
	}	 
}

void Huffman::findMin(unsigned int x,unsigned int &a,unsigned int &b)
{
	unsigned int i;
	a=0,b=0;
	for(i=1;i<=x;i++)
	{
		if( nodeArray[i].parent==0 )
		{
			if( nodeArray[i].weight<nodeArray[a].weight )
			{
				b=a;
				a=i;
			}
			else if( nodeArray[i].weight<nodeArray[b].weight )
			{
				b=i;
			}
		}
	}
}

string Huffman::getCode(char c)
{
	unsigned int i;
	bool exist=false;
	for(i=1;i<=leafSum;i++)
	{
		if( leafChars[i]==c )
		{
			exist=true;
			return leafCodes[i];
		}
	} 
	if(!exist)
	{
		cout<<"�Ƿ��ַ���\n"; 
		return "";
	}
} 

string Huffman::deCode(string codes)
{
	unsigned int i,root=nodeSum;
	string result="";
	for(i=0;i<codes.length();i++)
	{
		if( codes[i]=='0' )
		{
			root=nodeArray[root].lc;
		}
		else
		{
			root=nodeArray[root].rc;
		}
		if( nodeArray[root].lc==0&&nodeArray[root].rc==0 )//�Ѿ�����Ҷ�ڵ� 
		{
			result+=leafChars[root];
			root=nodeSum;//�ص����ڵ� 
		}
	}
	return result;
}

unsigned int Huffman::getNodeSum()
{
	return nodeSum;
}

unsigned int Huffman::getLeafSum()
{
	return leafSum;
}

char Huffman::getChar(unsigned int index)
{
	return leafChars[index];
}

string Huffman::getCodeIndex(unsigned int index)
{
	return leafCodes[index];
}

double Huffman::getWeight(unsigned int index)
{
	return (nodeArray[index]).weight; 
}
int main() 
{
	fstream encode,decode;
	unsigned int count,i;
	string s;
	encode.open("encode.txt",ios::in);
	decode.open("decode.txt",ios::in);
	
	cout<<"�����ַ�������\n";
	cin>>count;
	char *x=new char[count];
	double *y=new double[count];
	cout<<"���������ַ���\n";
	for(i=0;i<count;i++)
	{
		cin>>x[i];\
	}
	cout<<"���������ַ�Ȩֵ��\n";
	for(i=0;i<count;i++)
	{
		cin>>y[i];
	}
	Huffman h=Huffman(x,y,count);
	cout<<"������£�\n"<<"�ַ���"<<"\tȨֵ��"<<"\t���룺"<<'\n';;
	for(i=1;i<=count;i++)
	{
		cout<<h.getChar(i)<<'\t'<<h.getWeight(i)<<'\t'<<h.getCodeIndex(i)<<'\n';
	}
	cout<<"������봮��\n";
	cin>>s;
	cout<<"�����Ϊ��\n"<<h.deCode(s);
	return 0;
}



