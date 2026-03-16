static int32_t u_printf_scidbl_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 u_printf_spec_info scidbl_info ;
 double num = args [ 0 ] . doubleValue ;
 int32_t retVal ;
 UNumberFormat * format ;
 int32_t maxSigDecimalDigits , significantDigits ;
 memcpy ( & scidbl_info , info , sizeof ( u_printf_spec_info ) ) ;
 if ( scidbl_info . fPrecision == - 1 && num == uprv_trunc ( num ) ) {
 scidbl_info . fSpec = 0x0066 ;
 scidbl_info . fPrecision = 0 ;
 retVal = u_printf_double_handler ( handler , context , formatBundle , & scidbl_info , args ) ;
 }
 else if ( num < 0.0001 || ( scidbl_info . fPrecision < 1 && 1000000.0 <= num ) || ( scidbl_info . fPrecision != - 1 && num > uprv_pow10 ( scidbl_info . fPrecision ) ) ) {
 scidbl_info . fSpec = scidbl_info . fSpec - 2 ;
 if ( scidbl_info . fPrecision == - 1 ) {
 scidbl_info . fPrecision = 5 ;
 }
 retVal = u_printf_scientific_handler ( handler , context , formatBundle , & scidbl_info , args ) ;
 }
 else {
 format = u_locbund_getNumberFormat ( formatBundle , UNUM_DECIMAL ) ;
 if ( format == NULL ) {
 return 0 ;
 }
 maxSigDecimalDigits = unum_getAttribute ( format , UNUM_MAX_SIGNIFICANT_DIGITS ) ;
 significantDigits = scidbl_info . fPrecision ;
 scidbl_info . fSpec = 0x0066 ;
 if ( significantDigits == - 1 ) {
 significantDigits = 6 ;
 }
 unum_setAttribute ( format , UNUM_SIGNIFICANT_DIGITS_USED , TRUE ) ;
 unum_setAttribute ( format , UNUM_MAX_SIGNIFICANT_DIGITS , significantDigits ) ;
 retVal = u_printf_double_handler ( handler , context , formatBundle , & scidbl_info , args ) ;
 unum_setAttribute ( format , UNUM_MAX_SIGNIFICANT_DIGITS , maxSigDecimalDigits ) ;
 unum_setAttribute ( format , UNUM_SIGNIFICANT_DIGITS_USED , FALSE ) ;
 }
 return retVal ;
 }