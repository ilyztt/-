enum back{success,fail};  //���巵������ 
template<class nodeinput>
struct Node 
{
   nodeinput input;         //���������� 
   Node<nodeinput> *point;   //������ָ��
   Node(nodeinput elem, Node<nodeinput> *eleminput); //���캯��
};

template<class stackinput>
class Stack 
{
public:
   Stack(); //���캯�� 
   bool isempty() const;   //�ж϶�ջ�Ƿ�Ϊ��
   back push(const stackinput &elem);  //����Ԫ��
   back  pop();                           //ɾ��ջ��Ԫ��
   back  gettop(stackinput &elem) const;    //�õ�ջ��Ԫ��
   void clear();                              //�������Ԫ��
private:
   Node<stackinput> *topnode;               //����ջ��ָ��
};
template<class nodeinput>
Node<nodeinput>::Node(nodeinput elem, Node<nodeinput> *eleminput) //���캯��
{
   input = elem;
   point = eleminput;
}
template<class stackinput>
Stack<stackinput>::Stack() //���캯��
{
   topnode=NULL;
}
template<class stackinput>
bool Stack<stackinput>::isempty() const  //�ж϶�ջ�Ƿ�Ϊ��
{
  if(topnode==NULL)
     return true;
  else
     return false;
}
template<class stackinput>
back  Stack<stackinput>::push(const stackinput &elem)  //����ջ���Ԫ��
{
   Node<stackinput> *newtop = new Node<stackinput>(elem, topnode);
   if (newtop == NULL) 
   return fail;
   topnode = newtop;
   return success;
}
template<class stackinput>
back  Stack<stackinput>::pop()  //ɾ��ջ��Ԫ��
{
   Node<stackinput> *oldtop = topnode;
   if (topnode == NULL) 
   return fail;
   topnode = oldtop->point;
   delete oldtop;
   return success;
}
template<class stackinput>
back  Stack<stackinput>::gettop(stackinput &elem) const  //�õ�ջ��Ԫ��
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
void Stack<stackinput>::clear()   //��ն�ջ
{
   while (!isempty())
      pop();
}
