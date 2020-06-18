#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"
#include "parson.c"
#include <errno.h> 
#include <sys/types.h> 


void copy_string(char *target, char *source) {
    while (*source) {
      *target = *source;
      source++;
      target++;
   }

   *target = '\0';
}

void strcat2(char *a, const char *b){
     while(*a){
        a++;
    }
    while(*b){

        *a = *b;
        b++;
        a++;
    }

    *a = '\0';
}


int getCookies(char *text, char *list_cookies[], char *cookie){
    
    char *cookie2;
    int i = 0;

    while(text != NULL){

    cookie = strstr(text, "Set-Cookie");
        if(cookie != NULL){
            cookie2 = malloc(4093 * sizeof(char));
            copy_string(cookie2, cookie);
            cookie2 = cookie2 + 12;
            cookie2 = strtok(cookie2,";");
            list_cookies[i] = malloc(4093 *sizeof(char));
            copy_string(list_cookies[i],cookie2);
            i++;
        }

        text = strstr(text,"Set-Cookie");
        if(text != NULL){
            text = text + 15;
        }
     }

     return i;
}

void checkHostName(int hostname) 
{ 
    if (hostname == -1) 
    { 
        perror("gethostname"); 
        exit(1); 
    } 
} 
  
void checkHostEntry(struct hostent * hostentry) 
{ 
    if (hostentry == NULL) 
    { 
        perror("gethostbyname"); 
        exit(1); 
    } 
} 

void checkIPbuffer(char *IPbuffer) 
{ 
    if (NULL == IPbuffer) 
    { 
        perror("inet_ntoa"); 
        exit(1); 
    } 
} 


int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;
    JSON_Value *json_value;
    JSON_Object * json_object1, *data_obj, *query_obj;
    char *json;


    char *host = "185.118.200.35";
    char *site_name = "/task1/start";
    int port = 8081;

    sockfd = open_connection(host, port ,AF_INET, SOCK_STREAM, 0);
    message = compute_get_request2(host, site_name, NULL, NULL, 0, NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    close_connection(sockfd);

    //task 2 

    char delim = '{';
    char *list_cookies[50];
    int i = 0;
    char *text;
    char *cookie = NULL;
    char *response2;
    response2 = malloc(10000 *sizeof(char));
    copy_string(response2, response);
    text = strtok(response2,"{");
    json = strchr(response, delim);

    i = getCookies(text, list_cookies, cookie);

    json_value = json_parse_string(json);
    json_object1 = json_object(json_value);

    char *url_fol;
    char *method_fol;
    char *type_fol;
    char *username_fol;
    char *password_fol;
    char *token_fol;
    char *id_fol;
    char *url_data;
    char *method_data;
    char *q_fol;
    char *APPID_fol;
    char *url_params;
    char *url = "url";
    char *method = "method";
    char *type = "type";
    char *data = "data";
    char *username = "username";
    char *password = "password";
    char *token = "token";
    char *id = "id";
    char *query = "queryParams";
    char *post = "POST";
    char *get = "GET";
    char *raspuns1 = "omul";
    char *raspuns2 = "numele";
    char *q = "q";
    char *APPID = "APPID";
    char *string_post;

    url_fol = (char *) json_object_dotget_string (json_object1, url);
    method_fol = (char *) json_object_dotget_string(json_object1, method);
    type_fol = (char *) json_object_dotget_string(json_object1, type);
    data_obj = json_object_dotget_object(json_object1, data);
    username_fol = (char *)json_object_dotget_string(data_obj, username);
    password_fol = (char *) json_object_dotget_string(data_obj, password);

    string_post = malloc(10000 * sizeof(char));
    copy_string(string_post, "username=");
    strcat2(string_post, username_fol);
    strcat2(string_post, "&");
    strcat2(string_post,"password=");
    strcat2(string_post, password_fol);
    int len = i;

    free(message);
    free(response);

    if(strcmp(method_fol, post) == 0){
        sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);
        message = compute_post_request(host, url_fol, string_post, type_fol, list_cookies, len, NULL);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        printf("%s\n", response);
        close_connection(sockfd);
    }

    free(response2);
    free(string_post);
    i = 0;

    //task3 

    response2 = malloc(10000 *sizeof(char));
    copy_string(response2, response);
    text = strtok(response2,"{"); //se ia prima parte din raspuns 
    json = strchr(response, delim); // partea din mesaj in format json

    i = getCookies(text, list_cookies, cookie); // pun intr-o lista de stringuri fiecare cookie primit

    json_value = json_parse_string(json);
    json_object1 = json_object(json_value);

    url_fol = (char *)json_object_dotget_string (json_object1, url);
    method_fol = (char *)json_object_dotget_string(json_object1, method);
    data_obj = json_object_dotget_object(json_object1, data);
    token_fol = (char *)json_object_dotget_string(data_obj, token);
    query_obj = json_object_dotget_object(data_obj, query);
    id_fol = (char *)json_object_dotget_string(query_obj, id);
    username_fol = (char *)json_object_dotget_string(data_obj, username);
    password_fol = (char *) json_object_dotget_string(data_obj, password);

    string_post = malloc(10000 * sizeof(char));
    copy_string(string_post, url_fol);
    strcat2(string_post, "?");
    strcat2(string_post, "raspuns1=");
    strcat2(string_post, raspuns1);
    strcat2(string_post,"&raspuns2=");
    strcat2(string_post, raspuns2);
    strcat2(string_post, "&");
    strcat2(string_post, id);
    strcat2(string_post, "=");
    strcat2(string_post, id_fol);

    free(message);
    free(response);

    if(strcmp(get, method_fol) == 0){
        sockfd = open_connection(host, port,AF_INET, SOCK_STREAM, 0);
        message = compute_get_request2(host, string_post, NULL, list_cookies, i, token_fol);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        printf("%s\n", response);
        close_connection(sockfd);
    }

    free(response2);
    free(string_post);
    i = 0;

    //task4

    response2 = malloc(10000 *sizeof(char));
    copy_string(response2, response);
    text = strtok(response2,"{");
    json = strchr(response, delim);

    i = getCookies(text, list_cookies, cookie);

    json_value = json_parse_string(json);
    json_object1 = json_object(json_value);

    url_fol = (char *)json_object_dotget_string(json_object1, url);
    method_fol = (char *) json_object_dotget_string(json_object1, method);

    free(message);
    free(response);

    if(strcmp(method_fol, get) == 0){
        sockfd = open_connection(host, port,AF_INET, SOCK_STREAM, 0);
        message = compute_get_request2(host, url_fol, NULL, list_cookies, i, token_fol);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        printf("%s\n", response);
        close_connection(sockfd);
    }

    free(response2);
    i = 0;

    //task5

    response2 = malloc(10000 *sizeof(char));
    copy_string(response2, response);
    text = strtok(response2,"{");
    json = strchr(response, delim);

    i = getCookies(text, list_cookies, cookie);

    json_value = json_parse_string(json);
    json_object1 = json_object(json_value);

    url_fol = (char *)json_object_dotget_string(json_object1, url);
    method_fol = (char *)json_object_dotget_string(json_object1, method);
    type_fol =(char *) json_object_dotget_string(json_object1, type);
    data_obj = json_object_dotget_object(json_object1, data);
    url_data = (char *)json_object_dotget_string(data_obj, url);
    method_data = (char *)json_object_dotget_string(data_obj, method);
    query_obj = json_object_dotget_object(data_obj, query);
    q_fol = (char *)json_object_dotget_string(query_obj, q);
    APPID_fol = (char *)json_object_dotget_string(query_obj, APPID);

    url_params = malloc(1000 * sizeof(char));
    copy_string(url_params, q);
    strcat2(url_params, "=");
    strcat2(url_params, q_fol);
    strcat2(url_params, "&");
    strcat2(url_params, APPID);
    strcat2(url_params, "=");
    strcat2(url_params, APPID_fol);

    char *IPbuffer; 
    struct hostent *host_entry; 

    char *delim1 = "/";
    char *url_temp = malloc(100 * sizeof(char));

    copy_string(url_temp, url_data); 
    url_temp = strtok(url_temp, delim1); // prima parte din url 

    // se transforma in format ip url-ul
    char *hostbuffer1 = url_temp; 
    int length = strlen(hostbuffer1);
    host_entry = gethostbyname(hostbuffer1); 
    checkHostEntry(host_entry); 
    IPbuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); 

    url_data = url_data + length;

    free(message);
    free(response);

    if(strcmp(get, method_data) == 0){
        sockfd = open_connection(IPbuffer, 80,AF_INET, SOCK_STREAM, 0);
        message = compute_get_request2(IPbuffer, url_data, url_params, NULL, i, NULL);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        printf("%s\n", response);
        close_connection(sockfd);
    }

    free(url_params);
    free(response2);

    response2 = malloc(10000 *sizeof(char));
    copy_string(response2, response);
    text = strtok(response2,"{");
    json = strchr(response, delim);

    json_value = json_parse_string(json);
    json_object1 = json_object(json_value);

    free(response);
    free(message);

    if(strcmp(method_fol, post) == 0){
        sockfd = open_connection(host, port, AF_INET, SOCK_STREAM, 0);
        message = compute_post_request(host, url_fol, json, type_fol, list_cookies, i,token_fol);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        printf("%s\n", response);
        close_connection(sockfd);
    }

    free(url_temp);
    free(message);
    free(response);
    free(response2);

    return 0;
}