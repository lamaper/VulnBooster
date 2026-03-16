static ulmbcs_byte_t FindLMBCSLocale ( const char * LocaleID ) {
 const struct _LocaleLMBCSGrpMap * pTable = LocaleLMBCSGrpMap ;
 if ( ( ! LocaleID ) || ( ! * LocaleID ) ) {
 return 0 ;
 }
 while ( pTable -> LocaleID ) {
 if ( * pTable -> LocaleID == * LocaleID ) {
 if ( uprv_strncmp ( pTable -> LocaleID , LocaleID , strlen ( pTable -> LocaleID ) ) == 0 ) return pTable -> OptGroup ;
 }
 else if ( * pTable -> LocaleID > * LocaleID ) break ;
 pTable ++ ;
 }
 return ULMBCS_GRP_L1 ;
 }