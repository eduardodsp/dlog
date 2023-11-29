#include <stdio.h>
#include <unistd.h>

#include "dlog.h"

int main()
{ 
    dlog_t log;
    
    if( dlog_open(&log, "mylog", 80) != DLOG_OK )
        printf("ringfile_init FAILED \n");

    dlog_write_test(&log, 100);
    dlog_read_test(&log);
    
    dlog_close(&log);

    return 0;
}