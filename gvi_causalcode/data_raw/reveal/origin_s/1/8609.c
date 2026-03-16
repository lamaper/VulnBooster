static int32_t compareMappingsBytesFirst ( const void * context , const void * left , const void * right ) {
 UCMTable * table = ( UCMTable * ) context ;
 int32_t l = * ( const int32_t * ) left , r = * ( const int32_t * ) right ;
 return compareMappings ( table , table -> mappings + l , table , table -> mappings + r , FALSE ) ;
 }