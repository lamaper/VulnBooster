static inline void uprv_arrayCopy ( const int32_t * src , int32_t srcStart , int32_t * dst , int32_t dstStart , int32_t count ) {
 uprv_memcpy ( dst + dstStart , src + srcStart , ( size_t ) count * sizeof ( * src ) ) ;
 }