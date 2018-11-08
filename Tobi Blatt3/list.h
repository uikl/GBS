struct list_elem{
    pid_t pid;
    struct list_elem *next;
};

typedef struct list{
    struct list_elem *first;
} list_t;

void list_removeFirst(list_t *list);
void list_insert(list_t *list,pid_t pid);
list_t *list_init();
void list_finit(list_t *list);