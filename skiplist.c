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
    if(levelCount < m->m_maxLevel)
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
  int a;
  /* Set all next pointers to NULL by default */
  for(a = 0; a < level; a++)
    myNode->m_next[a] = NULL;
  myNode->m_id = id;
  myNode->m_mail = NULL;
  myNode->m_level = level;
  myNode->m_isStart = isStart;
  return myNode;
}
  
/* SkipListManmager Constructor */
SkipListManager * CreateSkipListManager(int maxLevel, int prob) {
  SkipListManager * myManager = malloc(sizeof(SkipListManager));
  myManager->m_maxLevel = maxLevel;
  myManager->m_prob = prob;
  myManager->m_start = CreateSkipNode(1, 0, maxLevel);
  return myManager;
}

/* Add a SkipNode */
void AddSkipNode(int id, SkipListManager * m) {
  /* Initialize variables */
  SkipNode * currentNode = m->m_start;         /* Temp Node for list traversing */
  SkipNode ** lastNodes;                    /* Last visited nodes in respective levels */  
  SkipNode * newNode;                       /* Newly created node */
  int levelCount;                           /* Keep track of levels for previous */
  int traverseLevel;                        /* Level of nodes traversing through */
  int a;                                    /* For loops */
  /* Set up node tracker for last visited nodes in all levels */
  lastNodes = malloc(m->m_maxLevel * sizeof(SkipNode));
  for(a = 0; a < m->m_maxLevel; a++)
    lastNodes[a] = m->m_start;
  traverseLevel = (m->m_maxLevel) - 1;
  while(currentNode != NULL) {
    /* If next node is NULL, move down level. Or insert if it is the last level */
    if(currentNode->m_next[traverseLevel] == NULL) {
      if(traverseLevel > 0) {
        /* Record last visited node in this level before leveling down */
        lastNodes[traverseLevel] = currentNode;
        traverseLevel --;
      }
      /* Insert if 1st level reached */
      else {
        lastNodes[traverseLevel] = currentNode;
        levelCount = LevelUpCount(m);
        newNode = CreateSkipNode(0, id, levelCount);
        /* Link new node to the next nodes */
        for(a = 0; a < levelCount; a++) {
          if(lastNodes[a]->m_next[0] == NULL)
            newNode->m_next[a] = NULL;
          else
            newNode->m_next[a] = lastNodes[a]->m_next[a];
        }
        /* Link previous nodes to the new node */
        for(a = 0; a < m->m_maxLevel; a++)
            lastNodes[a]->m_next[a] = newNode;
        currentNode = NULL;
      }
    }
    /* If new node is smaller than next node , go down a level until last level */
    else if(id < currentNode->m_next[traverseLevel]->m_id) {
      if(traverseLevel > 0) {
        lastNodes[traverseLevel] = currentNode;
        traverseLevel --;
      }
      /* Insert if 1st level reached */
      else{
        lastNodes[traverseLevel] = currentNode;
        levelCount = LevelUpCount(m);
        newNode = CreateSkipNode(0, id, levelCount);
        /* Link new node to the next nodes */
        for(a = 0; a < levelCount; a++) {
          if(lastNodes[a]->m_next[0] == NULL)
            newNode->m_next[a] = NULL;
          else
            newNode->m_next[a] = lastNodes[a]->m_next[a];
        }
        /* Link previous nodes to the new node */
        for(a = 0; a < m->m_maxLevel; a++)
            lastNodes[a]->m_next[a] = newNode;
        currentNode = NULL;
      }
    }
    /* If new node is bigger than next node, move to next node in same level */
    else if(id > currentNode->m_next[traverseLevel]->m_id) {
      currentNode = currentNode->m_next[traverseLevel];
      lastNodes[traverseLevel] = currentNode;
    }
  }
  free(lastNodes);
}

/* Search for a SkipNode, return NULL if not found*/
SkipNode * FindSkipNode(int id, SkipListManager * m) {
  /* Initialize variables */
  SkipNode * currentNode = m->m_start;  /* Node tracker */
  int traverseLevel;                    /* Level tracker for traversing through list */
  traverseLevel = (m->m_maxLevel) - 1;
  /* Loop to navigate to node */
  while(currentNode != NULL) {
    /* Return node pointer if id found */
    if(id == currentNode->m_id)
      return currentNode;
    /* If id is smaller than current node id, gown down a level until level 1*/
    else if(id < currentNode->m_id) {
      /* If it is lowest level, return NULL */
      if(traverseLevel == 1)
        return NULL;
      else
        traverseLevel --;
    }
    /* If id is bigger than current node id, go to the next node in the same level*/
    else if(id > currentNode->m_id) {
      /* Return NULL if end of list */
      if(currentNode->m_next[0] == NULL)
        return NULL;
      else
        currentNode = currentNode->m_next[0];
    }
  }
  return NULL;
}

void DeleteList(SkipListManager * m) {
    /* Initialize Variable */
    SkipNode * currNode;    /* Current Node */
    SkipNode * nextNode;    /* Next Node */
    int a;
    currNode = m->m_start;
    /* Loop through the list to delete all nodes */
    while(currNode != NULL) {
    nextNode = currNode->m_next[0];
    free(currNode->m_next);
    currNode->m_next = NULL;
    free(currNode);
    currNode = nextNode;
  }
  /* Free manager */
  free(m);
  m = NULL;
}

/* Insert MailBox into skip list */
void AddMailBox(int id, SkipListManager * m) {
  /* Initialize Variables */
  SkipNode * currentNode;     /* Targeted node associated with id */
  MailBox * newMail;          /* New MailBox instance */
  currentNode = FindSkipNode(id, m);
  /* If skip node does not exist, create one and insert it into the list */
  while(currentNode == NULL) {
    AddSkipNode(id, m);
    currentNode = FindSkipNode(id, m);
  }
  /* Add MailBox to the queue in the SkipNode */
  if(currentNode != NULL) {
    new
  }
}

/* DEBUG */
void printList(SkipListManager * m) {
  SkipNode * currNode = m->m_start;
  while(currNode != NULL) {
    printf("%d\n", currNode->m_id);
    currNode = currNode->m_next[0];
  }
  /*printf("%d\n", currNode->m_id);
  currNode = currNode->m_next[0];
  printf("%d\n", currNode->m_id);
  currNode = currNode->m_next[0];
  printf("%d\n", currNode->m_id);
  currNode = currNode->m_next[0];
  printf("%d\n", currNode->m_id);
  currNode = currNode->m_next[0];
  printf("%d\n", currNode->m_id);
  currNode = currNode->m_next[0];
  printf("%d\n", currNode->m_id);
  currNode = currNode->m_next[0];
  printf("%d\n", currNode->m_id);*/
}
