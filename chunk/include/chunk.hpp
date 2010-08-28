#ifndef ___libcow_chunk___
#define ___libcow_chunk___

#include "cow/libcow_def.hpp"

namespace libcow {
    /**
     * A class representing file chunks, i.e (offset, length) tuples.
     */
    class LIBCOW_EXPORT chunk 
    {
    public:
        chunk(size_t offset, size_t length)
            : off(offset), len(length) {}
        size_t offset() const { return off; }
        size_t length() const { return len; }
    private:
        size_t off; size_t len;
    };
}
    
#endif