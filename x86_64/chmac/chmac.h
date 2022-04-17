#ifndef __CHMAC_H__
#define __CHMAC_H__

#include <stdio.h>
#include <linux/if.h>


int get_socket(void);

int print_ifaces(FILE *fd_out);

int if_is_up(struct ifreq *if_ptr);

struct ifreq *if_index_to_ifreq(unsigned int if_index);

const char *get_if_name(struct ifreq *if_ptr);

short get_if_flags(int sock, struct ifreq *if_ptr);

short set_if_flags(int sock, struct ifreq *if_ptr);

#endif // __CHMAC_H__
