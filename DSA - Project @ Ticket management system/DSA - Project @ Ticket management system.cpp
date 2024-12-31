#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Node {
public:
	string name;
	int cnic;
	int ticketID;
	int age;
	string gender;
	Node* left;
	Node* right;
	Node* nxtNode;


	void setName(string nam) {
		name = nam;
	}
	void setCnic(int nic) {
		cnic = nic;
	}
	void setTicketID(int tktID) {
		ticketID = tktID;
	}
	void setAge(int ag) {
		age = ag;
	}
	void setGender(string g) {
		gender = g;
	}


	// for tree
	void setLeft(Node* l) {
		left = l;
	}
	void setRight(Node* r) {
		right = r;
	}

	void setNxtNode(Node* n) {
		nxtNode = n;
	}


	string getName() {
		return name;
	}
	int getCnic() {
		return cnic;
	}
	int getTicketID() {
		return ticketID;
	}
	int getAge() {
		return age;
	}
	string getGender() {
		return gender;
	}


	//for tree

	Node* getLeft() {
		return left;
	}
	Node* getRight() {
		return right;
	}
	Node* getNxtNode() {
		return nxtNode;
	}
};//Node class for stack and queue

class Stack {
public:
	Node* head;

	Stack() {
		head = NULL;
	}

	void push(Node* CanceledTicket) {
		Node* newnode = CanceledTicket;
		// copying data from the canceled ticket to newnode
		newnode->setName(CanceledTicket->getName());
		newnode->setCnic(CanceledTicket->getCnic());
		newnode->setTicketID(CanceledTicket->getTicketID());
		newnode->setAge(CanceledTicket->getAge());
		newnode->setGender(CanceledTicket->getGender());
		newnode->setTicketID(CanceledTicket->getTicketID());
		newnode->setNxtNode(NULL);

		if (head == NULL) {
			head = newnode;
		}
		else {
			newnode->setNxtNode(head);
			head = newnode;
		}

	}

	Node* pop() {
		if (head == NULL) {
			cout << "\n\tStack is empty!" << endl;
			return NULL;
		}
		Node* temp = head;
		head = head->nxtNode;
		temp->nxtNode = NULL;
		return temp;
	}

	bool isEmpty() {
		return head == NULL;
	}

	//This function will save the The Delected Ticket data into .txt file
	void SaveStack() {
		ofstream file("StackData.txt");
		if (file.is_open()) {
			Node* temp = head;

			while (temp != NULL) {
				file << temp->getTicketID() << endl;
				file << temp->getName() << endl;
				file << temp->getAge() << endl;
				file << temp->getGender() << endl;
				file << temp->getCnic() << endl;
				temp = temp->nxtNode; // Move to the next node
			}//while

			file.close(); // Close the file
			cout << "\n\tYour Deleted Ticket Data is saved successfully!";
		}//if
		else {
			cout << "\n\tUnable to open your file!";
		}//else
	}
	void clearStackFile() {
		ofstream file("StackData.txt", ios::out | ios::trunc);

		if (file.is_open()) {
			cout << "\n\tYour file is loaded and cleared successfully";

			file.close();
		}
		else {
			cout << "\n\tUnable to Clear your file";
		}
	}

	void LoadStack() {
		ifstream file("StackData.txt");
		if (file.is_open()) {
			string nm, gndr;
			int tktID, ag, cnc;

			while (file >> tktID >> nm >> ag >> gndr >> cnc) {
				Node* newnode = new Node();
				newnode->setTicketID(tktID);
				newnode->setName(nm);
				newnode->setAge(ag);
				newnode->setGender(gndr);
				newnode->setCnic(cnc);
				newnode->setNxtNode(NULL);

				push(newnode); // Push into the stack
			}//while
			clearStackFile();
			file.close(); // Close the file
			//cout << "\nYour all data of deleted tickets is loaded into the stack!";
		}//if
		else {
			cout << "\n\tUnable to open your file!";
		}//else
	}//LoadStack()
};//Stack Class




//////////////////////////////////////////////////////////////////////////////

class Tree {
	Node* root;

public:
	Tree() {
		root = NULL;
	}


	void addTicketToTree(Node* dequeuedTicket, bool addCheck) {

		if (addCheck != true) {
			SaveTree();
		}

		else {
			if (dequeuedTicket == NULL) {
				cout << "\n\tDequeued Ticket is NULL!";
				return;
			}

			dequeuedTicket->setLeft(NULL);
			dequeuedTicket->setRight(NULL);

			if (root == NULL) {
				root = dequeuedTicket; // Assign root
				cout << "\n\tTicket Confirmed" << endl;
			}
			else {



				Node* current = root;
				Node* parent = NULL;

				while (current != NULL) {
					parent = current;
					if (dequeuedTicket->getTicketID() < current->getTicketID()) {
						current = current->getLeft();
					}
					else {
						current = current->getRight();
					}
				}

				if (dequeuedTicket->getTicketID() < parent->getTicketID()) {
					parent->setLeft(dequeuedTicket);
				}
				else {
					parent->setRight(dequeuedTicket);
				}

				cout << "\n\tTicket Confirmed" << endl;
				//cout << "\n\tNode inserted with address: " << parent->getRight();
			}

			// cout << "\n\tTicket inserted with address: " << dequeuedTicket;
		}
	}

	void Inorder(Node* n) {
		if (n == NULL) {
			return; // Base case
		}

		Inorder(n->getLeft());
		cout << "\n\tTicket ID: " << n->getTicketID();
		cout << "\n\tName: " << n->getName();
		cout << "\n\tCnic: " << n->getCnic();
		cout << "\n\tAge: " << n->getAge();
		cout << "\n\tGender: " << n->getGender() << endl;
		Inorder(n->getRight());
	}

	void displayConfirmedTicket() {
		if (root == NULL) {
			cout << "\n\tNo confirmed ticket found (root is NULL)." << endl;
		}
		else {
			//cout << "\n\tStarting Inorder traversal from root at address: " << root;
			Inorder(root);
		}
	}


	//This function will save the data to to .txt file

	void SaveInorder(Node* n, ofstream& file) {
		if (n == NULL) return;

		SaveInorder(n->getLeft(), file);
		file << n->getTicketID() << endl;
		file << n->getName() << endl;
		file << n->getCnic() << endl;
		file << n->getAge() << endl;
		file << n->getGender() << endl;
		SaveInorder(n->getRight(), file);
	}//SaveInorder()

	bool isEmpty() {
		if (root == NULL)
			return true;
	}

	void SaveTree() {
		if (root == NULL) {
			cout << "\n\tTree is empty. Nothing to save!" << endl;
			return;
		}//if

		ofstream file("treeData.txt");
		if (file.is_open()) {
			SaveInorder(root, file);
			file.close();
			cout << "\n\tTree data has been saved successfully to your file!" << endl;
		}//if
		else {
			cout << "\n\tUnable to open your tree file" << endl;
		}//else
	}//save Tree()
	void clearTreeFile() {
		ofstream file("treeData.txt", ios::out | ios::trunc);

		if (file.is_open()) {
			cout << "\n\tYour file is loaded and cleared successfully";

			file.close();
		}
		else {
			cout << "\n\tUnable to Clear your file";
		}
	}

	void LoadTree() {

		ifstream file("treeData.txt");

		if (file.is_open()) {
			string nm, gndr;
			int tktID, ag, cnc;

			while (file >> tktID >> nm >> cnc >> ag >> gndr) {

				Node* newnode = new Node();
				newnode->setTicketID(tktID);
				newnode->setName(nm);
				newnode->setAge(ag);
				newnode->setGender(gndr);
				newnode->setCnic(cnc);

				addTicketToTree(newnode, true);


				//addTicketToTree(newnode, true); // add this ticket back to tree

			}
			clearTreeFile();
			//cout << "\n\tFile loaded Successfully";
			file.close();
		}//if
		else {
			cout << "\n\tUnable to open your tree file!";
		}//else
	}//LoadTree()
};
// BST class



//////////////////////////////////////////////////////////////////////////////
class Queue {

public:
	Node* front;
	Node* rear;
	Node* current;
	Node* prev;

	Stack s;
	Tree t;

	Queue() {
		front = NULL;
		rear = NULL;
		current = NULL;
		prev = NULL;
	}

	void enqueue(int tcktID, string nm, int ag, string gd, int cnc) {
		Node* newnode = new Node;
		newnode->setName(nm);
		newnode->setCnic(cnc);
		newnode->setAge(ag);
		newnode->setGender(gd);
		newnode->setTicketID(tcktID);
		newnode->setNxtNode(NULL);

		if (rear == NULL) {
			rear = newnode;
			front = newnode;
		}	// if
		else {
			rear->setNxtNode(newnode);
			rear = newnode;
		}//else

	}

	Node* dequeue(int tktID, bool cancelCheck) {
		current = front;
		prev = NULL;

		while (current != NULL) {
			if (current->ticketID == tktID) {
				Node* returnedTicket = NULL; // Initialize a variable to hold the returned ticket

				if (cancelCheck) { // If canceling the ticket
					s.push(current); // Push the Node and its ticket ID to stack
					cout << "\n\tTicket # " << current->ticketID << " is canceled successfully!" << endl;
				}
				else { // If confirming the ticket
					// Create a new node for confirmed ticket
					Node* confirmedTicket = new Node;
					confirmedTicket->setName(current->getName());
					confirmedTicket->setCnic(current->getCnic());
					confirmedTicket->setAge(current->getAge());
					confirmedTicket->setGender(current->getGender());
					confirmedTicket->setTicketID(current->getTicketID()); // Assign ticketID
					confirmedTicket->setLeft(NULL);
					confirmedTicket->setRight(NULL);
					confirmedTicket->setNxtNode(NULL);

					// Add the new node to the tree
				   // t.addTicketToTree(confirmedTicket);

				   // cout << "\n\tTicket # " << current->ticketID << " is confirmed successfully!" << endl;

					// Assign the confirmedTicket to the returnedTicket variable
					returnedTicket = confirmedTicket;
				}

				// Queue update: Removing the node from the front or middle of the queue
				if (current == front) { // If the node to delete/confirm is the front
					front = front->nxtNode;
					if (front == NULL) {
						rear = NULL; // Update rear if the queue becomes empty
					}
				}
				else { // If the node is in the middle or rear
					prev->nxtNode = current->nxtNode;
					if (current == rear) {
						rear = prev; // Update rear if the last node is removed
					}
				}

				// Disconnect the node from the queue
				current->nxtNode = NULL;

				// Return the ticket address after performing the necessary actions
				return returnedTicket; // Will return the confirmed ticket or NULL if canceled
			}

			prev = current;
			current = current->nxtNode;
		}

		// If no matching ticket is found
		cout << "\n\tTicket # " << tktID << " not found!" << endl;
		return NULL; // Return NULL if ticket not found
	}//dequeue()

	void undoDeletedTicket() {
		if (s.isEmpty()) {
			cout << "\n\tNo canceled ticket found to undo!" << endl;
			return;
		}

		Node* restoredTicket = s.pop();
		int restoredTicketID = restoredTicket->ticketID;

		if (restoredTicket == NULL) {
			cout << "\n\tNo ticket to restore!" << endl;
			return;
		}

		if (rear == NULL) {
			front = restoredTicket;
			rear = restoredTicket;
		}
		else {
			rear->nxtNode = restoredTicket;
			rear = restoredTicket;
		}

		restoredTicket->nxtNode = NULL;
		cout << "\n\tTicket ID " << restoredTicketID << " restored to the queue!" << endl;
	}


	void display() {
		Node* temp = front; // Use temp for traversal to avoid modifying front
		while (temp != NULL) {
			cout << "\n\t Ticket # " << temp->getTicketID() << ":";
			cout << "\n\t Name : " << temp->getName();
			cout << "\n\t Cnic : " << temp->getCnic();
			cout << "\n\t Age : " << temp->getAge();
			cout << "\n\t Gender : " << temp->getGender() << endl;

			temp = temp->getNxtNode();
		}
	}

	bool isEmpty() {
		return front == NULL;
	}

	//This function will save the queue data to .txt file
	void SaveQueue() {
		ofstream file("QueueData.txt");

		if (file.is_open()) {
			Node* temp = front;

			while (temp != NULL) {
				file << temp->getTicketID() << endl;
				file << temp->getName() << endl;
				file << temp->getAge() << endl;
				file << temp->getGender() << endl;
				file << temp->getCnic() << endl;

				temp = temp->getNxtNode();
			}//while

			file.close();

			cout << "\n\tYour all data from queue is saved Successfully" << endl;
		}//if
		else {
			cout << "\n\tUnable to open your Queue File!" << endl;
		}//else
	}//SaveQueue to file , this function will save queue to file

	void clearQueueFile() {
		ofstream file("QueueData.txt", ios::out | ios::trunc);

		if (file.is_open()) {
			cout << "\n\tYour file is loaded and cleared successfully";
			file.close();
		}
		else {
			cout << "\n\tUnable to Clear your file";
		}
	}



	//this funcion will load the data from the .txt file
	void LoadQueue() {


		ifstream file("QueueData.txt");
		if (file.is_open()) {
			string nm, gndr;
			int tktID, cnc, age;

			while (file >> tktID >> nm >> age >> gndr >> cnc) {
				enqueue(tktID, nm, age, gndr, cnc);
			}//while
			clearQueueFile();
			file.close();
			//cout << "\n\tYour Data is Loaded Successfully !";
		}//if
		else {
			cout << "\n\tUnable to open your file ! " << endl;
		}//else
	}//LoadQueue()

	
	void SaveStackData() {
		if (s.isEmpty())
			cout << "\n\tNo Data found for deleted Tickets!";
		else
			s.SaveStack();
	}//SAveStackData


	void LoadStackData() {
		s.LoadStack();
	}//LoadStackData


};//QueueClass



//////////////////////////////////////////////////////////////////////////////

int main() {

	int choice;

	string nm, gd;
	int ag, cnc, tcktID;
	int ammount;

	Node* address;
	Queue q;
	Stack s;
	Tree t;

	Node* root;
	int count = 0;

	while (true) {


		system("cls");




		cout << "\n\t***Ticket Management System***";

		cout << "\n\t1.Book a ticket.";
		cout << "\n\t2.Confirm Your Booked Ticket(Pay Now).";
		cout << "\n\t3.Cancel a booking.";
		cout << "\n\t4.Undo last Cancelation.";
		cout << "\n\t5.View Booking queue.";
		cout << "\n\t6.View Confirmed / Booked Tickets.";
		cout << "\n\t7.Save Your Booking queue Data to .txt file";
		cout << "\n\t8.Load Your Booking queue Data from .txt file";
		cout << "\n\t9.Save Your Deleted Data to .txt file (Stack) ";
		cout << "\n\t10.Load Your Deleted Data from .txt file (Stack)";
		cout << "\n\t11.Save Your Confirmed Tickets to .txt file (Tree)";
		cout << "\n\t12.Load Your Confirmed Tickets Data from .txt (Tree)";
		cout << "\n\t13.Exit.";


		cout << "\n\tEnter your choice : ";
		cin >> choice;


		switch (choice) {

		case 1:
			cout << "\n\tEnter Name : ";
			cin >> nm;
			cout << "\tEnter the age : ";
			cin >> ag;
			cout << "\tEnter cnic : ";
			cin >> cnc;
			cout << "\tEnter the Gender : ";
			cin >> gd;
			cout << "\tEnter the ticketID : ";
			cin >> tcktID;

			q.enqueue(tcktID, nm, ag, gd, cnc);

			cout << "\n\tYour ticket is booked successfully!" << endl;

			system("pause");
			break;


		case 2:
			// confirming that the queue is not empty , to confirm that ticket.

			cout << "\n\tEnter ruppes 100 to confirm : ";
			cin >> ammount; // just taking dummy amount

			if (ammount >= 100) {
				if (q.isEmpty()) {
					cout << "\n\tNo booked ticket found!" << endl;
				}//if
				else {
					cout << "\n\tEnter the ticked id to Confirm Your booking : ";
					cin >> tcktID;
					address = q.dequeue(tcktID, false); // i have passed false from here so the function in MinHeap class is called. 
					//cout<<"ticket address is added "<<address;
					t.addTicketToTree(address, true);

				}//else
			}//if
			else {
				cout << "\n\tPlease Pay amount(100) to comfirm the ticket. Otherwise it will be canceled" << endl;
			}//else

			system("pause");

			break;



		case 3:
			if (q.isEmpty()) {
				cout << "\n\tNo booked ticket found!" << endl;
			}//if
			else {
				cout << "\n\tEnter the ticked id to cancel the booking : ";
				cin >> tcktID;
				q.dequeue(tcktID, true);// i have passed true from here so the function in stack class is called.
			}//else

			system("pause");
			break;


		case 4:
			q.undoDeletedTicket();
			cout << "\n\tTicket has be restored! " << endl;
			system("pause");
			break;


		case 5:
			if (q.isEmpty()) {
				cout << "\n\tNo booked ticket found" << endl;
				system("pause");
			}//if
			else {
				q.display();
				system("pause");
			}
			break;

		case 6:


			t.displayConfirmedTicket();
			system("pause");
			break;

		case 7:
			if (q.isEmpty()) {
				cout << "\n\tNo Data found in queue to Save ";
			}
			else {
				q.SaveQueue();
			}
			system("pause");
			break;


		case 8:
			q.LoadQueue();
			system("pause");
			break;


		case 9:
			q.SaveStackData();

			system("pause");
			break;


		case 10:
			q.LoadStackData();
			system("pause");
			break;


		case 11:

			t.addTicketToTree(NULL, false);

			system("pause");
			break;


		case 12:
			//t.addTicketToTree(NULL, false, 1);
			t.LoadTree();
			system("pause");
			break;

		case 13:
			exit(0);
			break;


		default:
			cout << "\n\tPlease select a valid option!";
			break;

		}//switch
	}//while loop
}// main()