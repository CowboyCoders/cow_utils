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

#ifndef ___packetizer_hpp___
#define ___packetizer_hpp___

#ifdef DEBUG
    #include <cstdio>
#endif

#include <cstring>
#include <stdexcept>

#include "sync_packet.hpp"
#include "movie_packet.hpp"
#include "cow/utils/buffer.hpp"

namespace libcow
{
    /**
     * A utility class which packs and unpacks packages according
     * to the protocol specified at http://wiki.cowboycoders.se/wiki/Miniprojekt/MulticastServer.
     *
     * This class assumes that the computers CPU is using little-endian byte order.
     *
     * This class is used by both the multicast server and the receiver.
     * @author Erik Helin & Felix Rios
     * @version 1.0
     */
    class packetizer
    {
    public:
        /**
         * Initializes the internal variables of the packetizer.
         */
        packetizer() : counter_(0), sync_packet_size_(8), sync_frequency_(0) {}; // only init

        /**
         * Creates a movie packet from a buffer. The returned buffers
         * data array holds data which is packetized as follows:
         * bit 0: Sync packet flag, which is 0 since this is a movie packet
         * bit 1 - 7: Continuity counter, a counter of the sent packages
         * bit 8 - (buf.size() - 1): The movie data
         *
         * @param buf A buffer containing the movie data.
         *            The first element in the data array will be overwritten!
         */
        void create_movie_packet(const utils::buffer& buf);

        /**
         * Creates a sync packet. The returned buffers data array
         * holds data which is packetized as follows:
         * bit 0: Sync packet flag, which 1 since this is a sync packet
         * bit 1 - 7: Continuity counter, a counter of the sent packages
         * bit 8 - 10: Protocol version number
         * bit 11 - 31: A unique movie identifier
         * bit 32 - 63: A unique BitTorrent piece identifier
         *
         * @param version_number The protocol version, must be <= 7
         * @param movie_id The unique movie id, must be <= 2^21 - 1
         * @param piece_id The unique pieced id, must be <= 2^32 - 1
         * @param buf The buffer for the packet, the data array must be of size 8
         */
        void create_sync_packet(std::size_t version_number,
                                         std::size_t movie_id,
                                         std::size_t piece_id,
                                         const utils::buffer& buf);

        /**
         * Sets how often a sync packet should be sent.
         *
         * @param freq the frequency
         */
        void set_sync_frequency(size_t freq);

        /**
         * Checks wether a received buffer is a sync packet or not by
         * looking at the first bit.
         *
         * @param buf A buffer containing the packet
         * @return true if the buffer is a sync packet, false otherwise
         */
        bool is_sync_packet(const utils::buffer& buf) const;

        /**
         * Creates a sync packet from a buffer.
         *
         * @param buf The buffer containing the sync packet
         * @return A sync packet with the info
         */
        sync_packet unpack_sync_buffer(const utils::buffer& buf) const;

        /**
         * Creates a movie packet from a buffer. Note that the pointer
         * to the data array in the buffer is copied to movie packet.
         *
         * @param buf The buffer containing the movie packet
         * @return A movie packet with the info.
         */
        movie_packet unpack_movie_buffer(const utils::buffer& buf) const;

        /**
         * Returns the size of a sync packet array
         *
         * @return The size of a sync packet array
         */
        const std::size_t sync_packet_size() const
        {
            return sync_packet_size_;
        }

        /**
         * Returns the number of packages which have been packetized.
         *
         * @return The number of packages which have been packetized.
         */
        std::size_t counter() const
        {
            return counter_;
        }

       /**
        * Returns whether or not it's time to send a sync packet.
        * @return True of we should send a sync packet, otherwise false.
        */
        bool need_sync() {
            return (counter_ % sync_frequency_ == 0);
        }

    private:
        unsigned char get_counter();
        std::size_t counter_;
        const std::size_t sync_packet_size_; // in bytes
        std::size_t sync_frequency_;
    };
}

#endif // ___packetizer_hpp___
