#include "includes/http.h"
#include <signal.h>
//Web server
static uint16_t DEFAULT_PORT = 8080;

//To run the web server
// ./webserver -p <port>

//Handle the SIGINT calls
static void interupt_handler(void) {
	printf("[-] GPIO uninitialized...\n");
	gpioTerminate();
	exit(0);
}

//All the PI_OUTPUT pins
const int pin_outs[] = {24};

int main(int argc, char** argv) {
    //Arg parsing
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"--port") || !strcmp(argv[i], "-p")) {
            if (argv[i+1] != NULL) {
                DEFAULT_PORT = (uint16_t)atoi(argv[i+1]);
                i++;
            }
            else
                printf("[-] Error: Incorrect usage of argument... using default port (%i)", DEFAULT_PORT);
        }
        else
            printf("[-] Error: Unrecognized argument '%s', ignoring...\n", argv[i]);
    }

    //Initialize the GPIO
    if (gpioInitialise() < 0) {
        fprintf(stderr, "[-] Error initializing the GPIO...\n");
        return -1;
    }
    //Set GPIO OUTPUT pins
    for (int i = 0; i < sizeof(pin_outs)/sizeof(int); i++)
        gpioSetMode(pin_outs[i], PI_OUTPUT);

    printf("[+] Initializing HTTP server...\n");
    printf("[+] Running under port %u...\n", DEFAULT_PORT);

    int listenFD = init_listener_socket(DEFAULT_PORT);

    //Incoming connections
    int newfd;  //Listen on sock_fd, new connection on newfd
    struct sockaddr_storage their_addr; //Connector's address information
    char s[INET6_ADDRSTRLEN];

    //Terminate child processes and clean after signal interrupt
    start_reaper();

    signal(SIGINT, (void(*)())interupt_handler);

    for (;;) {
        socklen_t sin_size = sizeof their_addr;

        newfd = accept(listenFD, (struct sockaddr *)&their_addr, &sin_size);
        if (newfd == -1) {
            perror("[-] accept() error");
            continue;
        }

        // Print out a message that we got the connection
        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);

        printf("[+] Server Got connection from: %s\n", s);

        switch (fork()) {
            case 0:
                exit(handle_http_request(newfd));
            case -1:
                exit(-1);
        }

        close(newfd);
    }

    return 0;
}
