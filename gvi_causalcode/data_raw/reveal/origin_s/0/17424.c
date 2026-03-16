TSReturnCode TSTextLogObjectWrite ( TSTextLogObject the_object , const char * format , ... ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) format ) == TS_SUCCESS ) ;
 TSReturnCode retVal = TS_SUCCESS ;
 va_list ap ;
 va_start ( ap , format ) ;
 switch ( ( ( TextLogObject * ) the_object ) -> va_write ( format , ap ) ) {
 case ( Log : : LOG_OK ) : case ( Log : : SKIP ) : case ( Log : : AGGR ) : break ;
 case ( Log : : FULL ) : retVal = TS_ERROR ;
 break ;
 case ( Log : : FAIL ) : retVal = TS_ERROR ;
 break ;
 default : ink_assert ( ! "invalid return code" ) ;
 }
 va_end ( ap ) ;
 return retVal ;
 }