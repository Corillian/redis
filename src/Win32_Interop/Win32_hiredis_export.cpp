#include <hiredis.h>
#include <async.h>

#include <sdkddkver.h>
#include <WinSock2.h>

#ifdef USE_DLMALLOC
#include "Win32_dlmalloc.h"
#elif USE_JEMALLOC
#include <jemalloc/jemalloc.h>
#endif

/* Public API for the protocol parser. */
extern "C" __declspec(dllexport) redisReader *RedisReaderCreate(void)
{
    return redisReaderCreate();
}

extern "C" __declspec(dllexport) void RedisReaderFree(redisReader *r)
{
    return redisReaderFree(r);
}

extern "C" __declspec(dllexport) int RedisReaderFeed(redisReader *r, const char *buf, size_t len)
{
    return redisReaderFeed(r, buf, len);
}

extern "C" __declspec(dllexport) int RedisReaderGetReply(redisReader *r, void **reply)
{
    return redisReaderGetReply(r, reply);
}

/* Function to free the reply objects hiredis returns by default. */
extern "C" __declspec(dllexport) void FreeReplyObject(void *reply)
{
    freeReplyObject(reply);
}

/* Functions to format a command according to the protocol. */
extern "C" __declspec(dllexport) int RedisvFormatCommand(char **target, const char *format, va_list ap)
{
    return redisvFormatCommand(target, format, ap);
}

extern "C" __declspec(dllexport) int RedisFormatCommand(char **target, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    const int ret = redisvFormatCommand(target, format, args);

    va_end(args);

    return ret;
}

extern "C" __declspec(dllexport) int RedisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen)
{
    return redisFormatCommandArgv(target, argc, argv, argvlen);
}

/* Context for a connection to Redis */
extern "C" __declspec(dllexport) redisContext *RedisConnect(const char *ip, int port)
{
    return redisConnect(ip, port);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectWithTimeout(const char *ip, int port, const struct timeval tv)
{
    return redisConnectWithTimeout(ip, port, tv);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectNonBlock(const char *ip, int port)
{
    return redisConnectNonBlock(ip, port);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectBindNonBlock(const char *ip, int port, const char *source_addr)
{
    return redisConnectBindNonBlock(ip, port, source_addr);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectUnix(const char *path)
{
    return redisConnectUnix(path);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectUnixWithTimeout(const char *path, const struct timeval tv)
{
    return redisConnectUnixWithTimeout(path, tv);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectUnixNonBlock(const char *path)
{
    return redisConnectUnixNonBlock(path);
}

extern "C" __declspec(dllexport) redisContext *RedisConnectFd(int fd)
{
    return redisConnectFd(fd);
}

extern "C" __declspec(dllexport) int RedisSetTimeout(redisContext *c, const struct timeval tv)
{
    return redisSetTimeout(c, tv);
}

extern "C" __declspec(dllexport) int RedisEnableKeepAlive(redisContext *c)
{
    return redisEnableKeepAlive(c);
}

extern "C" __declspec(dllexport) void RedisFree(redisContext *c)
{
    redisFree(c);
}

extern "C" __declspec(dllexport) int RedisFreeKeepFd(redisContext *c)
{
    return redisFreeKeepFd(c);
}

extern "C" __declspec(dllexport) int RedisBufferRead(redisContext *c)
{
    return redisBufferRead(c);
}

extern "C" __declspec(dllexport) int RedisBufferWrite(redisContext *c, int *done)
{
    return redisBufferWrite(c, done);
}

/* In a blocking context, this function first checks if there are unconsumed
 * replies to return and returns one if so. Otherwise, it flushes the output
 * buffer to the socket and reads until it has a reply. In a non-blocking
 * context, it will return unconsumed replies until there are no more. */
extern "C" __declspec(dllexport) int RedisGetReply(redisContext *c, void **reply)
{
    return redisGetReply(c, reply);
}

extern "C" __declspec(dllexport) int RedisGetReplyFromReader(redisContext *c, void **reply)
{
    return redisGetReplyFromReader(c, reply);
}

/* Write a formatted command to the output buffer. Use these functions in blocking mode
 * to get a pipeline of commands. */
extern "C" __declspec(dllexport) int RedisAppendFormattedCommand(redisContext *c, const char *cmd, size_t len)
{
    return redisAppendFormattedCommand(c, cmd, len);
}

/* Write a command to the output buffer. Use these functions in blocking mode
 * to get a pipeline of commands. */
extern "C" __declspec(dllexport) int RedisvAppendCommand(redisContext *c, const char *format, va_list ap)
{
    return redisvAppendCommand(c, format, ap);
}

extern "C" __declspec(dllexport) int RedisAppendCommand(redisContext *c, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    const int ret = redisvAppendCommand(c, format, args);

    va_end(args);

    return ret;
}

extern "C" __declspec(dllexport) int RedisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen)
{
    return redisAppendCommandArgv(c, argc, argv, argvlen);
}

/* Issue a command to Redis. In a blocking context, it is identical to calling
 * redisAppendCommand, followed by redisGetReply. The function will return
 * NULL if there was an error in performing the request, otherwise it will
 * return the reply. In a non-blocking context, it is identical to calling
 * only redisAppendCommand and will always return NULL. */
extern "C" __declspec(dllexport) void *RedisvCommand(redisContext *c, const char *format, va_list ap)
{
    return redisvCommand(c, format, ap);
}

extern "C" __declspec(dllexport) void *RedisCommand(redisContext *c, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    void *ret = redisvCommand(c, format, args);

    va_end(args);

    return ret;
}

extern "C" __declspec(dllexport) void *RedisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen)
{
    return redisCommandArgv(c, argc, argv, argvlen);
}

/* Functions that proxy to hiredis */
extern "C" __declspec(dllexport) redisAsyncContext *RedisAsyncConnect(const char *ip, int port)
{
    return redisAsyncConnect(ip, port);
}

extern "C" __declspec(dllexport) redisAsyncContext *RedisAsyncConnectBind(const char *ip, int port, const char *source_addr)
{
    return redisAsyncConnectBind(ip, port, source_addr);
}

extern "C" __declspec(dllexport) redisAsyncContext *RedisAsyncConnectUnix(const char *path)
{
    return redisAsyncConnectUnix(path);
}

extern "C" __declspec(dllexport) int RedisAsyncSetConnectCallback(redisAsyncContext *ac, redisConnectCallback *fn)
{
    return redisAsyncSetConnectCallback(ac, fn);
}

extern "C" __declspec(dllexport) int RedisAsyncSetDisconnectCallback(redisAsyncContext *ac, redisDisconnectCallback *fn)
{
    return redisAsyncSetDisconnectCallback(ac, fn);
}

extern "C" __declspec(dllexport) void RedisAsyncDisconnect(redisAsyncContext *ac)
{
    redisAsyncDisconnect(ac);
}

extern "C" __declspec(dllexport) void RedisAsyncFree(redisAsyncContext *ac)
{
    redisAsyncFree(ac);
}

/* Handle read/write events */
extern "C" __declspec(dllexport) void RedisAsyncHandleRead(redisAsyncContext *ac)
{
    redisAsyncHandleRead(ac);
}

extern "C" __declspec(dllexport) void RedisAsyncHandleWrite(redisAsyncContext *ac)
{
    redisAsyncHandleWrite(ac);
}

extern "C" __declspec(dllexport) int RedisAsyncHandleWritePrep(redisAsyncContext *ac)
{
    return redisAsyncHandleWritePrep(ac);
}

extern "C" __declspec(dllexport) int RedisAsyncHandleWriteComplete(redisAsyncContext *ac, int written)
{
    return redisAsyncHandleWriteComplete(ac, written);
}

/* Command functions for an async context. Write the command to the
 * output buffer and register the provided callback. */
extern "C" __declspec(dllexport) int RedisvAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *format, va_list ap)
{
    return redisvAsyncCommand(ac, fn, privdata, format, ap);
}

extern "C" __declspec(dllexport) int RedisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    const int ret = redisvAsyncCommand(ac, fn, privdata, format, args);

    va_end(args);

    return ret;
}

extern "C" __declspec(dllexport) int RedisAsyncCommandArgv(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, int argc, const char **argv, const size_t *argvlen)
{
    return redisAsyncCommandArgv(ac, fn, privdata, argc, argv, argvlen);
}