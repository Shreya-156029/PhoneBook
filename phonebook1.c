#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct pbentry
{
    char lastname[50];
    char firstname[50];
    char phone[15];
    char email[26];
} Entry;


struct tree_node {
    Entry data;
    struct tree_node *left;
    struct tree_node *right;
};

/*Necessary functions.*/
struct tree_node * insert(struct tree_node *p ,Entry e);
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e);
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]);
struct tree_node * findminval(struct tree_node *p);

void search_node(struct tree_node *p, char l[], char f[]);
void print_tree(struct tree_node *p);

int main(void)
{
    int option = 0;
    int len=0;
    Entry e;
    struct tree_node *p = NULL;
    char ln[16];
    char fn[11];
    int i,j;


    while (1)
        {

        printf("MENU\n");
        printf("1. Add\n");
        printf("2. Delete\n");

        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Quit\n");

        printf("\nPlease select an option: ");
        scanf("%d", &option);

        switch(option)
         {
         case 1:

             printf("Enter The First Name: ");
            scanf("%s", &e.firstname);
            printf("Enter The Last Name: ");
            scanf("%s", &e.lastname);

            printf("Enter The Phone Number: ");
            scanf("%s", &e.phone);
            len=strlen(e.phone);
            if(len!=10)
            {
                printf(" Please Enter 10 digit no\n");

            }
            printf("Enter The Phone number: ");
            scanf("%s", &e.phone);
            printf("Enter The e-mail address: ");
            scanf("%s", &e.email);
            for(i=0,j=0;e.email[i]!='\0';i++)
            {
                if(e.email[i]='@' )
             {
                j=j+1;

              }
            }
                if(j!=1)
                printf("Not valid e-mail...please enter again\n");
                printf("Enter The e-mail address: ");
                scanf("%s", &e.email);


                p = insert(p, e);

            printf("Record added successfully.\n\n");
            break;

         case 2:


            printf("Please enter the last name: ");
            scanf("%s", &ln);
            printf("Please enter the first name: ");
            scanf("%s", &fn);

            p = delete_node(p, ln, fn);
            break;

         case 3:



            printf("Please enter the last name: ");
            scanf("%s", &ln);
            printf("Please enter the first name: ");
            scanf("%s", &fn);

            search_node(p, ln, fn);
            break;

         case 4:

            print_tree(p);
            break;
         case 5:
                exit(0);
         default:
            printf(" Please try again...\n\n");
        }

    }
    return 0;
}


struct tree_node * insert(struct tree_node *root, Entry e) {

    if (root == NULL) {

        root = create_node(NULL, NULL, e);
    }

    else if (strcmp(e.lastname, root->data.lastname) < 0) {

        root->left = insert(root->left, e);
    }

    else if (strcmp(e.lastname, root->data.lastname) > 0) {

        root->right = insert(root->right, e);
    }

    else {

        if (strcmp(e.firstname, root->data.firstname) < 0) {

            root->left = insert(root->left, e);
        }

        else if (strcmp(e.firstname, root->data.firstname) > 0) {

            root->right = insert(root->right, e);
        }

        else {

            return root;
        }
    }

    return root;
}


struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e) {
    struct tree_node* newnode;
    newnode = (struct tree_node*)(malloc(sizeof(struct tree_node)));
    newnode->data = e;
    newnode->left = q;
    newnode->right = r;
    return newnode;
}


struct tree_node * delete_node (struct tree_node *root, char l[], char f[]) {

    if(root==NULL)
    {

        printf("\nNo record to delete..");
        return;
    }

    if (strcmp(l, root->data.lastname) < 0 || strcmp(f, root->data.firstname) != 0) {

        root->left = delete_node(root->left, l, f);
    }

     if (strcmp(l, root->data.lastname) > 0 || strcmp(f, root->data.firstname) != 0) {

        root->right = delete_node(root->right, l, f);
    }
 //for node having 2 children
    if (root->left != NULL && root->right != NULL) {

        root->data = findminval(root->right)->data;  //copy value of inorder successor
        root->right = delete_node(root->right, l, f);//delete node

        printf("Record deleted successfully.\n\n");
    }
//if left subtree is not empty
     if (root->left != NULL) {

        root = root->left;

        printf("Record deleted successfully.\n\n");
    }
//if right subtree not empty
    if (root->right != NULL) {

        root = root->right;

        printf("Record deleted successfully.\n\n");
    }



    return root;
}


struct tree_node * findminval(struct tree_node *p) {


   if (p->left != NULL) {

        findminval(p->left);
    }

    return p;
}

void search_node(struct tree_node *p, char l[], char f[]) {

    if (strcmp(l, p->data.lastname) < 0) {

        search_node(p->left, l, f);
    }

    else if (strcmp(l, p->data.lastname) > 0) {

        search_node(p->right, l, f);
    }

    else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) != 0) {

        if (strcmp(f, p->data.firstname) < 0) {

            search_node(p->left, l, f);
        }

        if (strcmp(f, p->data.firstname) > 0) {

            search_node(p->right, l, f);
        }
    }

    else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) == 0) {

        printf("%s  %s  %s  %s\n\n", p->data.lastname , p->data.firstname , p->data.phone , p->data.email);
    }

    else {

        printf("Record could not be foundN.\n\n");
       }
}

void print_tree(struct tree_node *p)
{

    if (p != NULL) {

        print_tree(p->left);
        printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone, p->data.email);
        print_tree(p->right);
    }
}
