#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig_num) {
    // This will be called when we get SIGINT (Ctrl+C)
    if (sig_num == SIGINT)
		printf("\n");
    else if (sig_num == SIGQUIT)
		printf("\\n");
}

int main() {
    struct sigaction sa;

    // Set up the sigaction struct to use our handler
    sa.sa_handler = sigint_handler;

    // Block all other signals during our handler
    sigfillset(&sa.sa_mask);

    // No special options
    sa.sa_flags = 0;

    // Install the handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Ignore SIGQUIT
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    return 0;
}




