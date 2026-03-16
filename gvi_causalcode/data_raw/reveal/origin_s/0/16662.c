static const sasl_cmd * find_sasl_command ( tvbuff_t * tvb , gint offset ) {
 gint command_index ;
 for ( command_index = 0 ;
 command_index < sasl_commands_count ;
 command_index ++ ) {
 const sasl_cmd * cmd ;
 cmd = & sasl_commands [ command_index ] ;
 if ( 0 == tvb_strneql ( tvb , offset , cmd -> text , cmd -> length ) ) {
 return cmd ;
 }
 }
 return NULL ;
 }