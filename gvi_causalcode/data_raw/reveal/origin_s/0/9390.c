static inline void uprv_arrayCopy ( const int16_t * src , int32_t srcStart , int16_t * dst , int32_t dstStart , int32_t count ) {
 uprv_memcpy ( dst + dstStart , src + srcStart , ( size_t ) count * sizeof ( * src ) ) ;
 }