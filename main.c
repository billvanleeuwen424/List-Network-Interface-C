#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <errno.h>
#include <string.h>

int main(){
    //a linked list of the addresses
    struct ifaddrs *addresses;

    //get the list
    if((getifaddrs(&addresses)) == -1){
        fprintf(stderr, "get address failure. %s",  strerror(errno));
        exit(-1);
    }

    //create pointer to traverse list
    struct ifaddrs *address = addresses;
    
    char addressname[100];


    while(address){

        //check if addr is null for the list entry
        while(address->ifa_addr == NULL){
            address = address->ifa_next;
        }

        int addrfamily = address->ifa_addr->sa_family;

        //only print ipv4 or ipv6 addresses
        if (addrfamily == AF_INET || addrfamily == AF_INET6){

            printf("%s\t", address->ifa_name);
            printf("%s\t", addrfamily == AF_INET ? "IPv4" : "IPv6");

            //get the readable ipaddr
            getnameinfo(address->ifa_addr, sizeof(struct sockaddr_in), addressname, sizeof(addressname),0,0, NI_NUMERICHOST);
            printf("%s\n", addressname);
        }

        address = address->ifa_next;
    }

    freeifaddrs(addresses);
    return 0;
}