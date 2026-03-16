static inline void uprv_arrayCopy ( const double * src , double * dst , int32_t count ) {
 uprv_memcpy ( dst , src , ( size_t ) count * sizeof ( * src ) ) ;
 }