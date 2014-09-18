#ifndef __LOGGER_H_
#define __LOGGER_H_

#define LEVEL_CRITICAL  (int)1
#define LEVEL_ERROR     (int)2
#define LEVEL_WARNING   (int)3
#define LEVEL_INFO      (int)4
#define LEVEL_DEBUG     (int)5

#define DEFAULT_LOG_LEVEL   LEVEL_DEBUG

#define LEVEL_NO_PERMIT  -1
#define LEVEL_PERMIT 	1
#define DEFAULT_LOG_LIMIT   (4 * 1024 * 1024)

void log_append_to_file(char *filename, char *str, char *sourceFile,
			int fileLine);

void hex_log_append_to_file(char *filename, char *str, int length,
			    char *sourceFile, int fileLine);
void log_func(const char *file_name,int debug_level, char *format, ...);

void log_output(const char *log_file_name,int debug_level,const char *source_file_name,const char *fctn,int line, char *format, ...);

#endif
