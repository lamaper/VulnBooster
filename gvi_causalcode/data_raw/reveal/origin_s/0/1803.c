static chunk_t generate_ts ( traffic_selector_t * ts ) {
 chunk_t from , to ;
 uint8_t minbits = 0 , maxbits = 0 , unused ;
 host_t * net ;
 int bit , byte ;
 if ( ts -> to_subnet ( ts , & net , & minbits ) ) {
 unused = round_up ( minbits , BITS_PER_BYTE ) - minbits ;
 from = asn1_wrap ( ASN1_BIT_STRING , "m" , chunk_cat ( "cc" , chunk_from_thing ( unused ) , chunk_create ( net -> get_address ( net ) . ptr , ( minbits + unused ) / BITS_PER_BYTE ) ) ) ;
 net -> destroy ( net ) ;
 return from ;
 }
 net -> destroy ( net ) ;
 from = ts -> get_from_address ( ts ) ;
 for ( byte = from . len - 1 ;
 byte >= 0 ;
 byte -- ) {
 if ( from . ptr [ byte ] != 0 ) {
 minbits = byte * BITS_PER_BYTE + BITS_PER_BYTE ;
 for ( bit = 0 ;
 bit < BITS_PER_BYTE ;
 bit ++ ) {
 if ( from . ptr [ byte ] & 1 << bit ) {
 break ;
 }
 minbits -- ;
 }
 break ;
 }
 }
 to = ts -> get_to_address ( ts ) ;
 for ( byte = to . len - 1 ;
 byte >= 0 ;
 byte -- ) {
 if ( to . ptr [ byte ] != 0xFF ) {
 maxbits = byte * BITS_PER_BYTE + BITS_PER_BYTE ;
 for ( bit = 0 ;
 bit < BITS_PER_BYTE ;
 bit ++ ) {
 if ( ( to . ptr [ byte ] & 1 << bit ) == 0 ) {
 break ;
 }
 maxbits -- ;
 }
 break ;
 }
 }
 unused = round_up ( minbits , BITS_PER_BYTE ) - minbits ;
 from = asn1_wrap ( ASN1_BIT_STRING , "m" , chunk_cat ( "cc" , chunk_from_thing ( unused ) , chunk_create ( from . ptr , ( minbits + unused ) / BITS_PER_BYTE ) ) ) ;
 unused = round_up ( maxbits , BITS_PER_BYTE ) - maxbits ;
 to = asn1_wrap ( ASN1_BIT_STRING , "m" , chunk_cat ( "cc" , chunk_from_thing ( unused ) , chunk_create ( to . ptr , ( maxbits + unused ) / BITS_PER_BYTE ) ) ) ;
 return asn1_wrap ( ASN1_SEQUENCE , "mm" , from , to ) ;
 }