#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() 
{
    int i;
    Tab a;
    
    if(tabs.isEmpty()) return a;
    
    Node<Tab>* tab = tabs.getFirstNode() ;
    
    for(i = 0 ; i< activeTab ; i++ )
    {
        tab = tab->next;
    }
    a = tab->data;
    return a;
}

bool Window::isEmpty() const 
{
    return tabs.isEmpty(); 
}

void Window::newTab(const Tab &tab) 
{
    if(tabs.isEmpty())
    {
        activeTab=0;
    }
    
    else activeTab++;
    
    this->tabs.insertAtIndex(tab,activeTab);
}

void Window::closeTab() 
{
    
    if(tabs.isEmpty()) return;
    
    tabs.removeNodeAtIndex(activeTab);
    
    if(tabs.getSize()==0)
    {
        activeTab=-1;
    }
    else if(activeTab==(tabs.getSize())) 
    {
        activeTab--;
    }
    
    
}

void Window::moveActiveTabTo(int index) 
{

    if(index >= tabs.getSize()) index = tabs.getSize() - 1;
    
    Node<Tab>* active = tabs.getNodeAtIndex(activeTab);
    
    tabs.moveToIndex(activeTab,index);
    
    activeTab = tabs.getIndex(active);
    
}

void Window::changeActiveTabTo(int index) 
{
    if(index >= tabs.getSize()) return;
    if(index<0) return;
    
    activeTab = index;
}

void Window::addTab(Node<Tab> &tab) 
{
    
    if(tabs.getSize() == 0) activeTab=0;
    
    tabs.append(tab.data);
    //yeni node oluşturdum!!!!!!!!!!!!!!!!!
    
}

void Window::print() 
{
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
