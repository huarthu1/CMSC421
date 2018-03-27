#include "skiplist.h"

/* Global variables for SkipList Management */
SkipListManager * TheManager;

/* System call for project 1 starts here */
/* Initializes the skip list */
long slmbx_init(unsigned int ptrs, unsigned int prob) {
  /* Checks if the prob argument is valid input, if not return error */
  if(prob != 2 && prob != 4 && prob != 8 && prob != 16)
    return -1;
  /* If user is not root, return error */
  else if(getuid() != 0)
    return -2;
  /* Initialize SkipList Manager */
  TheManager = CreateSkipListManager(ptrs);
  return 0;
}

/*long slmbx_shutdown(void)
{
  
  if(getuid() != 0)
    return -2;
}*/

long slmbx_create(unsigned int id, int protected)
{
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

