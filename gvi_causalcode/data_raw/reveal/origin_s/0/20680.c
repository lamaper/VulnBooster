void proto_register_dns ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_dns_length , {
 "Length" , "dns.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Length of DNS-over-TCP request or response" , HFILL }
 }
 , {
 & hf_dns_flags , {
 "Flags" , "dns.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_flags_response , {
 "Response" , "dns.flags.response" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_response ) , F_RESPONSE , "Is the message a response?" , HFILL }
 }
 , {
 & hf_dns_flags_opcode , {
 "Opcode" , "dns.flags.opcode" , FT_UINT16 , BASE_DEC , VALS ( opcode_vals ) , F_OPCODE , "Operation code" , HFILL }
 }
 , {
 & hf_dns_flags_authoritative , {
 "Authoritative" , "dns.flags.authoritative" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_authoritative ) , F_AUTHORITATIVE , "Is the server is an authority for the domain?" , HFILL }
 }
 , {
 & hf_dns_flags_conflict_query , {
 "Conflict" , "dns.flags.conflict" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_conflict_query ) , F_CONFLICT , "Did we receive multiple responses to a query?" , HFILL }
 }
 , {
 & hf_dns_flags_conflict_response , {
 "Conflict" , "dns.flags.conflict" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_conflict_response ) , F_CONFLICT , "Is the name considered unique?" , HFILL }
 }
 , {
 & hf_dns_flags_truncated , {
 "Truncated" , "dns.flags.truncated" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_truncated ) , F_TRUNCATED , "Is the message truncated?" , HFILL }
 }
 , {
 & hf_dns_flags_recdesired , {
 "Recursion desired" , "dns.flags.recdesired" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_recdesired ) , F_RECDESIRED , "Do query recursively?" , HFILL }
 }
 , {
 & hf_dns_flags_tentative , {
 "Tentative" , "dns.flags.tentative" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_tentative ) , F_TENTATIVE , "Is the responder authoritative for the name, but not yet verified the uniqueness?" , HFILL }
 }
 , {
 & hf_dns_flags_recavail , {
 "Recursion available" , "dns.flags.recavail" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_recavail ) , F_RECAVAIL , "Can the server do recursive queries?" , HFILL }
 }
 , {
 & hf_dns_flags_z , {
 "Z" , "dns.flags.z" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_z ) , F_Z , "Z flag" , HFILL }
 }
 , {
 & hf_dns_flags_authenticated , {
 "Answer authenticated" , "dns.flags.authenticated" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_authenticated ) , F_AUTHENTIC , "Was the reply data authenticated by the server?" , HFILL }
 }
 , {
 & hf_dns_flags_ad , {
 "AD bit" , "dns.flags.authenticated" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , F_AUTHENTIC , NULL , HFILL }
 }
 , {
 & hf_dns_flags_checkdisable , {
 "Non-authenticated data" , "dns.flags.checkdisable" , FT_BOOLEAN , 16 , TFS ( & tfs_flags_checkdisable ) , F_CHECKDISABLE , "Is non-authenticated data acceptable?" , HFILL }
 }
 , {
 & hf_dns_flags_rcode , {
 "Reply code" , "dns.flags.rcode" , FT_UINT16 , BASE_DEC , VALS ( rcode_vals ) , F_RCODE , NULL , HFILL }
 }
 , {
 & hf_dns_transaction_id , {
 "Transaction ID" , "dns.id" , FT_UINT16 , BASE_HEX , NULL , 0x0 , "Identification of transaction" , HFILL }
 }
 , {
 & hf_dns_qry_type , {
 "Type" , "dns.qry.type" , FT_UINT16 , BASE_DEC | BASE_EXT_STRING , & dns_types_description_vals_ext , 0 , "Query Type" , HFILL }
 }
 , {
 & hf_dns_qry_class , {
 "Class" , "dns.qry.class" , FT_UINT16 , BASE_HEX , VALS ( dns_classes ) , 0x0 , "Query Class" , HFILL }
 }
 , {
 & hf_dns_qry_class_mdns , {
 "Class" , "dns.qry.class" , FT_UINT16 , BASE_HEX , VALS ( dns_classes ) , 0x7FFF , "Query Class" , HFILL }
 }
 , {
 & hf_dns_qry_qu , {
 "\"QU\" question" , "dns.qry.qu" , FT_BOOLEAN , 16 , NULL , C_QU , "QU flag" , HFILL }
 }
 , {
 & hf_dns_qry_name , {
 "Name" , "dns.qry.name" , FT_STRING , BASE_NONE , NULL , 0x0 , "Query Name" , HFILL }
 }
 , {
 & hf_dns_qry_name_len , {
 "Name Length" , "dns.qry.name.len" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Query Name Len" , HFILL }
 }
 , {
 & hf_dns_count_labels , {
 "Label Count" , "dns.count.labels" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Query Label Count" , HFILL }
 }
 , {
 & hf_dns_rr_type , {
 "Type" , "dns.resp.type" , FT_UINT16 , BASE_DEC | BASE_EXT_STRING , & dns_types_description_vals_ext , 0x0 , "Response Type" , HFILL }
 }
 , {
 & hf_dns_rr_class , {
 "Class" , "dns.resp.class" , FT_UINT16 , BASE_HEX , VALS ( dns_classes ) , 0x0 , "Response Class" , HFILL }
 }
 , {
 & hf_dns_rr_class_mdns , {
 "Class" , "dns.resp.class" , FT_UINT16 , BASE_HEX , VALS ( dns_classes ) , 0x7FFF , "Response Class" , HFILL }
 }
 , {
 & hf_dns_rr_cache_flush , {
 "Cache flush" , "dns.resp.cache_flush" , FT_BOOLEAN , 16 , NULL , C_FLUSH , "Cache flush flag" , HFILL }
 }
 , {
 & hf_dns_rr_ext_rcode , {
 "Higher bits in extended RCODE" , "dns.resp.ext_rcode" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_rr_edns0_version , {
 "EDNS0 version" , "dns.resp.edns0_version" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_rr_z , {
 "Z" , "dns.resp.z" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_rr_z_do , {
 "DO bit" , "dns.resp.z.do" , FT_BOOLEAN , 16 , TFS ( & tfs_dns_rr_z_do ) , 0x8000 , "DNSSEC OK" , HFILL }
 }
 , {
 & hf_dns_rr_z_reserved , {
 "Reserved" , "dns.resp.z.reserved" , FT_UINT16 , BASE_HEX , NULL , 0x7FFF , NULL , HFILL }
 }
 , {
 & hf_dns_srv_service , {
 "Service" , "dns.srv.service" , FT_STRING , BASE_NONE , NULL , 0x0 , "Desired service" , HFILL }
 }
 , {
 & hf_dns_srv_proto , {
 "Protocol" , "dns.srv.proto" , FT_STRING , BASE_NONE , NULL , 0x0 , "Desired protocol" , HFILL }
 }
 , {
 & hf_dns_srv_name , {
 "Name" , "dns.srv.name" , FT_STRING , BASE_NONE , NULL , 0x0 , "Domain this resource record refers to" , HFILL }
 }
 , {
 & hf_dns_srv_priority , {
 "Priority" , "dns.srv.priority" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_srv_weight , {
 "Weight" , "dns.srv.weight" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_srv_port , {
 "Port" , "dns.srv.port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_srv_target , {
 "Target" , "dns.srv.target" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_order , {
 "Order" , "dns.naptr.order" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_preference , {
 "Preference" , "dns.naptr.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_flags_length , {
 "Flags Length" , "dns.naptr.flags_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_flags , {
 "Flags" , "dns.naptr.flags" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_service_length , {
 "Service Length" , "dns.naptr.service_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_service , {
 "Service" , "dns.naptr.service" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_regex_length , {
 "Regex Length" , "dns.naptr.regex_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_regex , {
 "Regex" , "dns.naptr.regex" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_replacement_length , {
 "Replacement Length" , "dns.naptr.replacement_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_naptr_replacement , {
 "Replacement" , "dns.naptr.replacement" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_rr_name , {
 "Name" , "dns.resp.name" , FT_STRING , BASE_NONE , NULL , 0x0 , "Response Name" , HFILL }
 }
 , {
 & hf_dns_rr_ttl , {
 "Time to live" , "dns.resp.ttl" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "Response TTL" , HFILL }
 }
 , {
 & hf_dns_rr_len , {
 "Data length" , "dns.resp.len" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "Response Length" , HFILL }
 }
 , {
 & hf_dns_a , {
 "Address" , "dns.a" , FT_IPv4 , BASE_NONE , NULL , 0x0 , "Response Address" , HFILL }
 }
 , {
 & hf_dns_md , {
 "Mail Destination" , "dns.md" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_mf , {
 "Mail Forwarder" , "dns.mf" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_mb , {
 "MailBox Domaine" , "dns.mb" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_mg , {
 "Mail Group member" , "dns.mg" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_mr , {
 "Mail Rename domaine" , "dns.mr" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_null , {
 "Null (data)" , "dns.null" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_aaaa , {
 "AAAA Address" , "dns.aaaa" , FT_IPv6 , BASE_NONE , NULL , 0x0 , "AAAA Response Address" , HFILL }
 }
 , {
 & hf_dns_cname , {
 "CNAME" , "dns.cname" , FT_STRING , BASE_NONE , NULL , 0x0 , "Response Primary Name" , HFILL }
 }
 , {
 & hf_dns_rr_udp_payload_size_mdns , {
 "UDP payload size" , "dns.rr.udp_payload_size" , FT_UINT16 , BASE_HEX , NULL , 0x7FFF , NULL , HFILL }
 }
 , {
 & hf_dns_rr_udp_payload_size , {
 "UDP payload size" , "dns.rr.udp_payload_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_mname , {
 "Primary name server" , "dns.soa.mname" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_rname , {
 "Responsible authority's mailbox" , "dns.soa.rname" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_serial_number , {
 "Serial Number" , "dns.soa.serial_number" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_refresh_interval , {
 "Refresh Interval" , "dns.soa.refresh_interval" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_retry_interval , {
 "Retry Interval" , "dns.soa.retry_interval" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_expire_limit , {
 "Expire limit" , "dns.soa.expire_limit" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_soa_minimum_ttl , {
 "Minimum TTL" , "dns.soa.mininum_ttl" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ptr_domain_name , {
 "Domain Name" , "dns.ptr.domain_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_wks_address , {
 "Address" , "dns.wks.address" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_wks_protocol , {
 "Protocol" , "dns.wks.protocol" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & ipproto_val_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_wks_bits , {
 "Bits" , "dns.wks.bits" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_hinfo_cpu_length , {
 "CPU Length" , "dns.hinfo.cpu_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_hinfo_cpu , {
 "CPU" , "dns.hinfo.cpu" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_hinfo_os_length , {
 "OS Length" , "dns.hinfo.os_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_hinfo_os , {
 "OS" , "dns.hinfo.os" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_minfo_r_mailbox , {
 "Responsible Mailbox" , "dns.minfo.r" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_minfo_e_mailbox , {
 "Error Mailbox" , "dns.minfo.e" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_mx_preference , {
 "Preference" , "dns.mx.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_mx_mail_exchange , {
 "Mail Exchange" , "dns.mx.mail_exchange" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_txt_length , {
 "TXT Length" , "dns.txt.length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_txt , {
 "TXT" , "dns.txt" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_openpgpkey , {
 "OpenPGP Key" , "dns.openpgpkey" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_spf_length , {
 "SPF Length" , "dns.spf.length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_spf , {
 "SPF" , "dns.spf" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_nodeid_preference , {
 "Preference" , "dns.ilnp.nid.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_nodeid , {
 "NodeID" , "dns.ilnp.nid" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_locator32_preference , {
 "Preference" , "dns.ilnp.l32.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_locator32 , {
 "Locator32" , "dns.ilnp.l32" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_locator64_preference , {
 "Preference" , "dns.ilnp.l64.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_locator64 , {
 "Locator64" , "dns.ilnp.l64" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_locatorfqdn_preference , {
 "Preference" , "dns.ilnp.lp.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ilnp_locatorfqdn , {
 "Locator FQDN" , "dns.ilnp.lp" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_eui48 , {
 "EUI48 Address" , "dns.eui48" , FT_ETHER , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_eui64 , {
 "EUI64 Address" , "dns.eui64" , FT_EUI64 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_rrsig_type_covered , {
 "Type Covered" , "dns.rrsig.type_covered" , FT_UINT16 , BASE_DEC | BASE_EXT_STRING , & dns_types_description_vals_ext , 0x0 , "Identifies the type of the RRset that is covered by this RRSIG record" , HFILL }
 }
 , {
 & hf_dns_rrsig_algorithm , {
 "Algorithm" , "dns.rrsig.algorithm" , FT_UINT8 , BASE_DEC , VALS ( dnssec_algo_vals ) , 0x0 , "Identifies the cryptographic algorithm used to create the signature" , HFILL }
 }
 , {
 & hf_dns_rrsig_labels , {
 "Labels" , "dns.rrsig.labels" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Specifies the number of labels in the original RRSIG RR owner name" , HFILL }
 }
 , {
 & hf_dns_rrsig_original_ttl , {
 "Original TTL" , "dns.rrsig.original_ttl" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "Specifies the TTL of the covered RRset as it appears in the authoritative zone" , HFILL }
 }
 , {
 & hf_dns_rrsig_signature_expiration , {
 "Signature Expiration" , "dns.rrsig.signature_expiration" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , "Specify a validity period for the signature" , HFILL }
 }
 , {
 & hf_dns_rrsig_signature_inception , {
 "Signature Inception" , "dns.rrsig.signature_inception" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , "Specify a validity period for the signature" , HFILL }
 }
 , {
 & hf_dns_rrsig_key_tag , {
 "Key Tag" , "dns.rrsig.key_tag" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Contains the key tag value of the DNSKEY RR that validates this signature" , HFILL }
 }
 , {
 & hf_dns_rrsig_signers_name , {
 "Signer's name" , "dns.rrsig.signers_name" , FT_STRING , BASE_NONE , NULL , 0x0 , "Identifies the owner name of the DNSKEY RR that a validator is supposed to use to validate this signature" , HFILL }
 }
 , {
 & hf_dns_rrsig_signature , {
 "Signature" , "dns.rrsig.signature" , FT_BYTES , BASE_NONE , NULL , 0x0 , "Contains the cryptographic signature that covers the RRSIG RDATA" , HFILL }
 }
 , {
 & hf_dns_dnskey_flags , {
 "Flags" , "dns.dnskey.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_dnskey_flags_zone_key , {
 "Zone Key" , "dns.dnskey.flags.zone_key" , FT_BOOLEAN , 16 , TFS ( & dns_dnskey_zone_key_tfs ) , DNSKEY_FLAGS_ZK , NULL , HFILL }
 }
 , {
 & hf_dns_dnskey_flags_key_revoked , {
 "Key Revoked" , "dns.dnskey.flags.key_revoked" , FT_BOOLEAN , 16 , TFS ( & tfs_yes_no ) , DNSKEY_FLAGS_KR , NULL , HFILL }
 }
 , {
 & hf_dns_dnskey_flags_secure_entry_point , {
 "Key Signing Key" , "dns.dnskey.flags.secure_entry_point" , FT_BOOLEAN , 16 , TFS ( & tfs_yes_no ) , DNSKEY_FLAGS_SEP , NULL , HFILL }
 }
 , {
 & hf_dns_dnskey_flags_reserved , {
 "Key Signing Key" , "dns.dnskey.flags.reserved" , FT_UINT16 , BASE_HEX , NULL , DNSKEY_FLAGS_RSV , "Must be zero" , HFILL }
 }
 , {
 & hf_dns_dnskey_protocol , {
 "Protocol" , "dns.dnskey.protocol" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Must be 3" , HFILL }
 }
 , {
 & hf_dns_dnskey_algorithm , {
 "Algorithm" , "dns.dnskey.algorithm" , FT_UINT8 , BASE_DEC , VALS ( dnssec_algo_vals ) , 0x0 , "Identifies the public key's cryptographic algorithm and determines the format of the Public Key field" , HFILL }
 }
 , {
 & hf_dns_dnskey_key_id , {
 "Key id" , "dns.dnskey.key_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_dnskey_public_key , {
 "Public Key" , "dns.dnskey.public_key" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags , {
 "Flags" , "dns.key.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_authentication , {
 "Key allowed for authentication" , "dns.key.flags.authentication" , FT_BOOLEAN , 16 , TFS ( & tfs_not_allowed_allowed ) , 0x8000 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_confidentiality , {
 "Key allowed for confidentiality" , "dns.key.flags.confidentiality" , FT_BOOLEAN , 16 , TFS ( & tfs_not_allowed_allowed ) , 0x4000 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_key_required , {
 "Key required" , "dns.key.flags.required" , FT_BOOLEAN , 16 , TFS ( & tfs_required_experimental ) , 0x2000 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_associated_user , {
 "Key is associated with a user" , "dns.key.flags.associated_user" , FT_BOOLEAN , 16 , TFS ( & tfs_yes_no ) , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_associated_named_entity , {
 "Key is associated with the named entity" , "dns.key.flags.associated_named_entity" , FT_BOOLEAN , 16 , TFS ( & tfs_yes_no ) , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_ipsec , {
 "Key use with IPSEC" , "dns.key.flags.ipsec" , FT_BOOLEAN , 16 , TFS ( & tfs_valid_invalid ) , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_mime , {
 "Key use with MIME security multiparts" , "dns.key.flags.mime" , FT_BOOLEAN , 16 , TFS ( & tfs_valid_invalid ) , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_dns_key_flags_signatory , {
 "Signatory" , "dns.key.flags.signatory" , FT_UINT16 , BASE_DEC , NULL , 0x000F , NULL , HFILL }
 }
 , {
 & hf_dns_key_protocol , {
 "Protocol" , "dns.key.protocol" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_key_algorithm , {
 "Algorithm" , "dns.key.algorithm" , FT_UINT8 , BASE_DEC , VALS ( dnssec_algo_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_key_key_id , {
 "Key ID" , "dns.key.key_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_key_public_key , {
 "Public Key" , "dns.key.public_key" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_px_preference , {
 "Preference" , "dns.px.preference" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_px_map822 , {
 "MAP822" , "dns.px.map822" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_px_mapx400 , {
 "MAPX400" , "dns.px.map400" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_algo_name , {
 "Algorithm name" , "dns.tkey.algo_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_signature_expiration , {
 "Signature Expiration" , "dns.tkey.signature_expiration" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , "Specify a validity period for the signature" , HFILL }
 }
 , {
 & hf_dns_tkey_signature_inception , {
 "Signature Inception" , "dns.tkey.signature_inception" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , "Specify a validity period for the signature" , HFILL }
 }
 , {
 & hf_dns_tkey_mode , {
 "Mode" , "dns.tkey.mode" , FT_UINT16 , BASE_DEC , VALS ( tkey_mode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_error , {
 "Error" , "dns.tkey.error" , FT_UINT16 , BASE_DEC , VALS ( rcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_key_size , {
 "Key Size" , "dns.tkey.key_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_key_data , {
 "Key Data" , "dns.tkey.key_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_other_size , {
 "Other Size" , "dns.tkey.other_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tkey_other_data , {
 "Other Data" , "dns.tkey.other_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_gateway_precedence , {
 "Gateway Precedence" , "dns.ipseckey.gateway_precedence" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_gateway_algorithm , {
 "Gateway Algorithm" , "dns.ipseckey.gateway_algorithm" , FT_UINT8 , BASE_DEC , VALS ( gw_algo_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_gateway_type , {
 "Gateway Type" , "dns.ipseckey.gateway_type" , FT_UINT8 , BASE_DEC , VALS ( gw_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_gateway_ipv4 , {
 "IPv4 Gateway" , "dns.ipseckey.gateway_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_gateway_ipv6 , {
 "IPv6 Gateway" , "dns.ipseckey.gateway_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_gateway_dns , {
 "DNS Gateway" , "dns.ipseckey.gateway_dns" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ipseckey_public_key , {
 "Public Key" , "dns.ipseckey.public_key" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_a6_prefix_len , {
 "Prefix len" , "dns.a6.prefix_len" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_a6_address_suffix , {
 "Address Suffix" , "dns.a6.address_suffix" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_a6_prefix_name , {
 "Prefix name" , "dns.a6.prefix_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_dname , {
 "Dname" , "dns.dname" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_version , {
 "Version" , "dns.loc.version" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_size , {
 "Size" , "dns.loc.size" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_horizontal_precision , {
 "Horizontal Precision" , "dns.loc.horizontal_precision" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_vertical_precision , {
 "Vertial Precision" , "dns.loc.vertial_precision" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_latitude , {
 "Latitude" , "dns.loc.latitude" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_longitude , {
 "Longitude" , "dns.loc.longitude" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_altitude , {
 "Altitude" , "dns.loc.altitude" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_loc_unknown_data , {
 "Unknown data" , "dns.loc.unknown_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_nxt_next_domain_name , {
 "Next Domain Name" , "dns.nxt.next_domain_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_kx_preference , {
 "Preference" , "dns.kx.preference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_kx_key_exchange , {
 "Key Exchange" , "dns.kx.key_exchange" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_cert_type , {
 "Type" , "dns.cert.type" , FT_UINT16 , BASE_DEC , VALS ( dns_cert_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_cert_key_tag , {
 "Key Tag" , "dns.cert.key_tag" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_cert_algorithm , {
 "Algorithm" , "dns.cert.algorithm" , FT_UINT8 , BASE_DEC , VALS ( dnssec_algo_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_cert_certificate , {
 "Certificate (or CRL)" , "dns.cert.certificate" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_nsec_next_domain_name , {
 "Next Domain Name" , "dns.nsec.next_domain_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_ns , {
 "Name Server" , "dns.ns" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt , {
 "Option" , "dns.opt" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_code , {
 "Option Code" , "dns.opt.code" , FT_UINT16 , BASE_DEC , VALS ( edns0_opt_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_len , {
 "Option Length" , "dns.opt.len" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_data , {
 "Option Data" , "dns.opt.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_dau , {
 "DAU" , "dns.opt.dau" , FT_UINT8 , BASE_DEC , VALS ( dnssec_algo_vals ) , 0x0 , "DNSSEC Algorithm Understood" , HFILL }
 }
 , {
 & hf_dns_opt_dhu , {
 "DHU" , "dns.opt.dhu" , FT_UINT8 , BASE_DEC , VALS ( dns_ds_digest_vals ) , 0x0 , "DS Hash Understood" , HFILL }
 }
 , {
 & hf_dns_opt_n3u , {
 "N3U" , "dns.opt.n3u" , FT_UINT8 , BASE_DEC , VALS ( hash_algorithms ) , 0x0 , "NSEC3 Hash Understood" , HFILL }
 }
 , {
 & hf_dns_opt_client_family , {
 "Family" , "dns.opt.client.family" , FT_UINT16 , BASE_DEC , VALS ( afamily_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_client_netmask , {
 "Source Netmask" , "dns.opt.client.netmask" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_client_scope , {
 "Scope Netmask" , "dns.opt.client.scope" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_client_addr , {
 "Client Subnet" , "dns.opt.client.addr" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_client_addr4 , {
 "Client Subnet" , "dns.opt.client.addr4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_opt_client_addr6 , {
 "Client Subnet" , "dns.opt.client.addr6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_count_questions , {
 "Questions" , "dns.count.queries" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of queries in packet" , HFILL }
 }
 , {
 & hf_dns_count_zones , {
 "Zones" , "dns.count.zones" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of zones in packet" , HFILL }
 }
 , {
 & hf_dns_count_answers , {
 "Answer RRs" , "dns.count.answers" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of answers in packet" , HFILL }
 }
 , {
 & hf_dns_count_prerequisites , {
 "Prerequisites" , "dns.count.prerequisites" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of prerequisites in packet" , HFILL }
 }
 , {
 & hf_dns_count_auth_rr , {
 "Authority RRs" , "dns.count.auth_rr" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of authoritative records in packet" , HFILL }
 }
 , {
 & hf_dns_count_updates , {
 "Updates" , "dns.count.updates" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of updates records in packet" , HFILL }
 }
 , {
 & hf_dns_nsec3_algo , {
 "Hash algorithm" , "dns.nsec3.algo" , FT_UINT8 , BASE_DEC , VALS ( hash_algorithms ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_nsec3_flags , {
 "NSEC3 flags" , "dns.nsec3.flags" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_nsec3_flag_optout , {
 "NSEC3 Opt-out flag" , "dns.nsec3.flags.opt_out" , FT_BOOLEAN , 8 , TFS ( & tfs_flags_nsec3_optout ) , NSEC3_FLAG_OPTOUT , NULL , HFILL }
 }
 , {
 & hf_dns_nsec3_iterations , {
 "NSEC3 iterations" , "dns.nsec3.iterations" , FT_UINT16 , BASE_DEC , NULL , 0 , "Number of hashing iterations" , HFILL }
 }
 , {
 & hf_dns_nsec3_salt_length , {
 "Salt length" , "dns.nsec3.salt_length" , FT_UINT8 , BASE_DEC , NULL , 0 , "Length of salt in bytes" , HFILL }
 }
 , {
 & hf_dns_nsec3_salt_value , {
 "Salt value" , "dns.nsec3.salt_value" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_nsec3_hash_length , {
 "Hash length" , "dns.nsec3.hash_length" , FT_UINT8 , BASE_DEC , NULL , 0 , "Length in bytes of next hashed owner" , HFILL }
 }
 , {
 & hf_dns_nsec3_hash_value , {
 "Next hashed owner" , "dns.nsec3.hash_value" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_tlsa_certificate_usage , {
 "Certificate Usage" , "dns.tlsa.certificate_usage" , FT_UINT8 , BASE_DEC , VALS ( tlsa_certificate_usage_vals ) , 0 , "Specifies the provided association that will be used to match the certificate presented in the TLS handshake" , HFILL }
 }
 , {
 & hf_dns_tlsa_selector , {
 "Selector" , "dns.tlsa.selector" , FT_UINT8 , BASE_DEC , VALS ( tlsa_selector_vals ) , 0 , "Specifies which part of the TLS certificate presented by the server will be matched against the association data" , HFILL }
 }
 , {
 & hf_dns_tlsa_matching_type , {
 "Matching Type" , "dns.tlsa.matching_type" , FT_UINT8 , BASE_DEC , VALS ( tlsa_matching_type_vals ) , 0 , "Specifies how the certificate association is presented" , HFILL }
 }
 , {
 & hf_dns_tlsa_certificate_association_data , {
 "Certificate Association Data" , "dns.tlsa.certificate_association_data" , FT_BYTES , BASE_NONE , NULL , 0 , "The data refers to the certificate in the association" , HFILL }
 }
 , {
 & hf_dns_tsig_algorithm_name , {
 "Algorithm Name" , "dns.tsig.algorithm_name" , FT_STRING , BASE_NONE , NULL , 0x0 , "Name of algorithm used for the MAC" , HFILL }
 }
 , {
 & hf_dns_tsig_time_signed , {
 "Time Signed" , "dns.tsig.time_signed" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tsig_original_id , {
 "Original Id" , "dns.tsig.original_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tsig_error , {
 "Error" , "dns.tsig.error" , FT_UINT16 , BASE_DEC , VALS ( rcode_vals ) , 0x0 , "Expanded RCODE for TSIG" , HFILL }
 }
 , {
 & hf_dns_tsig_fudge , {
 "Fudge" , "dns.tsig.fudge" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of bytes for the MAC" , HFILL }
 }
 , {
 & hf_dns_tsig_mac_size , {
 "MAC Size" , "dns.tsig.mac_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of bytes for the MAC" , HFILL }
 }
 , {
 & hf_dns_tsig_other_len , {
 "Other Len" , "dns.tsig.other_len" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of bytes for Other Data" , HFILL }
 }
 , {
 & hf_dns_tsig_mac , {
 "MAC" , "dns.tsig.mac" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_tsig_other_data , {
 "Other Data" , "dns.tsig.other_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_response_in , {
 "Response In" , "dns.response_in" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "The response to this DNS query is in this frame" , HFILL }
 }
 , {
 & hf_dns_response_to , {
 "Request In" , "dns.response_to" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "This is a response to the DNS query in this frame" , HFILL }
 }
 , {
 & hf_dns_time , {
 "Time" , "dns.time" , FT_RELATIVE_TIME , BASE_NONE , NULL , 0x0 , "The time between the Query and the Response" , HFILL }
 }
 , {
 & hf_dns_count_add_rr , {
 "Additional RRs" , "dns.count.add_rr" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Number of additional records in packet" , HFILL }
 }
 , {
 & hf_dns_sshfp_algorithm , {
 "Algorithm" , "dns.sshfp.algorithm" , FT_UINT8 , BASE_DEC , VALS ( sshfp_algo_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_sshfp_fingerprint_type , {
 "Fingerprint type" , "dns.sshfp.fingerprint.type" , FT_UINT8 , BASE_DEC , VALS ( sshfp_fingertype_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_sshfp_fingerprint , {
 "Fingerprint" , "dns.sshfp.fingerprint" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_hip_hit_length , {
 "HIT length" , "dns.hip.hit.length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_hip_pk_algo , {
 "HIT length" , "dns.hip.hit.pk.algo" , FT_UINT8 , BASE_DEC , VALS ( hip_algo_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_hip_pk_length , {
 "PK length" , "dns.hip.pk.length" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_hip_hit , {
 "Host Identity Tag" , "dns.hip.hit" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_hip_pk , {
 "HIP Public Key" , "dns.hip.pk" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_hip_rendezvous_server , {
 "Rendezvous Server" , "dns.hip.rendezvous_server" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_dhcid_rdata , {
 "DHCID Data" , "dns.dhcid.rdata" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_ds_key_id , {
 "Key id" , "dns.ds.key_id" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_ds_algorithm , {
 "Algorithm" , "dns.ds.algorithm" , FT_UINT8 , BASE_DEC , VALS ( dnssec_algo_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_ds_digest_type , {
 "Digest Type" , "dns.ds.digest_type" , FT_UINT8 , BASE_DEC , VALS ( dns_ds_digest_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_ds_digest , {
 "Digest" , "dns.ds.digest" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_apl_address_family , {
 "Address Family" , "dns.apl.address_family" , FT_UINT16 , BASE_DEC , VALS ( afamily_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_apl_coded_prefix , {
 "Prefix Length" , "dns.apl.coded_prefix" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_apl_negation , {
 "Negation Flag" , "dns.apl.negation" , FT_BOOLEAN , 8 , TFS ( & tfs_dns_apl_negation ) , DNS_APL_NEGATION , NULL , HFILL }
 }
 , {
 & hf_dns_apl_afdlength , {
 "Address Length" , "dns.apl.afdlength" , FT_UINT8 , BASE_DEC , NULL , DNS_APL_AFDLENGTH , "in octets" , HFILL }
 }
 , {
 & hf_dns_apl_afdpart_ipv4 , {
 "Address" , "dns.apl.afdpart.ipv4" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_apl_afdpart_ipv6 , {
 "Address" , "dns.apl.afdpart.ipv6" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_apl_afdpart_data , {
 "Address" , "dns.apl.afdpart.data" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_gpos_longitude_length , {
 "Longitude length" , "dns.gpos.longitude_length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_gpos_longitude , {
 "Longitude" , "dns.gpos.longitude" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_gpos_latitude_length , {
 "Latitude length" , "dns.gpos.latitude_length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_gpos_latitude , {
 "Latitude" , "dns.gpos.latitude" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_gpos_altitude_length , {
 "Altitude length" , "dns.gpos.altitude_length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_gpos_altitude , {
 "Altitude" , "dns.gpos.altitude" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_rp_mailbox , {
 "Mailbox" , "dns.rp.mailbox" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_rp_txt_rr , {
 "TXT RR" , "dns.rp.txt_rr" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_afsdb_subtype , {
 "Subtype" , "dns.afsdb.subtype" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_afsdb_hostname , {
 "Hostname" , "dns.afsdb.hostname" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_x25_length , {
 "Length" , "dns.x25.length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_x25_psdn_address , {
 "PSDN-Address" , "dns.x25.psdn_address" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_isdn_length , {
 "Length" , "dns.idsn.length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_isdn_address , {
 "ISDN Address" , "dns.idsn.address" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_isdn_sa_length , {
 "Length" , "dns.idsn.sa.length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_isdn_sa , {
 "Sub Address" , "dns.idsn.sa.address" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_rt_preference , {
 "Preference" , "dns.rt.subtype" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_rt_intermediate_host , {
 "Intermediate Hostname" , "dns.rt.intermediate_host" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_nsap_rdata , {
 "NSAP Data" , "dns.nsap.rdata" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_nsap_ptr_owner , {
 "Owner" , "dns.nsap_ptr.owner" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_caa_flags , {
 "CAA Flags" , "dns.caa.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_caa_flag_issuer_critical , {
 "Issuer Critical" , "dns.caa.flags.issuer_critical" , FT_BOOLEAN , 8 , TFS ( & tfs_critical_not_critical ) , CAA_FLAG_ISSUER_CRITICAL , "Other CAs must not issue certificates" , HFILL }
 }
 , {
 & hf_dns_caa_issue , {
 "Issue" , "dns.caa.issue" , FT_STRING , BASE_NONE , NULL , 0x0 , "CA which is allowed to issue certificates" , HFILL }
 }
 , {
 & hf_dns_caa_issuewild , {
 "Issue Wildcard" , "dns.caa.issuewild" , FT_STRING , BASE_NONE , NULL , 0x0 , "CA which is allowed to issue wildcard certificates" , HFILL }
 }
 , {
 & hf_dns_caa_iodef , {
 "Report URL" , "dns.caa.iodef" , FT_STRING , BASE_NONE , NULL , 0x0 , "URL or email address for certificate issue requests and violation reports" , HFILL }
 }
 , {
 & hf_dns_caa_unknown , {
 "Unkown tag" , "dns.caa.unknown" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_caa_tag_length , {
 "Tag length" , "dns.caa.tag_length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_dns_caa_tag , {
 "Tag" , "dns.caa.tag" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_caa_value , {
 "Value" , "dns.caa.value" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_wins_local_flag , {
 "Local Flag" , "dns.wins.local_flag" , FT_BOOLEAN , 32 , TFS ( & tfs_true_false ) , 0x1 , NULL , HFILL }
 }
 , {
 & hf_dns_wins_lookup_timeout , {
 "Lookup timeout" , "dns.wins.lookup_timeout" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "In seconds" , HFILL }
 }
 , {
 & hf_dns_wins_cache_timeout , {
 "Cache timeout" , "dns.wins.cache_timeout" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "In seconds" , HFILL }
 }
 , {
 & hf_dns_wins_nb_wins_servers , {
 "Number of WINS servers" , "dns.wins.nb_wins_servers" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_wins_server , {
 "WINS Server Address" , "dns.wins.wins_server" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_winsr_local_flag , {
 "Local Flag" , "dns.winsr.local_flag" , FT_BOOLEAN , 32 , TFS ( & tfs_true_false ) , 0x1 , NULL , HFILL }
 }
 , {
 & hf_dns_winsr_lookup_timeout , {
 "Lookup timeout" , "dns.winsr.lookup_timeout" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "In seconds" , HFILL }
 }
 , {
 & hf_dns_winsr_cache_timeout , {
 "Cache timeout" , "dns.winsr.cache_timeout" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "In seconds" , HFILL }
 }
 , {
 & hf_dns_winsr_name_result_domain , {
 "Name Result Domain" , "dns.winsr.name_result_domain" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_dns_data , {
 "Data" , "dns.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_dns_opt_bad_length , {
 "dns.rr.opt.bad_length" , PI_MALFORMED , PI_ERROR , "Length too long for any type of IP address." , EXPFILL }
 }
 , {
 & ei_dns_undecoded_option , {
 "dns.undecoded.type" , PI_UNDECODED , PI_NOTE , "Undecoded option" , EXPFILL }
 }
 , {
 & ei_dns_depr_opc , {
 "dns.depr.opc" , PI_PROTOCOL , PI_WARN , "Deprecated opcode" , EXPFILL }
 }
 , {
 & ei_ttl_negative , {
 "dns.ttl.negative" , PI_PROTOCOL , PI_WARN , "TTL can't be negative" , EXPFILL }
 }
 , {
 & ei_dns_tsig_alg , {
 "dns.tsig.noalg" , PI_UNDECODED , PI_WARN , "No dissector for algorithm" , EXPFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_dns , & ett_dns_qd , & ett_dns_rr , & ett_dns_qry , & ett_dns_ans , & ett_dns_flags , & ett_dns_opts , & ett_nsec3_flags , & ett_key_flags , & ett_t_key , & ett_dns_mac , & ett_caa_flags , & ett_caa_data , }
 ;
 module_t * dns_module ;
 expert_module_t * expert_dns ;
 proto_dns = proto_register_protocol ( "Domain Name Service" , "DNS" , "dns" ) ;
 proto_register_field_array ( proto_dns , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_dns = expert_register_protocol ( proto_dns ) ;
 expert_register_field_array ( expert_dns , ei , array_length ( ei ) ) ;
 range_convert_str ( & global_dns_tcp_port_range , DEFAULT_DNS_PORT_RANGE , MAX_TCP_PORT ) ;
 range_convert_str ( & global_dns_udp_port_range , DEFAULT_DNS_PORT_RANGE , MAX_UDP_PORT ) ;
 dns_module = prefs_register_protocol ( proto_dns , proto_reg_handoff_dns ) ;
 prefs_register_range_preference ( dns_module , "tcp.ports" , "DNS TCP ports" , "TCP ports to be decoded as DNS (default: " DEFAULT_DNS_PORT_RANGE ")" , & global_dns_tcp_port_range , MAX_TCP_PORT ) ;
 prefs_register_range_preference ( dns_module , "udp.ports" , "DNS UDP ports" , "UDP ports to be decoded as DNS (default: " DEFAULT_DNS_PORT_RANGE ")" , & global_dns_udp_port_range , MAX_UDP_PORT ) ;
 prefs_register_bool_preference ( dns_module , "desegment_dns_messages" , "Reassemble DNS messages spanning multiple TCP segments" , "Whether the DNS dissector should reassemble messages spanning multiple TCP segments." " To use this option, you must also enable \"Allow subdissectors to reassemble TCP streams\" in the TCP protocol settings." , & dns_desegment ) ;
 prefs_register_bool_preference ( dns_module , "use_for_addr_resolution" , "Use DNS packet data for address resolution" , "Whether addressame pairs found in dissected DNS packets should be used by Wireshark for name resolution." , & dns_use_for_addr_resolution ) ;
 dns_tsig_dissector_table = register_dissector_table ( "dns.tsig.mac" , "DNS TSIG MAC Dissectors" , FT_STRING , BASE_NONE ) ;
 dns_tap = register_tap ( "dns" ) ;
 }