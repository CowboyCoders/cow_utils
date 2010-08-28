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

#ifndef ___sync_packet_hpp___
#define ___sync_packet_hpp___
#include <cstring>
namespace libcow
{
    /**
     * A sync packet contains information about the other packages currently being sent.
     *
     * @author Erik Helin & Felix Rios
     * @version 1.0
     */
    class sync_packet
    {
    public:
        /**
         * Initializes a new sync packet
         *
         * @param packet_counter In which order this packet were sent
         * @param protocol_id A unique identifier of the used protocol
         * @param movie_id A unique identifier of movie currently being sent
         * @param piece_id A unique identifier of the BitTorrent piece currently being sent
         */
        sync_packet(std::size_t packet_counter,
                    std::size_t protocol_id,
                    std::size_t movie_id,
                    std::size_t piece_id) :
                packet_counter_(packet_counter),
                protocol_id_(protocol_id),
                movie_id_(movie_id),
                piece_id_(piece_id) {}

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
        * Returns a number describing which version of the protocol that
        * is being used
        *
        * @return The protocol version
        */
        std::size_t protocol_id()
        {
            return protocol_id_;
        }

        /**
         * Returns a number that is unique identifier of the movie currently being sent
         *
         * @return The movie identifier
         */
        std::size_t movie_id()
        {
            return movie_id_;
        }

        /**
         * Returns which BitTorrent piece that is currently being sent
         *
         * @return The BitTorrent piece
         */
        std::size_t piece_id()
        {
            return piece_id_;
        }

    private:
        std::size_t packet_counter_;
        std::size_t protocol_id_;
        std::size_t movie_id_;
        std::size_t piece_id_;
    };
}

#endif // ___sync_packet_hpp___
