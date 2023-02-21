# InstaManager
A simple C application which allows users to manage their Instagram account.

When you start the application, it will read the accounts you follow (following) and the accounts follows you (followers) from external text files (following.txt and followers.txt), create two separate linked lists (one for the accounts you follow (following) and another one for the accounts follows you (followers) and then populate these lists with the accounts stored in those two text files. This application will then provide some operations for you to manage your Instagram account. When you exit from the application, the application will overwrite the external files with the latest version of the lists to include the latest accounts in your following and followers list.

Each account stored in the external files have uniqueID (given by the system), accountName, number of Posts, number of Following, number of Followers, and date-time. This values are sperated with a semicolon in the file. I assume that there is no semicolon in the given information (lady;gaga as a accountName cannot exist).

Adding account information works in the way that; First want user to enter the following information: accountName, number of Posts, number of Following, number of Followers. Date-time and uniqueID are given by the system. Then these values are stored in the linked list appropriately. Then the program writes this account to the appropriate file with semicolon ( ; ) between them. The program handles that overwriting the external file with the created linked list.

At the end I free the pointers and linkedLists with letting the user know the operation is done and quit the program.

Used approaches: Linkedlists, pointers, file handling, file reading with a token, data type conversion, memory allocating and deallocating.

