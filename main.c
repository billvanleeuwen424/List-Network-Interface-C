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


    while(address){

        char addressname[100];
        getnameinfo(address->ifa_addr, sizeof(struct sockaddr_in), addressname, sizeof(addressname),0,0, NI_NUMERICHOST);
        printf("%s\n", addressname);

        address = address->ifa_next;
    }
}