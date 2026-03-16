static const gchar * get_message_name ( guint8 prot_discr , guint8 message_type ) {
 if ( prot_discr == NLPID_DMS ) return val_to_str ( message_type , dms_message_type_vals , "Unknown (0x%02X)" ) ;
 else return val_to_str_ext ( message_type , & q931_message_type_vals_ext , "Unknown (0x%02X)" ) ;
 }