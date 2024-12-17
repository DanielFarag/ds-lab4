#include <iostream>
using namespace std;

// 1- Delete node if it is not root
// 2- find the node with min & max value in binary search tree

class Node {
public:
    int value;
    Node *right;
    Node *left;
    Node(int _value, Node *_right = nullptr, Node *_left = nullptr)
        : value(_value), right(_right), left(_left) {}
};

class BinaryTree{
    Node *head;
    Node *min;
    Node *max;

    /**
     * Get Maxmimum elemnt in right 
     */
    Node *getMaxRight(Node *node) {
        Node *current = node;
        while (current->right != nullptr)
            current = current->right;
        return current;
    }

    /**
     * Get Min element in left
     */
    Node *getMinLeft(Node *node) {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }
    
    
    /**
     * Recursive Method
     */
    Node* deleteNode(Node* current, int x) {
        /**
         * current node null, no node [ bye bye  !! ] 
         * this condtion will be verified if tree is empty [ null head ] or we've reached the end of tree [ stop recursive condition ] 
         */
        if(!current) return NULL;

        /**
         * check if the current node is the targeted node
         */
        if(current->value == x){
           
            /**
             * targeted node doesn't have right, or left [leaf node]
             * get rid of it ya basha !!! no side effect [ delete the node ] and return null as a new subtree to stop recusion
             */
            if(!current->left && !current->right){
                delete current;
                return NULL;
            }


            /**
             * targeted node has right node ONLY
             * so store the right sub tree of the current node in a temp to return it as new sub tree
             * get rid of current
             */
            if(!current->left && current->right){
                Node* temp = current->right; 
                delete current;
                return temp;
            }


            /**
             * targeted node has left node ONLY
             * so store the left sub tree of the current in a temp to return it as sub tree
             * get rid of current
             */
            if(current->left && !current->right){
                Node* temp = current->left;
                delete current;
                return temp;
            }


            /**
             * There are 2 nodes
             * - replace the value if the current with min-left of the right node [ containing for sure number greater than the current and all the elements in the left ;; without breaking the the tree ]
             * - delete the node of the min number
             */
            if(current->left && current->right){
                /**
                 * get smallest value in the current right sub tree
                 * so go to right and then traverse through the left [ min ]
                 */
                int mini = getMinLeft(current->right)->value;

                // replace the value and delete the node
                current->value = mini;

                // Delete the node containing the minimum value and update the right subtree [ right becuase we are modified the right tree ].
                current->right = deleteNode(current->right, mini);

                return current; // sub tree
            }
        }

        /**
         * node not allocated, specify the flow direction [ target < node  got to  left      otherwise    go to right]
         */
        else if(x < current->value){ 
            /**
             * Treat each recusrion as a new stand-alone subtree
             * based on the current, we will specify the attach direction [ left: if the target value is lower than the current node value ]
             */
            current->left = deleteNode(current->left, x);
        }
        else{
            /**
             * Treat each recusrion as a new stand-alone subtree
             * based on the current, we will specify the attach direction [ right: if the target value is greater than the current node value ]
             */
            current->right = deleteNode(current->right, x);
        }

        return current;        
    }

    public:
        BinaryTree(Node *_head = nullptr) : head(_head), min(nullptr), max(nullptr) {}

        int getMin() {
            return getMinLeft(head)->value;
        }

        int getMax() {
            return getMaxRight(head)->value;
        }

        void append(int el){
            Node *newNode = new Node(el);
            if (!head) {
                head = newNode;
                return;
            }
            Node *cursor = head;
            Node *parent = nullptr;

            while (cursor) {
                parent = cursor;
                cursor = (el > cursor->value) ? cursor->right : cursor->left;
            }

            if (el > parent->value){
                parent->right = newNode;
            }
            else{
                parent->left = newNode;
            }

        }

        void insert(int *x, int length) {
            for (int i = 0; i < length; i++)
                append(x[i]);
        }
        
        void display(Node *node) {
            if (node == nullptr) return;
            display(node->left);
            cout << node->value << " ";
            display(node->right);
        }

        void display() {
            display(head);
            cout << endl;
        }


        void remove(int x) {
            deleteNode(head, x);
        }
        
};


int main() {
    BinaryTree *bt = new BinaryTree();

    int x[] = {50, 80, 40, 90, 30, 10, 20, 60, 31};
    int length = sizeof(x) / sizeof(x[0]);

    bt->insert(x, length);
    cout << "Tree after insertion: "<<endl;
    bt->display();

    cout << "Min: " << bt->getMin() << endl;
    cout << "Max: " << bt->getMax() << endl;

    bt->remove(10);
    bt->remove(30);
    cout << "Tree after removing 10, 30: " << endl;
    bt->display();

    /**
                    SAMPLE OUTPUT
                    
    Tree after insertion: 10 20 30 31 40 50 60 80 90 
    Min: 10
    Max: 90
    Tree after removing 50: 10 20 30 31 40 60 80 90 
    */

    return 0;
}

/**
                                                                    50
                                                                   /  \
                                                                 40    80
                                                                /     /  \
                                                              30     60   90
                                                             /  \          
                                                            10   31        
                                                               \
                                                                20
                                                            
*/      


