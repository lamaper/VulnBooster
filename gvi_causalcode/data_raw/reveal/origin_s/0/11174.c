static int decode_blockcodes ( int code1 , int code2 , int levels , int * values ) {
 return decode_blockcode ( code1 , levels , values ) | decode_blockcode ( code2 , levels , values + 4 ) ;
 }