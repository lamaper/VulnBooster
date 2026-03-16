static guint16 de_red_party_sub_addr ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 gchar * extr_addr ;
 de_sub_addr ( tvb , tree , pinfo , offset , len , & extr_addr ) ;
 if ( extr_addr && add_string ) g_snprintf ( add_string , string_len , " - (%s)" , extr_addr ) ;
 return ( len ) ;
 }