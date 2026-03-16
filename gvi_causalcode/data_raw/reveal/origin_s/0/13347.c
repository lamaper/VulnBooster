static const struct var_expand_table * login_set_var_expand_table ( const struct master_service_settings_input * input ) {
 static struct var_expand_table static_tab [ ] = {
 {
 'l' , NULL , "lip" }
 , {
 'r' , NULL , "rip" }
 , {
 'p' , NULL , "pid" }
 , {
 's' , NULL , "service" }
 , {
 '\0' , NULL , "local_name" }
 , {
 '\0' , NULL , NULL }
 }
 ;
 struct var_expand_table * tab ;
 tab = t_malloc ( sizeof ( static_tab ) ) ;
 memcpy ( tab , static_tab , sizeof ( static_tab ) ) ;
 tab [ 0 ] . value = net_ip2addr ( & input -> local_ip ) ;
 tab [ 1 ] . value = net_ip2addr ( & input -> remote_ip ) ;
 tab [ 2 ] . value = my_pid ;
 tab [ 3 ] . value = input -> service ;
 tab [ 4 ] . value = input -> local_name ;
 return tab ;
 }