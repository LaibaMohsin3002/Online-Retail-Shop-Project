#include <iostream>
#include <conio.h>
using namespace std;
#define V 6
int INF = 1e9 + 10;
string addressF;

class Shop;

class TakeAwayOrders {
public:

	double bill;
	int productID; //the number to access product
	string name;
	string product;
	int quantity;
	int height;
	int orderId;  //to maintain order in tree
	Shop* st;

	TakeAwayOrders* left;
	TakeAwayOrders* next;
	TakeAwayOrders* right;

	TakeAwayOrders();
	TakeAwayOrders(string n, int q, int ID, Shop* s);
	void billing();
};

class HomeDeliveryNode {
public:

	double bill;
	int productID; //the number to access product
	string name;
	string product;
	int quantity;
	int height;
	int orderId;  //searching
	Shop* st;

	HomeDeliveryNode();
	HomeDeliveryNode(string n, int q, int ID, Shop* s);
};

class DeliveryOrders {      // home delivery
public:
	HomeDeliveryNode delivery;
	string address;
	double deliveryCharges;
	int deliveryDistance;
	int priority;

	DeliveryOrders();

	DeliveryOrders(string name, int quantity, int productID, Shop* s, string add, double charges, int distance, int bill, int p);
};

class HomeDeliveryHeap {     // min heap for home delivery
public:

	int count;
	int size;
	DeliveryOrders** deliveries;

	HomeDeliveryHeap() {
		deliveries = new DeliveryOrders * [20]{ NULL };
		count = 0;
		size = 20;
	}

	void insert(DeliveryOrders*& d) { //send address
		if (count == size)
			cout << "Delivery limit reached. Please try again later." << endl;

		else {
			count++;
			deliveries[count - 1] = d;
			heapify_up(count - 1);
		}
	}

	DeliveryOrders* remove() {
		DeliveryOrders* temp = deliveries[0];
		deliveries[0] = deliveries[count - 1];
		deliveries[count - 1] = NULL;
		count--;
		heapify_down(0);
		return temp;
	}

	void heapify_up(int i) {
		int parent = (i - 1) / 2;

		if (parent >= 0) {
			if (deliveries[i]->priority < deliveries[parent]->priority) {
				DeliveryOrders* temp = deliveries[i];
				deliveries[i] = deliveries[parent];
				deliveries[parent] = temp;

				heapify_up(parent);
			}
		}
	}

	void heapify_down(int i) {
		int smallest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < count && deliveries[left] != NULL && deliveries[left]->priority < deliveries[smallest]->priority) {
			smallest = left;
		}

		if (right < count && deliveries[right] != NULL && deliveries[right]->priority < deliveries[smallest]->priority) {
			smallest = right;
		}

		if (smallest != i) {
			DeliveryOrders* temp = deliveries[i];
			deliveries[i] = deliveries[smallest];
			deliveries[smallest] = temp;
			heapify_down(smallest);
		}
	}
};

class HashTable {
public:
	DeliveryOrders** Hasharray;
	int size;
	bool checkforEmpty = false;

	HashTable() {
		this->size = 20;

		Hasharray = new DeliveryOrders * [size];

		for (int i = 0; i < size; i++) {
			Hasharray[i] = NULL;
		}
	}

	void insert(DeliveryOrders* value) {
		int Hashkey = hashFunction(value->delivery.orderId);

		if (Hasharray[Hashkey] == NULL) {
			Hasharray[Hashkey] = value;
			checkforEmpty = true;
		}
	}

	void search(int orderID) {
		int hashkey = hashFunction(orderID);

		if (Hasharray[hashkey] != NULL && Hasharray[hashkey]->delivery.orderId == orderID) {
			cout << "********* Your order is yet to be delivered **********" << endl << endl;

			cout << "\n***************Order Details***************";
			cout << "\n Customer Name : " << Hasharray[hashkey]->delivery.name << "\n Order name : " << Hasharray[hashkey]->delivery.product << "\n Order ID : " << Hasharray[hashkey]->delivery.orderId << "\n Quantity : " << Hasharray[hashkey]->delivery.quantity << "\n Total bill : " << Hasharray[hashkey]->delivery.bill;
			cout << "\n Address : " << Hasharray[hashkey]->address << "\n Distance in km : " << Hasharray[hashkey]->deliveryDistance << "\n Delivery charges : " << Hasharray[hashkey]->deliveryCharges << endl;

		}

		else {
			cout << "******* No such order found! *******" << endl << endl;
		}
	}

	bool isEmpty() {
		if (checkforEmpty == true) {
			return false;
		}

		else
			return true;
	}

	void delete_val(int val) {
		int hashkey = hashFunction(val);

		if (Hasharray[hashkey] != NULL && Hasharray[hashkey]->delivery.orderId == val) {
			Hasharray[hashkey] = NULL;
		}
	}

	int hashFunction(int val) {
		return val % size;
	}
};


class Shop {
public:

	string name;
	string* product;
	int* price;
	string address;
	HomeDeliveryHeap homedeliveryqueue;     // min heap for home deliveries
	HashTable DeliveryOrderSearching;  

	Shop(string name, string* product, int* price, string address) {
		this->name = name;
		this->product = product;
		this->price = price;
		this->address = address;
	}

	void display_products() {
		cout << "\n------------------------------------------------------------------------";
		cout << "\n | ITEM NO. |             ITEM LIST                      |ORIGINAL PRICE|";
		cout << "\n------------------------------------------------------------------------";
		cout << "\n |    1     |\t      " << product[0] << "             |   " << price[0] << "   |";
		cout << "\n |    2     |\t      " << product[1] << "         |   " << price[1] << "   |";
		cout << "\n |    3     |\t      " << product[2] << "        |   " << price[2] << "   |";
		cout << "\n |    4     |\t      " << product[3] << "           |   " << price[3] << "   |";
		cout << "\n |    5     |\t      " << product[4] << "                  |   " << price[4] << "   |";
		cout << "\n |    6     |\t      " << product[5] << "            |   " << price[5] << "   |";
		cout << "\n |    7     |\t      " << product[6] << "              |   " << price[6] << "   |";
		cout << "\n |    8     |\t      " << product[7] << "       |   " << price[7] << "   |";
		cout << "\n |    9     |\t      " << product[8] << "                  |   " << price[8] << "   |";
		cout << "\n |    10    |\t      " << product[9] << "               |   " << price[9] << "   |";

		cout << "\n-------------------------------------------------------------------------" << endl;
	}
};




TakeAwayOrders::TakeAwayOrders() {}

TakeAwayOrders::TakeAwayOrders(string n, int q, int ID, Shop* s) { //send address of shop object
	static int id = 1;
	name = n;
	product = s->product[ID];
	quantity = q;
	productID = ID;
	orderId = id++;
	st = s;
	right = NULL;
	left = NULL;
	next = NULL;
}

void TakeAwayOrders::billing() {
	bill = quantity * (st->price[productID]);
}


HomeDeliveryNode::HomeDeliveryNode() {}

HomeDeliveryNode::HomeDeliveryNode(string n, int q, int ID, Shop* s) { //send address of shop object
	static int id = 1;
	name = n;
	product = s->product[ID];
	quantity = q;
	productID = ID;
	orderId = id++;
	st = s;
}


DeliveryOrders::DeliveryOrders() {}

DeliveryOrders::DeliveryOrders(string name, int quantity, int productID, Shop* s, string add, double charges, int distance, int bill, int p) {
	HomeDeliveryNode o(name, quantity, productID, s);
	delivery = o;
	address = add;
	deliveryCharges = charges;
	deliveryDistance = distance;
	priority = p;
	delivery.bill = bill;
}

DeliveryOrders* deliveryCustomer;

void placeOrderHomeDeliveryCustomer(string name, int quantity, int productID, Shop* s, string address, int deliveryCharges, int distanceDelivery, int bill)
{
	static int priority = 0;
	priority++;

	char option;

	cout << "Would you like to place an urgent order? Press [Y] for urgent, else press [N]: ";
	cin >> option;

	while (option != 'Y' && option != 'N') {
		cout << "Invalid option entered. Enter a valid option: ";
		cin >> option;
	}



	if (option == 'Y') {
		cout << endl << "*****  Extra Charges for urgent delivery: Rs. 500  *****" << endl;
		bill += 500;
		deliveryCharges += 500;
		deliveryCustomer = new DeliveryOrders(name, quantity, productID, s, address, deliveryCharges, distanceDelivery, bill, 0);
	}

	else {
		deliveryCustomer = new DeliveryOrders(name, quantity, productID, s, address, deliveryCharges, distanceDelivery, bill, priority);
	}

	s->homedeliveryqueue.insert(deliveryCustomer);
	s->DeliveryOrderSearching.insert(deliveryCustomer);

	cout << "\n------------------------------------------------------\n";
	cout << "\n***************Order Details***************";
	cout << "\n------------------------------------------------------\n";
	cout << "\n Customer Name : " << name << "\n Order name : " << s->product[productID] << "\n Quantity : " << quantity << "\n Total bill : " << deliveryCustomer->delivery.bill;
	cout << "\n Address : " << address << "\n Distance in km : " << distanceDelivery << "\n Delivery charges : " << deliveryCharges << endl;
}

void StartDeliveries(Shop* s) {     // start delivery

	if (s->homedeliveryqueue.deliveries[0] == NULL) {
		cout << "No home delivery orders placed yet!" << endl;
	}

	else {

		int counter = s->homedeliveryqueue.count;

		for (int i = 0; i < counter; i++) {
			DeliveryOrders* p = s->homedeliveryqueue.remove();
			s->DeliveryOrderSearching.delete_val(p->delivery.orderId);

			cout << "\n------------------------------------------------------";
			cout << "\n***************  Delivery Complete!  ***************";
			cout << "\n------------------------------------------------------\n";
			cout << "\n Customer Name : " << p->delivery.name << "\n Order name : " << p->delivery.product << "\n Order ID : " << p->delivery.orderId << "\n Quantity : " << p->delivery.quantity << "\n Total bill : " << p->delivery.bill;
			cout << "\n Address : " << p->address << "\n Distance in km : " << p->deliveryDistance << "\n Delivery charges : " << p->deliveryCharges << endl;
			cout << "------------------------------------------------------\n";
		}

		s->DeliveryOrderSearching.checkforEmpty = false;     // when check for empty flag is true , means orders otherwise no orders
	}
}


void displayAllOrdersHomeDeliveryCustomers(Shop* s)
{
	if (s->homedeliveryqueue.count == 0)
	{
		cout << "There is no Order for Home Delivery Customer till yet" << endl;
	}

	else {

		int n = s->homedeliveryqueue.count;

		for (int i = 0; i < n; i++) {
			cout << "\n------------------------------------------------------\n";
			cout << "-----------------------------------------------------" << endl;
			cout << "Home Delivery Customer : " << s->homedeliveryqueue.deliveries[i]->delivery.name << endl;
			cout << "Product Name : " << s->homedeliveryqueue.deliveries[i]->delivery.product << endl;
			cout << "Quantity : " << s->homedeliveryqueue.deliveries[i]->delivery.quantity << endl;
			cout << "Delivery Distance : " << s->homedeliveryqueue.deliveries[i]->deliveryDistance << "KM" << endl;
			cout << "Delivery Charges : " << s->homedeliveryqueue.deliveries[i]->deliveryCharges << endl;
			cout << "Bill : " << s->homedeliveryqueue.deliveries[i]->delivery.bill << " RS/_" << endl;
			cout << "Delivery Address : " << s->homedeliveryqueue.deliveries[i]->address << endl;
			//cout << "Priority: " << s->homedeliveryqueue.deliveries[i]->priority << endl;
			cout << "-----------------------------------------------------" << endl;
			cout << "\n------------------------------------------------------\n";
		}
	}


}


class AVLTreeforOrders {
public:
	TakeAwayOrders* root;

	AVLTreeforOrders() {
		root = NULL;
	}

	AVLTreeforOrders(TakeAwayOrders* n) {
		root = n;
	}

	int max(int a, int b) {
		if (a > b)return a;
		else return b;
	}


	int height(TakeAwayOrders* root) {
		if (root == NULL)
			return -1;
		else {
			int leftH = height(root->left);
			int rightH = height(root->right);

			return (1 + max(leftH, rightH));
		}
	}



	TakeAwayOrders* rightRotate(TakeAwayOrders* y)
	{
		TakeAwayOrders* x = y->left;
		TakeAwayOrders* T2 = x->right;

		// Perform rotation 
		x->right = y;
		y->left = T2;

		// Update heights 
		y->height = max(height(y->left),
			height(y->right)) + 1;
		x->height = max(height(x->left),
			height(x->right)) + 1;

		// Return new root 
		return x;
	}
	TakeAwayOrders* leftRotate(TakeAwayOrders* x)
	{
		TakeAwayOrders* y = x->right;
		TakeAwayOrders* T2 = y->left;

		// Perform rotation 
		y->left = x;
		x->right = T2;

		// Update heights 
		x->height = max(height(x->left),
			height(x->right)) + 1;
		y->height = max(height(y->left),
			height(y->right)) + 1;

		// Return new root 
		return y;
	}

	// Get Balance factor of TakeAwayOrders N 
	int getBalance(TakeAwayOrders* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) -
			height(N->right);
	}

	TakeAwayOrders* search(TakeAwayOrders*& root, int id)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else if (root->orderId == id)
		{
			return root;
		}
		else if (root->orderId < id)
		{
			return search(root->right, id);
		}
		else
		{
			return search(root->left, id);
		}
	}

	TakeAwayOrders* insert(TakeAwayOrders*& root, TakeAwayOrders* newNode)
	{

	
		if (root == NULL)
			return newNode;

		if (newNode->orderId < root->orderId)
			root->left = insert(root->left, newNode);
		else if (newNode->orderId > root->orderId)
			root->right = insert(root->right, newNode);
		else 
			return root;

		
		root->height = 1 + max(height(root->left),
			height(root->right));
		int balance = getBalance(root);
		// Left Left Case 
		if (balance > 1 && newNode->orderId < root->left->orderId)
			return rightRotate(root);
		// Right Right Case 
		if (balance < -1 && newNode->orderId > root->right->orderId)
			return leftRotate(root);
		// Left Right Case 
		if (balance > 1 && newNode->orderId > root->left->orderId)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		// Right Left Case 
		if (balance < -1 && newNode->orderId < root->right->orderId)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}

    // predecessor
	TakeAwayOrders* minValueOrders(TakeAwayOrders* Order)
	{
		TakeAwayOrders* current = Order;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}
	TakeAwayOrders* deleteOrders(TakeAwayOrders* root, int orderId)
	{

		if (root == NULL)
			return root;

		if (orderId < root->orderId)
			root->left = deleteOrders(root->left, orderId);

		else if (orderId > root->orderId)
			root->right = deleteOrders(root->right, orderId);

		else
		{
			// Orders with only one child or no child 
			if ((root->left == NULL) ||
				(root->right == NULL))
			{
				TakeAwayOrders* temp = root->left ?root->left :root->right;

				// No child case 
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // One child case 
					*root = *temp;

				delete(temp);
			}
			else
			{
				TakeAwayOrders* temp = minValueOrders(root->right);
				root->orderId = temp->orderId;
                root->name = temp->name;
                root->bill = temp->bill;
                root->product = temp->product;
                root->productID = temp->productID;
                root->quantity = temp->quantity;
				// Delete the inorder successor 
				root->right = deleteOrders(root->right,temp->orderId);
			}
		}

		if (root == NULL)
			return root;

		root->height = 1 + max(height(root->left), height(root->right));

		int balance = getBalance(root);

		if (balance > 1 && getBalance(root->left) >= 0)
			return rightRotate(root);

		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if (balance < -1 && getBalance(root->right) <= 0)
			return leftRotate(root);

		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	void display(TakeAwayOrders*& root)
	{
		cout << "\n----------------------------------" << endl;
		cout << "Name :" << root->name << endl;
		cout << "Product :" << root->product << endl;
		cout << "Quantity : " << root->quantity << endl;
		cout << "Bill : " << root->bill << endl;
		cout << "Order ID: " << root->orderId << endl;
		cout << "-----------------------------------\n" << endl;
	}

	void preOrder(TakeAwayOrders*& root)
	{
		if (this->root == NULL) {
			cout << "********** No Takeaway Orders currently **********" << endl;
		}

		else
		{
			display(root);
			if (root->left)
				preOrder(root->left);

			if (root->right)
				preOrder(root->right);
		}
	}

};

int DeliveryChoice = -1;
int DeliveryChoice1 = -1;
int* distanceP = new int[6];
int* dist = new int[6];     // for cities dijkstra
string CityName[] = { "Karachi", "Islamabad", "Lahore", "Multan", "Faisalabad", "Abbotabad" };

string Multan[] = { "Multan", "Fort Kohna Qasim Garden", "eid Ghah", "Garrison Public Library", "Bosan Town", "Sher Shah Town" };

string Abbotabad[] = { "Abbotabad", "Jinnahabad", "PMA", "Mandian", "Ayub Medical College", "Fawara Chowk" };

string Islamabad[] = { "Islamabad", "I-8" ,"Askari-14", "F-10", "F-7", "H-12" };

string Lahore[] = { "Lahore", "Johar Town", "Garden Town", "DHA", "Model Town", "Gulberg" };

string Karachi[] = { "karachi", "Bahria Town", "North Nazimabad", "Defence", "Clifton", "Liyari" };

string Faisalabad[] = { "Faisalabad", "Citi Housing Society", "Satiana Road" , "Wapda City" , "FDA City" , "Canal Road" };

int graph[V][V] = { {0, 4, 0, 0, 6, 1},   //Karachi
					{4, 0, 3, 8, 0, 0},	 //Islamabad
					{0, 3, 0, 2, 9, 4},	 //Lahore
					{0, 8, 2, 0, 1, 4},	 //multan
					{6, 0, 9, 1, 0, 8}, //Faisalabad	
					{1, 6, 0, 4, 8, 0} };	 //Abbotabad 

//----------------------Abbotabad--------------------------------				
int AtdGraph[V][V] = { { 0, 4, 4, 0, 0, 0 },
						{ 4, 0, 2, 0, 0, 0 }, //Jinnahabad
						{ 4, 2, 0, 3, 2, 4 },	//PMA
						{ 0, 0, 3, 0, 0, 3 },	//Mandian
						{ 0, 0, 2, 0, 0, 3 },	//Ayub
						{ 0, 0, 4, 3, 3, 0 } };	//Fawara

//---------------------Islamabad------------------------------------
int IsbGraph[V][V] = { { 0, 4, 0, 2, 0, 0 },
						{ 4, 0, 3, 1, 0, 6 },	//I-8
						{ 0, 3, 0, 4, 0, 7 },	//Askari
						{ 2, 1, 4, 0, 9, 0 },	//F-10
						{ 0, 0, 0, 9, 0, 5 },	//F-7
						{ 0, 6, 7, 0, 5, 0 } };	//H-12

//-----------------------Lahore---------------------------------------
int LhrGraph[V][V] = { { 0, 9, 15, 6, 0, 0 },
						{ 9, 0, 7, 0, 0, 8 },
						{ 15, 7, 0, 8, 9, 5 },
						{ 6, 0, 8, 0, 11, 0 },
						{ 0, 0, 9, 11, 0, 4 },
						{ 0, 8, 5,  0, 4, 0 } };

//----------------------Karachi----------------------------------------
int KarGraph[V][V] = { { 0, 6, 3, 0, 0, 1 },
						{ 6, 0, 0, 2, 0, 5 },	//Bahria Town
						{ 3, 0, 0, 0, 3, 5 },	//North Nazimabad
						{ 0, 2, 0, 0, 6, 4 },	//Defence
						{ 0, 0, 3, 6, 0, 6 },	//Clifton
						{ 1, 5, 5, 4, 6, 0 } };	//Liyari

//----------------------------------------------------------------------------------

//----------------------Faisalabad----------------------------------------
int FsdGraph[V][V] = { { 0, 2, 3, 0, 7, 1 },
						{ 2, 0, 4, 2, 0, 8 },	//Citi Housing Society
						{ 3, 4, 0, 5, 3, 0 },	//Satiana Road
						{ 0, 2, 5, 0, 6, 5 },	//Wapda City
						{ 7, 0, 3, 6, 0, 6 },	//FDA City
						{ 1, 8, 0, 5, 6, 0 } };	//Canal Road

//----------------------------------------------------------------------------------

//----------------------Multan----------------------------------------
int MulGraph[V][V] = { { 0, 0, 1, 5, 3, 1 },
						{ 0, 0, 2, 7, 0, 8 },	//Fort Kohna Qasim Garden
						{ 1, 2, 0, 5, 5, 0 },	//Satiana Road
						{ 5, 7, 5, 0, 6, 1 },	//Wapda City
						{ 3, 0, 5, 6, 0, 3 },	//FDA City
						{ 1, 8, 0, 1, 3, 0 } };	//Canal Road


class Edge {
public:
	int data;
	int weight;
	bool visited;
	Edge() : data(0), weight(0), visited(false) {}
	Edge(int data, int weight) : data(data), weight(weight), visited(false) {}
};
class MinHeapforDijkstra {
public:
    int count;
    int size;
    Edge** edges;

    MinHeapforDijkstra(int maxSize) : count(0), size(maxSize) {
        edges = new Edge*[size];
        for (int i = 0; i < size; ++i) {
            edges[i] = NULL;
        }
    }

    void insert(int data, int weight) {

            edges[count] = new Edge(data, weight);
            count++;
            heapify_up(count - 1);
       
    }

    int remove() {
        if (count <= 0) {
            cout << "Heap is empty." << endl;
            return -1; 
        }
        Edge* temp = edges[0];
        edges[0] = edges[count - 1];
        edges[count - 1] = NULL;
        count--;
        heapify_down(0);
        int data = temp->data;
        delete temp;
        return data;
    }

    void heapify_up(int i) {
        int parent = (i - 1) / 2;
        if (parent >= 0 && edges[i] != NULL && edges[parent] != NULL &&
            edges[i]->weight < edges[parent]->weight) {
            swap(edges[i], edges[parent]);
            heapify_up(parent);
        }
    }

    void heapify_down(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < count && edges[left] != NULL &&
            edges[left]->weight < edges[smallest]->weight) {
            smallest = left;
        }

        if (right < count && edges[right] != NULL &&
            edges[right]->weight < edges[smallest]->weight) {
            smallest = right;
        }

        if (smallest != i) {
            swap(edges[i], edges[smallest]);
            heapify_down(smallest);
        }
    }

    bool isEmpty() {
        return count == 0;
    }

    ~MinHeapforDijkstra() {
        for (int i = 0; i < count; ++i) {
            delete edges[i];
        }
        delete[] edges;
    }
};

int* dijkstra(int start, int graph[][V], string g[])
{
	bool visited[V] = { false };
	int* distance = new int[6];

	for (int i = 0; i < V; ++i) {
		distance[i] = INF; // Set initial distances to infinity
	}
	distance[start - 1] = 0; // Distance to the start vertex is 0

	MinHeapforDijkstra heap(V);
	heap.insert(start - 1, 0);

	while (!heap.isEmpty())
	{
		int u = heap.remove();
		
		visited[u] = true;

		for (int v = 0; v < V; ++v)
		{
			if (graph[u][v] != 0 && !visited[v])
			{
				int alt = distance[u] + graph[u][v];
				if (alt < distance[v])
				{
					distance[v] = alt;
                	heap.insert(v, alt);             
				}
			}
		}
	}

	// Output the calculated distances
	cout << "Shortest distances from " << g[0] << ":\n";
	for (int i = 1; i < V; ++i)
	{
		cout << g[i] << " :      " << distance[i] << "km " << endl;
	}
	return distance;
}




int city() {
	int opt;
	cout << "\nThe delivery is available for following Areas : \n" << endl;

	cout << "\n --------------------------------";
	cout << "\n |CITY CODE |        City       |";
	cout << "\n --------------------------------";
	cout << "\n |     1    |    Karachi        |" << endl;
	cout << "\n |     2    |    Islamabad      |" << endl;
	cout << "\n |     3    |    Lahore         |" << endl;
	cout << "\n |     4    |    Multan         |" << endl;
	cout << "\n |     5    |    Faisalabad     |" << endl;
	cout << "\n |     6    |    Abbotabad      |" << endl;
	cout << "---------------------------------\n" << endl;


	dist = dijkstra(1, graph, CityName);
	cout << "Enter your option :" << endl;
	cin >> opt;
	return opt;
}

//string Multan[] = { "Multan", "Fort Kohna Qasim Garden", "eid Ghah", "Garrison Public Library", "Bosan Town", "Sher Shah Town" };
int Mul() {
	int opt;
	cout << "\nThe delivery is available for following Areas in Multan: " << endl;

	cout << "\n---------------------------------------------";
	cout << "\n |CITY CODE |        AREA                   |";
	cout << "\n---------------------------------------------";
	cout << "\n |     1    |    Fort Kohna Qasim Garden    |" << endl;
	cout << "\n |     2    |    Eid Ghah                   |" << endl;
	cout << "\n |     3    |    Garrison Public Library    |" << endl;
	cout << "\n |     4    |    Bosan Town                 |" << endl;
	cout << "\n |     5    |    Sher Shah Town             |" << endl;
	cout << "-----------------------------------------------\n\n" << endl;

	distanceP = dijkstra(1, MulGraph, Multan);
	cout << "\nEnter your option :" << endl;
	cin >> opt;
	return opt;

}


int isb() {
	int opt;
	cout << "\nThe delivery is available for following Areas in Islamabad: " << endl;

	cout << "\n---------------------------------";
	cout << "\n |CITY CODE |        AREA       |";
	cout << "\n---------------------------------";
	cout << "\n |     1    |    I-8            |" << endl;
	cout << "\n |     2    |    Askari-14      |" << endl;
	cout << "\n |     3    |    F-10           |" << endl;
	cout << "\n |     4    |    F-7            |" << endl;
	cout << "\n |     5    |    H-12           |" << endl;
	cout << "---------------------------------\n\n" << endl;


	distanceP = dijkstra(1, IsbGraph, Islamabad);

	cout << "\nEnter your option :" << endl;
	cin >> opt;
	return opt;

}

int Atd() {
	int opt;
	cout << "\nThe delivery is available for following Areas in Abbotabad: " << endl;

	cout << "\n---------------------------------";
	cout << "\n |CITY CODE |        AREA       |";
	cout << "\n---------------------------------";
	cout << "\n |     1    |    Jinnahabad     |" << endl;
	cout << "\n |     2    |    PMA            |" << endl;
	cout << "\n |     3    |    Mandian        |" << endl;
	cout << "\n |     4    |    Ayub Medical   |" << endl;
	cout << "\n |     5    |    Fawara Chowk   |" << endl;
	cout << "---------------------------------\n\n" << endl;

	distanceP = dijkstra(1, AtdGraph, Abbotabad);

	cout << "\nEnter your option :" << endl;
	cin >> opt;
	return opt;

}

int Lhr() {
	int opt;
	cout << "\nThe delivery is available for following Areas in Lahore: " << endl;

	cout << "\n---------------------------------";
	cout << "\n |CITY CODE |        AREA       |";
	cout << "\n---------------------------------";
	cout << "\n |     1    |    Johar Town     |" << endl;
	cout << "\n |     2    |    Garden Town    |" << endl;
	cout << "\n |     3    |    DHA            |" << endl;
	cout << "\n |     4    |    Model Town     |" << endl;
	cout << "\n |     5    |    Gulberg    |" << endl;
	cout << "---------------------------------\n\n" << endl;

	distanceP = dijkstra(1, LhrGraph, Lahore);

	cout << "\nEnter your option :" << endl;
	cin >> opt;
	return opt;

}

int Kar() {
	int opt;
	cout << "\nThe delivery is available for following Areas in Karachi: " << endl;

	cout << "\n---------------------------------";
	cout << "\n |CITY CODE |        AREA       |";
	cout << "\n---------------------------------";
	cout << "\n |     1    |    Bahria Town    |" << endl;
	cout << "\n |     2    |    North Nazimabad|" << endl;
	cout << "\n |     3    |    Defence        |" << endl;
	cout << "\n |     4    |    Clifton        |" << endl;
	cout << "\n |     5    |    Liyari         |" << endl;
	cout << "---------------------------------\n\n" << endl;

	distanceP = dijkstra(1, KarGraph, Karachi);

	cout << "\nEnter your option :" << endl;
	cin >> opt;
	return opt;

}
int fslabd() {
	int opt;
	cout << "\nThe delivery is available for following Areas in Faisalabad: " << endl;

	cout << "\n----------------------------------------";
	cout << "\n |CITY CODE |            AREA           |";
	cout << "\n----------------------------------------";
	cout << "\n |     1    |    Citi Housing Society   |" << endl;
	cout << "\n |     2    |    Satiana Road           |" << endl;
	cout << "\n |     3    |    Wapda City             |" << endl;
	cout << "\n |     4    |    FDA City               |" << endl;
	cout << "\n |     5    |    Canal Road             |" << endl;
	cout << "-------------------------------------------\n\n" << endl;
	distanceP = dijkstra(1, FsdGraph, Faisalabad);
	cout << "\nEnter your option :" << endl;
	cin >> opt;
	return opt;

}
int FurthurArea(int option) {
	int opt;
	switch (option) {
		//distanceP[6] = { 0 };
	case 0:
	{
		opt = Kar();
		addressF = Karachi[opt];
		break;
	}
	case 1:
	{
		opt = isb();
		addressF = Islamabad[opt];

	}
	break;

	case 2:
	{
		opt = Lhr();
		addressF = Lahore[opt];

	}
	break;

	case 3:
	{
		opt = Mul();
		addressF = Multan[opt];
	}
	break;

	case 4:
	{
		opt = Atd();
		addressF = Abbotabad[opt];
	}
	break;
	case 5:
		opt = fslabd();
		addressF = Faisalabad[opt];
	}

	return opt;
}



int main() {

	string Products[12] = { "Elegant Leather Clutch" ,"Floral Print Crossbody Bag", "Quilted Chain Strap Handbag", "Vintage Inspired Satchel", "Suede Ankle Boots" ,"Slip On Canvas Sneakers", "Durable Travel Duffel" ,"Trendy Belt Bag / Fanny Pack", "Floral Maxi Dress" ,"Slim fit Denim Jeans" ,"Cozy Knit Sweater", "Linen Jumpsuit" };
	int prices[12] = { 3500, 2800, 4200, 3000, 5500, 2200, 4800, 1500, 3900, 2600, 2300, 3500 };
	string Name = "ONLINE ECOMMERCE STORE";
	string address = "Fast University Karachi.";
	AVLTreeforOrders order;

	Shop s(Name, Products, prices, address);
	int choice = -1;
	int x = -1;
	do
	{
		string name;
		int quantity;
		string productName;
		int productNumber;
		double bill;
		string address;
		int orderId;
		int distance;
		TakeAwayOrders* o;
		system("cls");
		cout << endl;
		cout << "----------------------------------------------------------------------------\n";
		cout << "************************  " << s.name << "  ************************" << endl;
		cout << "----------------------------------------------------------------------------\n\n";
		cout << "Location : " << s.address << endl;
		cout << endl;

		system("cls");
		cout << "Enter 1 for admin options.\n";
		cout << "Enter 2 for User options.\n";
		cout << "Enter 3 for exit.\n";

		cin >> x;
		
		cout << "\nPress any key to continue ....\n";
		char c = getch();
		if (x == 1)
		{
			
			system("cls");
			cout << endl;
			cout << "----------------------------------------------------------------------------\n";
			cout << "***************************    ADMIN  MENU    ****************************" << endl;
			cout << "----------------------------------------------------------------------------\n";
			cout << endl;

			cout << "1. Display the product and prices" << endl;
			cout << "2. Start Home Deliveries" << endl;
			cout << "3. Display all Delivery Orders" << endl;
			cout << "4. Display all Take-Away Orders" << endl;
			cout << "5.  EXIT " << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			while (choice < 1 || choice>5) {
				cout << "Wrong option entered. Entered a valid option: ";
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
			{
				system("cls");
				s.display_products();
				cout << "\nPress any key to continue ....\n";
				char c = getch();
			}
			break;

			case 2:
			{
				system("cls");
				cout << "----------------------------------------------------------------------------\n";
				cout << "*****************         START HOME DELIVERIES           ******************\n";
				cout << "----------------------------------------------------------------------------\n\n";
				StartDeliveries(&s);
				cout << "\nPress any key to continue ....\n";
				char c = getch();
			}
			break;

			case 3:
			{

				system("cls");
				cout << "----------------------------------------------------------------------------\n";
				cout << "*****************         ALL HOME DELIVERY ORDERS        ******************\n";
				cout << "----------------------------------------------------------------------------\n\n";
				displayAllOrdersHomeDeliveryCustomers(&s);
				
				cout << "\nPress any key to continue ....\n";
				char c = getch();
			}
			break;

			case 4:
			{
				system("cls");
				cout << "----------------------------------------------------------------------------\n";
				cout << "*****************         TAKE-AWAY DELIVERY ORDERS        ******************\n";
				cout << "----------------------------------------------------------------------------\n\n";
				order.preOrder(order.root);
				cout << "\nPress any key to continue ....\n";
				char c = getch();
			}
			break;

			case 5:
			{
				break;
			}



			}
		}
		else if (x == 2)
			{
				system("cls");
				cout << endl;
				cout << "----------------------------------------------------------------------------\n";
				cout << "***************************   USER MENU    ****************************" << endl;
				cout << "----------------------------------------------------------------------------\n";
				cout << endl;




				// Order placing
				cout << "1. Display the product and prices" << endl;
				cout << "2. Place order for Take-Away from Warehouse" << endl;
				cout << "3. Place order for Home Delivery " << endl;
				cout << "4. Search Delivery Orders" << endl;
				cout << "5. Get Order from Warehouse" << endl;
				cout << "6.  EXIT " << endl;
				cout << "Enter your choice: ";

				cin >> choice;
				while (choice < 1 || choice>6) {
					cout << "Wrong option entered. Entered a valid option: ";
					cin >> choice;
				}

				switch (choice)
				{
				case 1:
				{

					system("cls");
					s.display_products();
					cout << "\nPress any key to continue ....\n";
					char c = getch();
				}
				break;

				case 2:
				{
					system("cls");
					cout << "----------------------------------------------------------------------------\n";
					cout << "***************** PLACE ORDER FOR TAKE-AWAY FROM WAREHOUSE ******************\n";
					cout << "----------------------------------------------------------------------------\n\n";

					s.display_products();
					cout << "Enter the name of the customer: ";
					cin >> name;
				
					fflush(stdin);
					cout << "Enter the product Number: ";
					cin >> productNumber;
					while (productNumber < 1 || productNumber > 10) {
					cout << "Wrong option entered. Entered a valid option: ";
					cin >> productNumber;
					}
					cout << "Enter the quantity of the product: ";
					cin >> quantity;
					while (quantity <= 0 || quantity > 20) {
					cout << "Wrong option entered. Entered a valid option: ";
					cin >> quantity;
					}
				
					o = new TakeAwayOrders(name, quantity, productNumber - 1, &s);
					o->billing();
					order.root = order.insert(order.root, o);
					cout << "\n------------------------------------" << endl;
					cout << "**** Your order has been placed *****" << endl;
					cout << "Total amount : " << o->bill << endl;
					cout << "Order ID :" << o->orderId << endl;
					cout << "You can get your order from Warehouse " << endl;
					cout << "-------------------------------------\n" << endl;
					cout << "\nPress any key to continue ....\n";
					char c = getch();

				}
				break;
				case 3:
				{
					system("cls");
					cout << "----------------------------------------------------------------------------\n";
					cout << "*****************       PLACE ORDER FOR HOME DELIVERY      ******************\n";
					cout << "----------------------------------------------------------------------------\n\n";

					s.display_products();
					do
					{
						DeliveryChoice = city();   //Return The index of city that has been selected

					} while (!(DeliveryChoice >= 1 && DeliveryChoice <= 6));
					do
					{
						DeliveryChoice1 = FurthurArea(DeliveryChoice-1);  //Return index of area in a city

					} while (!(DeliveryChoice1 > 0 && DeliveryChoice1 <= 5));

					address = CityName[DeliveryChoice -1 ] + " " + addressF;
					distance = dist[DeliveryChoice -1] + distanceP[DeliveryChoice1 ];


					cout << "Enter the name of the customer: ";
					cin >> name;
					cout << "Enter the product Number: ";
					cin >> productNumber;
					while (productNumber < 1 || productNumber > 10) {
					cout << "Wrong option entered. Entered a valid option: ";
					cin >> productNumber;
					}
					cout << "Enter the quantity of the product: ";
					cin >> quantity;
					while (quantity <= 0 || quantity > 20) {
					cout << "Wrong option entered. Entered a valid option: ";
					cin >> quantity;
					}

					int deliveryChargesPerKM = 20;
					int deliveryCharges = deliveryChargesPerKM * distance;
					bill = quantity * s.price[productNumber - 1] + deliveryCharges;


					placeOrderHomeDeliveryCustomer(name, quantity, productNumber - 1, &s, address, deliveryCharges, distance, bill);
					cout<<"Order-Id :" << deliveryCustomer->delivery.orderId;
				
					cout << "\nPress any key to continue ....\n";
					char c = getch();
				}
				break;

				case 4:
				{

					int ID;
					if (!s.DeliveryOrderSearching.isEmpty()) {
						cout << "Please enter your order ID: ";
						cin >> ID;
	
						s.DeliveryOrderSearching.search(ID);        //it search order in hash table 


					}

					else
					cout << "******* No home delivery orders placed! *******" << endl << endl;
					cout << "\nPress any key to continue ....\n";
					char c = getch();
				}
				break;

				case 5:
				{
					// Get Order from Warehouse
					system("cls");
					cout << "----------------------------------------------------------------------------\n";
					cout << "*****************         GET ORDER FROM WAREHOUSE        ******************\n";
					cout << "----------------------------------------------------------------------------\n\n";
					cout << "Enter the Order Id: ";
					cin >> orderId;

					TakeAwayOrders* cust = order.search(order.root, orderId);

					if (cust == NULL) {

						cout << "\n----------------------------------" << endl;
						cout << "No such order is in the Warehouse " << endl;
						cout << "-----------------------------------\n" << endl;
						cout << "\nPress any key to continue ....\n";
						char c = getch();
					}
					else
					{

						order.root = order.deleteOrders(order.root, orderId);
						cout << "\n----------------------------------" << endl;
						cout << "Your order is ready for collection" << endl;
						cout << "  Please get it from the counter" << endl;
						cout << "-----------------------------------\n" << endl;
						cout << "\nPress any key to continue ....\n";
						char c = getch();
					}
				}
				break;
				case 6:
				{
					break;
				}

				}

			}
			else
			{
				while (x < 1 || x>3) {
					cout << "Wrong option entered. Entered a valid option: ";
					cin>>x;
				}

			}
			} while (x != 3);

			system("cls");
			cout << "--------------------------------------------------------------------------------------------------\n";
			cout << "*****************        THANK YOU FOR USING OUR ONLINE SHOPPING SYSTEM        ******************\n";
			cout << "--------------------------------------------------------------------------------------------------\n\n";
			return 0;
	

}



