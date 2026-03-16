static int dissect_dns_answer ( tvbuff_t * tvb , int offsetx , int dns_data_offset , column_info * cinfo , proto_tree * dns_tree , packet_info * pinfo , gboolean is_mdns ) {
 int len ;
 const guchar * name ;
 gchar * name_out ;
 int name_len ;
 int dns_type ;
 int dns_class ;
 int flush ;
 const char * class_name ;
 const char * type_name ;
 int data_offset ;
 int cur_offset ;
 int data_start ;
 gushort data_len ;
 proto_tree * rr_tree = NULL ;
 proto_item * trr = NULL ;
 data_start = data_offset = offsetx ;
 cur_offset = offsetx ;
 len = get_dns_name_type_class ( tvb , offsetx , dns_data_offset , & name , & name_len , & dns_type , & dns_class ) ;
 data_offset += len ;
 cur_offset += len ;
 if ( is_mdns ) {
 flush = dns_class & C_FLUSH ;
 dns_class &= ~ C_FLUSH ;
 }
 else {
 flush = 0 ;
 }
 type_name = val_to_str_ext ( dns_type , & dns_types_vals_ext , "Unknown (%d)" ) ;
 class_name = val_to_str_const ( dns_class , dns_classes , "Unknown" ) ;
 data_offset += 4 ;
 cur_offset += 4 ;
 data_len = tvb_get_ntohs ( tvb , data_offset ) ;
 data_offset += 2 ;
 cur_offset += 2 ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , "%s" , type_name ) ;
 if ( is_mdns && flush ) {
 col_append_str ( cinfo , COL_INFO , ", cache flush" ) ;
 }
 }
 if ( dns_tree != NULL ) {
 name_out = format_text ( name , strlen ( name ) ) ;
 if ( dns_type != T_OPT ) {
 rr_tree = proto_tree_add_subtree_format ( dns_tree , tvb , offsetx , ( data_offset - data_start ) + data_len , ett_dns_rr , & trr , "%s: type %s, class %s" , name_out , type_name , class_name ) ;
 add_rr_to_tree ( rr_tree , tvb , offsetx , name , name_len , dns_type , pinfo , is_mdns ) ;
 }
 else {
 rr_tree = proto_tree_add_subtree_format ( dns_tree , tvb , offsetx , ( data_offset - data_start ) + data_len , ett_dns_rr , & trr , "%s: type %s" , name_out , type_name ) ;
 add_opt_rr_to_tree ( rr_tree , tvb , offsetx , name , name_len , is_mdns ) ;
 }
 if ( is_mdns && flush ) {
 proto_item_append_text ( trr , ", cache flush" ) ;
 }
 }
 if ( data_len == 0 ) {
 return data_offset - data_start ;
 }
 switch ( dns_type ) {
 case T_A : {
 const char * addr ;
 addr = tvb_ip_to_str ( tvb , cur_offset ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , addr ) ;
 }
 proto_item_append_text ( trr , ", addr %s" , addr ) ;
 proto_tree_add_item ( rr_tree , hf_dns_a , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 if ( dns_use_for_addr_resolution && ( dns_class & 0x7f ) == C_IN ) {
 guint32 addr_int ;
 tvb_memcpy ( tvb , & addr_int , cur_offset , sizeof ( addr_int ) ) ;
 add_ipv4_name ( addr_int , name ) ;
 }
 }
 break ;
 case T_NS : {
 const guchar * ns_name ;
 int ns_name_len ;
 ns_name_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & ns_name ) ;
 name_out = format_text ( ns_name , strlen ( ns_name ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", ns %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_ns , tvb , cur_offset , ns_name_len , name_out ) ;
 }
 break ;
 case T_MD : {
 int hostname_len ;
 const guchar * hostname_str ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 hostname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & hostname_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_md , tvb , cur_offset , hostname_len , hostname_str ) ;
 }
 break ;
 case T_MF : {
 int hostname_len ;
 const guchar * hostname_str ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 hostname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & hostname_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_mf , tvb , cur_offset , hostname_len , hostname_str ) ;
 }
 break ;
 case T_CNAME : {
 const guchar * cname ;
 int cname_len ;
 cname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & cname ) ;
 name_out = format_text ( cname , strlen ( cname ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", cname %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_cname , tvb , cur_offset , cname_len , name_out ) ;
 }
 break ;
 case T_SOA : {
 const guchar * mname ;
 int mname_len ;
 const guchar * rname ;
 int rname_len ;
 proto_item * ti_soa ;
 mname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & mname ) ;
 name_out = format_text ( mname , strlen ( mname ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", mname %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_soa_mname , tvb , cur_offset , mname_len , name_out ) ;
 cur_offset += mname_len ;
 rname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & rname ) ;
 name_out = format_text ( rname , strlen ( rname ) ) ;
 proto_tree_add_string ( rr_tree , hf_dns_soa_rname , tvb , cur_offset , rname_len , name_out ) ;
 cur_offset += rname_len ;
 proto_tree_add_item ( rr_tree , hf_dns_soa_serial_number , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 ti_soa = proto_tree_add_item ( rr_tree , hf_dns_soa_refresh_interval , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti_soa , " (%s)" , time_secs_to_str ( wmem_packet_scope ( ) , tvb_get_ntohl ( tvb , cur_offset ) ) ) ;
 cur_offset += 4 ;
 ti_soa = proto_tree_add_item ( rr_tree , hf_dns_soa_retry_interval , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti_soa , " (%s)" , time_secs_to_str ( wmem_packet_scope ( ) , tvb_get_ntohl ( tvb , cur_offset ) ) ) ;
 cur_offset += 4 ;
 ti_soa = proto_tree_add_item ( rr_tree , hf_dns_soa_expire_limit , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti_soa , " (%s)" , time_secs_to_str ( wmem_packet_scope ( ) , tvb_get_ntohl ( tvb , cur_offset ) ) ) ;
 cur_offset += 4 ;
 ti_soa = proto_tree_add_item ( rr_tree , hf_dns_soa_minimum_ttl , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti_soa , " (%s)" , time_secs_to_str ( wmem_packet_scope ( ) , tvb_get_ntohl ( tvb , cur_offset ) ) ) ;
 }
 break ;
 case T_MB : {
 int hostname_len ;
 const guchar * hostname_str ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 hostname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & hostname_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_mb , tvb , cur_offset , hostname_len , hostname_str ) ;
 }
 break ;
 case T_MG : {
 int hostname_len ;
 const guchar * hostname_str ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 hostname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & hostname_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_mg , tvb , cur_offset , hostname_len , hostname_str ) ;
 }
 break ;
 case T_MR : {
 int hostname_len ;
 const guchar * hostname_str ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 hostname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & hostname_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_mr , tvb , cur_offset , hostname_len , hostname_str ) ;
 }
 break ;
 case T_NULL : {
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_null , tvb , cur_offset , data_len , ENC_NA ) ;
 }
 break ;
 case T_WKS : {
 int rr_len = data_len ;
 const char * wks_addr ;
 guint8 protocol ;
 guint8 bits ;
 int mask ;
 int port_num ;
 int i ;
 proto_item * ti_wks ;
 wmem_strbuf_t * bitnames = wmem_strbuf_new_label ( wmem_packet_scope ( ) ) ;
 wks_addr = tvb_ip_to_str ( tvb , cur_offset ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , wks_addr ) ;
 }
 proto_item_append_text ( trr , ", addr %s" , wks_addr ) ;
 proto_tree_add_item ( rr_tree , hf_dns_wks_address , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_wks_protocol , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 protocol = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 port_num = 0 ;
 while ( rr_len != 0 ) {
 bits = tvb_get_guint8 ( tvb , cur_offset ) ;
 if ( bits != 0 ) {
 mask = 1 << 7 ;
 wmem_strbuf_truncate ( bitnames , 0 ) ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 if ( bits & mask ) {
 if ( wmem_strbuf_get_len ( bitnames ) > 0 ) {
 wmem_strbuf_append ( bitnames , ", " ) ;
 }
 switch ( protocol ) {
 case IP_PROTO_TCP : wmem_strbuf_append ( bitnames , tcp_port_to_display ( wmem_packet_scope ( ) , port_num ) ) ;
 break ;
 case IP_PROTO_UDP : wmem_strbuf_append ( bitnames , udp_port_to_display ( wmem_packet_scope ( ) , port_num ) ) ;
 break ;
 default : wmem_strbuf_append_printf ( bitnames , "%u" , port_num ) ;
 break ;
 }
 }
 mask >>= 1 ;
 port_num ++ ;
 }
 ti_wks = proto_tree_add_item ( rr_tree , hf_dns_wks_bits , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti_wks , " (%s)" , wmem_strbuf_get_str ( bitnames ) ) ;
 }
 else {
 port_num += 8 ;
 }
 cur_offset += 1 ;
 rr_len -= 1 ;
 }
 }
 break ;
 case T_PTR : {
 const guchar * pname ;
 int pname_len ;
 pname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & pname ) ;
 name_out = format_text ( pname , strlen ( pname ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_ptr_domain_name , tvb , cur_offset , pname_len , name_out ) ;
 }
 break ;
 case T_HINFO : {
 int cpu_offset ;
 int cpu_len ;
 const char * cpu ;
 int os_offset ;
 int os_len ;
 const char * os ;
 cpu_offset = cur_offset ;
 cpu_len = tvb_get_guint8 ( tvb , cpu_offset ) ;
 cpu = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , cpu_offset + 1 , cpu_len , ENC_ASCII | ENC_NA ) ;
 os_offset = cpu_offset + 1 + cpu_len ;
 os_len = tvb_get_guint8 ( tvb , os_offset ) ;
 os = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , os_offset + 1 , os_len , ENC_ASCII | ENC_NA ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %.*s %.*s" , cpu_len , cpu , os_len , os ) ;
 }
 proto_item_append_text ( trr , ", CPU %.*s, OS %.*s" , cpu_len , cpu , os_len , os ) ;
 proto_tree_add_item ( rr_tree , hf_dns_hinfo_cpu_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_hinfo_cpu , tvb , cur_offset , cpu_len , ENC_ASCII | ENC_NA ) ;
 cur_offset += cpu_len ;
 proto_tree_add_item ( rr_tree , hf_dns_hinfo_os_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_hinfo_os , tvb , cur_offset , os_len , ENC_ASCII | ENC_NA ) ;
 }
 break ;
 case T_MINFO : {
 int rmailbx_len , emailbx_len ;
 const guchar * rmailbx_str , * emailbx_str ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 rmailbx_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & rmailbx_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_minfo_r_mailbox , tvb , cur_offset , rmailbx_len , rmailbx_str ) ;
 cur_offset += rmailbx_len ;
 emailbx_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & emailbx_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_minfo_e_mailbox , tvb , cur_offset , emailbx_len , emailbx_str ) ;
 }
 break ;
 case T_MX : {
 guint16 preference = 0 ;
 const guchar * mx_name ;
 int mx_name_len ;
 preference = tvb_get_ntohs ( tvb , cur_offset ) ;
 mx_name_len = get_dns_name ( tvb , cur_offset + 2 , 0 , dns_data_offset , & mx_name ) ;
 name_out = format_text ( mx_name , strlen ( mx_name ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %u %s" , preference , name_out ) ;
 }
 proto_item_append_text ( trr , ", preference %u, mx %s" , preference , name_out ) ;
 proto_tree_add_item ( rr_tree , hf_dns_mx_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_string ( rr_tree , hf_dns_mx_mail_exchange , tvb , cur_offset , mx_name_len , name_out ) ;
 }
 break ;
 case T_TXT : {
 int rr_len = data_len ;
 int txt_offset ;
 int txt_len ;
 txt_offset = cur_offset ;
 while ( rr_len != 0 ) {
 txt_len = tvb_get_guint8 ( tvb , txt_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_txt_length , tvb , txt_offset , 1 , ENC_BIG_ENDIAN ) ;
 txt_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_txt , tvb , txt_offset , txt_len , ENC_ASCII | ENC_NA ) ;
 txt_offset += txt_len ;
 rr_len -= txt_len ;
 }
 }
 break ;
 case T_RP : {
 int mbox_dname_len , txt_dname_len ;
 const guchar * mbox_dname , * txt_dname ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 mbox_dname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & mbox_dname ) ;
 proto_tree_add_string ( rr_tree , hf_dns_rp_mailbox , tvb , cur_offset , mbox_dname_len , mbox_dname ) ;
 cur_offset += mbox_dname_len ;
 txt_dname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & txt_dname ) ;
 proto_tree_add_string ( rr_tree , hf_dns_rp_txt_rr , tvb , cur_offset , txt_dname_len , txt_dname ) ;
 }
 break ;
 case T_AFSDB : {
 const guchar * host_name ;
 int host_name_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 host_name_len = get_dns_name ( tvb , cur_offset + 2 , 0 , dns_data_offset , & host_name ) ;
 proto_tree_add_item ( rr_tree , hf_dns_afsdb_subtype , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_string ( rr_tree , hf_dns_afsdb_hostname , tvb , cur_offset , host_name_len , host_name ) ;
 }
 break ;
 case T_X25 : {
 guint8 x25_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_x25_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 x25_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_x25_psdn_address , tvb , cur_offset , x25_len , ENC_ASCII | ENC_NA ) ;
 }
 break ;
 case T_ISDN : {
 guint8 isdn_address_len , isdn_sa_len ;
 int rr_len = data_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_isdn_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 isdn_address_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_isdn_address , tvb , cur_offset , isdn_address_len , ENC_ASCII | ENC_NA ) ;
 cur_offset += isdn_address_len ;
 rr_len -= isdn_address_len ;
 if ( rr_len > 1 ) {
 proto_tree_add_item ( rr_tree , hf_dns_isdn_sa_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 isdn_sa_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_isdn_sa , tvb , cur_offset , isdn_sa_len , ENC_ASCII | ENC_NA ) ;
 }
 }
 break ;
 case T_RT : {
 const guchar * host_name ;
 int host_name_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 host_name_len = get_dns_name ( tvb , cur_offset + 2 , 0 , dns_data_offset , & host_name ) ;
 proto_tree_add_item ( rr_tree , hf_dns_rt_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_string ( rr_tree , hf_dns_rt_intermediate_host , tvb , cur_offset , host_name_len , host_name ) ;
 }
 break ;
 case T_NSAP : {
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_nsap_rdata , tvb , cur_offset , data_len , ENC_NA ) ;
 }
 break ;
 case T_NSAP_PTR : {
 int nsap_ptr_owner_len ;
 const guchar * nsap_ptr_owner ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 nsap_ptr_owner_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & nsap_ptr_owner ) ;
 proto_tree_add_string ( rr_tree , hf_dns_nsap_ptr_owner , tvb , cur_offset , nsap_ptr_owner_len , nsap_ptr_owner ) ;
 }
 break ;
 case T_KEY : {
 int rr_len = data_len ;
 guint16 flags ;
 proto_item * tf , * ti_gen ;
 proto_tree * flags_tree ;
 guint8 algo ;
 guint16 key_id ;
 tf = proto_tree_add_item ( rr_tree , hf_dns_key_flags , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 flags_tree = proto_item_add_subtree ( tf , ett_key_flags ) ;
 flags = tvb_get_ntohs ( tvb , cur_offset ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_authentication , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_confidentiality , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 if ( ( flags & 0xC000 ) != 0xC000 ) {
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_key_required , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_associated_user , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_associated_named_entity , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_ipsec , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_mime , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_key_flags_signatory , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 }
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_key_protocol , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_key_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 algo = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 key_id = compute_key_id ( tvb , cur_offset - 4 , rr_len + 4 , algo ) ;
 ti_gen = proto_tree_add_uint ( rr_tree , hf_dns_key_key_id , tvb , 0 , 0 , key_id ) ;
 PROTO_ITEM_SET_GENERATED ( ti_gen ) ;
 if ( rr_len != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_key_public_key , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 }
 break ;
 case T_PX : {
 int px_map822_len , px_mapx400_len ;
 const guchar * px_map822_dnsname , * px_mapx400_dnsname ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_px_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 px_map822_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & px_map822_dnsname ) ;
 proto_tree_add_string ( rr_tree , hf_dns_px_map822 , tvb , cur_offset , px_map822_len , px_map822_dnsname ) ;
 cur_offset += px_map822_len ;
 px_mapx400_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & px_mapx400_dnsname ) ;
 proto_tree_add_string ( rr_tree , hf_dns_px_mapx400 , tvb , cur_offset , px_mapx400_len , px_mapx400_dnsname ) ;
 }
 break ;
 case T_GPOS : {
 guint8 long_len , lat_len , alt_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_gpos_longitude_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 long_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_gpos_longitude , tvb , cur_offset , long_len , ENC_ASCII | ENC_NA ) ;
 cur_offset += long_len ;
 proto_tree_add_item ( rr_tree , hf_dns_gpos_latitude_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 lat_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_gpos_latitude , tvb , cur_offset , lat_len , ENC_ASCII | ENC_NA ) ;
 cur_offset += lat_len ;
 proto_tree_add_item ( rr_tree , hf_dns_gpos_altitude_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 alt_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_gpos_altitude , tvb , cur_offset , alt_len , ENC_ASCII | ENC_NA ) ;
 }
 break ;
 case T_AAAA : {
 const char * addr6 ;
 addr6 = tvb_ip6_to_str ( tvb , cur_offset ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , addr6 ) ;
 }
 proto_item_append_text ( trr , ", addr %s" , addr6 ) ;
 proto_tree_add_item ( rr_tree , hf_dns_aaaa , tvb , cur_offset , 16 , ENC_NA ) ;
 if ( dns_use_for_addr_resolution && ( dns_class & 0x7f ) == C_IN ) {
 struct e_in6_addr addr_in6 ;
 tvb_memcpy ( tvb , & addr_in6 , cur_offset , sizeof ( addr_in6 ) ) ;
 add_ipv6_name ( & addr_in6 , name ) ;
 }
 }
 break ;
 case T_LOC : {
 guint8 version ;
 proto_item * ti ;
 version = tvb_get_guint8 ( tvb , cur_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_loc_version , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( version == 0 ) {
 cur_offset ++ ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_loc_size , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%g m)" , rfc1867_size ( tvb , cur_offset ) ) ;
 cur_offset ++ ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_loc_horizontal_precision , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%g m)" , rfc1867_size ( tvb , cur_offset ) ) ;
 cur_offset ++ ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_loc_vertical_precision , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%g m)" , rfc1867_size ( tvb , cur_offset ) ) ;
 cur_offset ++ ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_loc_latitude , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%s)" , rfc1867_angle ( tvb , cur_offset , "NS" ) ) ;
 cur_offset += 4 ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_loc_longitude , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%s)" , rfc1867_angle ( tvb , cur_offset , "EW" ) ) ;
 cur_offset += 4 ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_loc_altitude , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%g m)" , ( ( gint32 ) tvb_get_ntohl ( tvb , cur_offset ) - 10000000 ) / 100.0 ) ;
 }
 else {
 proto_tree_add_item ( rr_tree , hf_dns_loc_unknown_data , tvb , cur_offset , data_len , ENC_NA ) ;
 }
 }
 break ;
 case T_NXT : {
 int rr_len = data_len ;
 const guchar * next_domain_name ;
 int next_domain_name_len ;
 next_domain_name_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & next_domain_name ) ;
 name_out = format_text ( next_domain_name , strlen ( next_domain_name ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", next domain name %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_nxt_next_domain_name , tvb , cur_offset , next_domain_name_len , name_out ) ;
 cur_offset += next_domain_name_len ;
 rr_len -= next_domain_name_len ;
 dissect_type_bitmap_nxt ( rr_tree , tvb , cur_offset , rr_len ) ;
 }
 break ;
 case T_SRV : {
 guint16 priority = 0 ;
 guint16 weight = 0 ;
 guint16 port = 0 ;
 const guchar * target ;
 int target_len ;
 proto_tree_add_item ( rr_tree , hf_dns_srv_priority , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 priority = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_srv_weight , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 weight = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_srv_port , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 port = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 target_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & target ) ;
 name_out = format_text ( target , strlen ( target ) ) ;
 proto_tree_add_string ( rr_tree , hf_dns_srv_target , tvb , cur_offset , target_len , name_out ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %u %u %u %s" , priority , weight , port , name_out ) ;
 }
 proto_item_append_text ( trr , ", priority %u, weight %u, port %u, target %s" , priority , weight , port , name_out ) ;
 }
 break ;
 case T_NAPTR : {
 proto_item * ti_len ;
 int offset = cur_offset ;
 guint16 order ;
 guint16 preference ;
 gchar * flags ;
 guint8 flags_len ;
 guint8 service_len ;
 guint8 regex_len ;
 const guchar * replacement ;
 int replacement_len ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_order , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 order = tvb_get_ntohs ( tvb , offset ) ;
 offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_preference , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 preference = tvb_get_ntohs ( tvb , offset ) ;
 offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_flags_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 flags_len = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_flags , tvb , offset , flags_len , ENC_ASCII | ENC_NA ) ;
 flags = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , flags_len , ENC_ASCII | ENC_NA ) ;
 offset += flags_len ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_service_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 service_len = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_service , tvb , offset , service_len , ENC_ASCII | ENC_NA ) ;
 offset += service_len ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_regex_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 regex_len = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_naptr_regex , tvb , offset , regex_len , ENC_ASCII | ENC_NA ) ;
 offset += regex_len ;
 replacement_len = get_dns_name ( tvb , offset , 0 , dns_data_offset , & replacement ) ;
 name_out = format_text ( replacement , strlen ( replacement ) ) ;
 ti_len = proto_tree_add_uint ( rr_tree , hf_dns_naptr_replacement_length , tvb , offset , 0 , replacement_len ) ;
 PROTO_ITEM_SET_GENERATED ( ti_len ) ;
 proto_tree_add_string ( rr_tree , hf_dns_naptr_replacement , tvb , offset , replacement_len , name_out ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %u %u %s" , order , preference , flags ) ;
 }
 proto_item_append_text ( trr , ", order %u, preference %u, flags %s" , order , preference , flags ) ;
 }
 break ;
 case T_KX : {
 const guchar * kx_name ;
 int kx_name_len ;
 kx_name_len = get_dns_name ( tvb , cur_offset + 2 , 0 , dns_data_offset , & kx_name ) ;
 name_out = format_text ( kx_name , strlen ( kx_name ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %u %s" , tvb_get_ntohs ( tvb , cur_offset ) , name_out ) ;
 }
 proto_item_append_text ( trr , ", preference %u, kx %s" , tvb_get_ntohs ( tvb , cur_offset ) , name_out ) ;
 proto_tree_add_item ( rr_tree , hf_dns_kx_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_string ( rr_tree , hf_dns_kx_key_exchange , tvb , cur_offset + 2 , kx_name_len , name_out ) ;
 }
 break ;
 case T_CERT : {
 int rr_len = data_len ;
 proto_tree_add_item ( rr_tree , hf_dns_cert_type , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_cert_key_tag , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_cert_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 if ( rr_len != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_cert_certificate , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 }
 break ;
 case T_A6 : {
 unsigned short pre_len ;
 unsigned short suf_len ;
 unsigned short suf_octet_count ;
 const guchar * pname ;
 int pname_len ;
 int a6_offset ;
 int suf_offset ;
 struct e_in6_addr suffix ;
 address suffix_addr ;
 a6_offset = cur_offset ;
 pre_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset ++ ;
 suf_len = 128 - pre_len ;
 suf_octet_count = suf_len ? ( suf_len - 1 ) / 8 + 1 : 0 ;
 for ( suf_offset = 0 ;
 suf_offset < 16 - suf_octet_count ;
 suf_offset ++ ) {
 suffix . bytes [ suf_offset ] = 0 ;
 }
 for ( ;
 suf_offset < 16 ;
 suf_offset ++ ) {
 suffix . bytes [ suf_offset ] = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset ++ ;
 }
 if ( pre_len > 0 ) {
 pname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & pname ) ;
 }
 else {
 pname = "" ;
 pname_len = 0 ;
 }
 name_out = format_text ( pname , strlen ( pname ) ) ;
 SET_ADDRESS ( & suffix_addr , AT_IPv6 , 16 , suffix . bytes ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %d %s %s" , pre_len , address_to_str ( wmem_packet_scope ( ) , & suffix_addr ) , name_out ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_a6_prefix_len , tvb , a6_offset , 1 , ENC_BIG_ENDIAN ) ;
 a6_offset ++ ;
 if ( suf_len ) {
 proto_tree_add_ipv6 ( rr_tree , hf_dns_a6_address_suffix , tvb , a6_offset , suf_octet_count , suffix . bytes ) ;
 a6_offset += suf_octet_count ;
 }
 if ( pre_len > 0 ) {
 proto_tree_add_string ( rr_tree , hf_dns_a6_prefix_name , tvb , a6_offset , pname_len , name_out ) ;
 }
 proto_item_append_text ( trr , ", addr %d %s %s" , pre_len , address_to_str ( wmem_packet_scope ( ) , & suffix_addr ) , name_out ) ;
 }
 break ;
 case T_DNAME : {
 const guchar * dname ;
 int dname_len ;
 dname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & dname ) ;
 name_out = format_text ( dname , strlen ( dname ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", dname %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_dname , tvb , cur_offset , dname_len , name_out ) ;
 }
 break ;
 case T_OPT : {
 int rropt_len = data_len ;
 guint16 optcode , optlen ;
 proto_item * rropt , * rroptlen ;
 proto_tree * rropt_tree ;
 while ( rropt_len > 0 ) {
 optcode = tvb_get_ntohs ( tvb , cur_offset ) ;
 rropt_len -= 2 ;
 optlen = tvb_get_ntohs ( tvb , cur_offset + 2 ) ;
 rropt_len -= 2 ;
 rropt = proto_tree_add_item ( rr_tree , hf_dns_opt , tvb , cur_offset , 4 + optlen , ENC_NA ) ;
 proto_item_append_text ( rropt , ": %s" , val_to_str ( optcode , edns0_opt_code_vals , "Unknown (%d)" ) ) ;
 rropt_tree = proto_item_add_subtree ( rropt , ett_dns_opts ) ;
 rropt = proto_tree_add_item ( rropt_tree , hf_dns_opt_code , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rroptlen = proto_tree_add_item ( rropt_tree , hf_dns_opt_len , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rropt_tree , hf_dns_opt_data , tvb , cur_offset , optlen , ENC_NA ) ;
 switch ( optcode ) {
 case O_DAU : while ( optlen != 0 ) {
 proto_tree_add_item ( rropt_tree , hf_dns_opt_dau , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rropt_len -= 1 ;
 optlen -= 1 ;
 }
 break ;
 case O_DHU : while ( optlen != 0 ) {
 proto_tree_add_item ( rropt_tree , hf_dns_opt_dhu , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rropt_len -= 1 ;
 optlen -= 1 ;
 }
 break ;
 case O_N3U : while ( optlen != 0 ) {
 proto_tree_add_item ( rropt_tree , hf_dns_opt_n3u , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rropt_len -= 1 ;
 optlen -= 1 ;
 }
 break ;
 case O_CLIENT_SUBNET_EXP : expert_add_info_format ( pinfo , rropt , & ei_dns_depr_opc , "Deprecated opcode. Client subnet OPT assigned as %d." , O_CLIENT_SUBNET ) ;
 case O_CLIENT_SUBNET : {
 guint16 family ;
 guint16 addr_len = optlen - 4 ;
 union {
 guint32 addr ;
 guint8 bytes [ 16 ] ;
 }
 ip_addr = {
 0 }
 ;
 family = tvb_get_ntohs ( tvb , cur_offset ) ;
 proto_tree_add_item ( rropt_tree , hf_dns_opt_client_family , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rropt_tree , hf_dns_opt_client_netmask , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rropt_tree , hf_dns_opt_client_scope , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 if ( addr_len > 16 ) {
 expert_add_info ( pinfo , rroptlen , & ei_dns_opt_bad_length ) ;
 addr_len = 16 ;
 }
 tvb_memcpy ( tvb , ip_addr . bytes , cur_offset , addr_len ) ;
 switch ( family ) {
 case AFNUM_INET : proto_tree_add_ipv4 ( rropt_tree , hf_dns_opt_client_addr4 , tvb , cur_offset , addr_len , ip_addr . addr ) ;
 break ;
 case AFNUM_INET6 : proto_tree_add_ipv6 ( rropt_tree , hf_dns_opt_client_addr6 , tvb , cur_offset , addr_len , ip_addr . bytes ) ;
 break ;
 default : proto_tree_add_item ( rropt_tree , hf_dns_opt_client_addr , tvb , cur_offset , ( optlen - 4 ) , ENC_NA ) ;
 break ;
 }
 cur_offset += ( optlen - 4 ) ;
 rropt_len -= optlen ;
 }
 break ;
 default : cur_offset += optlen ;
 rropt_len -= optlen ;
 break ;
 }
 }
 }
 break ;
 case T_APL : {
 int rr_len = data_len ;
 guint16 afamily ;
 guint8 afdpart_len ;
 guint8 * addr_copy ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 while ( rr_len > 1 ) {
 afamily = tvb_get_ntohs ( tvb , cur_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_apl_address_family , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_apl_coded_prefix , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 afdpart_len = tvb_get_guint8 ( tvb , cur_offset ) & DNS_APL_AFDLENGTH ;
 proto_tree_add_item ( rr_tree , hf_dns_apl_negation , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rr_tree , hf_dns_apl_afdlength , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 if ( afamily == 1 && afdpart_len <= 4 ) {
 addr_copy = ( guint8 * ) wmem_alloc0 ( wmem_file_scope ( ) , 4 ) ;
 tvb_memcpy ( tvb , ( guint8 * ) addr_copy , cur_offset , afdpart_len ) ;
 proto_tree_add_ipv4 ( rr_tree , hf_dns_apl_afdpart_ipv4 , tvb , cur_offset , afdpart_len , * addr_copy ) ;
 }
 else if ( afamily == 2 && afdpart_len <= 16 ) {
 addr_copy = ( guint8 * ) wmem_alloc0 ( wmem_file_scope ( ) , 16 ) ;
 tvb_memcpy ( tvb , ( guint8 * ) addr_copy , cur_offset , afdpart_len ) ;
 proto_tree_add_ipv6 ( rr_tree , hf_dns_apl_afdpart_ipv6 , tvb , cur_offset , afdpart_len , addr_copy ) ;
 }
 else {
 proto_tree_add_item ( rr_tree , hf_dns_apl_afdpart_data , tvb , cur_offset , afdpart_len , ENC_NA ) ;
 }
 cur_offset += afdpart_len ;
 rr_len -= afdpart_len ;
 }
 }
 break ;
 case T_DS : case T_CDS : case T_DLV : {
 int rr_len = data_len ;
 proto_tree_add_item ( rr_tree , hf_dns_ds_key_id , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_ds_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_ds_digest_type , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_ds_digest , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 break ;
 case T_SSHFP : {
 int rr_len = data_len ;
 proto_tree_add_item ( rr_tree , hf_dns_sshfp_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_sshfp_fingerprint_type , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 if ( rr_len != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_sshfp_fingerprint , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 }
 break ;
 case T_IPSECKEY : {
 int rr_len = data_len ;
 guint8 gw_type ;
 const guchar * gw ;
 int gw_name_len ;
 proto_tree_add_item ( rr_tree , hf_dns_ipseckey_gateway_precedence , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_ipseckey_gateway_type , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 gw_type = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_ipseckey_gateway_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 switch ( gw_type ) {
 case 0 : break ;
 case 1 : proto_tree_add_item ( rr_tree , hf_dns_ipseckey_gateway_ipv4 , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 break ;
 case 2 : proto_tree_add_item ( rr_tree , hf_dns_ipseckey_gateway_ipv6 , tvb , cur_offset , 16 , ENC_NA ) ;
 cur_offset += 16 ;
 rr_len -= 16 ;
 break ;
 case 3 : gw_name_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & gw ) ;
 proto_tree_add_string ( rr_tree , hf_dns_ipseckey_gateway_dns , tvb , cur_offset , gw_name_len , gw ) ;
 cur_offset += gw_name_len ;
 rr_len -= gw_name_len ;
 break ;
 default : break ;
 }
 if ( rr_len != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_ipseckey_public_key , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 }
 break ;
 case T_RRSIG : case T_SIG : {
 int rr_len = data_len ;
 const guchar * signer_name ;
 int signer_name_len ;
 proto_item * ti ;
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_type_covered , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_labels , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_rrsig_original_ttl , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , " (%s)" , time_secs_to_str ( wmem_packet_scope ( ) , tvb_get_ntohl ( tvb , cur_offset ) ) ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_signature_expiration , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_signature_inception , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_key_tag , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 signer_name_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & signer_name ) ;
 proto_tree_add_string ( rr_tree , hf_dns_rrsig_signers_name , tvb , cur_offset , signer_name_len , signer_name ) ;
 cur_offset += signer_name_len ;
 rr_len -= signer_name_len ;
 if ( rr_len != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_rrsig_signature , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 }
 break ;
 case T_NSEC : {
 int rr_len = data_len ;
 const guchar * next_domain_name ;
 int next_domain_name_len ;
 next_domain_name_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & next_domain_name ) ;
 name_out = format_text ( next_domain_name , strlen ( next_domain_name ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", next domain name %s" , name_out ) ;
 proto_tree_add_string ( rr_tree , hf_dns_nsec_next_domain_name , tvb , cur_offset , next_domain_name_len , name_out ) ;
 cur_offset += next_domain_name_len ;
 rr_len -= next_domain_name_len ;
 dissect_type_bitmap ( rr_tree , tvb , cur_offset , rr_len ) ;
 }
 break ;
 case T_DNSKEY : case T_CDNSKEY : {
 int rr_len = data_len ;
 proto_item * tf , * ti_gen ;
 proto_tree * flags_tree ;
 guint16 key_id ;
 guint8 algo ;
 tf = proto_tree_add_item ( rr_tree , hf_dns_dnskey_flags , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 flags_tree = proto_item_add_subtree ( tf , ett_key_flags ) ;
 proto_tree_add_item ( flags_tree , hf_dns_dnskey_flags_zone_key , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_dnskey_flags_key_revoked , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_dnskey_flags_secure_entry_point , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_dns_dnskey_flags_reserved , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( flags_tree , hf_dns_dnskey_protocol , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( flags_tree , hf_dns_dnskey_algorithm , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 algo = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 key_id = compute_key_id ( tvb , cur_offset - 4 , rr_len + 4 , algo ) ;
 ti_gen = proto_tree_add_uint ( rr_tree , hf_dns_dnskey_key_id , tvb , 0 , 0 , key_id ) ;
 PROTO_ITEM_SET_GENERATED ( ti_gen ) ;
 proto_tree_add_item ( rr_tree , hf_dns_dnskey_public_key , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 break ;
 case T_DHCID : {
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_dhcid_rdata , tvb , cur_offset , data_len , ENC_NA ) ;
 }
 break ;
 case T_NSEC3 : {
 int rr_len , initial_offset = cur_offset ;
 guint8 salt_len , hash_len ;
 proto_item * flags_item ;
 proto_tree * flags_tree ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_algo , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 flags_item = proto_tree_add_item ( rr_tree , hf_dns_nsec3_flags , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 flags_tree = proto_item_add_subtree ( flags_item , ett_nsec3_flags ) ;
 proto_tree_add_item ( flags_tree , hf_dns_nsec3_flag_optout , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_iterations , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_salt_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 salt_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_salt_value , tvb , cur_offset , salt_len , ENC_NA ) ;
 cur_offset += salt_len ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_hash_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 hash_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_hash_value , tvb , cur_offset , hash_len , ENC_NA ) ;
 cur_offset += hash_len ;
 rr_len = data_len - ( cur_offset - initial_offset ) ;
 dissect_type_bitmap ( rr_tree , tvb , cur_offset , rr_len ) ;
 }
 break ;
 case T_NSEC3PARAM : {
 int salt_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_algo , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_flags , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_iterations , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_salt_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 salt_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 cur_offset += 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_nsec3_salt_value , tvb , cur_offset , salt_len , ENC_NA ) ;
 }
 break ;
 case T_TLSA : {
 int rr_len = data_len ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_tlsa_certificate_usage , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset ++ ;
 rr_len -- ;
 proto_tree_add_item ( rr_tree , hf_dns_tlsa_selector , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset ++ ;
 rr_len -- ;
 proto_tree_add_item ( rr_tree , hf_dns_tlsa_matching_type , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset ++ ;
 rr_len -- ;
 proto_tree_add_item ( rr_tree , hf_dns_tlsa_certificate_association_data , tvb , cur_offset , rr_len , ENC_NA ) ;
 }
 break ;
 case T_HIP : {
 guint8 hit_len ;
 guint16 pk_len ;
 int rr_len = data_len ;
 int rendezvous_len ;
 const guchar * rend_server_dns_name ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name ) ;
 }
 hit_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_hip_hit_length , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_hip_pk_algo , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset += 1 ;
 rr_len -= 1 ;
 pk_len = tvb_get_ntohs ( tvb , cur_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_hip_pk_length , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_hip_hit , tvb , cur_offset , hit_len , ENC_NA ) ;
 cur_offset += hit_len ;
 rr_len -= hit_len ;
 proto_tree_add_item ( rr_tree , hf_dns_hip_pk , tvb , cur_offset , pk_len , ENC_NA ) ;
 cur_offset += pk_len ;
 rr_len -= pk_len ;
 while ( rr_len > 1 ) {
 rendezvous_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & rend_server_dns_name ) ;
 proto_tree_add_string ( rr_tree , hf_dns_hip_rendezvous_server , tvb , cur_offset , rendezvous_len , rend_server_dns_name ) ;
 cur_offset += rendezvous_len ;
 rr_len -= rendezvous_len ;
 }
 }
 break ;
 case T_OPENPGPKEY : {
 proto_tree_add_item ( rr_tree , hf_dns_openpgpkey , tvb , cur_offset , data_len , ENC_ASCII | ENC_NA ) ;
 }
 break ;
 case T_SPF : {
 int rr_len = data_len ;
 int spf_offset ;
 int spf_len ;
 spf_offset = cur_offset ;
 while ( rr_len != 0 ) {
 spf_len = tvb_get_guint8 ( tvb , spf_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_spf_length , tvb , spf_offset , 1 , ENC_BIG_ENDIAN ) ;
 spf_offset += 1 ;
 rr_len -= 1 ;
 proto_tree_add_item ( rr_tree , hf_dns_spf , tvb , spf_offset , spf_len , ENC_ASCII | ENC_NA ) ;
 spf_offset += spf_len ;
 rr_len -= spf_len ;
 }
 }
 break ;
 case T_NID : {
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_nodeid_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_nodeid , tvb , cur_offset , 8 , ENC_NA ) ;
 }
 break ;
 case T_L32 : {
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_locator32_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_locator32 , tvb , cur_offset , 4 , ENC_NA ) ;
 }
 break ;
 case T_L64 : {
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_locator64_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_locator64 , tvb , cur_offset , 8 , ENC_NA ) ;
 }
 break ;
 case T_LP : {
 int lp_len ;
 const guchar * lp_str ;
 proto_tree_add_item ( rr_tree , hf_dns_ilnp_locatorfqdn_preference , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 lp_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & lp_str ) ;
 proto_tree_add_string ( rr_tree , hf_dns_ilnp_locatorfqdn , tvb , cur_offset , lp_len , lp_str ) ;
 }
 break ;
 case T_EUI48 : {
 proto_tree_add_item ( rr_tree , hf_dns_eui48 , tvb , cur_offset , 6 , ENC_NA ) ;
 }
 break ;
 case T_EUI64 : {
 proto_tree_add_item ( rr_tree , hf_dns_eui64 , tvb , cur_offset , 8 , ENC_NA ) ;
 }
 break ;
 case T_TKEY : {
 const guchar * tkey_algname ;
 int tkey_algname_len ;
 guint16 tkey_mode , tkey_keylen , tkey_otherlen ;
 proto_tree * key_tree ;
 proto_item * key_item ;
 tkey_algname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & tkey_algname ) ;
 proto_tree_add_string ( rr_tree , hf_dns_tkey_algo_name , tvb , cur_offset , tkey_algname_len , tkey_algname ) ;
 cur_offset += tkey_algname_len ;
 proto_tree_add_item ( rr_tree , hf_dns_tkey_signature_inception , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_tkey_signature_expiration , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_tkey_mode , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 tkey_mode = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_tkey_error , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_tkey_key_size , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 tkey_keylen = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 if ( tkey_keylen != 0 ) {
 key_item = proto_tree_add_item ( rr_tree , hf_dns_tkey_key_data , tvb , cur_offset , tkey_keylen , ENC_NA ) ;
 key_tree = proto_item_add_subtree ( key_item , ett_t_key ) ;
 switch ( tkey_mode ) {
 case TKEYMODE_GSSAPI : {
 tvbuff_t * gssapi_tvb ;
 gssapi_tvb = tvb_new_subset_length ( tvb , cur_offset , tkey_keylen ) ;
 if ( tvb_strneql ( gssapi_tvb , 0 , "NTLMSSP" , 7 ) == 0 ) {
 call_dissector ( ntlmssp_handle , gssapi_tvb , pinfo , key_tree ) ;
 }
 else {
 call_dissector ( gssapi_handle , gssapi_tvb , pinfo , key_tree ) ;
 }
 break ;
 }
 default : break ;
 }
 cur_offset += tkey_keylen ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_tkey_other_size , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 tkey_otherlen = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 if ( tkey_otherlen != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_tkey_other_data , tvb , cur_offset , tkey_otherlen , ENC_NA ) ;
 }
 }
 break ;
 case T_TSIG : {
 guint16 tsig_siglen , tsig_otherlen ;
 const guchar * tsig_algname ;
 int tsig_algname_len ;
 proto_item * ti ;
 tsig_algname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & tsig_algname ) ;
 proto_tree_add_string ( rr_tree , hf_dns_tsig_algorithm_name , tvb , cur_offset , tsig_algname_len , tsig_algname ) ;
 cur_offset += tsig_algname_len ;
 ti = proto_tree_add_item ( rr_tree , hf_dns_tsig_time_signed , tvb , cur_offset , 6 , ENC_NA ) ;
 if ( tvb_get_ntohs ( tvb , cur_offset ) ) {
 proto_item_append_text ( ti , " (high bits set)" ) ;
 }
 cur_offset += 6 ;
 proto_tree_add_item ( rr_tree , hf_dns_tsig_fudge , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 tsig_siglen = tvb_get_ntohs ( tvb , cur_offset ) ;
 proto_tree_add_item ( rr_tree , hf_dns_tsig_mac_size , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 if ( tsig_siglen != 0 ) {
 proto_item * mac_item ;
 proto_tree * mac_tree ;
 tvbuff_t * sub_tvb ;
 mac_item = proto_tree_add_item ( rr_tree , hf_dns_tsig_mac , tvb , cur_offset , tsig_siglen , ENC_NA ) ;
 mac_tree = proto_item_add_subtree ( mac_item , ett_dns_mac ) ;
 sub_tvb = tvb_new_subset_length ( tvb , cur_offset , tsig_siglen ) ;
 if ( ! dissector_try_string ( dns_tsig_dissector_table , tsig_algname , sub_tvb , pinfo , mac_tree , NULL ) ) {
 expert_add_info_format ( pinfo , mac_item , & ei_dns_tsig_alg , "No dissector for algorithm:%s" , tsig_algname ) ;
 }
 cur_offset += tsig_siglen ;
 }
 proto_tree_add_item ( rr_tree , hf_dns_tsig_original_id , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_tsig_error , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 cur_offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_tsig_other_len , tvb , cur_offset , 2 , ENC_BIG_ENDIAN ) ;
 tsig_otherlen = tvb_get_ntohs ( tvb , cur_offset ) ;
 cur_offset += 2 ;
 if ( tsig_otherlen != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_tsig_other_data , tvb , cur_offset , tsig_otherlen , ENC_NA ) ;
 }
 }
 break ;
 case T_CAA : {
 proto_item * caa_item ;
 proto_tree * caa_tree ;
 guint8 tag_len ;
 const char * tag ;
 gushort value_len ;
 const guchar * value ;
 int cur_hf = - 1 ;
 caa_item = proto_tree_add_item ( rr_tree , hf_dns_caa_flags , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 caa_tree = proto_item_add_subtree ( caa_item , ett_caa_flags ) ;
 proto_tree_add_item ( caa_tree , hf_dns_caa_flag_issuer_critical , tvb , cur_offset , 1 , ENC_BIG_ENDIAN ) ;
 cur_offset ++ ;
 tag_len = tvb_get_guint8 ( tvb , cur_offset ) ;
 tag = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , cur_offset + 1 , tag_len , ENC_ASCII | ENC_NA ) ;
 value_len = data_len - ( tag_len + 2 ) ;
 value = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , cur_offset + 1 + tag_len , value_len , ENC_ASCII | ENC_NA ) ;
 value = format_text ( value , value_len ) ;
 if ( strncmp ( tag , "issue" , tag_len ) == 0 ) {
 cur_hf = hf_dns_caa_issue ;
 }
 else if ( strncmp ( tag , "issuewild" , tag_len ) == 0 ) {
 cur_hf = hf_dns_caa_issuewild ;
 }
 else if ( strncmp ( tag , "iodef" , tag_len ) == 0 ) {
 cur_hf = hf_dns_caa_iodef ;
 }
 else {
 cur_hf = hf_dns_caa_unknown ;
 }
 caa_item = proto_tree_add_string ( rr_tree , cur_hf , tvb , cur_offset , 1 + tag_len + value_len , value ) ;
 caa_tree = proto_item_add_subtree ( caa_item , ett_caa_data ) ;
 proto_tree_add_uint ( caa_tree , hf_dns_caa_tag_length , tvb , cur_offset , 1 , tag_len ) ;
 proto_tree_add_string ( caa_tree , hf_dns_caa_tag , tvb , cur_offset + 1 , tag_len , tag ) ;
 proto_tree_add_string ( caa_tree , hf_dns_caa_value , tvb , cur_offset + 1 + tag_len , value_len , value ) ;
 }
 break ;
 case T_WINS : {
 int rr_len = data_len ;
 guint32 nservers ;
 proto_tree_add_item ( rr_tree , hf_dns_wins_local_flag , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_wins_lookup_timeout , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_wins_cache_timeout , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_wins_nb_wins_servers , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 nservers = tvb_get_ntohl ( tvb , cur_offset ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 while ( rr_len != 0 && nservers != 0 ) {
 proto_tree_add_item ( rr_tree , hf_dns_wins_server , tvb , cur_offset , 4 , ENC_NA ) ;
 cur_offset += 4 ;
 rr_len -= 4 ;
 nservers -- ;
 }
 }
 break ;
 case T_WINS_R : {
 const guchar * dname ;
 int dname_len ;
 proto_tree_add_item ( rr_tree , hf_dns_winsr_local_flag , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_winsr_lookup_timeout , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 proto_tree_add_item ( rr_tree , hf_dns_winsr_cache_timeout , tvb , cur_offset , 4 , ENC_BIG_ENDIAN ) ;
 cur_offset += 4 ;
 dname_len = get_dns_name ( tvb , cur_offset , 0 , dns_data_offset , & dname ) ;
 name_out = format_text ( dname , strlen ( dname ) ) ;
 proto_tree_add_string ( rr_tree , hf_dns_winsr_name_result_domain , tvb , cur_offset , dname_len , name_out ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , " %s" , name_out ) ;
 }
 proto_item_append_text ( trr , ", name result domain %s" , name_out ) ;
 }
 break ;
 default : expert_add_info_format ( pinfo , trr , & ei_dns_undecoded_option , "Dissector for DNS Type (%d)" " code not implemented, Contact Wireshark developers" " if you want this supported" , dns_type ) ;
 proto_tree_add_item ( rr_tree , hf_dns_data , tvb , cur_offset , data_len , ENC_NA ) ;
 break ;
 }
 data_offset += data_len ;
 return data_offset - data_start ;
 }