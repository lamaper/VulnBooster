static int sort_ft_key_read ( MI_SORT_PARAM * sort_param , void * key ) {
 int error ;
 SORT_INFO * sort_info = sort_param -> sort_info ;
 MI_INFO * info = sort_info -> info ;
 FT_WORD * wptr = 0 ;
 DBUG_ENTER ( "sort_ft_key_read" ) ;
 if ( ! sort_param -> wordlist ) {
 for ( ;
 ;
 ) {
 free_root ( & sort_param -> wordroot , MYF ( MY_MARK_BLOCKS_FREE ) ) ;
 if ( ( error = sort_get_next_record ( sort_param ) ) ) DBUG_RETURN ( error ) ;
 if ( ! ( wptr = _mi_ft_parserecord ( info , sort_param -> key , sort_param -> record , & sort_param -> wordroot ) ) ) DBUG_RETURN ( 1 ) ;
 if ( wptr -> pos ) break ;
 error = sort_write_record ( sort_param ) ;
 }
 sort_param -> wordptr = sort_param -> wordlist = wptr ;
 }
 else {
 error = 0 ;
 wptr = ( FT_WORD * ) ( sort_param -> wordptr ) ;
 }
 sort_param -> real_key_length = ( info -> s -> rec_reflength + _ft_make_key ( info , sort_param -> key , key , wptr ++ , sort_param -> filepos ) ) ;


 free_root ( & sort_param -> wordroot , MYF ( MY_MARK_BLOCKS_FREE ) ) ;
 sort_param -> wordlist = 0 ;
 error = sort_write_record ( sort_param ) ;
 }
 else sort_param -> wordptr = ( void * ) wptr ;
 DBUG_RETURN ( error ) ;
 }