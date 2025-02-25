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

/*
 * You can use this file to write a test microTCP server.
 * This file is already inserted at the build system.
 */

#include "../lib/microtcp.h"


int main(int argc, char **argv){
    
    microtcp_sock_t server;
    void* buf[512] = {0};
    int megethos=0;
    struct sockaddr_in myaddress;
    struct sockaddr_in client_address;
    socklen_t len = sizeof(myaddress);
    memset(&myaddress,0,sizeof(struct sockaddr_in));
    myaddress.sin_family = AF_INET;
    myaddress.sin_port = htons(19242);
    myaddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // client_address.sin_family = AF_INET;
    // client_address.sin_port = htons(19243);
    // client_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server = microtcp_socket(0,0,0);
    if(microtcp_bind(&server,(struct sockaddr*) &myaddress,sizeof(struct sockaddr_in)) == -1){
        exit(-1);
    }
    memset(&myaddress,0,sizeof(struct sockaddr_in));
    if(microtcp_accept(&server,(struct sockaddr*) &client_address,len)==-1){
        exit(-1);
    }
    microtcp_recv(&server,NULL,1000,0);
    // microtcp_shutdown(&server,0);
}
