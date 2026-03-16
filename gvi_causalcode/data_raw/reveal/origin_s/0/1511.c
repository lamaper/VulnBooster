static OFCondition parseSubItem ( DUL_SUBITEM * subItem , unsigned char * buf , unsigned long * itemLength , unsigned long availData ) {
 if ( availData < 4 ) return makeLengthError ( "subitem" , availData , 4 ) ;
 subItem -> type = * buf ++ ;
 subItem -> rsv1 = * buf ++ ;
 EXTRACT_SHORT_BIG ( buf , subItem -> length ) ;
 buf += 2 ;
 if ( subItem -> length > DICOM_UI_LENGTH ) {
 char buffer [ 256 ] ;
 sprintf ( buffer , "DUL illegal subitem length %d. Maximum allowed size is %d." , subItem -> length , DICOM_UI_LENGTH ) ;
 return makeDcmnetCondition ( DULC_ILLEGALPDULENGTH , OF_error , buffer ) ;
 }
 if ( availData - 4 < subItem -> length ) return makeLengthError ( "subitem" , availData , 0 , subItem -> length ) ;
 ( void ) memcpy ( subItem -> data , buf , subItem -> length ) ;
 subItem -> data [ subItem -> length ] = '\0' ;
 * itemLength = 2 + 2 + subItem -> length ;
 DCMNET_TRACE ( "Subitem parse: Type " << STD_NAMESPACE hex << STD_NAMESPACE setfill ( '0' ) << STD_NAMESPACE setw ( 2 ) << ( ( unsigned int ) subItem -> type ) << STD_NAMESPACE dec << ", Length " << STD_NAMESPACE setw ( 4 ) << ( int ) subItem -> length << ", Content: " << subItem -> data ) ;
 return EC_Normal ;
 }