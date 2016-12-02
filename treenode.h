#ifndef TREENODE_H
#define TREENODE_H

#include "tree.h"

enum NodeDirection{
   ND_Left = 0,
   ND_Right = 1
   };

template <typename T>
class TreeNode
{
   template <typename E>
   friend class Tree;

   TreeNode<T>* next[2];
public:
      T data;

   TreeNode();

   void setData(const T &value);
   T getData() const;
   void insert(T nData);
   T *find(T value);
   void del(TreeNode<T> *value);
   QString show();
   bool isEmpty();

   inline NodeDirection getDirection(T value);

   TreeNode<T>* getNextNode(NodeDirection dir);
   bool nodeExists(const NodeDirection dir);
   template <class X> friend QDataStream &operator <<(QDataStream &stream, const TreeNode<X> &data);
};


//========================================================


template <typename T>
TreeNode<T>::TreeNode()
   {
   data = T();
   next[ND_Left] = nullptr;
   next[ND_Right] = nullptr;
   }

template <typename T>
void TreeNode<T>::setData(const T &value)
   {
   data = value;
   }

template <typename T>
T TreeNode<T>::getData() const
   {
   return data;
   }

template <typename T>
void TreeNode<T>::insert(T nData)
   {
   NodeDirection currDirection;

   if (data == T())      //если данные текущего элемента пустые или идентичные
      data = nData;                             // то просто запишем в него то что пришло
   else {                                       //текущий элемент не пустой, нужно добавлять ниже
      //По какую сторону отправить новый элемент?
      currDirection = (nData > this->data)
                      ? ND_Right
                      : ND_Left;

      if (next[currDirection] == nullptr)       //Если узел ниже не создан
         next[currDirection] = new TreeNode<T>; //создаём узел в нужном направлении
      next[currDirection]->insert(nData);       //отправляем данные на добавление узлу ниже
      }
   }

template <typename T>
T* TreeNode<T>::find(T value)
   {
   if (data == T()) return nullptr;
   if (this->data == value)
      return this;
   else
      return find(getDirection(value));
   }

template <typename T>
void TreeNode<T>::del(TreeNode<T> *value)
   {
   if (value->next[ND_Right] != nullptr){
      del(next[ND_Right]);
      delete next[ND_Right];
      value->next[ND_Right] = nullptr;
      }
   if (value->next[ND_Left] != nullptr){
      del(next[ND_Left]);
      delete next[ND_Left];
      value->next[ND_Left] = nullptr;
      }
   }

template <typename T>
QString TreeNode<T>::show()
   {
   QString rw;
   if (next[ND_Left] != nullptr) rw.append(next[ND_Left]->show());
   rw.append(this->data.toString());
   if (next[ND_Right] != nullptr) rw.append(next[ND_Right]->show());
   return rw;
   }

template <typename T>
bool TreeNode<T>::isEmpty()
   {
   return data.isEmpty();
   }

template <typename T>
TreeNode<T> *TreeNode<T>::getNextNode(NodeDirection dir)
   {
   return this->next[(int)dir];
   }

template <typename T>
bool TreeNode<T>::nodeExists(NodeDirection dir)
   {
   return this->next[dir] != nullptr;
   }

template <typename T>
QDataStream &operator <<(QDataStream &stream, TreeNode<T> &data)
   {
   for(int i =0; i<2; ++i)
      if(data.nodeExists((NodeDirection)i))
         stream << *(data.getNextNode((NodeDirection)i));
   stream << data.data;
   return stream;
   }


#endif // TREENODE_H

