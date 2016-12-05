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
   T *find(T nData);
   int height();
   void balancing();
   void del();
   bool isLeaf();
   QString show(bool fullAccountNumber);
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

   if (nData.getId() > T::getGlobalNextID() )
      T::setGlobalNextID(nData.getId()+1);

   if (data == T() || data == nData)      //если данные текущего элемента пустые или идентичные
      data = nData;                             // то просто запишем в него то что пришло
   else {                                       //текущий элемент не пустой, нужно добавлять ниже
      //По какую сторону отправить новый элемент?
      currDirection = getDirection(nData);

      if (next[currDirection] == nullptr)       //Если узел ниже не создан
         next[currDirection] = new TreeNode<T>; //создаём узел в нужном направлении
      next[currDirection]->insert(nData);       //отправляем данные на добавление узлу ниже
      }
   }

template <typename T>
T* TreeNode<T>::find(T nData)
   {
   if (data == T()) return nullptr;
   if (this->data == nData)
      return &(this->data);
   else{
      NodeDirection nd = getDirection(nData);
      if (next[nd] != nullptr)
         return next[nd]->find(nData);
      else
         return nullptr;
      }
   }
template <typename T>
int TreeNode<T>::height()
   {
   int rw = (next[ND_Right] != nullptr) ? next[ND_Right]->height(): 0;
   rw += (next[ND_Left] != nullptr) ? next[ND_Left]->height(): 0;
   return rw;
   }

template <typename T>
void TreeNode<T>::del()
   {
   if (next[ND_Right] != nullptr){
      next[ND_Right]->del();
      delete next[ND_Right];
      next[ND_Right] = nullptr;
      }
   if (next[ND_Left] != nullptr){
      next[ND_Left]->del();
      delete next[ND_Left];
      next[ND_Left] = nullptr;
      }
   }
template <typename T>
bool TreeNode<T>::isLeaf()
   {
   return (next[ND_Left] != nullptr) && (next[ND_Right] != nullptr);
   }

template <typename T>
QString TreeNode<T>::show(bool fullAccountNumber)
   {
   QString rw;
   if (next[ND_Left] != nullptr) rw.append(next[ND_Left]->show(fullAccountNumber));
   rw.append(this->data.toString(fullAccountNumber));
   if (next[ND_Right] != nullptr) rw.append(next[ND_Right]->show(fullAccountNumber));
   return rw;
   }

template <typename T>
bool TreeNode<T>::isEmpty()
   {
   return data.isEmpty();
   }

template <typename T>
NodeDirection TreeNode<T>::getDirection(T value)
   {
   return (data < value)? ND_Right : ND_Left;
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

