#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int signum) {
    printf("Received Ctrl+C, but ignoring it, %d.\n", signum);
}

void handle_sigint_x(int signum) {
    printf("Received XXXX Ctrl+C, but ignoring it, %d.\n", signum);
}

int main() {
   // Press Ctrl+C to ignore (SIGINT)
//    signal(SIGINT, SIG_IGN); 
   signal(SIGINT, handle_sigint); 
   int count = 10;
   while (count--) {
       printf("Press Ctrl+C (ignored)...\n");
       sleep(1);
    }

    signal(SIGINT, handle_sigint_x); 
   count = 10;
   while (count--) {
       printf("Press Ctrl+C (ignored)...\n");
       sleep(1);
    }
   return 0;
}
