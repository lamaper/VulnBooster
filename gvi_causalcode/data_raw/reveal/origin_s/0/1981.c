static ufmt_args * parseArguments ( const UChar * alias , va_list ap , UErrorCode * status ) {
 ufmt_args * arglist = NULL ;
 ufmt_type_info * typelist = NULL ;
 UBool * islonglong = NULL ;
 int32_t size = 0 ;
 int32_t pos = 0 ;
 UChar type ;
 uint16_t handlerNum ;
 const UChar * aliasStart = alias ;
 for ( ;
 ;
 ) {
 while ( * alias != UP_PERCENT && * alias != 0x0000 ) {
 alias ++ ;
 }
 if ( * alias == 0x0000 ) {
 break ;
 }
 alias ++ ;
 if ( ISDIGIT ( * alias ) ) {
 if ( ISDIGIT ( * alias ) ) {
 pos = ( int ) ( * alias ++ - DIGIT_ZERO ) ;
 while ( ISDIGIT ( * alias ) ) {
 pos *= 10 ;
 pos += ( int ) ( * alias ++ - DIGIT_ZERO ) ;
 }
 }
 if ( * alias != SPEC_DOLLARSIGN ) {
 return NULL ;
 }
 }
 else {
 return NULL ;
 }
 if ( pos > size ) {
 size = pos ;
 }
 }
 typelist = ( ufmt_type_info * ) uprv_malloc ( sizeof ( ufmt_type_info ) * size ) ;
 islonglong = ( UBool * ) uprv_malloc ( sizeof ( UBool ) * size ) ;
 arglist = ( ufmt_args * ) uprv_malloc ( sizeof ( ufmt_args ) * size ) ;
 if ( ! typelist || ! islonglong || ! arglist ) {
 if ( typelist ) {
 uprv_free ( typelist ) ;
 }
 if ( islonglong ) {
 uprv_free ( islonglong ) ;
 }
 if ( arglist ) {
 uprv_free ( arglist ) ;
 }
 * status = U_MEMORY_ALLOCATION_ERROR ;
 return NULL ;
 }
 alias = aliasStart ;
 for ( ;
 ;
 ) {
 while ( * alias != UP_PERCENT && * alias != 0x0000 ) {
 alias ++ ;
 }
 if ( * alias == 0x0000 ) {
 break ;
 }
 alias ++ ;
 if ( ISDIGIT ( * alias ) ) {
 pos = ( int ) ( * alias ++ - DIGIT_ZERO ) ;
 while ( ISDIGIT ( * alias ) ) {
 pos *= 10 ;
 pos += ( int ) ( * alias ++ - DIGIT_ZERO ) ;
 }
 }
 pos -- ;
 while ( ISMOD ( * alias ) || ISFLAG ( * alias ) || ISDIGIT ( * alias ) || * alias == SPEC_ASTERISK || * alias == SPEC_PERIOD || * alias == SPEC_DOLLARSIGN ) {
 islonglong [ pos ] = FALSE ;
 if ( ISMOD ( * alias ) ) {
 alias ++ ;
 if ( * alias == MOD_LOWERL ) {
 islonglong [ pos ] = TRUE ;
 }
 }
 alias ++ ;
 }
 type = * alias ;
 handlerNum = ( uint16_t ) ( type - UPRINTF_BASE_FMT_HANDLERS ) ;
 if ( handlerNum < UPRINTF_NUM_FMT_HANDLERS ) {
 typelist [ pos ] = g_u_printf_infos [ handlerNum ] . info ;
 }
 else {
 typelist [ pos ] = ufmt_empty ;
 }
 }
 for ( pos = 0 ;
 pos < size ;
 pos ++ ) {
 switch ( typelist [ pos ] ) {
 case ufmt_string : case ufmt_ustring : case ufmt_pointer : arglist [ pos ] . ptrValue = va_arg ( ap , void * ) ;
 break ;
 case ufmt_char : case ufmt_uchar : case ufmt_int : if ( islonglong [ pos ] ) {
 arglist [ pos ] . int64Value = va_arg ( ap , int64_t ) ;
 }
 else {
 arglist [ pos ] . int64Value = va_arg ( ap , int32_t ) ;
 }
 break ;
 case ufmt_float : arglist [ pos ] . floatValue = ( float ) va_arg ( ap , double ) ;
 break ;
 case ufmt_double : arglist [ pos ] . doubleValue = va_arg ( ap , double ) ;
 break ;
 default : arglist [ pos ] . ptrValue = NULL ;
 break ;
 }
 }
 uprv_free ( typelist ) ;
 uprv_free ( islonglong ) ;
 return arglist ;
 }