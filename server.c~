/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

static int port = -1;

int main(int argc, char **argv) {
    int server_socket, new_socket;
    char buffer[2048];
    struct sockaddr_in server_address;
    struct sockaddr_storage server_storage;
    socklen_t address_size;
    
    sscanf(argv[1],"%d", &port);
    
    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
    	puts("Failed to create server socket.");
    	return 1;
    }    	
    
    server_address.sin_family = AF_INET;    
    server_address.sin_port = htons(port);    
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    memset(server_address.sin_zero, '\0', sizeof server_address.sin_zero);
    
    bind(server_socket, (struct sockaddr *)&server_address, sizeof server_address);
    
    if(listen(server_socket,5)==0)
        printf("\nListening.\n");
    else
        printf("\nError.\n");
    fflush(stdout);    
    
    address_size = sizeof(struct sockaddr_in);
    
    new_socket = accept(server_socket, (struct sockaddr *) &server_storage, &address_size);
    
    if(new_socket < 0){
    	puts("Accept failed.");
    	return 1;
    }
    
/*    strcpy(buffer,"Hello World\n");*/
/*    */
/*    if(send(new_socket,buffer,strlen(buffer),0)<0){*/
/*    	printf("Send to client failed.\n");*/
/*    	return 1;*/
/*    }*/
/*    else*/
/*    	printf("\nSent data to client\n");        */
/*    fflush(stdout);*/
    
    if(recv(new_socket, buffer, sizeof(buffer), 0) < 0)
        printf("No data received from client.\n");
    else
    	printf("Data received: %s\n", buffer);    
        
    //fflush(stdout);
    
    
/*    close(server_socket);*/
/*    close(new_socket);*/
    
    return 0;
}


