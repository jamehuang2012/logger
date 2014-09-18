/*
 *	logger.c
 *  	PBSC James Huang
 *	June 12 2013
 *
 * 	mofification:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "logger.h"

static unsigned long current_log_limit = (4 * 1024 * 1024);


/*
 * Check the file size , if file size more than current_log_limit
 * rename to file_name.0
 */

void check_file_size(const char *filename)
{
	char backup_filename[100];
	long file_size;
	FILE *fp;

	fp = fopen(filename, "a");
	if (fp != NULL) {
		fseek(fp,0, SEEK_END);
		file_size = ftell(fp);
		fclose(fp);
		if (file_size > current_log_limit ) {

					sprintf(backup_filename,"%s.0",filename);
					rename(filename,backup_filename);

		}

	}

}

/***********************************************************
 * NAME: level_to_str
 * DESCRIPTION: utility to convert an enumeration to a string.
 *
 * IN:  debug level
 * OUT: string representation of the debug level
 ***********************************************************/
static char *level_to_str(int debug_level)
{
	char *level = NULL;

	switch (debug_level) {
	case LEVEL_CRITICAL:
		level = "CRITICAL";
		break;
	case LEVEL_ERROR:
		level = "ERROR";
		break;
	case LEVEL_WARNING:
		level = "WARNING";
		break;
	case LEVEL_INFO:
		level = "INFO";
		break;
	case LEVEL_DEBUG:
		level = "DEBUG";
		break;
	default:
		level = "UNKNOWN";
		break;
	}
	return level;
}

int check_log_level(int level)
{
	if (level < LEVEL_CRITICAL) {
		return LEVEL_NO_PERMIT;
	}

	if (DEFAULT_LOG_LEVEL >= level) {
		return LEVEL_PERMIT;
	}

	return LEVEL_NO_PERMIT;

}

void log_append_to_file(char *file_name, char *str, char *sourceFile,
			int fileLine)
{
	int ret;
	time_t t;
	time(&t);
	struct tm *tp = localtime(&t);
	char now_str[100];
	char backup[100];
	strftime(now_str, 100, "%Y-%m-%d %H:%M:%S", tp);

	check_file_size(file_name);

	FILE *fo;
	fo = fopen(file_name, "a");
	if (fo == 0) {
		return;
	}


	fprintf(fo, "%s %s(:%d):%s\n", now_str, sourceFile, fileLine, str);
	fclose(fo);
}

void hex_log_append_to_file(char *file_name, char *str, int length,
			    char *sourceFile, int fileLine)
{
	int ret;
	time_t t;
	int i;
	time(&t);
	struct tm *tp = localtime(&t);
	char now_str[100];
	char backup[100];
	strftime(now_str, 100, "%Y-%m-%d %H:%M:%S", tp);

	check_file_size(file_name);
	
	FILE *fo;
	fo = fopen(file_name, "a");
	if (fo == 0) {
		return;
	}

	fprintf(fo, "%s %s(:%d):\n", now_str, sourceFile, fileLine);
	for (i = 0; i < length; i++) {
		fprintf(fo, "%.2x ", (unsigned char)str[i]);
		if (((i + 1) % 16) == 0) {
			fprintf(fo, "\n");
		}
	}
	fprintf(fo, "\n");
	fclose(fo);
}

void log_func(const char *file_name,int debug_level, char *format, ...)
{
	int ret;
	struct stat info;
	va_list args;
	struct timeval tv;
	char *time;
	char backup[100];


	if (check_log_level(debug_level) == LEVEL_NO_PERMIT)
		return;
	check_file_size(file_name);

	FILE *fo;
	fo = fopen(file_name, "a");
	if (fo != NULL) {


		gettimeofday(&tv, NULL);
		time = ctime(&tv.tv_sec);
		time[strlen(time) - 1] = 0;

		fprintf(fo, "[%s: %s]:", time, level_to_str(debug_level));
		va_start(args, format);
		vfprintf(fo, format, args);
		va_end(args);
		fprintf(fo, "\n");
		fflush(fo);
		fclose(fo);
	}

}

void log_output(const char *log_file_name,int debug_level,const char *source_file_name,const char *fctn,int line, char *format, ...)
{
	va_list args;
	struct timeval tv;
	char *time;


	if (check_log_level(debug_level) == LEVEL_NO_PERMIT)
		return;
	check_file_size(log_file_name);

	FILE *fo;
	fo = fopen(log_file_name, "a");
	if (fo != NULL) {


		gettimeofday(&tv, NULL);
		time = ctime(&tv.tv_sec);
		time[strlen(time) - 1] = 0;

		fprintf(fo, "[%s: %s %s %s %d]:", time, level_to_str(debug_level),source_file_name,fctn,line);
		va_start(args, format);
		vfprintf(fo, format, args);
		va_end(args);
		fprintf(fo, "\n");
		fflush(fo);
		fclose(fo);
	}

}
