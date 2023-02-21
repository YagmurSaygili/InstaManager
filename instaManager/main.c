/* Creator : Yağmur Saygılı / School Assigment */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Node
{
    int uniqueID;
    char accountName[40];
    int noPosts;
    int noFollowing;
    int noFollowers;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    struct Node *next;
};
struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct ListRecord *List;

List CreateList();

void MakeEmptyList(List l);

List initialiseMyAccount(char str[]); // This function reads the following/followers files and store them in linked lists

void addAccount(List l, char name[], int noPosts, int noFollowing, int noFollowers); // Takes either follower or following lists , asks the user details about the account and add the account to the list

void printMyAccount(List l); // Prints the list elements with starting from head and in the following content

void searchAccount(List l, char name[]);

void deleteAccount(List l, int uniqueID); // Deleting a node from linked list using its unique ID

void OverwriteMyAccount(char filename[], List l); // Writes the structure data to the files, overwrites them

// TODO: Menu can be seperated from main


// TODO: Menu can be seperated from main

int main()
{
    char name[30];
    int noPosts, noFollowers, noFollowing, option, accountoption; // Account option indicates whether a user wants to add a new account to followers or following
    // Option variable just decides what to choose in general menu
    int check = 1, uniqueID;
    List listfollowers, listfollowing, temp;
    char following[] = "following.txt";
    char followers[] = "followers.txt";
    listfollowers = initialiseMyAccount(followers);
    listfollowing = initialiseMyAccount(following);
    printf("\nThe following.txt file has been loaded successfully");
    printf("\nThe followers.txt file has been loaded successfully\n\n");
    do
    {
        printf("---- MENU ----");
        printf("\n1. Add a new Account\n2. Print My Account Info\n3. Search Account\n4. Delete Account\n5. Exit");
        printf("\n\nEnter your option: ");
        scanf(" %d", &option);
        if (option == 1)
        {
            printf("\n(1) Add a following account\n(2) Add a follower account\nEnter your option: ");
            scanf(" %d", &accountoption);
            fflush(stdin);
            printf("Enter name of the account: ");
            gets(name);
            printf("Enter number of posts: ");
            scanf(" %d", &noPosts);
            printf("Enter number of followers: ");
            scanf(" %d", &noFollowers);
            printf("Enter number of following: ");
            scanf(" %d", &noFollowing);
            if (accountoption == 1)
            {
                temp = listfollowing;
                temp->tail = temp->head;
                while (temp->tail->next != NULL)
                {
                    if (strcmp(temp->tail->accountName, name) == 0) // Check here takes value 0 if the account already exists
                    {
                        printf("\n\nAccount already exists!!\n\n");
                        check = 0;
                    }
                    temp->tail = temp->tail->next;
                }
                if (check)
                    addAccount(listfollowing, name, noPosts, noFollowing, noFollowers);
            }
            else if (accountoption == 2)
            {
                temp = listfollowers;
                temp->tail = temp->head;
                while (temp->tail->next != NULL)
                {
                    if (strcmp(temp->tail->accountName, name) == 0) // Check here takes value 0 if the account already exists
                    {
                        printf("\n\nAccount already exists!!\n\n");
                        check = 0;
                    }
                    temp->tail = temp->tail->next;
                }
                if (check)
                    addAccount(listfollowers, name, noPosts, noFollowing, noFollowers);
            }
        }
        else if (option == 2)
        {
            printf("\n(1) Print following list\n(2) Print follower list\nEnter your option: ");
            scanf(" %d", &accountoption);
            if (accountoption == 1)
                printMyAccount(listfollowing);
            else if (accountoption == 2)
                printMyAccount(listfollowers);
        }
        else if (option == 3)
        {
            printf("\n(1) Search following list\n(2) Search follower list\nEnter your option: ");
            scanf(" %d", &accountoption);
            printf("Enter the name of the account: ");
            fflush(stdin);
            gets(name);
            if (accountoption == 1)
                searchAccount(listfollowing, name);
            else if (accountoption == 2)
                searchAccount(listfollowers, name);
        }
        else if (option == 4)
        {
            printf("\n(1) Delete account from following list\n(2) Delete account from follower list\nEnter your option: ");
            scanf(" %d", &accountoption);
            fflush(stdin);
            printf("Enter account ID: ");
            scanf(" %d", &uniqueID);
            if (accountoption == 1)
                deleteAccount(listfollowing, uniqueID);
            else if (accountoption == 2)
                deleteAccount(listfollowers, uniqueID);
        }
        else if (option == 5)
            printf("\n\nGood bye!\n\n");
    } while (option != 5);
    OverwriteMyAccount(following, listfollowing);
    printf("\nThe following.txt has been updated successfully");
    OverwriteMyAccount(followers, listfollowers);
    printf("\nThe follower.txt has been updated successfully");
    free(listfollowers);
    free(listfollowing);
    free(temp);
    return 0;
}

void MakeEmptyList(List l)
{
    l->head = (struct Node *)malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!1\n");
    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}

List CreateList()
{
    List l;
    l = (struct ListRecord *)malloc(sizeof(struct ListRecord));
    if (l == NULL)
        printf("Out of memory!2\n");
    else
        MakeEmptyList(l);
    return l;
}

List initialiseMyAccount(char str[]) // This function reads the following/followers files and store them in linked lists
{
    List l = CreateList();
    int i;
    char line[200], val[50]; // String here reads the values in terms of strings
    FILE *fp;
    fp = fopen(str, "r");
    if (fp == NULL)
        printf("\nCould not open file");
    while (fgets(line, sizeof(line), fp))
    {
        // Takes the first element in a line and stores it in string type
        strcpy(val, strtok(line, ";"));
        l->tail->uniqueID = atoi(val); // Takes the val and convert it to integer value
        strcpy(val, strtok(NULL, ";"));
        strcpy(l->tail->accountName, val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->noPosts = atoi(val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->noFollowing = atoi(val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->noFollowers = atoi(val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->day = atoi(val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->month = atoi(val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->year = atoi(val);
        strcpy(val, strtok(NULL, ";"));
        l->tail->hour = atoi(val);
        strcpy(val, strtok(NULL, "\n"));
        l->tail->minute = atoi(val);
        l->tail->next = (struct Node *)malloc(sizeof(struct Node));
        if (l->tail->next == NULL)
        {
            printf("\n\n\nOut of memory3");
            exit(1);
        }
        l->size = l->size + 1;
        l->tail = l->tail->next;
    }
    l->tail->next = NULL;
    fclose(fp);
    return l;
}

void addAccount(List l, char name[], int noPosts, int noFollowing, int noFollowers) // Takes either follower or following lists , asks the user details about the account and add the account to the list
{
    time_t ti = time(NULL);
    struct tm t = *localtime(&ti);
    int uniqueID;
    l->size = l->size + 1;
    uniqueID = l->size;
    l->tail->uniqueID = uniqueID;
    strcpy(l->tail->accountName, name);
    l->tail->noPosts = noPosts;
    l->tail->noFollowers = noFollowers;
    l->tail->noFollowing = noFollowing;
    l->tail->day = t.tm_mday;
    l->tail->month = t.tm_mon + 1;
    l->tail->year = t.tm_year + 1900; // Assigning the current time
    l->tail->hour = t.tm_hour;
    l->tail->minute = t.tm_min;
    l->tail->next = (struct Node *)malloc(sizeof(struct Node)); // Creating node for next operation if there will be one
    l->tail = l->tail->next;
    l->tail->next = NULL;
    printf("\n\nAccount successfully added!!\n\n");
}

void printMyAccount(List l) // Prints the list elements with starting from head and in the following content
{
    List p = l;
    p->tail = p->head; // Bringing tail to the head so we can start from beginning node
    if (p->tail->next == NULL)
    {
        printf("\n\nNo account found !!!\n");
    }
    else
    {
        while (p->tail->next != NULL)
        {
            printf("\nAccount ID: %d", p->tail->uniqueID);
            printf("\nAccount name: %s", p->tail->accountName);
            printf("\nNumber of posts: %d", p->tail->noPosts);
            printf("\nNumber of following: %d", p->tail->noFollowing);
            printf("\nNumber of followers: %d", p->tail->noFollowers);
            printf("\nDate: %d/%d/%d", p->tail->day, p->tail->month, p->tail->year);
            printf("\nTime: %d:%d", p->tail->hour, p->tail->minute);
            printf("\n\n");
            p->tail = p->tail->next;
        }
    }

    printf("\n");
}

void searchAccount(List l, char name[])
{
    List p = l;
    p->tail = p->head;
    int check = 1;
    while (p->tail->next != NULL)
    {
        if (strcmp(p->tail->accountName, name) == 0)
        {
            printf("\nAccount ID: %d", p->tail->uniqueID);
            printf("\nAccount name: %s", p->tail->accountName);
            printf("\nNumber of posts: %d", p->tail->noPosts);
            printf("\nNumber of following: %d", p->tail->noFollowing);
            printf("\nNumber of followers: %d", p->tail->noFollowers);
            printf("\nDate: %d/%d/%d", p->tail->day, p->tail->month, p->tail->year);
            printf("\nTime: %d:%d\n\n", p->tail->hour, p->tail->minute);
            check = 0;
        }
        p->tail = p->tail->next;
    }
    if (check)
        printf("\nAccount does not exist!!\n\n");
}

void deleteAccount(List l, int uniqueID) // Deleting a node from linked list using its unique ID
{
    List temp1 = l, temp2 = l;
    l->tail = l->head;
    temp1->tail = temp1->head;
    temp2->tail = temp2->head;
    int i;
    if (l->head->uniqueID != uniqueID)
        while (temp1->tail->next->uniqueID != uniqueID) // Finding n-1 node (the n node is the node to be deleted)
        {
            temp1->tail = temp1->tail->next;
            temp2->tail = temp2->tail->next;
        }
    if (l->head->uniqueID == uniqueID) // Checking if the node entered is the first node or not
    {
        temp1->tail = temp1->head;
        l->head = temp1->tail->next;
        free(temp1->tail);
    }
    else
    {
        temp2->tail = l->tail->next;           // n th node
        temp1->tail->next = temp2->tail->next; // (n+1) th node
        free(temp2->tail);
        free(temp1->tail);
    }
    printf("\n\nAccount deleted successfully\n\n");
}

void OverwriteMyAccount(char filename[], List l) // Writes the structure data to the files, overwrites them
{
    FILE *fp;
    int i;
    l->tail = l->head;
    fp = fopen(filename, "w");
    if (fp == NULL)
        printf("\nError opening file!!!");
    for (i = 0; i < l->size; i++) // Assigning values one by one
    {
        fprintf(fp, "%d;%s;%d;%d;%d;%d;%d;%d;%d;%d\n", l->tail->uniqueID, l->tail->accountName, l->tail->noPosts, l->tail->noFollowing, l->tail->noFollowers, l->tail->day, l->tail->month, l->tail->year, l->tail->hour, l->tail->minute);
        l->tail = l->tail->next;
    }
    fclose(fp);
}


