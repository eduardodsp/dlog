#include <stdio.h>
#include <unistd.h>

#include "dlog.h"

int main()
{ 
    dlog_t log;
    
    if( dlog_open(&log, "mylog", 7) != DLOG_OK )
        printf("dlog_open FAILED \n");

    dlog_write_test(&log, 10);
    dlog_read_test(&log);
    
    dlog_close(&log);

    return 0;
}