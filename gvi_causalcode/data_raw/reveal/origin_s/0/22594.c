void print_object_list ( int list_type ) {
 hoststatus * temp_hoststatus = NULL ;
 servicestatus * temp_servicestatus = NULL ;
 int x = 0 ;
 int row_color = 0 ;
 int host_passive = FALSE ;
 int service_passive = FALSE ;
 printf ( "<tr><td colspan=\"2\">&nbsp;
</td></tr>\n" ) ;
 printf ( "<tr class=\"sectionHeader\"><td colspan=\"2\" >Affected Objects</td></tr>\n" ) ;
 printf ( "<tr><td colspan=\"2\">\n" ) ;
 printf ( "<script language='javascript' type=\"text/javascript\">\nchecked=false;
\n" ) ;
 printf ( "function checkAllBoxes() {
\n" " checked = (checked == false) ? true : false;
\n" " for (var i=0;
 i < %d;
 i++) {
\n" " var checkboxes = document.getElementById(\"cb_\" + i);
\n" " if (checkboxes != null ) {
 checkboxes.checked = checked;
 }
\n" " }
\n" "}
\n" , NUMBER_OF_STRUCTS ) ;
 printf ( "</script>\n" ) ;
 printf ( "<TABLE cellspacing='2' cellpadding='0' border='0' width='100%%'>\n" ) ;
 if ( list_type == PRINT_SERVICE_LIST ) printf ( "<tr class=\"objectTableHeader\"><td width=\"46%%\">Host</td><td width=\"46%%\">Service</td><td width='16'><input type='checkbox' onclick=\"checkAllBoxes();
\" title=\"Check All\"></td></tr>\n" ) ;
 else if ( list_type == PRINT_HOST_LIST ) printf ( "<tr class=\"objectTableHeader\"><td colspan=\"2\" width=\"96%%\">Hosts</td><td width='16'><input type='checkbox' onclick=\"checkAllBoxes();
\" title=\"Check All\"></td></tr>\n" ) ;
 else printf ( "<tr><td colspan=\"3\">&nbsp;
</td></tr>\n" ) ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( list_type == PRINT_HOST_LIST || list_type == PRINT_SERVICE_LIST ) {
 host_passive = FALSE ;
 service_passive = FALSE ;
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( list_type == PRINT_SERVICE_LIST && commands [ x ] . description == NULL ) continue ;
 if ( strlen ( commands [ x ] . host_name ) != 0 && ( command_type == CMD_SCHEDULE_HOST_CHECK || command_type == CMD_DISABLE_HOST_CHECK || command_type == CMD_SCHEDULE_SVC_CHECK || command_type == CMD_DISABLE_SVC_CHECK ) ) {
 if ( ( temp_hoststatus = find_hoststatus ( commands [ x ] . host_name ) ) != NULL ) {
 if ( temp_hoststatus -> checks_enabled == FALSE ) host_passive = TRUE ;
 }
 if ( list_type == PRINT_SERVICE_LIST && strlen ( commands [ x ] . description ) != 0 ) {
 if ( ( temp_servicestatus = find_servicestatus ( commands [ x ] . host_name , commands [ x ] . description ) ) != NULL ) {
 if ( temp_servicestatus -> checks_enabled == FALSE ) service_passive = TRUE ;
 }
 }
 }
 }
 else {
 if ( multi_ids [ x ] == FALSE ) continue ;
 }
 row_color = ( row_color == 0 ) ? 1 : 0 ;
 printf ( "<tr class=\"status%s\"><td width=\"50%%\"" , ( row_color == 0 ) ? "Even" : "Odd " ) ;
 if ( list_type == PRINT_SERVICE_LIST ) {
 if ( strlen ( commands [ x ] . host_name ) != 0 && strlen ( commands [ x ] . description ) != 0 ) {
 printf ( ">%s</td><td>%s" , escape_string ( commands [ x ] . host_name ) , escape_string ( commands [ x ] . description ) ) ;
 if ( service_passive == TRUE ) {
 printf ( "<img src='%s%s' align=right border=0 style='padding-right:2px' alt='Passive' title='Passive Service'>" , url_images_path , PASSIVE_ICON ) ;
 }
 printf ( "</td>\n" ) ;
 printf ( "<td align='center'><input type='checkbox' name='hostservice' id=\"cb_%d\" value='%s^%s' title=\"%s Service\" %s></td></tr>\n" , x , escape_string ( commands [ x ] . host_name ) , escape_string ( commands [ x ] . description ) , ( service_passive == FALSE ) ? "Active" : "Passive" , ( service_passive == FALSE ) ? "checked" : "" ) ;
 }
 else {
 if ( ! strcmp ( commands [ x ] . host_name , "" ) ) printf ( "><INPUT TYPE='TEXT' NAME='host' SIZE=30></td>" ) ;
 else printf ( "><INPUT TYPE='HIDDEN' NAME='host' VALUE='%s'>%s</td>" , escape_string ( commands [ x ] . host_name ) , escape_string ( commands [ x ] . host_name ) ) ;
 if ( ! strcmp ( commands [ x ] . description , "" ) ) printf ( "<td><INPUT TYPE='TEXT' NAME='service' SIZE=30></td>" ) ;
 else printf ( "<td><INPUT TYPE='HIDDEN' NAME='service' VALUE='%s'>%s</td>" , escape_string ( commands [ x ] . description ) , escape_string ( commands [ x ] . description ) ) ;
 printf ( "<td></td></tr>\n" ) ;
 }
 }
 else if ( list_type == PRINT_HOST_LIST ) {
 if ( ! strcmp ( commands [ x ] . host_name , "" ) ) printf ( " style=\"font-weight:bold;
\">Host:</td><td><INPUT TYPE='TEXT' NAME='host' SIZE=30></td><td></td></tr>\n" ) ;
 else {
 printf ( " style=\"font-weight:bold;
\">Host:</td><td>%s" , escape_string ( commands [ x ] . host_name ) ) ;
 if ( host_passive == TRUE ) {
 printf ( "<img src='%s%s' align=right border=0 style='padding-right:2px' alt='Passive' title='Passive Service'>" , url_images_path , PASSIVE_ICON ) ;
 }
 printf ( "</td>\n" ) ;
 printf ( "<td align='center'><input type='checkbox' name='host' id=\"cb_%d\" value='%s' title=\"%s Host\" %s></td></tr>\n" , x , escape_string ( commands [ x ] . host_name ) , ( host_passive == FALSE ) ? "Active" : "Passive" , ( host_passive == FALSE ) ? "checked" : "" ) ;
 }
 }
 else if ( list_type == PRINT_COMMENT_LIST ) {
 printf ( " style=\"font-weight:bold;
\">Comment ID:</td><td><INPUT TYPE='HIDDEN' NAME='com_id' VALUE='%lu'>%lu</td></tr>\n" , multi_ids [ x ] , multi_ids [ x ] ) ;
 }
 else if ( list_type == PRINT_DOWNTIME_LIST ) {
 printf ( " style=\"font-weight:bold;
\">Scheduled Downtime ID:</td><td><INPUT TYPE='HIDDEN' NAME='down_id' VALUE='%lu'>%lu</td></tr>\n" , multi_ids [ x ] , multi_ids [ x ] ) ;
 }
 }
 printf ( "</td><tr></table>\n</td></tr>\n" ) ;
 return ;
 }