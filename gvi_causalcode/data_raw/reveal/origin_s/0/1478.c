static OFCondition parseDummy ( unsigned char * buf , unsigned long * itemLength , unsigned long availData ) {
 if ( availData < 4 ) return makeLengthError ( "dummy item" , availData , 4 ) ;
 unsigned short userLength ;
 buf ++ ;
 buf ++ ;
 EXTRACT_SHORT_BIG ( buf , userLength ) ;
 buf += 2 ;
 * itemLength = userLength + 4 ;
 if ( availData - 4 < userLength ) return makeLengthError ( "dummy item" , availData , 0 , userLength ) ;
 return EC_Normal ;
 }