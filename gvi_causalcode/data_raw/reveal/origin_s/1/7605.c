static OFCondition parseDummy ( unsigned char * buf , unsigned long * itemLength , unsigned long availData ) {
 unsigned short userLength ;
 if ( availData < 4 ) return makeLengthError ( "dummy item" , availData , 4 ) ;
 buf ++ ;
 buf ++ ;
 EXTRACT_SHORT_BIG ( buf , userLength ) ;
 buf += 2 ;
 if ( availData - 4 < userLength ) return makeLengthError ( "dummy item" , availData , 0 , userLength ) ;
 * itemLength = userLength + 4 ;
 return EC_Normal ;
 }