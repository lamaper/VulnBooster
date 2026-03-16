static int process_header_records ( wtap * wth , int * err , gchar * * err_info , gint16 maj_vers , guint8 network ) {
 char record_type [ 2 ] ;
 char record_length [ 4 ] ;
 guint16 type , length ;
 int bytes_to_read ;
 unsigned char buffer [ 256 ] ;
 for ( ;
 ;
 ) {
 if ( ! wtap_read_bytes_or_eof ( wth -> fh , record_type , 2 , err , err_info ) ) {
 if ( * err != 0 ) return - 1 ;
 return 0 ;
 }
 type = pletoh16 ( record_type ) ;
 if ( ( type != REC_HEADER1 ) && ( type != REC_HEADER2 ) && ( type != REC_HEADER3 ) && ( type != REC_HEADER4 ) && ( type != REC_HEADER5 ) && ( type != REC_HEADER6 ) && ( type != REC_HEADER7 ) && ( ( type != REC_V2DESC ) || ( maj_vers > 2 ) ) ) {
 if ( file_seek ( wth -> fh , - 2 , SEEK_CUR , err ) == - 1 ) return - 1 ;
 return 0 ;
 }
 if ( ! wtap_read_bytes ( wth -> fh , record_length , 4 , err , err_info ) ) return - 1 ;
 length = pletoh16 ( record_length ) ;
 if ( ( network == NETWORK_SYNCHRO || network == NETWORK_ASYNC ) && type == REC_HEADER2 ) {
 bytes_to_read = MIN ( length , ( int ) sizeof buffer ) ;
 if ( ! wtap_read_bytes ( wth -> fh , buffer , bytes_to_read , err , err_info ) ) return - 1 ;
 switch ( maj_vers ) {
 case 2 : if ( process_rec_header2_v2 ( wth , buffer , length , err , err_info ) < 0 ) return - 1 ;
 break ;
 case 1 : case 4 : case 5 : if ( process_rec_header2_v145 ( wth , buffer , length , maj_vers , err , err_info ) < 0 ) return - 1 ;
 break ;
 }
 if ( length > sizeof buffer ) {
 if ( file_seek ( wth -> fh , length - sizeof buffer , SEEK_CUR , err ) == - 1 ) return - 1 ;
 }
 }
 else {
 if ( file_seek ( wth -> fh , length , SEEK_CUR , err ) == - 1 ) return - 1 ;
 }
 }
 }