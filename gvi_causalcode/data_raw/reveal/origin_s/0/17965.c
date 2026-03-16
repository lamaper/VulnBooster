static void convert_bytea_to_scalar ( Datum value , double * scaledvalue , Datum lobound , double * scaledlobound , Datum hibound , double * scaledhibound ) {
 int rangelo , rangehi , valuelen = VARSIZE ( DatumGetPointer ( value ) ) - VARHDRSZ , loboundlen = VARSIZE ( DatumGetPointer ( lobound ) ) - VARHDRSZ , hiboundlen = VARSIZE ( DatumGetPointer ( hibound ) ) - VARHDRSZ , i , minlen ;
 unsigned char * valstr = ( unsigned char * ) VARDATA ( DatumGetPointer ( value ) ) , * lostr = ( unsigned char * ) VARDATA ( DatumGetPointer ( lobound ) ) , * histr = ( unsigned char * ) VARDATA ( DatumGetPointer ( hibound ) ) ;
 rangelo = 0 ;
 rangehi = 255 ;
 minlen = Min ( Min ( valuelen , loboundlen ) , hiboundlen ) ;
 for ( i = 0 ;
 i < minlen ;
 i ++ ) {
 if ( * lostr != * histr || * lostr != * valstr ) break ;
 lostr ++ , histr ++ , valstr ++ ;
 loboundlen -- , hiboundlen -- , valuelen -- ;
 }
 * scaledvalue = convert_one_bytea_to_scalar ( valstr , valuelen , rangelo , rangehi ) ;
 * scaledlobound = convert_one_bytea_to_scalar ( lostr , loboundlen , rangelo , rangehi ) ;
 * scaledhibound = convert_one_bytea_to_scalar ( histr , hiboundlen , rangelo , rangehi ) ;
 }