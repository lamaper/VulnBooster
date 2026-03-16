void replace_dynstr_append_uint ( DYNAMIC_STRING * ds , uint val ) {
 char buff [ 22 ] ;
 char * end = longlong10_to_str ( val , buff , 10 ) ;
 replace_dynstr_append_mem ( ds , buff , end - buff ) ;
 }