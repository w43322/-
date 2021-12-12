#ifndef AVLTREE_H
#define AVLTREE_H

#endif // AVLTREE_H

#include <QLabel>
#include <QDebug>

struct AVLNode
{
    struct AVLNode *left,*right;
    int data,height;
    QLabel lab,Llink,Rlink;
};

class AVL
{
private:

public:
    struct AVLNode * root;
    AVL();
    ~AVL();
    int calheight(struct AVLNode *);
    int bf(struct AVLNode *);
    struct AVLNode * llrotation(struct AVLNode *);
    struct AVLNode * lrrotation(struct AVLNode *);
    struct AVLNode * rlrotation(struct AVLNode *);
    struct AVLNode * rrrotation(struct AVLNode *);
    struct AVLNode* insert(struct AVLNode *,int);
    struct AVLNode* deleteAVLNode(struct AVLNode *,int);
    struct AVLNode* inpre(struct AVLNode*);
    struct AVLNode* insuc(struct AVLNode*);
    struct AVLNode* find(struct AVLNode*,int);
};
