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
		double weight;//权值
		unsigned int parent,lc,rc;//父节点、左孩子、右孩子位置 
		HuffmanNode()
		{
			weight=0;
			parent=0,lc=0,rc=0;//节点数组的第0位不会使用，所以这里的0相当于“NULL”的功能 
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
		HuffmanNode *nodeArray;//节点数组，第0位不用 
		unsigned int nodeSum;//节点数 
		unsigned int leafSum;//叶节点数 
		char *leafChars;//叶节点字符数组，第0位不用  
		string *leafCodes;//叶节点编码数组，第0位不用  
	public:
		Huffman(char chars[],double weights[],unsigned int num);//由字符数组和权值数组以及字符个数构造哈夫曼树，完成编码
		string getCode(char c);//返回指定字符的编码
		string deCode(string codes);//译码 
		void findMin(unsigned int x,unsigned int &a,unsigned int &b);//从nodeArray[1]到nodeArray[x]寻找无父节点且权值最小的两个节点位置 
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
	//存好字符与权值 
	for(i=0;i<leafSum;i++)
	{
		leafChars[i+1]=chars[i];
		nodeArray[i+1].weight=weights[i];
	} 
	nodeArray[0].weight=numeric_limits<double>::max();//方便findMin()的使用 
	//构造分支节点
	for(i=leafSum+1;i<=nodeSum;i++)
	{
		unsigned int a,b;
		findMin(i-1,a,b);
		nodeArray[i].weight=nodeArray[a].weight+nodeArray[b].weight;//nodeArray[i]作为根节点 
		nodeArray[i].lc=a;
		nodeArray[i].rc=b;
		nodeArray[a].parent=i;
		nodeArray[b].parent=i;
	}
	//求编码 
	for(i=1;i<=leafSum;i++)
	{
		string code="";
		unsigned int j=i;
		while(nodeArray[j].parent!=0)
		{
			if(nodeArray[nodeArray[j].parent].lc==j)
			{
				code+='0';//是左子树，末尾添0 
			}
			else
			{
				code+='1';//是右子树，末尾添1 
			}
			j=nodeArray[j].parent;
		}
		reverse(code.begin(),code.end());//反转过来 
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
		cout<<"非法字符！\n"; 
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
		if( nodeArray[root].lc==0&&nodeArray[root].rc==0 )//已经到达叶节点 
		{
			result+=leafChars[root];
			root=nodeSum;//回到根节点 
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
	
	cout<<"输入字符个数：\n";
	cin>>count;
	char *x=new char[count];
	double *y=new double[count];
	cout<<"输入所有字符：\n";
	for(i=0;i<count;i++)
	{
		cin>>x[i];\
	}
	cout<<"输入所有字符权值：\n";
	for(i=0;i<count;i++)
	{
		cin>>y[i];
	}
	Huffman h=Huffman(x,y,count);
	cout<<"结果如下：\n"<<"字符："<<"\t权值："<<"\t编码："<<'\n';;
	for(i=1;i<=count;i++)
	{
		cout<<h.getChar(i)<<'\t'<<h.getWeight(i)<<'\t'<<h.getCodeIndex(i)<<'\n';
	}
	cout<<"输入编码串：\n";
	cin>>s;
	cout<<"译码后为：\n"<<h.deCode(s);
	return 0;
}



