static void dnslabel_clear ( struct dnslabel_table * table ) {
 int i ;
 for ( i = 0 ;
 i < table -> n_labels ;
 ++ i ) free ( table -> labels [ i ] . v ) ;
 table -> n_labels = 0 ;
 }