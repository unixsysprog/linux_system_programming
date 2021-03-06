#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <limits.h> 
#include <netdb.h> 
#include "protocol.h"
#include "clnt_common.h"
#include "base.h"



/**
 * Much of this taken from provided client.c code
 */
int main(int argc, char *argv[])
{
	int socketFD, portNumber;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
   
  // Check usage & args 
	if (argc < 4) { fprintf(stderr,"USAGE: %s plaintext_file key_file port\n", argv[0]); exit(0); } 

  int ptfsz = verify_file(argv[1]);
  int kfsz = verify_file(argv[2]);
  if(kfsz < ptfsz){ error("Key file of insufficient length"); }
  
  // Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) 
		error("CLIENT: ERROR connecting");

  //Identify ourselves to server
  send_client_type(socketFD, ENCC);
  parse_response(socketFD);

  //send plaintext file size
  send_file_size(socketFD, ptfsz);
  parse_response(socketFD);
  
  //send plaintext 
  send_file(socketFD, argv[1], ptfsz);
  parse_response(socketFD);
  
  //send key file size
  send_file_size(socketFD, kfsz);
  parse_response(socketFD);
  
  //send key 
  send_file(socketFD, argv[2], kfsz);
  parse_response(socketFD);
  
  //get cyphertext 
  char *encbuff = NULL;
  encbuff = recv_bytes(socketFD, ptfsz);
  if(DEBUG){fprintf(stderr, "%s", "otp_enc: after recv_bytes\n");}

  //print out encbytes!
  fprintf(stdout, "%s", encbuff);
  
  //we're closing in the parent, so the call to shutdown shouldn't be necessary  
  shutdown(socketFD, SHUT_WR);
  close(socketFD);
	return 0;
}


