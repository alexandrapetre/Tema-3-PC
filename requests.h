#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_post_request(char *host, char *url, char *form_data, char* type, char* cookies[], int len, char *token);
char *compute_get_request2(char *host, char *url, char *url_params,char *cookies[], int len, char *token);
void copy_string(char *target, char *source);
void strcat2(char *a, const char *b);
#endif