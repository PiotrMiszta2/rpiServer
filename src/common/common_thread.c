/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file
 * @brief
 *
 **********************************************************************************************************************/

/* INCLUDES ***********************************************************************************************************/
#include "common_thread.h"
#include "logger.h"
#include "double_linked_list.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct CommonThreadS
{
    uint8_t index;
}CommonThreadS;
/* Global Variable Definitions ****************************************************************************************/
DoubleLinkedList* commonThreadList;
/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/
static inline int custom_thread_list_compare(void* arg, void* arg2)
{
    CommonThreadS* n = arg;
    CommonThreadS* m = arg2;
    if ( n->index < m->index)
        return -1;
    else if( n->index > m->index)
        return 1;
    else
        return 0;
}

static inline CommonThreadS* custom_thread_create(const uint8_t i)
{
    CommonThreadS* thread = malloc(sizeof(CommonThreadS));
    assert(thread);
    thread->index = i;
    return thread;
}
/* Global Function Definitions ****************************************************************************************/
void common_thread_init(void)
{
    commonThreadList = dll_create(NULL, custom_thread_list_compare);
}
int common_thread_create(   pthread_t *restrict thread,
                            const pthread_attr_t *restrict attr,
                            void*(*start_runtine)(void *),
                            void *restrict arg,
                            const uint8_t id )
{
    int x = pthread_create(thread, attr, start_runtine, arg);
    if( x != 0 )
    {
        LOG_ERROR("Can't create thread %d", id);
    }
    else
    {
        LOG_INFO("Thread %d created", id);
        dll_push_back(commonThreadList, (void*)(custom_thread_create(id)));
    }
    CommonThreadS* c = custom_thread_create(10);
    printf("%d\n\n",dll_find(commonThreadList, c));
    return x;
}
/* Static Function Definitions ****************************************************************************************/
