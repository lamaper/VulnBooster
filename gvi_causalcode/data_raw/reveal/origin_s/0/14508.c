static bfd_boolean internal_srec_write_object_contents ( bfd * abfd , int symbols ) {
 tdata_type * tdata = abfd -> tdata . srec_data ;
 srec_data_list_type * list ;
 if ( symbols ) {
 if ( ! srec_write_symbols ( abfd ) ) return FALSE ;
 }
 if ( ! srec_write_header ( abfd ) ) return FALSE ;
 list = tdata -> head ;
 while ( list != ( srec_data_list_type * ) NULL ) {
 if ( ! srec_write_section ( abfd , tdata , list ) ) return FALSE ;
 list = list -> next ;
 }
 return srec_write_terminator ( abfd , tdata ) ;
 }