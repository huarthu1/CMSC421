#include "skiplist.h"

/* Global variables for SkipList Management */
SkipListManager * TheManager;

/* System call for project 1 starts here */
/* Initializes the skip list */
long slmbx_init(unsigned int ptrs, unsigned int prob) {
  /* Checks if the prob argument is valid input, if not return error */
  if(prob != 2 && prob != 4 && prob != 8 && prob != 16)
    return -EINVAL;
  /* If user is not root, return error */
  else if(getuid() != 0)
    return -EINVAL;
  /* If maximum level of the node is 0, return error */
  else if(ptrs <= 0)
    return -EPERM;
  /* Initialize SkipList Manager */
  TheManager = CreateSkipListManager(ptrs, prob);
  return 0;
}

long slmbx_shutdown(void)
{
  /* If not root user, return error */
  if(getuid() != 0)
    return -EPERM;
  /* Delete the entire skip list */
  DeleteList(TheManager);
  return 0;
}

long slmbx_create(unsigned int id, int protected)
{
  /* If id is negative or 0, return error */
  if(id <= 0)
    return -EINVAL;
  /* If id is too large, return error */
  if(id >= 4294967295)
    return -EINVAL;
  /* If MailBox already exist, return error */
  if(FindSkipNode(id, TheManager) != NULL)
    return -EEXIST;
  /* Add the MailBox */
  AddSkipNode(id, TheManager, getuid());
  return 0;
}

/*long slmbx_destroy(unsigned int id)
{
  
}*/

/*long slmbx_count(unsigned int id)
{
  
}*/

/*long slmbx_send(unsigned int id, const unsigned char *msg, unsigned int len)
{

}*/

/*long slmbx_recv(unsigned int id, unsigned char *msg, unsigned int len)
{
  
}*/

/*long slmbx_length(unsigned int id)
{
  
}*/

