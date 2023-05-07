#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

/*
 * This function should return the active tab of the window. If there are no tabs in the
window, this function should return an empty Tab.
 */
Tab Window::getActiveTab() {
	if(tabs.isEmpty())
		return Tab();

	Node<Tab> *newTab = tabs.getNodeAtIndex(activeTab);
	return newTab->data;
}

/*
 * This function should return true if the Window is empty (i.e., there are no tabs left in
the window). If the Window is not empty, it should return false.
 */
bool Window::isEmpty() const {
	return tabs.isEmpty();
}

/*
 * This function should add a new tab to the Window. The new tab should be added after
the active tab of the window (i.e. if the active tab is the fourth tab, then the new tab should
be added as the fifth tab), and should be made the active tab of the window.
 */
void Window::newTab(const Tab &tab) {
    if(tabs.getSize()==0) //if the window is empty, add the tab as the active tab
    {
        tabs.prepend(tab);
        activeTab=0;
        return;
    }

    //if there are tabs
	tabs.insertAfterNode(tab, tabs.getNodeAtIndex(activeTab));
	activeTab++;
}

/*
 * This function should destroy the active tab of the Window. The new active tab must be
the tab that was following the previous active tab, if there were any other tabs in the window
other than the active tab. If there are no tabs left in the window, activeTab must be set to
-1.
 */
void Window::closeTab() {

    if(activeTab != -1) //if there are tabs
    {
    	tabs.removeNodeAtIndex(activeTab); //close the tab
    	if (tabs.getSize()==activeTab)  //if the window has still tabs, make the active tab the previous tab
    	{
    	    activeTab--;
    	}

    }
}

/*
 * This function should change the position of the active tab of the window. Active tab
should be moved to the position of the index. If the index is greater than the number of
nodes in the list, then the active tab must be moved to the end of the list.
 */
void Window::moveActiveTabTo(int index) {
    if(activeTab != -1) //if the window is not empty
    {

        Node<Tab> *temp=tabs.getNodeAtIndex(activeTab); //temp is the tab that will be moved
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;

        Node<Tab> *p=tabs.getNodeAtIndex(index);
        p->prev->next=temp;
        temp->next=p;
        temp->prev=p->prev;
        p->prev=temp;

        activeTab=index;

    }
}

/*
 *This function should change which tab is the active tab of the window. The index’th
tab of the window should be made the active tab. If the index is greater than the number
of tabs in the window, then do nothing.
 */
void Window::changeActiveTabTo(int index) {

	if(index>tabs.getSize()-1||index<0) //if index is out of bounds, do nothing
		return;

	activeTab=index;
}


/*
 * This function should add the given tab to the Window. We will use this function to add
tabs that were removed from other windows. The position of the tab should be right at the
end of the list of tabs (i.e. add the tab as the last tab). If the Window is empty, then the
newly added tab should be made the active tab.
 */
void Window::addTab(Node<Tab> &tab) {
	if(tabs.isEmpty()) //if there are no tabs in the window
	{
		tabs.prepend(tab.data); //add a new tab with using given tab's data
		delete &tab; //delete the given tab node
	}

	else
	{
	    tabs.append(tab.data);
	}

}

/*
 * This function print the linked list to the standard output.
 */
void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
