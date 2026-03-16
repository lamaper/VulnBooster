static inline void uprv_arrayCopy ( const double * src , int32_t srcStart , double * dst , int32_t dstStart , int32_t count ) {
 uprv_memcpy ( dst + dstStart , src + srcStart , ( size_t ) count * sizeof ( * src ) ) ;
 }