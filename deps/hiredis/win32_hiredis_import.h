#ifndef _HIREDIS_SHARED_IMPORT_H_
#define _HIREDIS_SHARED_IMPORT_H_

#include "hiredis.h"
#include "async.h"

extern "C" __declspec(dllimport) void RedisInitialize();

/* Public API for the protocol parser. */
extern "C" __declspec(dllimport) redisReader *RedisReaderCreate(void);
extern "C" __declspec(dllimport) void RedisReaderFree(redisReader *r);
extern "C" __declspec(dllimport) int RedisReaderFeed(redisReader *r, const char *buf, size_t len);
extern "C" __declspec(dllimport) int RedisReaderGetReply(redisReader *r, void **reply);

#define redisReaderCreate RedisReaderCreate
#define redisReaderFree RedisReaderFree
#define redisReaderFeed RedisReaderFeed
#define redisReaderGetReply RedisReaderGetReply

/* Function to free the reply objects hiredis returns by default. */
extern "C" __declspec(dllimport) void FreeReplyObject(void *reply);
extern "C" __declspec(dllimport) int RedisvFormatCommand(char **target, const char *format, va_list ap);
extern "C" __declspec(dllimport) int RedisFormatCommand(char **target, const char *format, ...);
extern "C" __declspec(dllimport) int RedisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen);

#define freeReplyObject FreeReplyObject
#define redisvFormatCommand RedisvFormatCommand
#define redisFormatCommand RedisFormatCommand
#define redisFormatCommandArgv RedisFormatCommandArgv

/* Context for a connection to Redis */
extern "C" __declspec(dllimport) redisContext *RedisConnect(const char *ip, int port);
extern "C" __declspec(dllimport) redisContext *RedisConnectWithTimeout(const char *ip, int port, const struct timeval tv);
extern "C" __declspec(dllimport) redisContext *RedisConnectNonBlock(const char *ip, int port);
extern "C" __declspec(dllimport) redisContext *RedisConnectBindNonBlock(const char *ip, int port, const char *source_addr);
extern "C" __declspec(dllimport) redisContext *RedisConnectUnix(const char *path);
extern "C" __declspec(dllimport) redisContext *RedisConnectUnixWithTimeout(const char *path, const struct timeval tv);
extern "C" __declspec(dllimport) redisContext *RedisConnectUnixNonBlock(const char *path);
extern "C" __declspec(dllimport) redisContext *RedisConnectFd(int fd);
extern "C" __declspec(dllimport) int RedisSetTimeout(redisContext *c, const struct timeval tv);
extern "C" __declspec(dllimport) int RedisEnableKeepAlive(redisContext *c);
extern "C" __declspec(dllimport) void RedisFree(redisContext *c);
extern "C" __declspec(dllimport) int RedisFreeKeepFd(redisContext *c);
extern "C" __declspec(dllimport) int RedisBufferRead(redisContext *c);
extern "C" __declspec(dllimport) int RedisBufferWrite(redisContext *c, int *done);

#define redisConnect RedisConnect
#define redisConnectWithTimeout RedisConnectWithTimeout
#define redisConnectNonBlock RedisConnectNonBlock
#define redisConnectBindNonBlock RedisConnectBindNonBlock
#define redisConnectUnix RedisConnectUnix
#define redisConnectUnixWithTimeout RedisConnectUnixWithTimeout
#define redisConnectUnixNonBlock RedisConnectUnixNonBlock
#define redisConnectFd RedisConnectFd
#define redisSetTimeout RedisSetTimeout
#define redisEnableKeepAlive RedisEnableKeepAlive
#define redisFree RedisFree
#define redisFreeKeepFd RedisFreeKeepFd
#define redisBufferRead RedisBufferRead
#define redisBufferWrite RedisBufferWrite

/* In a blocking context, this function first checks if there are unconsumed
 * replies to return and returns one if so. Otherwise, it flushes the output
 * buffer to the socket and reads until it has a reply. In a non-blocking
 * context, it will return unconsumed replies until there are no more. */
extern "C" __declspec(dllimport) int RedisGetReply(redisContext *c, void **reply);
extern "C" __declspec(dllimport) int RedisGetReplyFromReader(redisContext *c, void **reply);

#define redisGetReply RedisGetReply
#define redisGetReplyFromReader RedisGetReplyFromReader

/* Write a formatted command to the output buffer. Use these functions in blocking mode
 * to get a pipeline of commands. */
extern "C" __declspec(dllimport) int RedisAppendFormattedCommand(redisContext *c, const char *cmd, size_t len);

#define redisAppendFormattedCommand RedisAppendFormattedCommand

/* Write a command to the output buffer. Use these functions in blocking mode
 * to get a pipeline of commands. */
extern "C" __declspec(dllimport) int RedisvAppendCommand(redisContext *c, const char *format, va_list ap);
extern "C" __declspec(dllimport) int RedisAppendCommand(redisContext *c, const char *format, ...);
extern "C" __declspec(dllimport) int RedisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);

#define redisvAppendCommand RedisvAppendCommand
#define redisAppendCommand RedisAppendCommand
#define redisAppendCommandArgv RedisAppendCommandArgv

/* Issue a command to Redis. In a blocking context, it is identical to calling
 * redisAppendCommand, followed by redisGetReply. The function will return
 * NULL if there was an error in performing the request, otherwise it will
 * return the reply. In a non-blocking context, it is identical to calling
 * only redisAppendCommand and will always return NULL. */
extern "C" __declspec(dllimport) void *RedisvCommand(redisContext *c, const char *format, va_list ap);
extern "C" __declspec(dllimport) void *RedisCommand(redisContext *c, const char *format, ...);
extern "C" __declspec(dllimport) void *RedisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);

#define redisvCommand RedisvCommand
#define redisCommand RedisCommand
#define redisCommandArgv RedisCommandArgv

/* Functions that proxy to hiredis */
extern "C" __declspec(dllimport) redisAsyncContext *RedisAsyncConnect(const char *ip, int port);
extern "C" __declspec(dllimport) redisAsyncContext *RedisAsyncConnectBind(const char *ip, int port, const char *source_addr);
extern "C" __declspec(dllimport) redisAsyncContext *RedisAsyncConnectUnix(const char *path);
extern "C" __declspec(dllimport) int RedisAsyncSetConnectCallback(redisAsyncContext *ac, redisConnectCallback *fn);
extern "C" __declspec(dllimport) int RedisAsyncSetDisconnectCallback(redisAsyncContext *ac, redisDisconnectCallback *fn);
extern "C" __declspec(dllimport) void RedisAsyncDisconnect(redisAsyncContext *ac);
extern "C" __declspec(dllimport) void RedisAsyncFree(redisAsyncContext *ac);

#define redisAsyncConnect RedisAsyncConnect
#define redisAsyncConnectBind RedisAsyncConnectBind
#define redisAsyncConnectUnix RedisAsyncConnectUnix
#define redisAsyncSetConnectCallback RedisAsyncSetConnectCallback
#define redisAsyncSetDisconnectCallback RedisAsyncSetDisconnectCallback
#define redisAsyncDisconnect RedisAsyncDisconnect
#define redisAsyncFree RedisAsyncFree

/* Handle read/write events */
extern "C" __declspec(dllimport) void RedisAsyncHandleRead(redisAsyncContext *ac);
extern "C" __declspec(dllimport) void RedisAsyncHandleWrite(redisAsyncContext *ac);
extern "C" __declspec(dllimport) int RedisAsyncHandleWritePrep(redisAsyncContext *ac);
extern "C" __declspec(dllimport) int RedisAsyncHandleWriteComplete(redisAsyncContext *ac, int written);

#define redisAsyncHandleRead RedisAsyncHandleRead
#define redisAsyncHandleWrite RedisAsyncHandleWrite
#define redisAsyncHandleWritePrep RedisAsyncHandleWritePrep
#define redisAsyncHandleWriteComplete RedisAsyncHandleWriteComplete

/* Command functions for an async context. Write the command to the
 * output buffer and register the provided callback. */
extern "C" __declspec(dllimport) int RedisvAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *format, va_list ap);
extern "C" __declspec(dllimport) int RedisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *format, ...);
extern "C" __declspec(dllimport) int RedisAsyncCommandArgv(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, int argc, const char **argv, const size_t *argvlen);

#define redisvAsyncCommand RedisvAsyncCommand
#define redisAsyncCommand RedisAsyncCommand
#define redisAsyncCommandArgv RedisAsyncCommandArgv

/* Misc helpers */
extern "C" __declspec(dllimport) void RedisInitialize();

#endif