int chk_size ( MI_CHECK * param , register MI_INFO * info ) {
 int error = 0 ;
 register my_off_t skr , size ;
 char buff [ 22 ] , buff2 [ 22 ] ;
 DBUG_ENTER ( "chk_size" ) ;
 if ( ! ( param -> testflag & T_SILENT ) ) puts ( "- check file-size" ) ;
 flush_key_blocks ( info -> s -> key_cache , info -> s -> kfile , FLUSH_FORCE_WRITE ) ;
 size = mysql_file_seek ( info -> s -> kfile , 0L , MY_SEEK_END , MYF ( MY_THREADSAFE ) ) ;
 if ( ( skr = ( my_off_t ) info -> state -> key_file_length ) != size ) {
 if ( skr > size && mi_is_any_key_active ( info -> s -> state . key_map ) ) {
 error = 1 ;
 mi_check_print_error ( param , "Size of indexfile is: %-8s Should be: %s" , llstr ( size , buff ) , llstr ( skr , buff2 ) ) ;
 }
 else mi_check_print_warning ( param , "Size of indexfile is: %-8s Should be: %s" , llstr ( size , buff ) , llstr ( skr , buff2 ) ) ;
 }
 if ( ! ( param -> testflag & T_VERY_SILENT ) && ! ( info -> s -> options & HA_OPTION_COMPRESS_RECORD ) && ulonglong2double ( info -> state -> key_file_length ) > ulonglong2double ( info -> s -> base . margin_key_file_length ) * 0.9 ) mi_check_print_warning ( param , "Keyfile is almost full, %10s of %10s used" , llstr ( info -> state -> key_file_length , buff ) , llstr ( info -> s -> base . max_key_file_length - 1 , buff ) ) ;
 size = mysql_file_seek ( info -> dfile , 0L , MY_SEEK_END , MYF ( 0 ) ) ;
 skr = ( my_off_t ) info -> state -> data_file_length ;
 if ( info -> s -> options & HA_OPTION_COMPRESS_RECORD ) skr += MEMMAP_EXTRA_MARGIN ;


 info -> state -> data_file_length = size ;
 if ( skr > size && skr != size + MEMMAP_EXTRA_MARGIN ) {
 error = 1 ;
 mi_check_print_error ( param , "Size of datafile is: %-9s Should be: %s" , llstr ( size , buff ) , llstr ( skr , buff2 ) ) ;
 param -> testflag |= T_RETRY_WITHOUT_QUICK ;
 }
 else {
 mi_check_print_warning ( param , "Size of datafile is: %-9s Should be: %s" , llstr ( size , buff ) , llstr ( skr , buff2 ) ) ;
 }
 }
 if ( ! ( param -> testflag & T_VERY_SILENT ) && ! ( info -> s -> options & HA_OPTION_COMPRESS_RECORD ) && ulonglong2double ( info -> state -> data_file_length ) > ( ulonglong2double ( info -> s -> base . max_data_file_length ) * 0.9 ) ) mi_check_print_warning ( param , "Datafile is almost full, %10s of %10s used" , llstr ( info -> state -> data_file_length , buff ) , llstr ( info -> s -> base . max_data_file_length - 1 , buff2 ) ) ;
 DBUG_RETURN ( error ) ;
 }