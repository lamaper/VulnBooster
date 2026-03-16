static guint qname_labels_count ( const guchar * name , guint name_len ) {
 guint labels = 0 ;
 unsigned i ;
 if ( name_len > 1 ) {
 for ( i = 0 ;
 i < strlen ( name ) ;
 i ++ ) {
 if ( name [ i ] == '.' ) labels ++ ;
 }
 labels ++ ;
 }
 return labels ;
 }