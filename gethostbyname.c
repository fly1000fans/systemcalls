#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <bits/socket.h>

#if 0
struct hostent 
{
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* alias list */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* list of addresses */
};
#endif

#define INET_ADDRSTRLEN 16

int main(int argc, char **argv)
{
    char *ptr;
    char **pptr;

    char str[INET_ADDRSTRLEN] = {0};
    struct hostent *hptr;

    while (--argc > 0)
    {
        ptr = *++argv;
        if (NULL == (hptr = gethostbyname(ptr)))
        {
            printf("gethostbyname error for host %s: %s", ptr, hstrerror(h_errno));
            continue;
        }

        printf("official hostname : %s\n", hptr->h_name);

        for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
        {
            printf("\talias: %s\n", *pptr);
        }

        switch (hptr->h_addrtype)
        {
            case AF_INET:   
                for (pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
                {
                    printf("\taddress: %s\n", inet_ntop(AF_INET, *pptr, str, sizeof(str)));
                }

                break;
            default:
                printf("unknown address type\n");
                return -1;
        }

    }

    return 0;
}
