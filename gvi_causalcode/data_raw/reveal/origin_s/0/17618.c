static guint16 de_setup_cont ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 dtap_cc_setup ( tvb , tree , pinfo , offset , len ) ;
 return ( len ) ;
 }