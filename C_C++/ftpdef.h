/* FTP SERVER CONFIG */
#define FTP_MAX_QUEUE 1500
#define FTP_DIR "/home/seven/Code/C_C++/FTP_Files/"
#define FTP_CONTROL_PORT 21
#define FTP_CONTROL_TYPE 1
#define FTP_DATA_PORT 20
#define FTP_DATA_TYPE 0
#define CMD_MAX_LENGTH 128
#define FB_MAX_LENGTH 512
#define FILE_MAX_BUFFER 1024
#define MAX_FILE_NAME 64

/*
 * A better way is to present the cmds as a byte hexadecimal number just like 0x10.
 */
#define FTP_CMD_USER "User"
#define FTP_CMD_PASS "Pass"
#define FTP_CMD_LIST "List"
#define FTP_CMD_QUIT "Quit"
#define FTP_CMD_PUT "Put"
#define FTP_CMD_GET "Get"
#define FTP_CMD_HELP "Help"

/* File transport cmds, not for explict using */
#define FTP_FTR_CMD_CONTINUE 0x11
#define FTP_FTS_CMD_CONTINUE 0x12
#define FTP_FTR_CMD_ENDALL 0x13
#define FTP_FTS_CMD_ENDALL 0x14
#define FTP_FT_ERR 0x20

/* FTP RESPONSE */
#define FTP_RSP_R_PASS 0x01
#define FTP_RSP_P_PASS 0x02
#define FTP_RSP_E_PASS 0x03
#define FTP_RSP_LIST 0x04
#define FTP_RSP_RF_START 0x05       /* SERVER RECEIVING FILE STARTS */
#define FTP_RSP_SF_START 0x06       /* SENDING FILE STARTS */
#define FTP_RSP_FT_END 0x07         /* FOR FUTURE */
#define FTP_RSP_R_LOG 0x08
#define FTP_RSP_ERR 0x09
#define FTP_RSP_BYE 0x10

#define FTP_LOG_HEAD "[LOG]"

#include <string>
void set_no_blocking(int sock);
string byte2std(int size);
string get_help_info();
