#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

/*
 * This function should create a new empty window in the browser. The window that is
created should be made the first element of the lis
 */
void Browser::newWindow() {
    windows.prepend(Window());

}

/*
 * This function should destroy the first window of the browser. If there are no windows in
the browser, do nothing.
 */
void Browser::closeWindow() {

    if (windows.getSize()>0) //if browser is not empty
		windows.removeNodeAtIndex(0);

}


/*
 * This function should make the given window the first window of the browser.
 */
void Browser::switchToWindow(int index) {
    windows.moveToIndex(index, 0);
}


/*
 * This function returns a reference the index’th window of the browser.
 */
Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}


/*
 * This function closes the active tab of the from window, and create a new tab with the
same data in the to window. If from becomes empty after its active tab is closed, then you
should leave it empty (to be later closed by closeEmptyWindows).
 */
void Browser::moveTab(Window &from, Window &to) {
	to.changeActiveTabTo(0);
	to.newTab(from.getActiveTab());
	from.closeTab();
}


/*This function merges two windows together by adding all the tabs of one window to the
other. In this function, you should add the tabs of window2 to window1. You shouldn’t
change the order of the tabs in window1, and the tabs from window2 must come after the
tabs of window1 in its list.
 */

void Browser::mergeWindows(Window &window1, Window &window2) {

	window2.changeActiveTabTo(0);

	while(!window2.isEmpty())
	{
		window1.newTab(window2.getActiveTab());
		window2.closeTab();
	}

}

/*
 * This function merges all the windows of the browser into a single window. Tabs of all
the windows in the browser must be put into the first window. You shouldn’t change the
order of the tabs of the first window, and the windows should be merged in the order that
they appear in windows.
 */
void Browser::mergeAllWindows() {

	Node<Window> *temp=windows.getFirstNode();
	Node<Window> *temp_sec=temp->next; //second window

	while(temp_sec!=temp) //merge until there is one window in the browser
	{
		Node<Window> *random=temp_sec->next;
		mergeWindows(temp->data, temp_sec->data);
		temp_sec=random;
	}
}


//This function closes all windows of the browser.
void Browser::closeAllWindows() {
	windows.removeAllNodes();
}

/*
 * This function should look for empty windows in the browser, and close any empty windows
that is finds. If there aren’t any empty windows in the browser, then do nothing.
 */
void Browser::closeEmptyWindows() {

	Node<Window> *temp= windows.getFirstNode();
	int temp_index = 0;
	int t_size=windows.getSize();
    Node<Window> *temp_n;
	while(temp_index<t_size)
	{
        temp_n=temp->next;
		if(temp->data.isEmpty())
		{
			windows.removeNodeAtIndex(temp_index);
		}
		temp=temp_n;
		temp_index++;
	}
	Node<Window> *last_window=windows.getLastNode();
	int size=windows.getSize();
	for(int i=size-1; i>=0; i--)
	{
		if(last_window->data.isEmpty())
		{
			windows.removeNodeAtIndex(i);
		}
	}
}


//This function print the linked list to the standard output.
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
