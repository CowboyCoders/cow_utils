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

#ifndef ___buffer_hpp___
#define ___buffer_hpp___
#include <cstring>
namespace libcow
{
    namespace utils
    {
        /**
         * The buffer is meant to be used instead of an ordinary char array.
         * This is to make sure that the size of the char array is always being sent
         * together with the array, in order to avoid reading out of bounds.
         *
         * @author Erik Helin & Felix Rios
         * @version 1.0
         */
        class buffer
        {
        public:
            /**
             * Creates a new buffer
             *
             * @param data A char pointer pointing to the data array
             * @param size The size of the data array
             */
            buffer(char *data, std::size_t size):
                    data_(data),size_(size)
            {}

            /**
             * Returns a pointer to the data array.
             *
             * @return A char pointer to the data array
             */
            char *data() const
            {
                return data_;
            }

            /**
             * Returns the size of the data array
             *
             * @return A size_t describing the size of the data array
             */
            std::size_t size() const
            {
                return size_;
            }

        private:
            char *data_;
            std::size_t size_;
        };
    }
}

#endif // ___buffer_hpp___
