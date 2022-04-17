#include <stdlib.h>

#include "chmac.h"


int main(int argc, char **argv)
{
    int sock = get_socket();
    if(sock == -1) exit(1);

    struct ifreq *if_ptr = if_index_to_ifreq(6);
    if(!if_ptr) exit(1);

    if(get_if_flags(sock, if_ptr)) {
        printf("%s: %d\n", get_if_name(if_ptr), if_is_up(if_ptr));
    }

    shutdown(sock, SHUT_RDWR);
    free(if_ptr);
    return 0;
}
