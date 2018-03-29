CMSC 421 Project 1
Name: 		Arthur Huang
Student ID:	LQ41339
E-mail:		huarthu1@umbc.edu
Description:
	"skiplist.h" contains all the declaration for the "SkipListManager", "SkipNode", and "MailNode" 
	structs and all their associated modifier functions. "skiplist.c" contains all the definitions 
	respective to the declarations in "skiplist.h". "SkipListManager" is a struct used to keep track
	of the whole skip list system and uses both "SkipNode" and "MailNode" to build the skip list.
	"SkipNode" is also known as the "Mail Box" mentioned in the project prompt and an instance of this
	struct is a unit in the skip list uniquely distinguished by its associated ID. Each "SkipNode" 
	instance is linked to the beginning of a linked list made of "MailNode" instances. "MailNode" instances
	act as the "messages" mentioned in the project prompt. Unfortunately, I was unable to implement all
	the functions in time because several class projects were also due along with this one. However, the 
	linked list made of "MailNode"s will work as new "MailNode"s are added to the end of the list and old
	"MailNode"s are popped off from the beginning of the linked list. (Thus satisfies the FIFO rule)
	
	