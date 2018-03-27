#include "skiplist.h"

/* MailBox Constructor */
MailBox * CreateMailBox(char * message, MailBox * mail) {
  MailBox * myBox = malloc(sizeof(MailBox));
  myBox -> m_message = message;
  /* Check if MailBox pointer is passed in */
  if(mail != NULL)
    myBox -> m_next = mail;
  else
    myBox -> m_next = NULL;
  return myBox;
}

/* SkipNode Constructor */
SkipNode * CreateSkipNode(struct MailBox * mail, int maxLevel, int isStart) {
  SkipNode * myNode = malloc(sizeof(SkipNode));
  myNode -> m_next = NULL;
  if(mail != NULL)
    myNode -> m_mail = mail;
  else
    myNode -> m_mail = NULL;
  /* Create different levels of skip node if it is not the start node*/
  if(!isStart) {
  	
  }
  return myNode;
}
  
/* SkipListManager Constructor */
SkipListManager * CreateSkipListManager(int maxLevel) {
  SkipListManager * myManager = malloc(sizeof(SkipListManager));
  myManager -> m_maxLevel = maxLevel;
  myManager -> m_start = CreateSkipNode(NULL, maxLevel, 1);
  myManager -> m_previous = NULL;
  return myManager;
}