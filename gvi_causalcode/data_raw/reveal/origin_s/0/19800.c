static inline void uprv_arrayCopy ( const int8_t * src , int8_t * dst , int32_t count ) {
 uprv_memcpy ( dst , src , ( size_t ) count * sizeof ( * src ) ) ;
 }