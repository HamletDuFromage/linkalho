#ifndef __LINKUSER_CONSTANTS_HPP__
#define __LINKUSER_CONSTANTS_HPP__

//#define DEBUG
#define USE_GENERATORS
#define LOCAL_PATH "sdmc:/switch/" APP_TITLE_LOWER "/"
#define BACKUP_PATH LOCAL_PATH "backups/"
#define RESTORE_FILE_DIR LOCAL_PATH "restore/"
#define RESTORE_FILE_PATH RESTORE_FILE_DIR "restore.zip"

#ifdef DEBUG
# define ACCOUNT_PATH LOCAL_PATH "debug"
#else
# define ACCOUNT_PATH "account:/su"
#endif
# define RESTORE_PATH ACCOUNT_PATH


#endif // __LINKUSER_CONSTANTS_HPP__
