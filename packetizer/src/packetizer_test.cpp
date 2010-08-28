/*
Copyright 2010 CowboyCoders. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY COWBOYCODERS ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COWBOYCODERS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of CowboyCoders.
*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include "packetizer.hpp"
#include "cow/utils/buffer.hpp"
#include "movie_packet.hpp"

int main()
{
    libcow::packetizer p;
    const int packet_length = 500; // in bytes

    std::ifstream file;
    file.open("/home/erik/Videos/big_buck_bunny_480p_h264.mov", std::ifstream::in | std::ifstream::binary);

    char* data = new char[packet_length+1]; // for sync data

    file.read(++data, packet_length);

    libcow::utils::buffer movie_buf(data,packet_length);
    std::cout << "movie packet:" << std::endl;
    p.create_movie_packet(movie_buf);
    libcow::movie_packet mov_pak = p.unpack_movie_buffer(movie_buf);
    printf("packet_counter: %u\n", mov_pak.packet_counter());

    std::cout <<  "sync packet:" << std::endl;
    char* sync_data = new char[8];
    libcow::utils::buffer sync_buf(sync_data, 8);
    p.create_sync_packet(1,255,43483,sync_buf);

    libcow::sync_packet sy = p.unpack_sync_buffer(sync_buf);

    printf("movie_id hex: %x\n", sy.movie_id());
    printf("movie_id dec: %u\n", sy.movie_id());
    printf("packet_counter hex: %x\n", sy.packet_counter());
    printf("packet_counter dec: %u\n", sy.packet_counter());
    printf("protocol_id hex: %x\n", sy.protocol_id());
    printf("protocol_id dec: %u\n", sy.protocol_id());
    printf("piece_id hex: %x\n", sy.piece_id());
    printf("piece_id dec: %u\n", sy.piece_id());

    bool bsync = p.is_sync_packet(sync_buf);
    printf("bsync: %u\n", bsync);

    bool msync = p.is_sync_packet(movie_buf);
    printf("msync: %u\n", msync);

    return 0;
}
