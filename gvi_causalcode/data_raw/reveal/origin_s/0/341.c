static UBool isAcceptable ( void * context , const char * type , const char * name , const UDataInfo * pInfo ) {
 if ( pInfo -> size >= 20 && pInfo -> isBigEndian == U_IS_BIG_ENDIAN && pInfo -> charsetFamily == U_CHARSET_FAMILY && pInfo -> dataFormat [ 0 ] == 0x4D && pInfo -> dataFormat [ 1 ] == 0x79 && pInfo -> dataFormat [ 2 ] == 0x44 && pInfo -> dataFormat [ 3 ] == 0x74 && pInfo -> formatVersion [ 0 ] == 1 && pInfo -> dataVersion [ 0 ] == 1 ) {
 return TRUE ;
 }
 else {
 return FALSE ;
 }
 }