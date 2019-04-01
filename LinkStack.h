enum back{success,fail};  //定义返回类型 
template<class nodeinput>
struct Node 
{
   nodeinput input;         //定义结点数据 
   Node<nodeinput> *point;   //定义结点指针
   Node(nodeinput elem, Node<nodeinput> *eleminput); //构造函数
};

template<class stackinput>
class Stack 
{
public:
   Stack(); //构造函数 
   bool isempty() const;   //判断堆栈是否为空
   back push(const stackinput &elem);  //传入元素
   back  pop();                           //删除栈顶元素
   back  gettop(stackinput &elem) const;    //得到栈顶元素
   void clear();                              //清空所有元素
private:
   Node<stackinput> *topnode;               //定义栈顶指针
};
template<class nodeinput>
Node<nodeinput>::Node(nodeinput elem, Node<nodeinput> *eleminput) //构造函数
{
   input = elem;
   point = eleminput;
}
template<class stackinput>
Stack<stackinput>::Stack() //构造函数
{
   topnode=NULL;
}
template<class stackinput>
bool Stack<stackinput>::isempty() const  //判断堆栈是否为空
{
  if(topnode==NULL)
     return true;
  else
     return false;
}
template<class stackinput>
back  Stack<stackinput>::push(const stackinput &elem)  //往堆栈添加元素
{
   Node<stackinput> *newtop = new Node<stackinput>(elem, topnode);
   if (newtop == NULL) 
   return fail;
   topnode = newtop;
   return success;
}
template<class stackinput>
back  Stack<stackinput>::pop()  //删除栈顶元素
{
   Node<stackinput> *oldtop = topnode;
   if (topnode == NULL) 
   return fail;
   topnode = oldtop->point;
   delete oldtop;
   return success;
}
template<class stackinput>
back  Stack<stackinput>::gettop(stackinput &elem) const  //得到栈顶元素
{
   if(isempty())
     return fail;
   else
   {
     elem=topnode->input;
     return success;
   }
}
template<class stackinput>
void Stack<stackinput>::clear()   //清空堆栈
{
   while (!isempty())
      pop();
}
