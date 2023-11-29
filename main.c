#include <stdio.h>
#include <unistd.h>

#include "dlog.h"

int main()
{ 
    dlog_t log1;
    
    if( dlog_open(&log1, "mylog", 20) != DLOG_OK )
        printf("ringfile_init FAILED \n");

    dlog_test(&log1, 30, 0);
    dlog_close(&log1);

    return 0;
}