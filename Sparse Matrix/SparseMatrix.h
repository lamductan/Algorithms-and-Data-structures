typedef struct node* pnode;
typedef struct node
{
    int value;
    pnode next_node;
    int col;

    node() {next_node = NULL;}
    node(int value, int col):
        value(value), col(col), next_node(NULL) {}
};

typedef struct listNode* plistNode;
struct listNode
{
    int index;
    pnode head_node;
    plistNode next_list;

    listNode() {next_list = NULL;}
    listNode(int index, plistNode next_list = NULL)
        : index(index), next_list(next_list) {}
};

void delList(plistNode& head);

pnode newNode(pnode& prevNode, int value, int col);

class SparseMatrix
{
private:
    int nRows;
    int nCols;
    plistNode head_row;

public:
    SparseMatrix();
    SparseMatrix(int, int, int**);
//    pnode node_at(int, int);
//    pnode insert(int, int, int);
//    pnode del(int, int);
    void printMatrix();
    SparseMatrix* operator+(SparseMatrix);
    ~SparseMatrix();
};
