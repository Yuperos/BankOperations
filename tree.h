#ifndef TREE_H
#define TREE_H

#include <QDataStream>

#include "treenode.h"

template <typename T>
class Tree
{
   TreeNode<T>* root;

public:
   Tree();

   void append(T nData);
   void clear();
   QString showTree(bool fullAccNumber);
   T* find(T nData);
   T operator[](int i);

   template <class X> friend QDataStream &operator<< (QDataStream &stream, const Tree<X> &data);
   template <class X> friend QDataStream &operator>> (QDataStream &stream, Tree<X> &data);
};

//========================================================

template <typename T>
Tree<T>::Tree()
   {
   root = new TreeNode<T>;
   }

template <typename T>
void Tree<T>::append(T nData)
   {
   root->insert(nData);
   }

template <typename T>
void Tree<T>::clear()
   {
   if(root) root->del();
   }

template <typename T>
QString Tree<T>::showTree(bool fullAccNumber)
   {
   return (root != nullptr) ? root->show(fullAccNumber) : QString();
   }

template <typename T>
T *Tree<T>::find(T nData)
   {
   return root->find(nData);
   }

template <typename T>
T Tree::operator[](int i)
   {
   T a(false);
   a.setId(i);
   return find(a);
   }



template <typename T>
QDataStream &operator>> (QDataStream &stream, Tree<T> &data)
   {
   while(!stream.atEnd()){
      T instance;
      stream >> instance;
      data.append(instance);
      }
   return stream;
   }

template <typename T>
QDataStream &operator<< (QDataStream &stream, const Tree<T> &data)
   {
   if(!data.root->isEmpty())
      stream << *(data.root);
   return stream;
   }



#endif // TREE_H
