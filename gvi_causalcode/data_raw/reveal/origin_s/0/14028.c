const char * netbios_name_type_descr ( int name_type ) {
 return val_to_str_ext_const ( name_type , & nb_name_type_vals_ext , "Unknown" ) ;
 }