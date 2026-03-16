static void get_last_ber_identifier ( gint8 * ber_class , gboolean * pc , gint32 * tag ) {
 if ( ber_class ) * ber_class = last_class ;
 if ( pc ) * pc = last_pc ;
 if ( tag ) * tag = last_tag ;
 }