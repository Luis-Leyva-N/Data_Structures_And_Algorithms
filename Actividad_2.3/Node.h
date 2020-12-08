//Estrcutura de datos para la linked list y la queue
struct Node{
    Node();
    Node(Node *next, Node *prev);
    string mes;
    int dia, seg, min, hora;
    string tiempo;
    string ip;
    string event;
    long long int ordenFecha;
    Node *next;
    Node *prev;
};

Node::Node(){
    this -> next = nullptr;
    this -> prev = nullptr;
}