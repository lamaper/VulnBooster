static inline void fill_64 ( uint8_t * dst , const uint64_t pix , int32_t n , int32_t row_offset ) {
 for ( ;
 n > 0 ;
 dst += row_offset , n -- ) AV_WN64A ( dst , pix ) ;
 }