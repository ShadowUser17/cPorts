#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "chmac.h"


int get_socket(void)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock == -1) {
        perror("get_socket");
        return -1;
    }

    return sock;
}


int print_ifaces(FILE *fd_out)
{
    if(!fd_out) fd_out = stdout;

    struct if_nameindex *if_list, *if_ptr;
    if_list = if_nameindex();

    if(!if_list) return -1;

    for(if_ptr = if_list; (if_ptr->if_index && if_ptr->if_name); if_ptr++) {
        fprintf(fd_out, "%d: %s\n", if_ptr->if_index, if_ptr->if_name);
    }

    if_freenameindex(if_list);

    return 0;
}


int if_is_up(struct ifreq *if_ptr)
{
    if(!if_ptr) return 0;

    return if_ptr->ifr_ifru.ifru_flags & IFF_UP;
}


struct ifreq *if_index_to_ifreq(unsigned int if_index)
{
    char if_name[IFNAMSIZ];

    if(!if_indextoname(if_index, if_name)) return NULL;

    struct ifreq *if_item = (struct ifreq*)malloc(sizeof(struct ifreq));
    if(!if_item) return NULL;

    memset(if_item->ifr_ifrn.ifrn_name, 0, IFNAMSIZ);
    strncpy(if_item->ifr_ifrn.ifrn_name, if_name, IFNAMSIZ);

    return if_item;
}


const char *get_if_name(struct ifreq *if_ptr)
{
    if(!if_ptr) return NULL;

    return if_ptr->ifr_ifrn.ifrn_name;
}


short get_if_flags(int sock, struct ifreq *if_ptr)
{
    if(!if_ptr) return 0;

    if(ioctl(sock, SIOCGIFFLAGS, if_ptr) == -1) {
        perror("get_if_flags");
        return 0;
    }

    return if_ptr->ifr_ifru.ifru_flags;
}


short set_if_flags(int sock, struct ifreq *if_ptr)
{
    if(!if_ptr) return 0;

    if(ioctl(sock, SIOCSIFFLAGS, if_ptr) == -1) {
        perror("set_if_flags");
        return 0;
    }

    return if_ptr->ifr_ifru.ifru_flags;
}
