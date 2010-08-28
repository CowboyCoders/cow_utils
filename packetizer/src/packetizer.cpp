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

#include "cow/libcow_def.hpp"
#include "packetizer.hpp"

#include <iostream>
namespace libcow
{
    void packetizer::create_movie_packet(const utils::buffer& buf)
    {
        if(buf.size() < 1)
        {
            throw std::invalid_argument("Buffer too small");
        }
        char * const data = buf.data();
        data[0] = 0;
        data[0] |= get_counter();

        #ifdef DEBUG
        printf("data[0] hex: %x\n", (data[0] & 0x000000ff));
        #endif
    }

    void packetizer::create_sync_packet(std::size_t protocol_id,
                                                 std::size_t movie_id,
                                                 std::size_t piece_id,
                                                 const utils::buffer& buf)
    {
        if(buf.size() != sync_packet_size_) {
            throw std::invalid_argument("Buffer has wrong size");
        }

        char * const data = buf.data();

        for(std::size_t i =0; i < sync_packet_size_; ++i) {
            data[i] = 0;
        }
        int sync = 0x1;

        data[0] |= sync << 7;
        data[0] |= get_counter();


        data[1] |= (protocol_id & 0x7) << 5;
        data[1] |= (movie_id & 0x001f0000) >> 16;

        data[2] |= (movie_id & 0x0000ff00) >> 8;

        data[3] |= (movie_id & 0x000000ff);

        data[4] |= (piece_id & 0xff000000) >> 24;

        data[5] = (piece_id & 0x00ff0000) >> 16;

        data[6] = (piece_id & 0x0000ff00) >> 8;

        data[7] = (piece_id & 0x000000ff);

        #ifdef DEBUG
        // a char is 8 bits
        printf("data[0] hex: %x\n", (data[0] & 0x000000ff));
        printf("data[1] hex: %x\n", (data[1] & 0x000000ff));
        printf("data[2] hex: %x\n", (data[2] & 0x000000ff));
        printf("data[3] hex: %x\n", (data[3] & 0x000000ff));
        printf("data[4] hex: %x\n", (data[4] & 0x000000ff));
        printf("data[5] hex: %x\n", (data[5] & 0x000000ff));
        printf("data[6] hex: %x\n", (data[6] & 0x000000ff));
        printf("data[7] hex: %x\n", (data[7] & 0x000000ff));
        #endif
    }
        
    void packetizer::set_sync_frequency(size_t freq)
    {
        sync_frequency_ = freq;
    }

    unsigned char packetizer::get_counter()
    {
        unsigned char ret = (counter_ & 0x0000007f); // last seven bits
        ++counter_;

        return ret;
    }

    bool packetizer::is_sync_packet(const utils::buffer &buf) const
    {
        char *const data = buf.data();
        return !!(data[0] & 0x80);
    }

    movie_packet packetizer::unpack_movie_buffer(const utils::buffer &buf) const
    {
        char *data = buf.data();
        std::size_t packet_counter = (data[0] & 0x7f);
        utils::buffer movie_data(++data, buf.size()-1);
        return movie_packet(packet_counter, movie_data);
    }

    sync_packet packetizer::unpack_sync_buffer(const utils::buffer &buf) const
    {
        if(buf.size() < sync_packet_size_)
        {
            throw std::invalid_argument("Buffer too small");
        }
        char *data = buf.data();
        std::size_t packet_counter = (data[0] & 0x7f);
        std::size_t protocol_id = (data[1] & 0xe0) >> 5;

        std::size_t tmp = 0;
        std::size_t movie_id = 0;

        // movie_id begins here
        tmp = (data[1] & 0x1f); // the highet 5 bits of the id
        tmp = tmp << 16;
        tmp &= 0x001f0000;
        movie_id |= tmp;

        tmp = data[2];
        tmp = tmp << 8;
        tmp &= 0x0000ff00;
        movie_id |= tmp;
    
        tmp = data[3];
        tmp &= 0x000000ff;
        movie_id |= tmp;

        // piece_id begins here
        tmp = 0;
        std::size_t piece_id = 0;
        tmp = data[4];
        tmp = tmp << 24;
        tmp &= 0xff000000;
        piece_id |= tmp;

        tmp = data[5];
        tmp = tmp << 16;
        tmp &= 0x00ff0000;
        piece_id |= tmp;

        tmp = data[6];
        tmp = tmp << 8;
        tmp &= 0x0000ff00;
        piece_id |= tmp;

        tmp = data[7];
        tmp &= 0x000000ff;
        piece_id |= tmp;

        return sync_packet(packet_counter, protocol_id, movie_id, piece_id);
    }
}
