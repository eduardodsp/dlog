#ifndef _DLOG_H_
#define _DLOG_H_

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>

#define DLOG_NAME_MAX_SIZE 25
#define DLOG_LINE_MAX_SIZE 80

/**
 * @brief Enable/Disable automatic clean up after writing a new line.
 * By default when we overwrite a line we also remove any remaining old
 * characters to improve readability. This, however, takes some time so 
 * if readability is not a concern you can turn it off by setting option
 * DLOG_OPT_AUTO_CLR_OFF. 
*/
#define DLOG_OPT_AUTO_CLR       ( 1 << 0 )

/**
 * @brief Enable/Disable overwrite of older logs when full
*/
#define DLOG_OPT_OVERWRITE      ( 1 << 1 )

/**
 * @brief Enable/Disable CRC check to make sure that logs
 * are not corrupted. Not supported yet.
*/
#define DLOG_OPT_CRC            ( 1 << 2 )

#define DLOG_OPT_ALL (DLOG_OPT_AUTO_CLR | DLOG_OPT_OVERWRITE | DLOG_OPT_CRC)

/**
 * @brief Return codes
*/
enum DLOG_ERR_CODES {

    DLOG_OK             =  1,
    DLOG_EMPTY_QUEUE    =  0,
    DLOG_FULL_QUEUE     = -1,
    DLOG_NULL_PTR       = -2,
    DLOG_BAD_PARAM      = -3,
    DLOG_INTERNAL_ERR   = -4,
    DLOG_FILESYSTEM_ERR = -5,
    DLOG_MSG_SIZE_ERR   = -6,
};

/**
 * @brief Log file control block instance. Member variables
 * are for internal use only.
*/
typedef struct _dlog_t{

    char         filename[DLOG_NAME_MAX_SIZE]; // internal use only!!!
    unsigned int qsize;                         // internal use only!!!

    unsigned int qcount;        // internal use only!!!
    unsigned int qtail;         // internal use only!!!
    unsigned int qhead;         // internal use only!!!

    fpos_t log_begin_pos;       // internal use only!!!
    fpos_t tail_pos;            // internal use only!!!
    fpos_t head_pos;            // internal use only!!!
    fpos_t header_tail_pos;     // internal use only!!!
    fpos_t header_head_pos;     // internal use only!!!
    fpos_t header_count_pos;    // internal use only!!!
    FILE*  file_ptr;            // internal use only!!!

    unsigned char en_auto_clr;  // internal use only!!!
    unsigned char en_overwrite; // internal use only!!!
    unsigned char en_crc;       // internal use only!!!

}dlog_t;

/**
 * @brief Initialize the log file control block
 * @param ptr Pointer to the log file control block
 * @param filename Name of the log file without format extension
 * @param size Max number of lines in the log file
 * @return DLOG_ERR_CODES
 */
int dlog_open(dlog_t* ptr, char* filename, unsigned int size);

/**
 * @brief Set option flagss
 * @param ptr Pointer to the log file control block
 * @param opt Option bitmask
 * @return DLOG_ERR_CODES
 */
int dlog_set_opt(dlog_t* ptr, unsigned char opt, unsigned char value);

/**
 * @brief Read a message from the log file
 * @param ptr Pointer to the log file control block
 * @param msg Output buffer
 * @param size Size of the message in bytes
 * @return DLOG_ERR_CODES
 */
int dlog_get(dlog_t* ptr, char* msg, int size);

/**
 * @brief Put a message into the log file
 * @param ptr Pointer to the log file control block
 * @param msg Message string
 * @return DLOG_ERR_CODES
 */
int dlog_put(dlog_t* ptr, char* msg);

/**
 * @brief Run a simple write and readback test
 * @param ptr Pointer to the log file control block
 * @param n Number of automatic generated messages to write
 * @return DLOG_ERR_CODES
 */
int dlog_test(dlog_t* ptr, unsigned int n, unsigned char updown);

/**
 * @brief Close the log file and reset control block
 * @param ptr Pointer to the log file control block
 * @return DLOG_ERR_CODESNGFILE_ERR_CODES
 */
int dlog_close(dlog_t* ptr);

#endif //_DLOG_H_