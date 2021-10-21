
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct
{	int *elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList *L)
{
	L->elem=(int *)malloc(LIST_INIT_SIZE *sizeof(int));
	if (!L->elem) return(0);
	L->length=0;
	L->
	listsize=LIST_INIT_SIZE;
	return(1);
}

void main()
{
    SqList L;
	printf("%s","nitList_Sq.cpp ");
    if(!InitList_Sq(&L))
       printf("Failure to Initialize a Sq_List !");
    else
       printf("Success to Initialize a Sq_List! ");
    getch();
}
