#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <poll.h>

#define SERVER "127.0.0.1"
#define SERVER_PORT 5000

#define MAXMSG 1400
#define OP_SIZE 20

#define SEQ0 0
#define SEQ1 1

#define REGISTER "REGISTER"
#define UPDATE "UPDATE"
#define QUERY "QUERY"
#define RESPONSE "RESPONSE"
#define FINISH "FINISH"
#define ACK "ACK"
#define GET "GET"
#define EXIT "EXIT"

#define TIMEOUT 500000		/* 1000 ms */




/* This structure can be used to pass arguments */
struct ip_port {
	unsigned int ip;
	unsigned short port;
};

/* for bonus, store the ip_port options*/
struct ip_port ip_port_option[100];

int set_timeout(int sockfd, int usec) {
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = usec; /* 100 ms */
	int ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
			(struct timeval *)&tv, sizeof(struct timeval));
	if (ret == SO_ERROR) {
		return -1;
	}
	return 0;
}


int unset_timeout(int sockfd) {
	return set_timeout(sockfd, 0);
}


int rdt3_send(int sockfd, struct sockaddr_in servaddr, char ack_num, char *buffer, unsigned len) {
	int waiting = 1;
	char noack_num = ack_num;
	struct sockaddr_in recv_addr;
	unsigned int recv_len;
	char recv_buf[MAXMSG];

	char seq;
	char op[OP_SIZE];
	char remain[MAXMSG];

	sendto(sockfd, (const char *)buffer, len,
		0, (const struct sockaddr *) &servaddr, sizeof(servaddr));

	set_timeout(sockfd, TIMEOUT);

	int parse_idx = 0;

	while (waiting) {

		/***********************************************
		 * You should receive and parse the response here.
		 * Then, you should check whether it is the ACK
		 * packet you are waiting for by comparing the
		 * sequence number and checking packet type.
		 * Waiting until receiving the right ACK.
		 *
		 * START YOUR CODE HERE
		 **********************************************/
		unsigned int addr_len = sizeof(struct sockaddr);
		recv_len = recvfrom(sockfd, &recv_buf, MAXMSG, 0, (struct sockaddr *)&recv_addr, &addr_len);
		if(recv_len > 0)
		{
			memcpy(&seq,recv_buf,sizeof(seq));
			parse_idx += 2;

			memcpy(&op, recv_buf+parse_idx,strlen(ACK));
			parse_idx += strlen(ACK);

			if(seq == noack_num && strncmp(op, ACK, strlen(ACK))==0)
			{

				break;
			}
		}
		else
		{
			sendto(sockfd, (const char *)buffer, len,
				0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
			continue;
		}

		/***********************************************
		 * END OF YOUR CODE
		 **********************************************/

		bzero(recv_buf, MAXMSG);
	}

	unset_timeout(sockfd);

	return 0;
}


/* Send query to the server */
int send_register(int sockfd, struct sockaddr_in servaddr, unsigned int ip, unsigned short port) {
	char buffer[MAXMSG];
	
	bzero(buffer, MAXMSG);

	char seq = SEQ1;

	/* Compose send buffer: REGISTER IP Port */
	int total_len = 0;

	memcpy(buffer, &seq, sizeof(seq));
	total_len ++; /* add a seq */

	buffer[total_len] = ' ';
	total_len ++; /* add a blank */

	memcpy(buffer + total_len, REGISTER, strlen(REGISTER));
	total_len += strlen(REGISTER);

	buffer[total_len] = ' ';
	total_len ++; /* add a blank */

	memcpy(buffer + total_len, &ip, sizeof(ip));
	total_len += sizeof(ip);

	memcpy(buffer + total_len, &port, sizeof(port));
	total_len += sizeof(port);

	buffer[total_len] = '\0';

	rdt3_send(sockfd, servaddr, seq, buffer, total_len);

	printf("REGISTER finished !\n");
	
	return 0;
}


/* Send query to the server */
int send_update(int sockfd, struct sockaddr_in servaddr, unsigned int ip, unsigned short port, unsigned file_map) {
	char buffer[MAXMSG];
	
	bzero(buffer, MAXMSG);

	char seq = SEQ1;

	/***********************************************
	 * You should follw the send_register pattern to
	 * implement a function to send UPDATE message.
	 *
	 * START YOUR CODE HERE
	 **********************************************/
	int total_len = 0;

	memcpy(buffer,&seq, sizeof(seq));
	total_len++;

	buffer[total_len] = ' ';
	total_len++;

	memcpy(buffer + total_len, UPDATE, strlen(UPDATE));
	total_len += strlen(UPDATE);

	buffer[total_len] = ' ';
	total_len++;

	memcpy(buffer + total_len, &ip, sizeof(ip));
	total_len += sizeof(ip);

	memcpy(buffer + total_len, &port, sizeof(port));
	total_len += sizeof(port);

	memcpy(buffer + total_len, &file_map, sizeof(file_map));
	total_len += sizeof(file_map);

	buffer[total_len] = '\0';

	rdt3_send(sockfd,servaddr,seq,buffer,total_len);

	/***********************************************
	 * END OF YOUR CODE
	 **********************************************/
	
	printf("UPDATE finished !\n");

	return 0;
}


int receive_query(int sockfd, struct sockaddr_in servaddr, struct ip_port* option_pointer ) {
	struct sockaddr_in recv_addr;
	unsigned int recv_len;
	char buffer[MAXMSG];

	int n = 0;
	unsigned parse_idx = 0;
	char seq;

	char send_buf[MAXMSG];
	unsigned send_idx = 0;

	unset_timeout(sockfd);

	printf("Receiving query ...\n");

	char unfinished = 1;
	int option = 1; // bonus, for the option number print out
	int num_options = 0; // for bonus
	while (unfinished) {

		n = recvfrom(sockfd, (char *)buffer, MAXMSG,
				MSG_WAITALL, ( struct sockaddr *) &recv_addr, &recv_len);
		if (n < 0) {
			continue;
		}

		buffer[n] = '\0';

		seq = buffer[0];
		parse_idx += 2; /* skip seq and blank */

		

		/* If receive FINISH signal, stop receiving. */
		if (strncmp(buffer + parse_idx, FINISH, strlen(FINISH)) == 0) {
			unfinished = 0;
			option = 1; // for bonus
		/* Receive RESPONSE */
		} else if (strncmp(buffer + parse_idx, RESPONSE, strlen(RESPONSE)) == 0) {
			// Receive and parse packet
			unsigned int ip;
			unsigned short port;

			parse_idx += strlen(RESPONSE);
			parse_idx ++; /*skip blank */

			memcpy(&ip, buffer + parse_idx, sizeof(ip));
			parse_idx += sizeof(ip);

			memcpy(&port, buffer + parse_idx, sizeof(port));
			parse_idx += sizeof(port);

			struct in_addr addr;
			addr.s_addr = ip;
			char *ip_str = inet_ntoa(addr);

			printf("[%d] %s : %d\n", option,ip_str, port); // modified for bonus

			// for bonus
			option_pointer[num_options].ip = ip;
			option_pointer[num_options].port = port;
			num_options++;
			option++;
			

		} else {
			printf("Unknown operation: %s\n", buffer + 2);
			goto nooperation;
		}


		// Compose and send ACK packet
		memcpy(send_buf, &seq, sizeof(seq));
		send_idx += 2; /* seq and blank */

		memcpy(send_buf + send_idx, ACK, strlen(ACK));
		send_idx += strlen(ACK);

		int res = sendto(sockfd, (const char *)send_buf, send_idx,
				0, (const struct sockaddr *) &servaddr, sizeof(servaddr));

		if (res < 0) { 
		}

	nooperation:
		bzero(buffer, MAXMSG);
		bzero(send_buf, MAXMSG);
		parse_idx = 0;
		send_idx = 0;
	}

	return num_options; // modified, return the number of options
}


/* Send query to the server */
int send_query(int sockfd, struct sockaddr_in servaddr, char *filename, int len) {
	char buffer[MAXMSG];

	bzero(buffer, sizeof(buffer));

	char seq = SEQ1;

	/* Compose send buffer: REGISTER IP Port */
	int total_len = 0;

	memcpy(buffer, &seq, sizeof(seq));
	total_len ++; /* add a seq */

	buffer[total_len] = ' ';
	total_len ++; /* add a blank */

	memcpy(buffer + total_len, QUERY, strlen(QUERY));
	total_len += strlen(QUERY);

	buffer[total_len] = ' ';
	total_len ++; /* add a blank */

	memcpy(buffer + total_len, filename, len);
	total_len += len;

	buffer[total_len] = '\0';

	rdt3_send(sockfd, servaddr, seq, buffer, total_len);

	printf("QUERY finished !\n");

	// sleep(1); // [> begin to receive queried messages <]
	
	int n = receive_query(sockfd, servaddr,ip_port_option); // modified for bonus, n means number of options

	return n; // modified for bonus
}


unsigned int get_file_map() {
	DIR *dir;
    struct dirent *entry;
	unsigned int file_map = 0U;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Enumerate files in the directory
    while ((entry = readdir(dir)) != NULL) {
		unsigned int bit = (1U << 31);

		char file_idx = (entry->d_name[0] - '0') * 10 + (entry->d_name[1] - '0');
		if (file_idx < 0 || file_idx > 31) {
			continue;
		}


		file_map |= (bit >> file_idx);
    }

    // Close the directory
    closedir(dir);
	// printf("%u\n",file_map);
	return file_map;
}


// Add a new file descriptor to the set
void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    if (*fd_count == *fd_size) {
        *fd_size *= 2; // Double it

        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}


// Remove an index from the set
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count-1];

    (*fd_count)--;
}


void* p2p_server(void* arg) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAXMSG] = {0};
    FILE *fp;
    ssize_t bytes_read;

	struct ip_port *ip_port_info = (struct ip_port *) arg;

	int fd_count = 0;
	int fd_size = 100; /* at most 100 sockets */
	struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt error");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(ip_port_info->port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) < 0) {
        perror("listen fails to start");
        exit(EXIT_FAILURE);
    }

	printf("p2p server is listening ...\n");

	/***********************************************
	 * Initialize the pfds here.
	 *
	 * START YOUR CODE HERE
	 **********************************************/
	// pfds[0].fd = server_fd;
	// pfds[0].events = POLLIN;
	add_to_pfds(&pfds,server_fd,&fd_count,&fd_size);

	/***********************************************
	 * END OF YOUR CODE
	 **********************************************/

	while (1) {
		int poll_count = poll(pfds, fd_count, -1);

		if (poll_count == -1) {
			perror("poll error");
			exit(1);
		}

		// Run through the existing connections looking for data to read
		for(int i = 0; i < fd_count; i++) {
			// Check if someone's ready to read
			if (pfds[i].revents & POLLIN) {
				if (pfds[i].fd == server_fd) { /* the server receives a connection request */
					/***********************************************
					 * Add your code here to receive a new connection
					 *
					 * START YOUR CODE HERE
					 **********************************************/
					new_socket = accept(server_fd,(struct sockaddr* )&address, &addrlen);
					if(new_socket < 0)
					{
						perror("accept failed");
						exit(EXIT_FAILURE);
					} 
					add_to_pfds(&pfds,new_socket,&fd_count,&fd_size);

					/***********************************************
					 * END OF YOUR CODE
					 **********************************************/


				} else { /* the client receive a message */

					new_socket = pfds[i].fd;

					// Receive file name from client
					if (recv(new_socket, buffer, MAXMSG, 0) < 0) {
						perror("recv");
						exit(EXIT_FAILURE);
					}
					// printf("receve connection\n");

					// Open requested file
					fp = fopen(buffer, "rb");
					if (fp == NULL) {
						perror("fopen file error");
						exit(EXIT_FAILURE);
					}

					bzero(buffer, MAXMSG);

					long file_size;
					// Get the file size
					fseek(fp, 0, SEEK_END);
					file_size = ftell(fp);
					fseek(fp, 0, SEEK_SET);

					/***********************************************
					 * Refer to the description, send the file length
					 * and file content to the p2p client.
					 *
					 * START YOUR CODE HERE
					 **********************************************/
					// strncpy(buffer,(char*)&file_size, sizeof(fd_size));
					if(send(new_socket,&file_size,sizeof(file_size),0) < 0)
					{
						perror("send length failed\n");
						exit(EXIT_FAILURE);
					}

					long remain_size = file_size;
					bzero(buffer,MAXMSG);
					while(remain_size > 0)
					{
						bzero(buffer,MAXMSG);
						bytes_read = fread(buffer,sizeof(char),MAXMSG,fp);
						if(send(new_socket, buffer, bytes_read, 0) < 0)
						{
							perror("send file failed\n");
							exit(EXIT_FAILURE);
						}
						remain_size -= bytes_read;
						
					} 

					/***********************************************
					 * END OF YOUR CODE
					 **********************************************/

					fclose(fp);
					close(new_socket);
					del_from_pfds(pfds, i, &fd_count);

					bzero(buffer, MAXMSG);


				}
			}
		}
	}

    close(server_fd);
	pthread_exit(NULL);
}


int p2p_client(unsigned int ip, unsigned short port, char *file_name) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAXMSG] = {0};
    FILE *fp;
    ssize_t bytes_read;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket fails to create");
        return -1;
    }

    // Set server address and port
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = ip;
    serv_addr.sin_port = htons(port);

	printf("Connecting to p2p server ...\n");

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect error");
        return -1;
    }

	sleep(5);

    // Send file name to server
    if (send(sock, file_name, strlen(file_name), 0) < 0) {
        perror("send file name error");
        return -1;
    }


    // Receive file contents from server
    fp = fopen(file_name, "wb");
    if (fp == NULL) {
        perror("fopen file error");
        return -1;
    }


	/***********************************************
	 * Refer to the description of file transfer
	 * process to receive and save the file.
	 *
	 * START YOUR CODE HERE
	 **********************************************/
	long file_size = 0;

	if(recv(sock,&file_size,sizeof(file_size),0) < 0)
	{
		perror("receive length failed.\n");
		exit(EXIT_FAILURE);
	}
	// printf("%ld\n",file_size);
	while(file_size > 0)
	{
		bzero(buffer,MAXMSG);
		
		bytes_read = recv(sock,buffer,MAXMSG,0);
		// printf("receive %ld bytes: %s", bytes_read,buffer);
		if(bytes_read < 0)
		{
			perror("receive file failed.\n");
			exit(EXIT_FAILURE);
		}
		fwrite(buffer, sizeof(char), bytes_read, fp);
		file_size -= bytes_read;
		
		
	}



	/***********************************************
	 * END OF YOUR CODE
	 **********************************************/

	printf("Receive finished !\n");

    fclose(fp);
    close(sock);
    return 0;
}


void clear (void)
{
    while ( getchar() != '\n' );
}


int main() {


	char ip_string[20] = "127.0.0.1";
	unsigned short port = 6000;

	printf("\nInput ip address: ");
	scanf("%s", ip_string);
	unsigned int ip = inet_addr(ip_string);

	printf("\nInput port number: ");
	scanf("%hu", &port);

	/* start p2p server service */
	pthread_t tid;
	struct ip_port arg;
	arg.ip = ip;
	arg.port = port;

	printf("Creating p2p server ...\n");

	/***********************************************
	 * Start the p2p server using pthread
	 *
	 * START YOUR CODE HERE
	 **********************************************/

	if(pthread_create(&tid,NULL,&p2p_server,&arg) != 0)
	{
		perror("pthread_create failed\n");
		exit(EXIT_FAILURE);
	}


	/***********************************************
	 * END OF YOUR CODE
	 **********************************************/

	sleep(1);


	int sockfd;
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER);
	servaddr.sin_port = htons(SERVER_PORT);

	char command[100];
	char file_name[256];
	unsigned int local_map;

	char register_flag = 0;
	char query_flag = 0;

	int num_options; // for bonus

	do {
		clear();

		bzero(command, sizeof(command));

		printf("\nInput command: ");
		scanf("%s", command);

		if (strncmp(command, REGISTER, strlen(REGISTER)) == 0) {
			printf("resigter\n");
			send_register(sockfd, servaddr, ip, port);
			register_flag = 1;
			continue;
		}

		if (strncmp(command, UPDATE, strlen(UPDATE)) == 0) {
			if ( register_flag == 0 ) {
				printf("You should first register!");
			} else {
				local_map = get_file_map();
				send_update(sockfd, servaddr, ip, port, local_map);
			}
			continue;
		}

		if (strncmp(command, QUERY, strlen(QUERY)) == 0) {
			printf("\nInput file name: ");
			scanf("%s", file_name);
			num_options = send_query(sockfd, servaddr, file_name, strlen(file_name));// modified for bonus
			query_flag = 1;
			continue;
		}

		if (strncmp(command, GET, strlen(GET)) == 0) {

			if ( query_flag == 0 ) {
				printf("You should first query some files!");
			} else {
				char input_ip[32];
				unsigned short input_port;
				char input_buffer[MAXMSG];
				bzero(input_buffer,MAXMSG);

				printf("\nInput ip port (e.g., 127.0.0.1 6001) or option (e.g., 1): "); // modified for bonus
				clear(); // clear stdin
				fgets(input_buffer,MAXMSG,stdin);
				ungetc('\n',stdin);
				
				if(strlen(input_buffer) < 7)// option 
				{
					int input_option = atoi(input_buffer) - 1;
					if(input_option < 0 || input_option >= num_options)
					{
						printf("invalid input option.\n");
						continue;
					}	
					p2p_client(ip_port_option[input_option].ip,ip_port_option[input_option].port,file_name);					
				}
				else // normal (ip_port pair)
				{
					sscanf(input_buffer, "%s %hu", input_ip,&input_port);
					p2p_client(inet_addr(input_ip), input_port, file_name);
				}

				

				sleep(2);

				/* then update */
				local_map = get_file_map();
				send_update(sockfd, servaddr, ip, port, local_map);
			}

			continue;
		}

		if (strncmp(command, EXIT, strlen(EXIT)) == 0) {
			printf("Exit!");
			return 0;
		}

		printf("\nValid commands: REGISTER | UPDATE | QUERY | GET | EXIT\n");

	} while (1);

    // Wait for server thread to finish
    if (pthread_join(tid, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

	close(sockfd);
	return 0;
}
