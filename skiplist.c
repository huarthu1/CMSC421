#include "skiplist.h"
/* RNG Code */
static unsigned int generate_random_int(void) {
  next_random = next_random * 1103515245 + 12345;
  return (next_random / 65536) % 32768;
}
static void seed_random(unsigned int seed) {
  next_random = seed;
}
/* Returns true or false based on whether the node levels up */
int RNG(int p) {
  /* Initialize variables */
  int passMark;       /* Number that determins whether the RNG number passes the probability test */
  switch(p){
    case 2:
      passMark = pass_mark_2;
      break;
    case 4:
      passMark = pass_mark_4;
      break;
    case 8:
      passMark = pass_mark_8;
      break;
    case 16:
      passMark = pass_mark_16;
      break;
  }
  if(generate_random_int() > passMark)
    return 0;
  else 
    return 1;
}
/* Returns the number of times the node levels up */
int LevelUpCount(SkipListManager * m) {
  int levelCount = 1;
  int levelUp = RNG(m->m_prob);
  while(levelUp && levelCount <= m->m_maxLevel) {
    levelCount ++;
    levelUp = RNG(m->m_prob);
  }
  return levelCount;
}

/* MailBox Constructor */
MailBox * CreateMailBox(char * message, MailBox * mail) {
  MailBox * myBox = malloc(sizeof(MailBox));
  myBox->m_message = message;
  /* Check if MailBox pointer is passed in */
  if(mail != NULL)
    myBox->m_next = mail;
  else
    myBox->m_next = NULL;
  return myBox;
}

/* SkipNode Constructor */
SkipNode * CreateSkipNode(int isStart, int id, int level) {
  SkipNode * myNode = malloc(sizeof(SkipNode));
  myNode->m_next = malloc(level * sizeof(SkipNode));
  myNode->m_id = id;
  myNode->m_mail = NULL;
  myNode->m_level = level;
  myNode->m_isStart = isStart;
}
  
/* SkipListManmager Constructor */
SkipListManager * CreateSkipListManager(int maxLevel, int prob) {
  SkipListManager * myManager = malloc(sizeof(SkipListManager));
  myManager->m_maxLevel = maxLevel;
  myManager->m_prob = prob;
  myManager->m_start = CreateSkipNode(1, 0, 1);
}

/* Add a SkipNode */
int AddSkipNode(int id, SkipListManager * m) {
  /* Initialize variables */
  SkipNode * tempNode = m->m_start;         /* Temp Node for list traversing */
  SkipNode ** lastNodes;                    /* Last visited nodes in respective levels */  
  SkipNode * newNode;                       /* Newly created node */
  int levelCount;                           /* Keep track of levels for previous */
  int a;                                    /* For loops */
  /* Set up node tracker for last visited nodes in all levels */
  lastNodes = malloc(m->m_maxLevel * sizeof(SkipNode));
  for(a = 0; a < m->m_maxLevel; a++)
    lastNodes[a] = NULL;
  /* Traverse through the list */
  while(tempNode != NULL) {
    /* If there are no nodes in the list and tempNode is Start Node*/
    /* Link start node to new node, link new node to NULL */
    /*if(tempNode->m_next[0] == NULL && tempNode->m_isStart) {
      levelCount = LevelUpCount(m);
      newNode = CreateSkipNode(0, id, levelCount);
      tempNode->m_next[0] = newNode;
      for(a = 0; a < levelCount; a++)
        newNode->m_next[a] = NULL;
    }*/
    /* If new node is larger than all nodes */
    if(tempNode->m_next[0] == NULL) {
      levelCount = LevelUpCount(m);
      newNode = CreateSkipNode(0, id, levelCount);
      for(a = 0; a < levelCount; a++) {
        /* Link previous nodes to new node */
        if(a < tempNode->m_level)
          tempNode->m_next[a] = newNode;
        else if(lastNodes[a] != NULL)
          lastNodes[a]->m_next[a] = newNode;
        /* Link new node to NULL */
        newNode->m_next[a] = NULL;
      }
    }
    /* If the new node is smaller than the next node */
    /* Link previous node to new node, link new node to next node */
    else if(tempNode->m_next[0]->m_id > id) {
      levelCount = LevelUpCount(m);
      newNode = CreateSkipNode(0, id, levelCount);
      for(a = 0; a < levelCount; a++) {
        /* Link previous nodes to new node */
        if(a < tempNode->m_level)
          tempNode->m_next[a] = newNode;
        else if(lastNodes[a] != NULL)
          lastNodes[a]->m_next[a] = newNode;
        /* Link new node to NULL */
        newNode->m_next[a] = NULL;
      }
      /* Link new node to next nodes if not completely linked */
      
    }
    /* If node ids are less than the new node id, record previously available link based on level*/
    else {
      int a;
      for(a = 0; a < tempNode->m_level; a++) {
        lastNodes[a] = tempNode;
      }
    }
    /* Next node */;
    tempNode = tempNode -> m_next[0];
  }  
  /* Free Memory */
  free(lastNodes);
}


