/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <math.h>
#include <ctype.h>

static int port = -1, r, start_again;
static char message[1024],choice[1];


int main(int argc, char **argv) {
    time_t t;
    int server_socket, client_socket;
    char reply[2048];
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
    else{
        puts("Error.");
    	return 1;
    }
    fflush(stdout);    
    
    address_size = sizeof(struct sockaddr_in);
    
    client_socket = accept(server_socket, (struct sockaddr *) &server_storage, &address_size);
    
    if(client_socket < 0){
    	puts("Accept failed.");
    	return 1;
    }
    
/*    strcpy(reply,"Hello World\n");*/
/*    */
	
	while(1){
    
		if(recv(client_socket, reply, sizeof(reply), 0) < 0){
			puts("No data received from client.");
			return 1;
		}        
		else
			printf("Data received: %s\n", reply);    
		    
		fflush(stdout);
	   
		r = (rand()%2);
		
		printf("Choice is %d\n", r);
		
		switch(r){
			case 0:
				strcpy(choice, "s");
				puts("Server chose Silent.\n");
				break;
			case 1:
				strcpy(choice, "b");
				puts("Server chose Betray.\n");
				break;
			default:
				puts("\nServer failed to make a choice.");
				return 1;
		}
		    
		if(strcasecmp(reply, choice) < 0){
			strcpy(message, "\nOh, you Betrayed the server. You monster!\n");
		}
		else if(strcasecmp(reply, choice) > 0)
			strcpy(message, "\nThe server decided to betray you. Tough luck.\n");
		else{
			if(strcasecmp(choice,"b") == 0)
				strcpy(message, "\nYou both chose to Betray. How intriguing!\n");
			else if(strcasecmp(choice,"s") == 0)
				strcpy(message, "\nYou both chose to remain Silent.\n");
		}
		
		printf("This is the message length: %zu\n", strlen(message));
		
		printf("This is the message: ");
		puts(message);    
		
		if(send(client_socket, message, sizeof(message), 0) <= 0){
			printf("Send to client failed.\n");
			return 1;
		}
		else
			printf("\nSent data to client\n");        
		
		
		
		fflush(stdout);
		
		if(recv(client_socket, reply, sizeof(reply), 0) <= 0){
			puts("No reply from client to continue game. Goodbye.");
			return 1;
		}
		if(strcasecmp(reply,"n") == 0)
			break;    
    }
    
/*    close(server_socket);*/
/*    close(client_socket);*/
    
    return 0;
}


