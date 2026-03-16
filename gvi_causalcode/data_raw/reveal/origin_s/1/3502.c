static OFCondition parseUserInfo ( DUL_USERINFO * userInfo , unsigned char * buf , unsigned long * itemLength , unsigned char typeRQorAC , unsigned long availData ) {
 unsigned short userLength ;
 unsigned long length ;
 OFCondition cond = EC_Normal ;
 PRV_SCUSCPROLE * role ;
 SOPClassExtendedNegotiationSubItem * extNeg = NULL ;
 UserIdentityNegotiationSubItem * usrIdent = NULL ;
 if ( availData < 4 ) return makeLengthError ( "user info" , availData , 4 ) ;
 userInfo -> type = * buf ++ ;
 userInfo -> rsv1 = * buf ++ ;
 EXTRACT_SHORT_BIG ( buf , userInfo -> length ) ;
 buf += 2 ;
 userLength = userInfo -> length ;
 * itemLength = userLength + 4 ;
 if ( availData - 4 < userLength ) return makeLengthError ( "user info" , availData , 0 , userLength ) ;
 DCMNET_TRACE ( "Parsing user info field (" << STD_NAMESPACE hex << STD_NAMESPACE setfill ( '0' ) << STD_NAMESPACE setw ( 2 ) << ( unsigned int ) userInfo -> type << STD_NAMESPACE dec << "), Length: " << ( unsigned long ) userInfo -> length ) ;
 while ( userLength > 0 ) {
 DCMNET_TRACE ( "Parsing remaining " << ( long ) userLength << " bytes of User Information" << OFendl << "Next item type: " << STD_NAMESPACE hex << STD_NAMESPACE setfill ( '0' ) << STD_NAMESPACE setw ( 2 ) << ( unsigned int ) * buf ) ;
 switch ( * buf ) {
 case DUL_TYPEMAXLENGTH : cond = parseMaxPDU ( & userInfo -> maxLength , buf , & length , userLength ) ;
 if ( cond . bad ( ) ) return cond ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 DCMNET_TRACE ( "Successfully parsed Maximum PDU Length" ) ;
 break ;
 case DUL_TYPEIMPLEMENTATIONCLASSUID : cond = parseSubItem ( & userInfo -> implementationClassUID , buf , & length , userLength ) ;
 if ( cond . bad ( ) ) return cond ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 case DUL_TYPEASYNCOPERATIONS : cond = parseDummy ( buf , & length , userLength ) ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 case DUL_TYPESCUSCPROLE : role = ( PRV_SCUSCPROLE * ) malloc ( sizeof ( PRV_SCUSCPROLE ) ) ;
 if ( role == NULL ) return EC_MemoryExhausted ;
 cond = parseSCUSCPRole ( role , buf , & length , userLength ) ;
 if ( cond . bad ( ) ) return cond ;
 LST_Enqueue ( & userInfo -> SCUSCPRoleList , ( LST_NODE * ) role ) ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 case DUL_TYPEIMPLEMENTATIONVERSIONNAME : cond = parseSubItem ( & userInfo -> implementationVersionName , buf , & length , userLength ) ;
 if ( cond . bad ( ) ) return cond ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 case DUL_TYPESOPCLASSEXTENDEDNEGOTIATION : extNeg = new SOPClassExtendedNegotiationSubItem ;
 if ( extNeg == NULL ) return EC_MemoryExhausted ;
 cond = parseExtNeg ( extNeg , buf , & length , userLength ) ;
 if ( cond . bad ( ) ) return cond ;
 if ( userInfo -> extNegList == NULL ) {
 userInfo -> extNegList = new SOPClassExtendedNegotiationSubItemList ;
 if ( userInfo -> extNegList == NULL ) return EC_MemoryExhausted ;
 }
 userInfo -> extNegList -> push_back ( extNeg ) ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 case DUL_TYPENEGOTIATIONOFUSERIDENTITY : if ( typeRQorAC == DUL_TYPEASSOCIATERQ ) usrIdent = new UserIdentityNegotiationSubItemRQ ( ) ;
 else usrIdent = new UserIdentityNegotiationSubItemAC ( ) ;
 if ( usrIdent == NULL ) return EC_MemoryExhausted ;
 cond = usrIdent -> parseFromBuffer ( buf , length , userLength ) ;
 if ( cond . bad ( ) ) {
 delete usrIdent ;
 return cond ;
 }
 userInfo -> usrIdent = usrIdent ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 default : cond = parseDummy ( buf , & length , userLength ) ;
 buf += length ;
 userLength -= ( unsigned short ) length ;
 break ;
 }
 }
 return EC_Normal ;
 }