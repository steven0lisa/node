/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef TASK_H_
#define TASK_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define TEST_PORT 9123
#define TEST_PORT_2 9124

#ifdef _WIN32
# define TEST_PIPENAME "\\\\.\\pipe\\uv-test"
# define TEST_PIPENAME_2 "\\\\.\\pipe\\uv-test2"
#else
# define TEST_PIPENAME "/tmp/uv-test-sock"
# define TEST_PIPENAME_2 "/tmp/uv-test-sock2"
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))

typedef enum {
  TCP = 0,
  UDP,
  PIPE
} stream_type;

/* Log to stderr. */
#define LOG(...)                        \
  do {                                  \
    fprintf(stderr, "%s", __VA_ARGS__); \
    fflush(stderr);                     \
  } while (0)

#define LOGF(...)                       \
  do {                                  \
    fprintf(stderr, __VA_ARGS__);       \
    fflush(stderr);                     \
  } while (0)

/* Die with fatal error. */
#define FATAL(msg)                                        \
  do {                                                    \
    fprintf(stderr,                                       \
            "Fatal error in %s on line %d: %s\n",         \
            __FILE__,                                     \
            __LINE__,                                     \
            msg);                                         \
    fflush(stderr);                                       \
    abort();                                              \
  } while (0)



/* Have our own assert, so we are sure it does not get optimized away in
 * a release build.
 */
#define ASSERT(expr)                                      \
 do {                                                     \
  if (!(expr)) {                                          \
    fprintf(stderr,                                       \
            "Assertion failed in %s on line %d: %s\n",    \
            __FILE__,                                     \
            __LINE__,                                     \
            #expr);                                       \
    abort();                                              \
  }                                                       \
 } while (0)


/* Just sugar for wrapping the main() for a task or helper. */
#define TEST_IMPL(name)   \
  int run_test_##name()

#define BENCHMARK_IMPL(name)  \
  int run_benchmark_##name()

#define HELPER_IMPL(name)  \
  int run_helper_##name()


/* Pause the calling thread for a number of milliseconds. */
void uv_sleep(int msec);

/* Format big numbers nicely. WARNING: leaks memory. */
const char* fmt(double d);

#endif /* TASK_H_ */
