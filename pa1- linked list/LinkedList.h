#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.



private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

/*
 * This is the default constructor for our circular doubly linked list
 */
template<class T>
LinkedList<T>::LinkedList()
{
	size=0;
	head=NULL;
}

/*
 * This is the copy constructor. You should make necessary initializations, create new nodes
by copying the nodes in the rhs, and insert those new nodes into the linked list.
 */
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) //
{

    if(obj.head == NULL)
    {
        head = NULL;
    }
    else
    {
        head = new Node<T>(obj.head->data);
        Node<T> *curr = head;
        Node<T> *obj_curr = obj.head;
        Node<T> *t = head;

        while(obj_curr->next != obj.head)
        {
            curr->next = new Node<T>(obj_curr->next->data);
            obj_curr = obj_curr->next;
            curr = curr->next;
            curr->prev = t;
            t= t->next;
        }
        head->prev = curr;
        curr->next = head;
    }
    size=obj.size;
}

/*
 * This is the destructor. You should deallocate all the memory that you had allocated
before.
 */
template<class T>
LinkedList<T>::~LinkedList()
{

    if(head)
    {
        Node<T> *tmp = head;
        while(tmp->next != head)
        {
            Node<T> *t = tmp;
            tmp = tmp->next;
            delete t;
            size--;
        }
        delete tmp;
        size--;
        head = NULL;
    }
}

/*
 * This is the overloaded assignment operator. You should remove all nodes in the linked
list and then, you should create new nodes by copying the nodes in the given rhs and insert
those new nodes into the linked list.
 */
template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{

    if (this != &rhs)
    {
        this->removeAllNodes();

        if(rhs.head!=NULL)
        {
            append(rhs.head->data);
            Node<T> *rhs_temp=rhs.head->next;


            while(rhs_temp!=rhs.head)
            {
                append(rhs_temp->data);
                rhs_temp=rhs_temp->next;
            }
        }
        else{
            head=NULL;
        }
    }
    return *this;
}

/*
 * This function should return the size of the linked list
 */
template<class T>
int LinkedList<T>::getSize() const
{
	return size;
}

/*
 * This function should return true if the linked list is empty
 */
template<class T>
bool LinkedList<T>::isEmpty() const //checking if the linked list is empty
{

	if(head==NULL){
		return true;
	}
	return false;
}

/*
 * This function should return true if the linked list contains the given node (i.e., any
prev/next in the nodes of the linked list matches with node). Otherwise, it should return
false.
 */
template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    if(head==NULL)
        return false;


	Node<T> *temp=head;
	if (head==node)
        return true;

	temp=temp->next;
	while(temp!=head){
		if(temp==node)
		{
			return true;
		}
		temp=temp->next;
	}

	return false;
}

/*
 * This function should return a pointer to the first node in the linked list. If the linked list
is empty, it should return NULL.
 */
template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
	return head;
}


/*
 * This function should return a pointer to the last node in the linked list. If the linked list
is empty, it should return NULL.
 */
template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{

	if(head)
		return head->prev;

	return NULL;
}


/*
 * You should search the linked list for the node that has the same data with the given data
and return a pointer to that node. If there exists multiple such nodes in the linked list, return
a pointer to the first occurrence. If there exists no such node in the linked list, you should
 return NULL.
 */
template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{

	if(head==NULL) {
		return NULL;
	}
	else
	{
		if(head->data==data)//if head has the data return head
		{
			return head;
		}


		Node<T> *temp=head->next;
		while(temp!=head)
		{
			if(temp->data==data)
			{
				return temp;
			}
			temp=temp->next;
		}
	}
	return NULL;
}

/*
 * You should search the linked list for the node at the given zero-based index and return
 * a pointer to that node. If there exists no such node in the linked list, you should return NULL.
 */
template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{

	if(head==NULL) //if head is null, you should return null
	{
		return NULL;
	}
	else //if linked list has nodes, search the linked list
    {
		if(index==0)
		{
			return head;
		}

        if(index>=0 && index<size) //if index is in bounds of the linked list
        {
            Node<T> *temp=head->next;
		    int i=1;
		    while(temp!=head)
		    {
			    if(i==index)
			    {
				    return temp;
			    }
			    i++;
			    temp=temp->next;
		    }
        }

        //if index is out of bound, you should return null
		return NULL;
	}
}

/*
 * You should create a new node with the given data and insert it at the end of the linked
list as the last node.
 */
template<class T>
void LinkedList<T>::append(const T &data)
{

	if(size==0) //if linked list is empty
	{
		Node<T> *newnode=new Node<T>(data);
		head=newnode;
		head->next=head;
		head->prev=head;
		size=1;
		return;
	}

	if(size==1) //if there is only one node at the linked list
	{
		Node<T> *newnode=new Node<T>(data);
		head->next=newnode;
		newnode->prev=head;
		newnode->next=head;
		head->prev=newnode;
		size++;
		return;
	}



	//if there are more than one node in the list
	Node<T> *newnode=new Node<T>(data);
	head->prev->next=newnode;
	newnode->next=head;
	newnode->prev=head->prev;
	head->prev=newnode;
	size++;
	return;
}


/*
 *You should create a new node with the given data and insert it at the front of the linked
list as the first node.
 */
template<class T>
void LinkedList<T>::prepend(const T &data)
{
	if(head==NULL)	//if linked list is empty, inserted node should be the head
	{
		Node<T> *newnode=new Node<T>(data);
		head=newnode;
		head->next=head;
		head->prev=head;
		size=1;
		return;
	}

	if(size==1) //if there is only one node in the list
	{
		Node<T> *newhead=new Node<T>(data);

		newhead->prev=head;
		head->prev=newhead;
		newhead->next=head;
		head->next=newhead;

		head=newhead;
		size++;
		return;
	}
	//if there are more than one node in the list
	Node<T> *prenode=new Node<T>(data);
	Node<T> *temp=head;
	temp->prev->next=prenode;
	prenode->next=temp;
	prenode->prev=temp->prev;
	temp->prev=prenode;
	head=prenode;
	size++;

}


/*
 * You should create a new node with the given data and insert it after the given node as
its next node. If the given node is not in the linked list, do nothing.
 */
template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{

	if (size==0 || node==NULL)//if head is null or the given node is null
	{
		return;
	}

	if (size==1) //if there is only one node in the list
	{
	    if(head==node) //is given node is the head
	    {
	        append(data); //call append to insert it as the last node
	        return;
	    }
	}

	//if given node is the last node of the linked list
	if(node==head->prev)
	{
	    append(data); //call append to insert it as the last node
	    return;
	}

	//if the given node is somewhere in the linked list (not the head nor the tail)
	Node<T> *temp=head->next;
	while(temp!=head)
	{
		if(temp==node) //if the given node is the temp (if the given node exists in the linked list)
		{
			Node<T> *insertnode=new Node<T>(data); //allocate memory for the new node
			insertnode->next=temp->next; //make necessery pointer modifications
			temp->next->prev=insertnode;
			temp->next=insertnode;
			insertnode->prev=temp;
			size++; //increase size
			return;
		}
		temp=temp->next;
	}
}

/*
 * You should create a new node with the given data and insert it at the given index.
 * If there exists no such index in the linked list (i.e., index is out of bounds), you should not insert the element.
 */
template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
	if(index>=0 && index<size) //check if the index is valid
	{
		if(index==0) //insert it as the head
		{
			prepend(data); //call prepend to insert node as head
			return;
		}


		Node<T> *temp=head->next;
		int i=0; //counter for index
		while(temp!=head)
		{
			if(i==index-2) //newly inserted node will be at given index so you should insert the new node at given_index-2 position
            {
				Node<T> *insertedindexnode=new Node<T>(data);
				temp->next->prev=insertedindexnode;
				insertedindexnode->next=temp->next;
				temp->next=insertedindexnode;
				insertedindexnode->prev=temp;
				size++;
			}
			temp=temp->next;
		    i++;
		}
		return;
	}
	 //if index is not valid, do nothing
}

/*
 * This function should return the index of the given node in the linked list. If the node is
not in the list, it should return -1 instead.
 */
template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
	if(size==0) //if linked list is empty
		return -1;

	if(head==node) //if node is head, index is zero
		return 0;

	if(head->prev==node) //if node is the last node in the list, index will be size-1
		return size-1;

	//else (if the node is somewhere in the linked list
	int i=0;
	Node<T> *temp=head->next;
	while(temp!=head)
	{
		if(temp==node) //if the node exists in linked list
		{
			return i;
		}
		i++;
		temp=temp->next;
	}
	return -1; //if there is no such node, return -1
}

/*
 * This function should move the node at the currentIndex to newIndex. For this function,
you are not allowed to just change the data in the given nodes. Also, you are not allowed to
create new nodes. Do the moving by changing the pointers in the nodes of the linked list.
If the newIndex is greater than the number of nodes in the list, then the node should be
moved to the end of the list. If the currentIndex is greater than the number of nodes in
the list, then do nothing.
 */
template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex==newIndex) //make no change
        return;

    if(currentIndex>=size) //If the currentIndex is out of bounds, then do nothing.
		return;


    if(head==NULL || size==1) //if linked list is empty, do nothing
        return;



    if(size==2 && ((newIndex- currentIndex)==1 || (currentIndex- newIndex==1))) //if there is two nodes in the list and you want to swap them
    {
        head=head->next;
        return;
    }

    if(newIndex>=size) //if new_index is out of bounds, you should move the node at the end of the list
    {
        if(currentIndex==size-1) //if node is already the last node, do nothing
            return;

        int i=1; //if node is not at the end, move it
        Node<T> *temp=head->next;
        while(temp!=head)
        {
            if(i==currentIndex)
            {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                head->prev->next=temp;
                temp->prev=head->prev;
                head->prev=temp;
                temp->next=head;
                break;
            }
            temp=temp->next;
            i++;
        }
        return;
    }


	if(newIndex<size) //if new_index is in bounds
	{
		if (currentIndex==0)//if you will move the head
		{
			if(newIndex==size-1)//if you'll move the head to the end
			{
			    head=head->next;
			    return;
			}


			int i=1;
			Node<T> *temp=head->next;
			Node<T> *t=head;
            while(temp!=head)
            {
                if(i==newIndex )
                {
                    head->prev->next=head->next;
                    head->next->prev=head->prev;
                    head=head->next;

                    t->next=temp->next;
                    temp->next->prev=t;
                    temp->next=t;
                    t->prev=temp;
                    break;
                }
                temp=temp->next;
                i++;
            }
            return;
		}
		if(newIndex==0) //if you move a node to the beginning, make it head
		    {
		    	Node<T> *temp=getNodeAtIndex(currentIndex);
		    	temp->next->prev=temp->prev;
		    	temp->prev->next=temp->next;

		    	temp->next=head;
		    	head->prev->next=temp;
		    	temp->prev=head->prev;
		    	head->prev=temp;
		    	head=temp;


		    }

        //if you are moving the node to a non-neighbour index
		else if ((currentIndex - newIndex!=1 )&& (newIndex - currentIndex!=1 ))
		{
		    Node<T> *temp=getNodeAtIndex(currentIndex);
			Node<T> *t=getNodeAtIndex(newIndex);

		    temp->prev->next=temp->next;
            temp->next->prev=temp->prev;

            temp->next=t->next;
            t->next=temp;
            temp->next->prev=temp;
            temp->prev=t;
            return;
		}

        //if you are moving a node to a neighbour
		else if ((newIndex - currentIndex==1)|| (currentIndex - newIndex==1 ))
		{
			Node<T> *temp=getNodeAtIndex(currentIndex);
			Node<T> *t=getNodeAtIndex(newIndex);

			if(currentIndex>newIndex) //if you are moving the node to previous index
			{

				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;

				t->prev->next=temp;
				t->next->prev=t->prev;

				t->prev=temp;
				temp->next=t;
				return;
			}
			else //if you are moving the node to next index
			{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;

				temp->next=t->next;
				t->next->prev=temp;

				temp->prev=t;
				t->next=temp;

			}
			return;
		}
	}
}

/*
 * You should remove the given node from the linked list. If the given node is not
 * in the linked list (i.e., the linked list does not contain the given node), do nothing.
 */
template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{

    if(head==NULL) //if list is empty, do nothing
        return;

    if(node==head) //remove head
    {

        if(size==1) //if there is only head in the link list
        {
            Node<T> *temp=head;
            delete temp;
            size--;
            head=NULL;
            return;
        }

        //if there is not only head in the list, remove head
        Node<T> *temp=head;
        head->prev->next=temp->next;
        head->next->prev=temp->prev;
        head=head->next;
        delete temp;
        size--;
        return;
    }

    Node<T> *temp=head->next;
    while(temp!=head) //search the node
    {

        if(temp==node) //if you find the node, delete it
        {
            if(size==2) //if there are two nodes, you will delete the second node so after the removal there will be only head in the list
            {
                delete temp;
                head->next=head;
                head->prev=head;
                size--;
                return;
            }
            else
            {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                delete temp;
                size--;
                return;
            }
        }
        temp=temp->next;

    }
}

/*
 * You should remove the node that has the same data with the given data from the linked
list. If there exists multiple such nodes in the linked list, remove all occurrences.
If there exists no such node in the linked list, do nothing.
 */
template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    Node<T>* nodeToDelete;
    Node<T>* temp;
    while(head != NULL && head->data == data) //remove the head
    {
        if(head->next == head)  //if there is only head, list will be empty after the removal
        {
            head = NULL;
        }
        else //if there are more node, delete the head and make pointer modifications
        {
            nodeToDelete = head;
            temp = head;
            while(temp->next != head)
            {
                temp = temp->next;
            }
            head = head->next;
            temp->next = head;
            head->prev = temp;
            delete nodeToDelete;
            size--;
        }
    }


    temp = head;
    if(temp != NULL)
    {
        while(temp->next != head) //traverse the list
        {
            if(temp->next->data == data) //if you find the node, delete it.
            {
                nodeToDelete = temp->next;
                temp->next = temp->next->next;
                temp->next->prev = temp;
                delete nodeToDelete;
                size--;
            }
            else //in case there are more than one node with given data, do not break the loop so that you can delete other occurrences
            {
                temp = temp->next;
            }
        }
    }
}


/*
 * You should remove the node at the given index from the list. If there exists no such index in the linked
list (i.e., index is out of bounds), or if the list is empty, you should not do anything.
 */
template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    Node<T>* nodeToDelete = head;
    Node<T>* temp = head;
    if(index < 0 || index >= size) //if index is out of bound, do nothing
        return;

    else if (index == 0) //if head will be removed
     {
        if(size==1) //if there is only head, the list will be empty after the removal
        {
            delete temp;
            head=NULL;
            size--;
            return;
        }
        else //if there are more than one node in the list
        {
            while(temp->next != head) //find the tail of the list
            {
                temp = temp->next;
            }

            head = head->next;
            temp->next = head;
            head->prev = temp;
            delete nodeToDelete;
            size--;
            return;
        }
    }

    else //if you want to delete a node that is not the head
    {
        temp = head;
        for(int i = 0; i < index-1; i++) //find the previous of the node taht will be deleted
            temp = temp->next;

        nodeToDelete = temp->next; //nodeToDelete is the node to be deleted
        temp->next = temp->next->next;
        temp->next->prev = temp;
        delete nodeToDelete;
        size--;
        return;
    }
}

/*
 * You should remove all nodes in the linked list so that the linked list becomes empty.
 */
template<class T>
void LinkedList<T>::removeAllNodes()
{

    if(head)
    {
        Node<T> *tmp = head;
        while(tmp->next != head) //remove nodes until there is one node in the list
        {
            Node<T> *t = tmp;
            tmp = tmp->next;
            delete t;
            size--;
        }
        delete tmp; //delete head
        size--;
        head = NULL;
    }
}

/*
 * This function print the linked list to the standard output.
 */
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

#endif //LINKEDLIST_H
