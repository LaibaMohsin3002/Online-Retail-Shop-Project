# Online Retail Shop Project
 
Data Structure Concepts Used
1. AVL Tree
The AVLTreeforOrders Class is implemented to manage takeaway orders using an AVL tree, ensuring
balance after each insertion or deletion to maintain its height. This AVL tree plays a crucial role in
efficiently handling and organizing takeaway orders for each shop. The tree's balancing mechanism
facilitates quick retrieval and insertion of orders, enhancing the overall efficiency of managing the store's
inventory. Operations such as searching, deletion, and insertion are optimized using the AVL tree, with
the order ID provided by the user serving as a key parameter for insertion and deletion processes.
2. Graphs (for Dijkstra's Algorithms)
Graphs are a key element in our project, visually depicting delivery areas and presented through an
adjacency matrix. To enhance system navigation, we employ Dijkstra's algorithm. This algorithm excels
in determining the shortest path between two nodes, with nodes representing cities and areas in the cities
in our case. We utilize it to calculate distances between cities, optimizing our home delivery routes and
enhancing the efficiency of the delivery process.
3. Linked List
As linked lists allow efficient insertion and deletion of elements, our project employs them to handle
customer details and order information, storing user preferences (Delivery, Take Away) in the linked list.
Linked lists are chosen over arrays due to their dynamic size, providing flexibility in managing and
adapting to varying amounts of data.
1
4. Heaps
A min-heap is used to prioritize home delivery orders based on their urgency. The priority is determined
by the priority attribute of the DeliveryOrders class. The heapify_up and heapify_down functions ensure
that the min-heap properties are maintained during insertion and removal operations. Urgent orders,
indicated by lower priority values, are moved to the front of the heap, ensuring that they are processed
first. This allows for efficient retrieval of the highest-priority order when deliveries are being made.
5. Hash Table
The hash table is used to efficiently store and search home delivery orders based on their order ID. The
insert method is used to insert a new delivery order into the hash table based on its order ID. The search
method is used to search for a delivery order by its order ID. The delete_val method is used to delete a
delivery order from the hash table based on its order ID. The hashFunction method calculates the hash
key based on the order ID and the size of the hash table.
