/* Creator : Yagmur Saygili / School Assigment
    This file is created for seperating the functions
    for those who want to look up the functions more
    clearly

    Here, there are the prototype of the functions
    , declarations.
*/
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