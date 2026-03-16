static gboolean destroy_srcdsc ( gpointer k _U_ , gpointer v , gpointer p _U_ ) {
 k12_src_desc_t * rec = ( k12_src_desc_t * ) v ;
 g_free ( rec -> input_name ) ;
 g_free ( rec -> stack_file ) ;
 g_free ( rec ) ;
 return TRUE ;
 }