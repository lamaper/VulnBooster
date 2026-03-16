static inline void uprv_arrayCopy ( const int32_t * src , int32_t * dst , int32_t count ) {
 uprv_memcpy ( dst , src , ( size_t ) count * sizeof ( * src ) ) ;
 }