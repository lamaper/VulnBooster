static OFCondition parseSCUSCPRole ( PRV_SCUSCPROLE * role , unsigned char * buf , unsigned long * length , unsigned long availData ) {
 unsigned short UIDLength ;
 if ( availData < 8 ) return makeLengthError ( "SCU-SCP role list" , availData , 8 ) ;
 role -> type = * buf ++ ;
 role -> rsv1 = * buf ++ ;
 EXTRACT_SHORT_BIG ( buf , role -> length ) ;
 buf += 2 ;
 EXTRACT_SHORT_BIG ( buf , UIDLength ) ;
 buf += 2 ;
 if ( availData - 4 < role -> length ) return makeLengthError ( "SCU-SCP role list" , availData , 0 , role -> length ) ;
 if ( role -> length < 4 ) return makeLengthError ( "SCU-SCP role list UID" , role -> length , 4 ) ;
 if ( role -> length - 4 < UIDLength ) return makeLengthError ( "SCU-SCP role list UID" , role -> length , 0 , UIDLength ) ;
 ( void ) memcpy ( role -> SOPClassUID , buf , UIDLength ) ;
 role -> SOPClassUID [ UIDLength ] = '\0' ;
 buf += UIDLength ;
 role -> SCURole = * buf ++ ;
 role -> SCPRole = * buf ++ ;
 * length = 2 + 2 + role -> length ;
 DCMNET_TRACE ( "Subitem parse: Type " << STD_NAMESPACE hex << STD_NAMESPACE setfill ( '0' ) << STD_NAMESPACE setw ( 2 ) << ( unsigned int ) role -> type << STD_NAMESPACE dec << ", Length " << STD_NAMESPACE setw ( 4 ) << ( int ) role -> length << ", Content: " << role -> SOPClassUID << " " << ( int ) role -> SCURole << " " << ( int ) role -> SCPRole ) ;
 return EC_Normal ;
 }