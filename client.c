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
#include <stdlib.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <math.h>
#include <ctype.h>
/*
 * 
 */
static int port;
static char p[1];

void play_again(){
	
	while(1){
		puts("Play again? (Y/N)");
	
		scanf("%s", p);
		
		if(strcasecmp(p,"y") == 0 || strcasecmp(p,"n") == 0)
			return;		
		
		puts("I'm sorry, I didn't understand that answer.");	 	
	}
}

int main(int argc, char **argv) {
    char message[1], reply[1024];
       
    
    int client_socket;
    //char message[2048];
    struct sockaddr_in server_address;
    //struct sockaddr_storage server_storage;
    socklen_t address_size;    
    
    sscanf(argv[1],"%d", &port);
    //sscanf(argv[2],"%s", &IP);
    client_socket = socket(PF_INET,SOCK_STREAM,0);
    if(client_socket==-1){
    	puts("\nFailed to create client socket.");
    	return 1;
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);    
    server_address.sin_addr.s_addr = inet_addr(argv[2]);
    
    memset(server_address.sin_zero,'\0',sizeof(server_address.sin_zero));    
    
    address_size = sizeof(server_address);
    
    if(connect(client_socket,(struct sockaddr *) &server_address, address_size) < 0){
    	puts("\nFailed to connect to server.");
    	return 1;
    }
/*    else*/
/*    	printf("\nConnected to server.\n");        */
    
    
    while(1){    
    
		printf("Please type S for Silent, or B for Betray: ");
		scanf("%s", message);
		
		while(1){    	
			if((tolower(message[0])-tolower('s')) == 0){
				printf("\nYou have chosen to remain Silent. ");
				break;
			}
			else if((tolower(message[0])-tolower('b')) == 0){
				printf("\nYou have chosen to Betray. How naughty. ");
				break;
			}
			else{
				printf("\nYou have entered an incorrect option. ");
				fflush(stdout);
				printf("Please type S for Silent, or B for Betray: ");
		scanf("%s", message);	
			}
		}
		//strcpy(message, "This is the client sending things.");
		
		if(send(client_socket, message, sizeof(message), 0) < 0){
			puts("Send failed");
			return 1;    
		}
		else    
			printf("Your choice is being processed.\n");   
		//fflush(stdout); 
		
		if(recv(client_socket, reply, sizeof(reply), 0) <= 0){
		    printf("No data received from server.\n");
			return 1;
		}
		else
		    puts(reply);
				
		fflush(stdout);
    	
    	play_again();
    	
    	if(strcasecmp(p, "n") == 0)
    		break;
    	else{    		
    		
    		if(send(client_socket, p, sizeof(p), 0) <= 0){
    			puts("Failed to send game request to server. Goodbye.");
    			return 1;
    		}
    	}			
    }
    
    puts("Thanks for playing!");
    //close(client_socket);
    return 0;
}

