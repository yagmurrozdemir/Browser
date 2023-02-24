#include <iostream>

#include "Node.h"



template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    Node<T>* iter;
    head = NULL;
    size = 0;
    
    iter = obj.getFirstNode();
    if(!iter) return;
    
    this -> append(iter -> data);
    iter = iter -> next;
    while(iter != obj.getFirstNode())
    {
        this -> append(iter -> data);
        iter = iter -> next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    this->removeAllNodes();
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if(this==&rhs) return *this;
    this->removeAllNodes();
    int i;
    Node<T>* iter;
    
    iter = rhs.getFirstNode();
    if(!iter) return *this;
    
    for(i=0 ; i<rhs.getSize() ; i++)
    {
        this -> append(iter->data);
        iter = iter->next;
    }
    
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if(size) return false;
    else return true;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    int i;
    bool b = 0;
    Node<T>* temp = head;
    
    for( i=0 ; i < size ; i++ )
    {
        if (temp == node)
        {
            b = 1;
            break;
        }
        temp = temp->next;
    }
    return b;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if(size == 0)
    {
        return NULL;
    }
    else
    {
        return head->prev;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    int i;
    Node<T> * temp = head;
    
    for(i=0;i<size;i++)
    {
        if(temp->data == data)
        {
            return temp;
        }
            temp = temp->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    
    if((index < 0) or (index >= size))
    {
        return NULL;
    }
    
    Node<T>* iter=head;
    
    while( index )
    {
        iter=iter->next;
        index--;
    }
    return iter;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    
    Node<T>* lastNode = this->getLastNode();
    Node<T>* node = new Node<T>(data,lastNode, head);
    
    if(!size)
    {
        head=node;
        head->next = head;
        head->prev = head;
    }
    else
    {
        lastNode->next = node;
        head->prev = node;
    }
    size++;

}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    this->append(data);
    head = head->prev;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if(!(this->containsNode(node))) return;
    Node<T>* firstHead = head;
    head = node -> next;
    this->append(data);
    head = firstHead;
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    Node<T>* firstHead = head;
    
    if(index>size) return;
    if(index==0){
        this->prepend(data);
        return;
    }
    
    while(index)
    {
        head = head->next;
        index--;
    }
    this->append(data);
    if(size>1)head = firstHead;
    
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    int i;
    Node<T>* iter = head;
    i = 0;
    if(!(this->containsNode(node))) return -1;
    
    while(1){
        if(iter== node)
        {
            return i;
        }
    
        else
        {
            iter = iter->next;
            i++;
        }
    }
    
    
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    int i;
    Node<T> *from, *to;

    if((currentIndex == newIndex) or (currentIndex >= size)) return;
    if(newIndex >= size) newIndex = (size - 1);

    from = to = this->getFirstNode();
    
    for(i = 0; i < currentIndex; i++)
    {
        from = from->next;
    }
    
    for(i = 0; i < newIndex; i++)
    {
        to = to->next;
    }

    if(currentIndex == 0)
    {
        head = head->next;
    }
    
    from->prev->next = from->next;
    from->next->prev = from->prev;
    
    if(newIndex > currentIndex)
    {
        from->prev = to;
        from->next = to->next;
        to->next->prev = from;
        to->next = from;
    }
    else
    {
        from->prev = to->prev;
        from->next = to;
        to->prev->next = from;
        to->prev = from;
    }    
    if(newIndex == 0){
        this->head = from;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if(!(this->containsNode(node))) return;
    
    else
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
  

        if(node == head)
        {
            if(size==1){
                head=NULL;
            }
            else{
                head = node->next;
            }
        }
    
        delete node;
        size--;
    
    }   
    
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    
    while(this->getNode(data))
    {
        Node<T>* node = this->getNode(data);
        this->removeNode(node);
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if(index >= size) return;
    
    Node<T>* node = this->getNodeAtIndex(index);
    
    this->removeNode(node);
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    if(!head) return;
    
    while(size>1)
    {
        head = head->next;
        delete (head->prev);
        size = size-1;
    }
    if(size==1){
        delete head;
        head = NULL;
        size = 0;
    }
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());

}
