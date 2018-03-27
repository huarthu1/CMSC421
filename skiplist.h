#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <linux/kernel.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
/* The given RNG function */
static unsigned int next_random = 9001;
static unsigned int generate_random_int(void) {
  next_random = next_random * 1103515245 + 12345;
  return (next_random / 65536) % 32768;
}
static void seed_random(unsigned int seed) {
  next_random = seed;
}

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
}SkipNode;

/* Skip List Manager: Manages the SkipNodes AND MailBox */
typedef struct SkipListManager {
  int m_maxLevel;               /* Maximum level of the skip list */
  struct SkipNode * m_start;    /* Start SkipNode of the skip list */
  struct SkipNode * m_previous; /* Tracker for previously visited SkipNode */
}SkipListManager;

/* MailBox Constructor */
MailBox * CreateMailBox(char * message, MailBox * mail);

/* SkipList Constructor */
SkipNode * CreateSkipNode(struct MailBox * mail, int maxLevel, int isStart);
  
/* SkipListManager Constructor */
SkipListManager * CreateSkipListManager(int maxLevel);

#endif