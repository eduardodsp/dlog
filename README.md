# Dlog

Stupid simple log file manager written entirely in ANSI C.

Features:
    - Circular log with user defined size.
    - Overwrite old logs if file is full. This option can be disabled at runtime.
    - Save messages to a human readable file.
    - Multiple instances.

Warning: NOT THREAD SAFE!

All APIs are documented in dlog.h

### Usage:
```

    dlog_t log1;
    char readbuf[DLOG_LINE_MAX_SIZE] = "";
    char msg1[] = "Sample Info message1";

    if( dlog_open(&log1, "mylog", 4) !=  DLOG_OK ) {
        printf("dlog_open FAILED \n");
        return 0;
    }

    //write a message into the file
    if ( dlog_put(&log1, msg1) !=  DLOG_OK ){
        printf("ringfile_put FAILED \n");
        return 0;
    }

    //read the message
    if ( dlog_get(&log1, readbuf, sizeof(readbuf)) == DLOG_OK )
      printf("%s", readbuf);

```

