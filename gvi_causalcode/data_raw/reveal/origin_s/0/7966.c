static int32_t ucnv_copyPlatformString ( char * platformString , UConverterPlatform pltfrm ) {
 switch ( pltfrm ) {
 case UCNV_IBM : uprv_strcpy ( platformString , "ibm-" ) ;
 return 4 ;
 case UCNV_UNKNOWN : break ;
 }
 * platformString = 0 ;
 return 0 ;
 }