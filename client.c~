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


/*This is to handle if the player wants to play again*/
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
    
    struct sockaddr_in server_address;
    
    socklen_t address_size;    
    
    //Scan the port and assign it to a variable
    sscanf(argv[1],"%d", &port);
    
    //Create the socket for connecting to server     
    client_socket = socket(PF_INET, SOCK_STREAM,0);
    
    if(client_socket==-1){
    	puts("\nFailed to create client socket.");
    	return 1;
    }
    
    //Set up server_address things
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);    
    server_address.sin_addr.s_addr = inet_addr(argv[2]);
    
    //Create the variable because I am lazy.
    address_size = sizeof(server_address);
    
    //Error checking the connection
    if(connect(client_socket,(struct sockaddr *) &server_address, address_size) < 0){
    	puts("\nFailed to connect to server.");
    	return 1;
    }
    
    //While loop for the duration of the game.
    while(1){    
    
		printf("Please type S for Silent, or B for Betray: ");
		scanf("%s", message);
		
		//Initial tomfoolery to compare characters. I have yet to change it.
		//Also interprets player input, and repeats if it is incorrect input.
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
		
		//Error checking if the message is sent to server.
		if(send(client_socket, message, sizeof(message), 0) < 0){
			puts("Send failed");
			return 1;    
		}
		else    
			printf("Your choice is being processed.\n");   
		 
		//Error checking for receiving a reply from server.
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
    		//Error checking to send a request to play again.
    		if(send(client_socket, p, sizeof(p), 0) <= 0){
    			puts("Failed to send game request to server. Goodbye.");
    			return 1;
    		}
    	}			
    }
    
    puts("Thanks for playing!");
    close(client_socket);
    return 0;
}

