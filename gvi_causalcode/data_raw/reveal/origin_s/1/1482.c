int handle__publish ( struct mosquitto_db * db , struct mosquitto * context ) {
 char * topic ;
 mosquitto__payload_uhpa payload ;
 uint32_t payloadlen ;
 uint8_t dup , qos , retain ;
 uint16_t mid = 0 ;
 int rc = 0 ;
 uint8_t header = context -> in_packet . command ;
 int res = 0 ;
 struct mosquitto_msg_store * stored = NULL ;
 int len ;
 int slen ;
 char * topic_mount ;

 int i ;
 struct mosquitto__bridge_topic * cur_topic ;
 bool match ;

 dup = ( header & 0x08 ) >> 3 ;
 qos = ( header & 0x06 ) >> 1 ;
 if ( qos == 3 ) {
 log__printf ( NULL , MOSQ_LOG_INFO , "Invalid QoS in PUBLISH from %s, disconnecting." , context -> id ) ;
 return 1 ;
 }
 retain = ( header & 0x01 ) ;
 if ( packet__read_string ( & context -> in_packet , & topic , & slen ) ) return 1 ;
 if ( ! slen ) {
 mosquitto__free ( topic ) ;
 return 1 ;
 }

 for ( i = 0 ;
 i < context -> bridge -> topic_count ;
 i ++ ) {
 cur_topic = & context -> bridge -> topics [ i ] ;
 if ( ( cur_topic -> direction == bd_both || cur_topic -> direction == bd_in ) && ( cur_topic -> remote_prefix || cur_topic -> local_prefix ) ) {
 rc = mosquitto_topic_matches_sub ( cur_topic -> remote_topic , topic , & match ) ;
 if ( rc ) {
 mosquitto__free ( topic ) ;
 return rc ;
 }
 if ( match ) {
 if ( cur_topic -> remote_prefix ) {
 if ( ! strncmp ( cur_topic -> remote_prefix , topic , strlen ( cur_topic -> remote_prefix ) ) ) {
 topic_temp = mosquitto__strdup ( topic + strlen ( cur_topic -> remote_prefix ) ) ;
 if ( ! topic_temp ) {
 mosquitto__free ( topic ) ;
 return MOSQ_ERR_NOMEM ;
 }
 mosquitto__free ( topic ) ;
 topic = topic_temp ;
 }
 }
 if ( cur_topic -> local_prefix ) {
 len = strlen ( topic ) + strlen ( cur_topic -> local_prefix ) + 1 ;
 topic_temp = mosquitto__malloc ( len + 1 ) ;
 if ( ! topic_temp ) {
 mosquitto__free ( topic ) ;
 return MOSQ_ERR_NOMEM ;
 }
 snprintf ( topic_temp , len , "%s%s" , cur_topic -> local_prefix , topic ) ;
 topic_temp [ len ] = '\0' ;
 mosquitto__free ( topic ) ;
 topic = topic_temp ;
 }
 break ;
 }
 }
 }
 }

 mosquitto__free ( topic ) ;
 return 1 ;
 }
 if ( mosquitto_validate_utf8 ( topic , strlen ( topic ) ) != MOSQ_ERR_SUCCESS ) {
 mosquitto__free ( topic ) ;
 return 1 ;
 }
 if ( qos > 0 ) {
 if ( packet__read_uint16 ( & context -> in_packet , & mid ) ) {
 mosquitto__free ( topic ) ;
 return 1 ;
 }
 }
 payloadlen = context -> in_packet . remaining_length - context -> in_packet . pos ;
 G_PUB_BYTES_RECEIVED_INC ( payloadlen ) ;
 if ( context -> listener && context -> listener -> mount_point ) {
 len = strlen ( context -> listener -> mount_point ) + strlen ( topic ) + 1 ;
 topic_mount = mosquitto__malloc ( len + 1 ) ;
 if ( ! topic_mount ) {
 mosquitto__free ( topic ) ;
 return MOSQ_ERR_NOMEM ;
 }
 snprintf ( topic_mount , len , "%s%s" , context -> listener -> mount_point , topic ) ;
 topic_mount [ len ] = '\0' ;
 mosquitto__free ( topic ) ;
 topic = topic_mount ;
 }
 if ( payloadlen ) {
 if ( db -> config -> message_size_limit && payloadlen > db -> config -> message_size_limit ) {
 log__printf ( NULL , MOSQ_LOG_DEBUG , "Dropped too large PUBLISH from %s (d%d, q%d, r%d, m%d, '%s', ... (%ld bytes))" , context -> id , dup , qos , retain , mid , topic , ( long ) payloadlen ) ;
 goto process_bad_message ;
 }
 if ( UHPA_ALLOC ( payload , payloadlen + 1 ) == 0 ) {
 mosquitto__free ( topic ) ;
 return MOSQ_ERR_NOMEM ;
 }
 if ( packet__read_bytes ( & context -> in_packet , UHPA_ACCESS ( payload , payloadlen ) , payloadlen ) ) {
 mosquitto__free ( topic ) ;
 UHPA_FREE ( payload , payloadlen ) ;
 return 1 ;
 }
 }
 rc = mosquitto_acl_check ( db , context , topic , MOSQ_ACL_WRITE ) ;
 if ( rc == MOSQ_ERR_ACL_DENIED ) {
 log__printf ( NULL , MOSQ_LOG_DEBUG , "Denied PUBLISH from %s (d%d, q%d, r%d, m%d, '%s', ... (%ld bytes))" , context -> id , dup , qos , retain , mid , topic , ( long ) payloadlen ) ;
 goto process_bad_message ;
 }
 else if ( rc != MOSQ_ERR_SUCCESS ) {
 mosquitto__free ( topic ) ;
 UHPA_FREE ( payload , payloadlen ) ;
 return rc ;
 }
 log__printf ( NULL , MOSQ_LOG_DEBUG , "Received PUBLISH from %s (d%d, q%d, r%d, m%d, '%s', ... (%ld bytes))" , context -> id , dup , qos , retain , mid , topic , ( long ) payloadlen ) ;
 if ( qos > 0 ) {
 db__message_store_find ( context , mid , & stored ) ;
 }
 if ( ! stored ) {
 dup = 0 ;
 if ( db__message_store ( db , context -> id , mid , topic , qos , payloadlen , & payload , retain , & stored , 0 ) ) {
 return 1 ;
 }
 }
 else {
 mosquitto__free ( topic ) ;
 topic = stored -> topic ;
 dup = 1 ;
 }
 switch ( qos ) {
 case 0 : if ( sub__messages_queue ( db , context -> id , topic , qos , retain , & stored ) ) rc = 1 ;
 break ;
 case 1 : if ( sub__messages_queue ( db , context -> id , topic , qos , retain , & stored ) ) rc = 1 ;
 if ( send__puback ( context , mid ) ) rc = 1 ;
 break ;
 case 2 : if ( ! dup ) {
 res = db__message_insert ( db , context , mid , mosq_md_in , qos , retain , stored ) ;
 }
 else {
 res = 0 ;
 }
 if ( ! res ) {
 if ( send__pubrec ( context , mid ) ) rc = 1 ;
 }
 else if ( res == 1 ) {
 rc = 1 ;
 }
 break ;
 }
 return rc ;
 process_bad_message : mosquitto__free ( topic ) ;
 UHPA_FREE ( payload , payloadlen ) ;
 switch ( qos ) {
 case 0 : return MOSQ_ERR_SUCCESS ;
 case 1 : return send__puback ( context , mid ) ;
 case 2 : db__message_store_find ( context , mid , & stored ) ;
 if ( ! stored ) {
 if ( db__message_store ( db , context -> id , mid , NULL , qos , 0 , NULL , false , & stored , 0 ) ) {
 return 1 ;
 }
 res = db__message_insert ( db , context , mid , mosq_md_in , qos , false , stored ) ;
 }
 else {
 res = 0 ;
 }
 if ( ! res ) {
 res = send__pubrec ( context , mid ) ;
 }
 return res ;
 }
 return 1 ;
 }