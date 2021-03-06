/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <stdio.h>
#include <B.h>

int lock_lock(void);
int lock_unlock(void);


static unsigned long long factorial(unsigned long long n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int run() {
    const char *name = get_instance_name();

    printf("%s: started.\n", name);

    printf("%s: trying to acquire the lock...\n", name);
    lock_lock();
    printf("%s: got it!\n", name);

    printf("%s: Let's do some actual work (not like that other lazy instance)...\n", name);
    unsigned long long n = 23;
    unsigned long long  result = factorial(n);
    printf("%s: So, it turns out factorial %llu is %llu\n", name, n, result);
    printf("%s: Let's take a breather...\n", name);
    for (int i = 0; i < 100000; i++)
        asm volatile ("");

    printf("%s: Unlocking...\n", name);
    lock_unlock();

    printf("%s: Exiting\n", name);

    return 0;
}

