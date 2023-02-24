#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    windows.prepend(Window());
}

void Browser::closeWindow() {
    if(windows.isEmpty()) return;
    windows.removeNodeAtIndex(0);
}

void Browser::switchToWindow(int index) {
    windows.moveToIndex(index,0);
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    Tab a = from.getActiveTab();
    from.closeTab();
    to.newTab(a);
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    Tab tab;
    
    if(window2.isEmpty()) return;
    
    window2.changeActiveTabTo(0);
    
    while(!(window2.isEmpty())){
        
        tab = window2.getActiveTab();
        
        window1.newTab(tab);
        window2.closeTab();
    }
}

void Browser::mergeAllWindows() {
    int i;
    for(i = 1; i < windows.getSize(); i++)
    {

        mergeWindows(this -> getWindow(0), this -> getWindow(i));
    }
}

void Browser::closeAllWindows() {
    while(!(windows.isEmpty()))
    {
        this->closeWindow();
    }
}

void Browser::closeEmptyWindows() {
    int size = windows.getSize();
    int i;
    
    for(i = 0 ; i < size ; i++){
        if(windows.getNodeAtIndex(i)->data.isEmpty()){
            this->switchToWindow(i);
            this->closeWindow();
            i--;
            size--;
        }
    }
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
