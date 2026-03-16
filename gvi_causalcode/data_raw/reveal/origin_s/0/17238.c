static inline void uprv_arrayCopy ( const int16_t * src , int16_t * dst , int32_t count ) {
 uprv_memcpy ( dst , src , ( size_t ) count * sizeof ( * src ) ) ;
 }