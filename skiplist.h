#include <linux/kernel.h>
#include <unistd.h>
#include <stdlib.h>
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
	int m_id;
	char * m_message;
	struct MailBox * m_next;
}MailBox;
/* MailBox Constructor */
MailBox * CreateMailBox(char * message) {
  MailBox * myBox = malloc(sizeof(MailBox));
  myBox -> m_message = message;
  myBox -> m_next = NULL;
  return myBox;
}
/* Mail Box Manager */
typedef struct MailBoxManager {
  struct MailBox * m_current;
  struct MailBox * m_start;
}MailBoxManager;
/* MailBoxManager Constructor */
MailBoxManager * CreateMailBoxManager() {
  MailBoxManager * myManager = malloc(sizeof(MailBoxManager));
  return myManager;
}
/* Skip List Struct */
typedef struct SkipNode{
  struct SkipNode * m_next;
}SkipNode;
/* System call for project 1 starts here */
/* Initializes the skip list */
long slmbx_init(unsigned int ptrs, unsigned int prob) {
  /* Checks if the prob argument is valid input, if not return error */
  if(prob != 2 && prob != 4 && prob != 8 && prob != 16)
    return -1;
  /* If user is not root, return error */
  else if(getuid() != 0)
    return -2;
  /* Initialize variables */
  return 0;
  /* Loop to initialize the list */
}

/*long slmbx_shutdown(void)
{
  
  if(getuid() != 0)
    return -2;
}

long slmbx_create(unsigned int id, int protected)
{
  
}

long slmbx_destroy(unsigned int id)
{
  
}

long slmbx_count(unsigned int id)
{
  
}

long slmbx_send(unsigned int id, const unsigned char *msg, unsigned int len)
{

}

long slmbx_recv(unsigned int id, unsigned char *msg, unsigned int len)
{
  
}

long slmbx_length(unsigned int id)
{
  
}*/
