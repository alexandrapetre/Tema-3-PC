#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"


char *compute_get_request2(char *host, char *url, char *url_params, char *cookies[], int len, char *token)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *cookie = malloc(LINELEN * sizeof(char));

    if (url_params != NULL)
    {
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else
    {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);


    if(token != NULL){
        sprintf(line, "Authorization: Basic %s", token);
        compute_message(message, line);
    }

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    int i; 
    int ok = 0;
    if(cookies != NULL){
        ok = 1;
        for(i = 0; i < len; i++){
            if(i == 0){
                copy_string(cookie, cookies[i]);
                continue;
            }
        strcat2(cookie, "; ");
        strcat2(cookie, cookies[i]);
        }
    }

    if(ok == 1){
        sprintf(line, "Cookie: %s", cookie);
        compute_message(message, line);
    }
    

    line[0] = 0;
    compute_message(message, line);

    return message;
}




char *compute_post_request(char *host, char *url, char *form_data, char *type, char** cookies, int len, char *token)
{

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *cookie = malloc(LINELEN * sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    if(token != NULL){
        sprintf(line, "Authorization: Basic %s", token);
        compute_message(message, line);
    }

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    sprintf(line,"Content-Type: %s", type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);


    int i; 
    int ok = 0;
    if(cookies != NULL){
        ok = 1;
        for(i = 0; i < len; i++){
            if(i == 0){
                copy_string(cookie, cookies[i]);
                continue;
            }
        strcat2(cookie, "; ");
        strcat2(cookie, cookies[i]);
        }
    }

    if(ok == 1){
        sprintf(line, "Cookie: %s", cookie);
        compute_message(message, line);
    }


    line[0] = 0;
    compute_message(message, line);


    sprintf(line, "%s", form_data);
    compute_message(message, line);


    return message;
}

