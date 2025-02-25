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
 * You can use this file to write a test microTCP client.
 * This file is already inserted at the build system.
 */

#include "../lib/microtcp.h"

int main(int argc, char **argv){
   microtcp_sock_t s;
   char buf[1000] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tincidunt tortor vel quam eleifend, ut rhoncus elit scelerisque. Proin ut bibendum ipsum. Vivamus aliquam risus eu ligula malesuada, eu fermentum justo dapibus. Duis vulputate arcu et dolor auctor, at mattis lectus cursus. Nulla facilisi. Integer ac nulla vel nulla posuere vestibulum. Quisque nec justo nec neque bibendum efficitur ac vitae justo. Maecenas varius metus at odio consectetur, in volutpat sapien tincidunt. Ut et hendrerit lectus. Praesent euismod, justo sit amet tempor malesuada, eros arcu gravida justo, ut fermentum ligula libero vel elit. Nam id justo vel tortor malesuada euismod. Sed malesuada orci nec velit dictum, eu tincidunt lectus vestibulum. Aenean eget ex vel ligula dignissim vestibulum. Vestibulum fermentum purus id ex auctor, ac fringilla tortor vulputate. Donec tristique purus id justo fermentum, ac commodo turpis convallis. Fusce efficitur, sem quis suscipit posuere, lacus ex aliquam orci, at iaculis elit libero nec mi. In hac habitasse platea dictumst. Curabitur facilisis dolor vel facilisis mattis. Maecenas congue elit in facilisis ultrices. Sed sit amet justo ac nunc tincidunt cursus eu eu arcu. Ut quis justo vitae sapien dapibus cursus. Fusce vel bibendum nulla. Phasellus tristique vestibulum dapibus. Nullam venenatis ligula vitae ante ultricies, vel accumsan arcu congue. Duis at tortor fringilla, posuere tortor nec, fermentum ligula. Sed eu metus tristique, sodales lacus vel, viverra mi. Morbi dapibus elit sed nulla venenatis, ac dapibus orci euismod. Integer consectetur justo eu eros tempus, id bibendum leo vulputate. Integer in turpis vel tortor congue dictum. Curabitur pharetra sem vel sapien accumsan, nec bibendum tortor gravida. Sed tincidunt felis eu justo finibus, vel scelerisque justo ultricies. In ac accumsan odio. Aliquam fringilla dictum nisi vel auctor. In in bibendum odio. Nam non ligula vel arcu dapibus pellentesque. Nulla facilisi. Fusce varius quam nec ligula tristique, vel consectetur tortor malesuada. Maecenas in libero ut ligula mattis ullamcorper sit amet id purus. Fusce id felis sed orci tincidunt fermentum vel in metus. Integer ullamcorper justo vitae quam luctus, non ultrices ligula tincidunt. Curabitur ac lacinia lacus. Fusce quis tellus et nunc volutpat tristique sit amet ut mauris. Curabitur ut odio non quam efficitur accumsan. Fusce euismod diam vel sagittis mattis. Phasellus ullamcorper dui nec nisl tempus, ut ultricies metus vestibulum. Suspendisse quis augue id odio iaculis bibendum. Vestibulum eu lectus ut turpis vehicula facilisis. Nam eu magna ut tortor tincidunt fringilla sit amet vitae quam. Sed auctor quam et tellus egestas, ac scelerisque velit tincidunt. Suspendisse id felis ut neque dictum blandit. Aenean sit amet metus at lacus scelerisque viverra ut nec justo. Integer tincidunt odio eu ligula efficitur tincidunt. In hac habitasse platea dictumst. Vivamus quis dui ac purus ullamcorper iaculis ut ac nisi. Sed eu arcu a libero malesuada fermentum vel nec quam. Integer vel tellus vel justo cursus convallis. Phasellus ullamcorper lacus et dui scelerisque, eu interdum purus eleifend. Integer in mauris sed augue dictum vulputate eu at elit. Sed fermentum quam id orci fermentum, at auctor tortor volutpat. Suspendisse consectetur arcu ut ligula sagittis, ut tristique libero scelerisque. In eu ligula et turpis rhoncus hendrerit eu vel metus. Fusce aliquam ipsum eu interdum feugiat. Curabitur nec lectus vel ligula viverra egestas. Donec sit amet sapien ac tellus sagittis hendrerit. Morbi euismod odio at bibendum vulputate. Vestibulum sodales elit sit amet lectus scelerisque, vel facilisis neque scelerisque. Integer ut nisi vel quam interdum rhoncus nec a elit. Vivamus euismod massa et finibus hendrerit. Integer ac odio vel dui bibendum dictum. Nunc sit amet enim id libero cursus interdum vel eu quam. Etiam consectetur elit ac nisi hendrerit varius. Vivamus bibendum mi nec lorem tempor, sit amet volutpat augue ultrices. Quisque ultricies, nisl sit amet vestibulum dignissim, lectus tellus tincidunt justo, in aliquam nulla urna eu libero. Quisque id efficitur tellus. Morbi eget libero quis risus malesuada sollicitudin. Suspendisse potenti. Quisque non neque vitae augue scelerisque tincidunt. Integer gravida lectus ut diam sagittis, vitae fermentum libero vestibulum. Ut consectetur ipsum vitae lectus convallis, vitae consequat mauris pulvinar. Proin id justo quis elit finibus volutpat. Suspendisse potenti. Integer a ex id justo egestas iaculis. Proin vel volutpat metus. Aliquam nec metus ac quam semper congue vel ac leo. Fusce ut orci nec sapien fermentum euismod. Quisque eu tincidunt risus. Etiam mattis ultrices magna, id gravida purus tempus vitae. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Maecenas efficitur dolor in tellus lacinia, eu aliquet justo fringilla. In hac habitasse platea dictumst. Integer auctor enim at lacinia pellentesque. Vestibulum nec ex vitae velit semper condimentum sit amet eu lacus. In hac habitasse platea dictumst. Phasellus in mi eget tortor cursus fermentum eu a nisl. Nunc at bibendum tortor. Donec ullamcorper nisl eget quam tincidunt, sit amet aliquet nunc pharetra. Maecenas nec efficitur quam. Duis eu congue metus. Vivamus vel tellus elit.";
   s = microtcp_socket(0,0,0);
   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(struct sockaddr_in));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(19242);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if(microtcp_connect(&s,(const struct sockaddr*) &addr, (socklen_t*)sizeof(struct sockaddr_in))==-1){
      exit(-1);
   }
   microtcp_send(&s,&buf,1000,0);
   sleep(5);
   // microtcp_shutdown(&s,0);
}
