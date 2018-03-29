#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <linux/kernel.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
/*#define NULL 0*/
#define pass_mark_2 16383
#define pass_mark_4 8191
#define pass_mark_8 4095
#define pass_mark_16 2047
/* The given RNG function */
static unsigned int next_random = 9001;
static unsigned int generate_random_int(void);
static void seed_random(unsigned int seed);

/* Mail Box Struct */
typedef struct MailNode {
  char * m_message;           /* Message for the MailNode */
  struct MailNode * m_next;    /* Next MailNode */
}MailNode;

/* Skip List Struct */
typedef struct SkipNode{
  int m_id;                     /* ID of the node */
  struct SkipNode ** m_next;    /* List of pointers to the next node in each level */
  struct MailNode * m_mail;      /* The MailNode associated with this ID */
  int m_isStart;                /* Whether or not this is a start node */
  int m_level;                  /* Level of the Node */
  int m_uid;                    /* User id that created this node */
}SkipNode;

/* Skip List Manager: Manages the SkipNodes AND MailNode */
typedef struct SkipListManager {
  int m_maxLevel;               /* Maximum level of the skip list */
  int m_prob;
  struct SkipNode * m_start;    /* Start SkipNode of the skip list */
}SkipListManager;

/* RNG Combined with calculation of probability */
int RNG(int p);
int LevelUpCount(SkipListManager * m);

/* CreateMailNode() - Constructor 
   Input: Mail message
   Output: Makes MailNode instance
*/
MailNode * CreateMailNode(char * msg);

/* CreateSkipNode() - Constructor 
   Input: Is the node start node?, id of node, max level of node, user id that made this node
   Output: Makes a node instance for skip list
*/
SkipNode * CreateSkipNode(int isStart, int id, int level, int uid);

/* CreateSkipListManager() - Constructor
   Input: Max level of the list, Prob
   Output: Makes an instance that manages the skip list
 */
SkipListManager * CreateSkipListManager(int maxLevel, int prob);

/* Add a SkipNode 
   Input: Id of node, SkipListManager, user id that creates the node
   Output: Creates a node for skiplist and inserts it into the skiplist
*/
void AddSkipNode(int id, SkipListManager * m, int uid);

/* Search for a SkipNode 
   Input: Node id, SkipListManager
   Output: Find the node with given id and return pointer to it. Returns NULL if node with id not found
*/
SkipNode * FindSkipNode(int id, SkipListManager * m);

/* Add a MailNode into the skip list by id 
   Input: Node id, SKipListManager, Mail message
   Output: Inserts message to Mail Box (Skip Node) specified by id. Creates skip node if skip 
           node with id does not exist. Return error if skip node with id already exists.
*/
void AddMailNode(int id, SkipListManager * m, char * msg);

/* Delete the Entire tree of SkipNodes 
   Input: SkipListManager
   Output: Deletes the entire skip list and frees all memory
*/
void DeleteList(SkipListManager * m);

/* DEBUG */
void printList(SkipListManager * m);

#endif