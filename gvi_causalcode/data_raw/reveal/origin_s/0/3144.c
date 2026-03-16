int insert_pointer_name ( reg1 POINTER_ARRAY * pa , char * name ) {
 uint i , length , old_count ;
 uchar * new_pos ;
 const char * * new_array ;
 DBUG_ENTER ( "insert_pointer_name" ) ;
 if ( ! pa -> typelib . count ) {
 if ( ! ( pa -> typelib . type_names = ( const char * * ) my_malloc ( ( ( PC_MALLOC - MALLOC_OVERHEAD ) / ( sizeof ( char * ) + sizeof ( * pa -> flag ) ) * ( sizeof ( char * ) + sizeof ( * pa -> flag ) ) ) , MYF ( MY_WME ) ) ) ) DBUG_RETURN ( - 1 ) ;
 if ( ! ( pa -> str = ( uchar * ) my_malloc ( ( uint ) ( PS_MALLOC - MALLOC_OVERHEAD ) , MYF ( MY_WME ) ) ) ) {
 my_free ( pa -> typelib . type_names ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 pa -> max_count = ( PC_MALLOC - MALLOC_OVERHEAD ) / ( sizeof ( uchar * ) + sizeof ( * pa -> flag ) ) ;
 pa -> flag = ( uint8 * ) ( pa -> typelib . type_names + pa -> max_count ) ;
 pa -> length = 0 ;
 pa -> max_length = PS_MALLOC - MALLOC_OVERHEAD ;
 pa -> array_allocs = 1 ;
 }
 length = ( uint ) strlen ( name ) + 1 ;
 if ( pa -> length + length >= pa -> max_length ) {
 if ( ! ( new_pos = ( uchar * ) my_realloc ( ( uchar * ) pa -> str , ( uint ) ( pa -> length + length + PS_MALLOC ) , MYF ( MY_WME ) ) ) ) DBUG_RETURN ( 1 ) ;
 if ( new_pos != pa -> str ) {
 my_ptrdiff_t diff = PTR_BYTE_DIFF ( new_pos , pa -> str ) ;
 for ( i = 0 ;
 i < pa -> typelib . count ;
 i ++ ) pa -> typelib . type_names [ i ] = ADD_TO_PTR ( pa -> typelib . type_names [ i ] , diff , char * ) ;
 pa -> str = new_pos ;
 }
 pa -> max_length = pa -> length + length + PS_MALLOC ;
 }
 if ( pa -> typelib . count >= pa -> max_count - 1 ) {
 int len ;
 pa -> array_allocs ++ ;
 len = ( PC_MALLOC * pa -> array_allocs - MALLOC_OVERHEAD ) ;
 if ( ! ( new_array = ( const char * * ) my_realloc ( ( uchar * ) pa -> typelib . type_names , ( uint ) len / ( sizeof ( uchar * ) + sizeof ( * pa -> flag ) ) * ( sizeof ( uchar * ) + sizeof ( * pa -> flag ) ) , MYF ( MY_WME ) ) ) ) DBUG_RETURN ( 1 ) ;
 pa -> typelib . type_names = new_array ;
 old_count = pa -> max_count ;
 pa -> max_count = len / ( sizeof ( uchar * ) + sizeof ( * pa -> flag ) ) ;
 pa -> flag = ( uint8 * ) ( pa -> typelib . type_names + pa -> max_count ) ;
 memcpy ( ( uchar * ) pa -> flag , ( char * ) ( pa -> typelib . type_names + old_count ) , old_count * sizeof ( * pa -> flag ) ) ;
 }
 pa -> flag [ pa -> typelib . count ] = 0 ;
 pa -> typelib . type_names [ pa -> typelib . count ++ ] = ( char * ) pa -> str + pa -> length ;
 pa -> typelib . type_names [ pa -> typelib . count ] = NullS ;
 ( void ) strmov ( ( char * ) pa -> str + pa -> length , name ) ;
 pa -> length += length ;
 DBUG_RETURN ( 0 ) ;
 }