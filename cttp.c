#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <task.h>

char *ROOT;

enum {
    STACK = 32768
};

char *server;
int port;
void http_serve_task(void*);
void rwtask(void*);

int*
mkfd2(int fd1, int fd2) {
    int *a;

    a = malloc(2 * sizeof a[0]);
    if (a == 0) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    a[0] = fd1;
    a[1] = fd2;
    return a;
}

#define BYTES 1024

void
serve_http2_task(void* client_fd) {
    char mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
    int rcvd, fd, bytes_read;
    memset((void*) mesg, (int) '\0', 99999);
    rcvd = recv((int) client_fd, mesg, 99999, 0);

    if (rcvd < 0) // receive error
        fprintf(stderr, ("recv() error\n"));
    else if (rcvd == 0) // receive socket closed
        fprintf(stderr, "Client disconnected upexpectedly.\n");
    else // message received
    {
        printf("%s", mesg);
        reqline[0] = strtok(mesg, " \t\n");
        if (strncmp(reqline[0], "GET\0", 4) == 0) {
            reqline[1] = strtok(NULL, " \t");
            reqline[2] = strtok(NULL, " \t\n");
            if (strncmp(reqline[2], "HTTP/1.0", 8) != 0 && strncmp(reqline[2], "HTTP/1.1", 8) != 0) {
                write(client_fd, "HTTP/1.0 400 Bad Request\n", 25);
            } else {
                if (strncmp(reqline[1], "/\0", 2) == 0)
                    reqline[1] = "/index.html"; //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...

                strcpy(path, ROOT);
                strcpy(&path[strlen(ROOT)], reqline[1]);
                printf("file: %s\n", path);

                if ((fd = open(path, O_RDONLY)) != -1) //FILE FOUND
                {
                    send(client_fd, "HTTP/1.0 200 OK\n\n", 17, 0);
                    while ((bytes_read = read(fd, data_to_send, BYTES)) > 0)
                        write(client_fd, data_to_send, bytes_read);
                } else write(client_fd, "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
            }
        }
    }
}

void
taskmain(int argc, char **argv) {

    int client_fd, listen_fd, listen_port;
    int client_port;

    if (argc != 2) {
        fprintf(stderr, "usage: cttp localport\n");
        taskexitall(1);
    }

    listen_port = atoi(argv[1]);

    if ((listen_fd = netannounce(TCP, 0, listen_port)) < 0) {
        fprintf(stderr, "cannot announce on tcp port %d: %s\n", listen_port, strerror(errno));
        taskexitall(1);
    }
    fdnoblock(listen_fd);

    ROOT = getenv("PWD");

    while ((client_fd = netaccept(listen_fd, NULL, NULL)) >= 0) {
        taskcreate(serve_http2_task, (void*) client_fd, STACK);
    }
}
