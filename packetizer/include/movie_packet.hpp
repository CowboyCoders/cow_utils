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

#ifndef ___movie_packet_hpp___
#define ___movie_packet_hpp___
#include <cstring>
#include "cow/utils/buffer.hpp"
namespace libcow
{
    /**
     * A movie packet contains both the movie data as a buffer
     * and a packet counter describing when the packet was sent relative to
     * other packages.
     *
     * @author Erik Helin & Felix Rios
     * @version 1.0
     */
    class movie_packet
    {
    public:
        /**
         * Creates a new movie packet.
         *
         * @param packet_counter In which order this packet were sent
         * @param data The movie data
         */
        movie_packet(std::size_t packet_counter, utils::buffer data) :
                packet_counter_(packet_counter), data_(data) {}

        /**
         * Returns a number describing when this packet was sent relative to
         * other packages
         *
         * @return The packet count number
         */
        std::size_t packet_counter()
        {
            return packet_counter_;
        }

        /**
         * Returns the movie data of the packet as a buffer
         *
         * @return The movie data
         */
        utils::buffer data()
        {
            return data_;
        }

    private:
        int packet_counter_;
        utils::buffer data_;
    };
}

#endif // ___movie_packet_hpp___
