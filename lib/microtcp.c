/*
 * microtcp, a lightweight implementation of TCP for teaching,
 * and academic purposes.
 *
 * Copyright (C) 2015-2017  Manolis Surligas <surligas@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "microtcp.h"

microtcp_sock_t
microtcp_socket (int domain, int type, int protocol)
{
  microtcp_sock_t s;
  int sock;
  if ((sock = socket (AF_INET,SOCK_DGRAM ,0)) == -1) {
      perror ( " SOCKET COULD NOT BE OPENED " );
      return s;
  }
  srand(time(0));
  s.sd = sock;
  s.state = INVALID;
  s.init_win_size = MICROTCP_WIN_SIZE ;
  s.curr_win_size = MICROTCP_WIN_SIZE ;
  s.buf_fill_level = 0;
  s.recvbuf = 0;
  s.cwnd = 0;
  s.ssthresh = 0;
  s.seq_number = 0;
  s.ack_number = 0;
  s.packets_send = 0;
  s.packets_received = 0;
  s.packets_lost = 0;
  s.bytes_send = 0;
  s.bytes_lost = 0;
  s.bytes_received = 0;
  return s; 
}

void print_microtcp_header(const microtcp_header_t *header) {
    //einai anapoda px: 1 0 0  einai to 0 0 1
    printf("Sequence Number: [%d]\t", header->seq_number);
  //    uint32_t num32 = header->seq_number;
  //     for(uint32_t bit=0;bit<(sizeof(uint32_t) *(uint32_t) 8); bit++){
  //     printf("%i ", num32 & 0x01);
  //     num32 = num32 >> 1;
  //  }
   printf("\n");
    printf("ACK Number: [%d]    ", header->ack_number);
  //   num32 = header->ack_number;
  //     for(uint32_t bit=0;bit<(sizeof(uint32_t) * (uint32_t) 8); bit++){
  //     printf("%i ", num32 & 0x01);
  //     num32 = num32 >> 1;
  //  }
   printf("\n");

    printf("Control Bits: [%d]    ", header->control);
     uint16_t num16 = header->control;
          printf("[");
       for(uint16_t bit1=0;bit1<(sizeof(uint16_t ) * (uint16_t) 8); bit1++){
       printf("%i ", num16 & 0x01);
       num16 = num16 >> 1;
  }
   printf("]\n");

    printf("Window Size: [%d] bytes    ", header->window);
  //   num16 = header->window;
  //     for(uint16_t bit1=0;bit1<(sizeof(uint16_t ) * (uint16_t) 8); bit1++){
  //     printf("%i ", num16 & 0x01);
  //     num16 = num16 >> 1;
  //  }
   printf("\n");

    printf("Data Length: [%d] bytes    ", header->data_len);
  //   num32 = header->data_len;
  //     for(int32_t bit=0;bit<(sizeof(uint32_t) * (uint32_t) 8); bit++){
  //     printf("%i ", num32 & 0x01);
  //     num32 = num32 >> 1;
  //  }
   printf("\n");

   
    printf("Checksum: [%d]    ", header->checksum);
  //   num32 = header->checksum;
  //     for(int32_t bit=0;bit<(sizeof(uint32_t) * (uint32_t) 8); bit++){
  //     printf("%i ", num32 & 0x01);
  //     num32 = num32 >> 1;
  //  }
   printf("\n");
}

void assign_checksum_to_packet(void* ptr){
  microtcp_header_t *p = (microtcp_header_t*) ptr;
  p->checksum = crc32(ptr,MICROTCP_RECVBUF_LEN);
}

void header_set(microtcp_sock_t *socket,microtcp_header_t *header, uint32_t seq_number, uint32_t ack_number, uint16_t control, uint16_t window){
  header->seq_number = seq_number;
  header->ack_number = ack_number;
  header->control = control;
  header->window = window;
  header->data_len = MICROTCP_MSS;
  header->checksum = 0;

  memcpy(socket->sendbuf,header,sizeof(microtcp_header_t));
  assign_checksum_to_packet(socket->sendbuf);
}


int
microtcp_bind (microtcp_sock_t *socket, const struct sockaddr *address,
               socklen_t address_len)
{
   if(bind(socket->sd,address,address_len) == -1){
    perror("Error in binding the socket");
    return -1;
  }
  socket->state = LISTEN;
  return 0;
}

int
microtcp_connect (microtcp_sock_t *socket, const struct sockaddr *address,socklen_t address_len){
  microtcp_header_t first;
  struct sockaddr_in myaddress;
  microtcp_header_t *ptr;
  uint32_t N = rand() % 10000;
  socket->type = 1;
  myaddress.sin_family = AF_INET;
  myaddress.sin_port = htons(19243);
  myaddress.sin_addr.s_addr = htonl(INADDR_ANY);
  if(microtcp_bind(socket, (const*) &myaddress,address_len)== -1){
    return -1;
  }
  socket->address =(struct sockaddr_in*) address;
  socket->address_len = address_len;

  socket->sendbuf = malloc(MICROTCP_SENDBUF_LEN);
  socket->recvbuf = malloc(MICROTCP_RECVBUF_LEN);
  
  ptr = (microtcp_header_t*) socket->recvbuf;
  memset(socket->sendbuf,0,MICROTCP_SENDBUF_LEN);
  memset(socket->recvbuf,0,MICROTCP_RECVBUF_LEN);

  header_set(socket,&first,N,0,0b0100000000000000,socket->curr_win_size);
  if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,address,address_len) == -1){
    perror("error in sending\n");
    return -1;
  }

  recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,NULL,NULL);
  if(!check_checksum(socket->recvbuf)){
    perror("different checksums");
    return -1;
  }

  if(ptr->control != 0b0001000000000000 ){
    perror("Wrong control bits received\n");
    return -1;
  }
  printf("Client received the second packet\n");
  print_microtcp_header((microtcp_header_t*)socket->recvbuf);
  header_set(socket,&first, N+1, ptr->seq_number + 1, 0b0001000000000000,socket->init_win_size);
  if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,address,address_len) == -1){
    perror("error in sending\n");
    return -1;
  }
  socket->state = ESTABLISHED;
  socket->seq_number = N + 1 ;
  socket->ack_number = ptr ->seq_number + 1;
  return 0;
}

int check_checksum(void* buf){
  microtcp_header_t* pointer = (microtcp_header_t*) buf;
  void* buf2 = malloc(MICROTCP_RECVBUF_LEN);
  microtcp_header_t* pointer2 = (microtcp_header_t*) buf2;
  memcpy(buf2,buf,MICROTCP_RECVBUF_LEN);
  pointer2->checksum = 0;
  pointer2->checksum = crc32(buf2,MICROTCP_RECVBUF_LEN);
  if( pointer2->checksum != pointer->checksum ){
    printf("RECEIVED CHECKSUM :: %d\n", pointer->checksum );
    printf("CALCULATED CHECKSUM :: %d\n", pointer2->checksum );
    free(buf2);
    return 0;
  }
  free(buf2);
  return 1; 
}

int
microtcp_accept (microtcp_sock_t *socket, struct sockaddr *address,socklen_t address_len){
  microtcp_header_t second;
  int M = rand() % 10000;
  socket->type = 0;
  socket->recvbuf =  malloc(MICROTCP_RECVBUF_LEN);
  socket->sendbuf =  malloc(MICROTCP_SENDBUF_LEN);
  memset(socket->sendbuf,0,MICROTCP_SENDBUF_LEN);
  memset(socket->recvbuf,0,MICROTCP_RECVBUF_LEN);
  microtcp_header_t* ptr = (microtcp_header_t*) socket->recvbuf;
  if(recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,address,&address_len) ==-1){
    perror(" ");
    return -1;
  }
  socket->address = address;
  socket->address_len = address_len;
  if(!check_checksum(socket->recvbuf)){
    perror("different checksums");
    return -1;
  }
  if(ptr->control != 0b0100000000000000 ){
    perror("Wrong control bits received\n");
    return -1;
  }
  socket->init_win_size = ptr->window;
  socket->curr_win_size = ptr->window; 
  printf("Server received the first packet  \n");
  print_microtcp_header((microtcp_header_t*)socket->recvbuf);

  header_set(socket,&second,M,ptr->seq_number + 1,0b0001000000000000,socket->curr_win_size);

  if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,address,address_len) == -1){
    return -1;
  }
  memset(socket->recvbuf,0,MICROTCP_RECVBUF_LEN);
  if(recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,NULL,NULL)==-1){
    return -1;
  }
  if(!check_checksum(socket->recvbuf)){
    perror("different checksums");
    return -1;
  }
  if(ptr->control != 0b0001000000000000 ){
    perror("Wrong control bits received\n");
    return -1;
  }
  printf("\nServer received the third packet : \n");
  print_microtcp_header((microtcp_header_t*)socket->recvbuf);
  socket->state = ESTABLISHED;
  socket->seq_number = M ;
  socket->ack_number = ptr ->seq_number + 1;
  return 0;
}

int microtcp_shutdown (microtcp_sock_t *socket, int how){
  struct sockaddr_in address;
  socklen_t len = sizeof(address);
  microtcp_header_t *ptr = (microtcp_header_t*)socket->recvbuf;
  microtcp_header_t h;
  memset(socket->recvbuf,0,MICROTCP_RECVBUF_LEN);
  memset(socket->sendbuf,0,MICROTCP_SENDBUF_LEN);
  switch(socket->type){
    case 0:
    if(how != 1){
      if(recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,(struct sockaddr*) &address,&len)==-1){
        return -1;
      }
     
      if(!check_checksum(socket->recvbuf)){
        perror("different checksums");
        return -1;
      }
      printf("\n\nServer received first FIN PACKET : \n");
      print_microtcp_header((microtcp_header_t*)socket->recvbuf);
    }  

    header_set(socket,&h,0,ptr->seq_number + 1,0b0001000000000000,socket->curr_win_size);
    if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,(struct sockaddr*) &address,len) == -1){
      return -1;
    }
    socket->state = CLOSING_BY_PEER;
    header_set(socket,&h,rand() % 100000,0,0b1001000000000000,socket->curr_win_size);

    if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,(struct sockaddr*) &address,len) == -1){
      return -1;
    }
    if(recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,(struct sockaddr*) &address,&len)==-1){
      return -1;
    }
    socket->state = CLOSED;
    if(!check_checksum(socket->recvbuf)){
      perror("different checksums");
      return -1;
    }
    printf("\n\nServer received last ACK packet: \n");
    print_microtcp_header((microtcp_header_t*)socket->recvbuf);
    break;



    case 1: 
    address.sin_family = AF_INET;
    address.sin_port = htons(19242);
    address.sin_addr.s_addr = htonl(INADDR_ANY);


    header_set(socket,&h,rand() % 100000,0,0b1001000000000000,socket->curr_win_size);
    socket->seq_number = h.seq_number;
    if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,(struct sockaddr*) &address,len) == -1){
      return -1;
    }
    if(recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,NULL,NULL)==-1){
      return -1;
    }
    if(!check_checksum(socket->recvbuf)){
      perror("different checksums");
      return -1;
    }
    socket->state = CLOSING_BY_HOST;
    printf("\n\nClient received ACK PACKET: \n");
    print_microtcp_header((microtcp_header_t*)socket->recvbuf);
    memset(socket->recvbuf,0,MICROTCP_RECVBUF_LEN);
    if(recvfrom(socket->sd,socket->recvbuf,MICROTCP_RECVBUF_LEN,0,NULL,NULL)==-1){
      return -1;
    }
    if(!check_checksum(socket->recvbuf)){
      perror("different checksums");
      return -1;
    }
    printf("\n\nClient received FIN,ACK PACKET : \n");
    print_microtcp_header((microtcp_header_t*)socket->recvbuf);
    header_set(socket,&h,socket->seq_number + 1,ptr->seq_number + 1,0b0001000000000000,socket->curr_win_size);
    socket->state = CLOSED;
    if(sendto(socket->sd,socket->sendbuf,MICROTCP_RECVBUF_LEN,0,(struct sockaddr*) &address,len) == -1){
      return -1;
    }
    break;
    default: 
    break;
  }
  return 0;
}

ssize_t microtcp_send (microtcp_sock_t *socket, const void *buffer, size_t length, int flags){
  microtcp_header_t *head = (microtcp_header_t*) malloc(sizeof(microtcp_header_t));
  if (socket == NULL || buffer == NULL || length == 0) {
      return -1;  
  }
  head->seq_number=socket->seq_number;
  size_t frag = length / MICROTCP_MSS ; //sel 229,232
  if(length % MICROTCP_MSS){
      frag++;
  }
  int i;

  head->seq_number+=MICROTCP_MSS;
  socket->seq_number+=MICROTCP_MSS;
  for(i = 0; i<frag; i++){
    memset(socket->sendbuf,'0',MICROTCP_SENDBUF_LEN);
    memcpy(socket->sendbuf+sizeof(microtcp_header_t),buffer + i*MICROTCP_MSS,MICROTCP_MSS);
    header_set(socket,head,head->seq_number,0,0,socket->curr_win_size);
    socket->bytes_send += sendto(socket->sd,socket->sendbuf,sizeof(microtcp_header_t)+MICROTCP_MSS,flags, (struct sockaddr *) (socket->address),socket->address_len);
    printf("PACKET SENT WITH SEQ_NO: [%d]\n", socket->seq_number);
    head->seq_number+=MICROTCP_MSS;
    socket->seq_number+=MICROTCP_MSS;
  }
  for(i = 0; i<frag; i++){
      memset(socket->recvbuf,'0',MICROTCP_RECVBUF_LEN);
      recvfrom(socket->sd,socket->recvbuf,sizeof(microtcp_header_t),0,NULL,NULL);
      printf("ACK NO:[%d]\n", i );
      print_microtcp_header((microtcp_header_t*) socket->recvbuf);
  }
    free(head);
    return length;
}

ssize_t microtcp_recv (microtcp_sock_t *socket, void *buffer, size_t length, int flags){
  size_t left = 0;
  int count = length / MICROTCP_MSS;
  microtcp_header_t h;
  left = length % MICROTCP_MSS;
  while(count>0){
    memset(socket->recvbuf,'0',MICROTCP_RECVBUF_LEN);
    recvfrom(socket->sd,socket->recvbuf,sizeof(microtcp_header_t) + MICROTCP_MSS,flags,NULL,NULL);
    if(!check_checksum(socket->recvbuf)){
      perror("different checksums");
      return -1;
    }
    header_set(socket,&h,socket->seq_number,socket->ack_number,0,100);
    sendto(socket->sd,socket->sendbuf,sizeof(microtcp_header_t),0,socket->address,socket->address_len);
    printf("Count :: %d \n\n", count );
    print_microtcp_header((microtcp_header_t*)socket->recvbuf);
    count--;
    socket->ack_number += MICROTCP_MSS;
    socket->packets_received++;
  }
  if(left!=0){
    recvfrom(socket->sd,socket->recvbuf,left + sizeof(microtcp_header_t),flags,NULL,NULL);
    if(!check_checksum(socket->recvbuf)){
      perror("different checksums");
      return -1;
    }
    print_microtcp_header((microtcp_header_t*)socket->recvbuf);
  }
}
