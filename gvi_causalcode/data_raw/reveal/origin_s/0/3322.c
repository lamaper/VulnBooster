static void srec_print_symbol ( bfd * abfd , void * afile , asymbol * symbol , bfd_print_symbol_type how ) {
 FILE * file = ( FILE * ) afile ;
 switch ( how ) {
 case bfd_print_symbol_name : fprintf ( file , "%s" , symbol -> name ) ;
 break ;
 default : bfd_print_symbol_vandf ( abfd , ( void * ) file , symbol ) ;
 fprintf ( file , " %-5s %s" , symbol -> section -> name , symbol -> name ) ;
 }
 }