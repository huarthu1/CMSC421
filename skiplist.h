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
typedef struct MailBox {
  char * m_message;           /* Message for the mailbox */
  struct MailBox * m_next;    /* Next MailBox */
}MailBox;

/* Skip List Struct */
typedef struct SkipNode{
  int m_id;                     /* ID of the node */
  struct SkipNode ** m_next;    /* List of pointers to the next node in each level */
  struct MailBox * m_mail;      /* The MailBox associated with this ID */
  int m_isStart;
  int m_level;
}SkipNode;

/* Skip List Manager: Manages the SkipNodes AND MailBox */
typedef struct SkipListManager {
  int m_maxLevel;               /* Maximum level of the skip list */
  int m_prob;
  struct SkipNode * m_start;    /* Start SkipNode of the skip list */
}SkipListManager;

/* RNG Combined with calculation of probability */
int RNG(int p);
int LevelUpCount(SkipListManager * m);

/* MailBox Constructor */
MailBox * CreateMailBox(char * message, MailBox * mail);

/* SkipList Constructor */
SkipNode * CreateSkipNode(int isStart, int id, int leve);

/* SkipListManager Constructor */
SkipListManager * CreateSkipListManager(int maxLevel, int prob);

/* Add a SkipNode */
void AddSkipNode(int id, SkipListManager * m);

/* Search for a SkipNode */
SkipNode * FindSkipNode(int id, SkipListManager * m);

/* Add a MailBox into the skip list by id */
void AddMailBox(int id, SkipListManager * m);

/* Delete the Entire tree of SkipNodes */
void DeleteList(SkipListManager * m);

/* DEBUG */
void printList(SkipListManager * m);

#endif