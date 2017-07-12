/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kristofer
 *
 * Created on July 11, 2017, 6:46 PM
 */

#include <stdio.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
/*
 * 
 */
static int port;


int main(int argc, char **argv) {
    int client_socket;
    char buffer[2048];
    struct sockaddr_in server_address;
    //struct sockaddr_storage server_storage;
    socklen_t address_size;    
    
    sscanf(argv[1],"%d", &port);
    //sscanf(argv[2],"%s", &IP);
    client_socket = socket(PF_INET,SOCK_STREAM,0);
    if(client_socket==-1){
    	puts("Failed to create client socket.");
    	return 1;
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);    
    server_address.sin_addr.s_addr = inet_addr(argv[2]);
    
    memset(server_address.sin_zero,'\0',sizeof(server_address.sin_zero));    
    
    address_size = sizeof(server_address);
    
    if(connect(client_socket,(struct sockaddr *) &server_address, address_size) < 0){
    	printf("\nFailed to connect to server.\n");
    	return 1;
    }
    else
    	printf("\nConnected to server.\n");        
    fflush(stdout);
    
    strcpy(buffer, "This is the client sending things.");
    
    if(send(client_socket, buffer, strlen(buffer), 0) < 0){
    	puts("Send failed");
    	return 1;    
    }
    else    
    	printf("\nSent to server.\n");   
    fflush(stdout); 

/*    if(recv(client_socket, buffer, strlen(buffer), 0)>=0)*/
/*        printf("Data received: %s\n", buffer);*/
/*    else*/
/*        printf("No data received from server.\n");*/
/*    fflush(stdout);*/
    
    //close(client_socket);
    return 0;
}

