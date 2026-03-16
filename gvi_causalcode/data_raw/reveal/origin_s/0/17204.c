void proto_register_rsvp ( void ) {
 gint i ;
 static hf_register_info rsvpf_info [ ] = {
 {
 & hf_rsvp_filter [ RSVPF_MSG ] , {
 "Message Type" , "rsvp.msg" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & message_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_PATH ] , {
 "Path Message" , "rsvp.path" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RESV ] , {
 "Resv Message" , "rsvp.resv" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_PATHERR ] , {
 "Path Error Message" , "rsvp.perr" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RESVERR ] , {
 "Resv Error Message" , "rsvp.rerr" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_PATHTEAR ] , {
 "Path Tear Message" , "rsvp.ptear" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RESVTEAR ] , {
 "Resv Tear Message" , "rsvp.rtear" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RCONFIRM ] , {
 "Resv Confirm Message" , "rsvp.resvconf" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RTEARCONFIRM ] , {
 "Resv Tear Confirm Message" , "rsvp.rtearconf" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_BUNDLE ] , {
 "Bundle Message" , "rsvp.bundle" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ACK ] , {
 "Ack Message" , "rsvp.ack" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SREFRESH ] , {
 "Srefresh Message" , "rsvp.srefresh" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_HELLO ] , {
 "HELLO Message" , "rsvp.hello" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_OBJECT ] , {
 "Object class" , "rsvp.object" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsvp_class_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ctype , {
 "C-type" , "rsvp.ctype" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_parameter , {
 "Parameter" , "rsvp.parameter" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & svc_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_parameter_flags , {
 "Parameter flags" , "rsvp.parameter_flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_parameter_length , {
 "Parameter length" , "rsvp.parameter_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_value , {
 "Error value" , "rsvp.error_value" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_class , {
 "Class" , "rsvp.class" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_class_length , {
 "Length" , "rsvp.class_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_switching_granularity , {
 "Switching granularity" , "rsvp.switching_granularity" , FT_UINT16 , BASE_DEC , VALS ( rsvp_switching_granularity_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_NOTIFY ] , {
 "Notify Message" , "rsvp.notify" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION ] , {
 "SESSION" , "rsvp.session" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_HOP ] , {
 "HOP" , "rsvp.hop" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_HELLO_OBJ ] , {
 "HELLO Request/Ack" , "rsvp.hello_obj" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_INTEGRITY ] , {
 "INTEGRITY" , "rsvp.integrity" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_TIME_VALUES ] , {
 "TIME VALUES" , "rsvp.time" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ERROR ] , {
 "ERROR" , "rsvp.error" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SCOPE ] , {
 "SCOPE" , "rsvp.scope" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_STYLE ] , {
 "STYLE" , "rsvp.style" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_FLOWSPEC ] , {
 "FLOWSPEC" , "rsvp.flowspec" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_FILTER_SPEC ] , {
 "FILTERSPEC" , "rsvp.filter" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SENDER ] , {
 "SENDER TEMPLATE" , "rsvp.sender" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_TSPEC ] , {
 "SENDER TSPEC" , "rsvp.tspec" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADSPEC ] , {
 "ADSPEC" , "rsvp.adspec" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_POLICY ] , {
 "POLICY" , "rsvp.policy" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_CONFIRM ] , {
 "CONFIRM" , "rsvp.confirm" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_LABEL ] , {
 "LABEL" , "rsvp.label" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RECOVERY_LABEL ] , {
 "RECOVERY LABEL" , "rsvp.recovery_label" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_UPSTREAM_LABEL ] , {
 "UPSTREAM LABEL" , "rsvp.upstream_label" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SUGGESTED_LABEL ] , {
 "SUGGESTED LABEL" , "rsvp.suggested_label" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_LABEL_SET ] , {
 "LABEL SET" , "rsvp.label_set" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ACCEPTABLE_LABEL_SET ] , {
 "ACCEPTABLE LABEL SET" , "rsvp.acceptable_label_set" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_PROTECTION ] , {
 "PROTECTION" , "rsvp.protection" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV ] , {
 "DIFFSERV" , "rsvp.diffserv" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DSTE ] , {
 "CLASSTYPE" , "rsvp.dste" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RESTART_CAP ] , {
 "RESTART CAPABILITY" , "rsvp.restart" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_LINK_CAP ] , {
 "LINK CAPABILITY" , "rsvp.link" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_LABEL_REQUEST ] , {
 "LABEL REQUEST" , "rsvp.label_request" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_ATTRIBUTE ] , {
 "SESSION ATTRIBUTE" , "rsvp.session_attribute" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_EXPLICIT_ROUTE ] , {
 "EXPLICIT ROUTE" , "rsvp.explicit_route" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_RECORD_ROUTE ] , {
 "RECORD ROUTE" , "rsvp.record_route" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_MESSAGE_ID ] , {
 "MESSAGE-ID" , "rsvp.msgid" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_MESSAGE_ID_ACK ] , {
 "MESSAGE-ID ACK" , "rsvp.msgid_ack" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_MESSAGE_ID_LIST ] , {
 "MESSAGE-ID LIST" , "rsvp.msgid_list" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DCLASS ] , {
 "DCLASS" , "rsvp.dclass" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_LSP_TUNNEL_IF_ID ] , {
 "LSP INTERFACE-ID" , "rsvp.lsp_tunnel_if_id" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS ] , {
 "ADMIN STATUS" , "rsvp.admin_status" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_REFLECT ] , {
 "Reflect" , "rsvp.admin_status.reflect" , FT_BOOLEAN , 32 , NULL , 0x80000000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_HANDOVER ] , {
 "Handover" , "rsvp.admin_status.handover" , FT_BOOLEAN , 32 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_LOCKOUT ] , {
 "Lockout" , "rsvp.admin_status.lockout" , FT_BOOLEAN , 32 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_INHIBIT ] , {
 "Inhibit Alarm Communication" , "rsvp.admin_status.inhibit" , FT_BOOLEAN , 32 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_CALL_MGMT ] , {
 "Call Management" , "rsvp.admin_status.callmgmt" , FT_BOOLEAN , 32 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_TESTING ] , {
 "Testing" , "rsvp.admin_status.testing" , FT_BOOLEAN , 32 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_DOWN ] , {
 "Administratively down" , "rsvp.admin_status.down" , FT_BOOLEAN , 32 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ADMIN_STATUS_DELETE ] , {
 "Delete in progress" , "rsvp.admin_status.delete" , FT_BOOLEAN , 32 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_LSP_ATTRIBUTES ] , {
 "LSP ATTRIBUTES" , "rsvp.lsp_attributes" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ASSOCIATION ] , {
 "ASSOCIATION" , "rsvp.association" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_CALL_ATTRIBUTES ] , {
 "CALL ATTRIBUTES" , "rsvp.call_attributes" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_NOTIFY_REQUEST ] , {
 "NOTIFY REQUEST" , "rsvp.notify_request" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_GENERALIZED_UNI ] , {
 "GENERALIZED UNI" , "rsvp.generalized_uni" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_CALL_ID ] , {
 "CALL ID" , "rsvp.call_id" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_3GPP2_OBJECT ] , {
 "3GPP2 OBJECT" , "rsvp.3gpp2_object" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_PRIVATE_OBJ ] , {
 "Private object" , "rsvp.obj_private" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_UNKNOWN_OBJ ] , {
 "Unknown object" , "rsvp.obj_unknown" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_IP ] , {
 "Destination address" , "rsvp.session.ip" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_SHORT_CALL_ID ] , {
 "Short Call ID" , "rsvp.session.short_call_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_PORT ] , {
 "Port number" , "rsvp.session.port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_PROTO ] , {
 "Protocol" , "rsvp.session.proto" , FT_UINT8 , BASE_DEC , VALS ( proto_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_TUNNEL_ID ] , {
 "Tunnel ID" , "rsvp.session.tunnel_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_EXT_TUNNEL_ID ] , {
 "Extended tunnel ID" , "rsvp.session.ext_tunnel_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SESSION_EXT_TUNNEL_ID_IPV6 ] , {
 "Extended tunnel ID" , "rsvp.session.ext_tunnel_id_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_JUNIPER ] , {
 "Juniper" , "rsvp.juniper" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SENDER_IP ] , {
 "Sender IPv4 address" , "rsvp.sender.ip" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SENDER_PORT ] , {
 "Sender port number" , "rsvp.sender.port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SENDER_LSP_ID ] , {
 "Sender LSP ID" , "rsvp.sender.lsp_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_SENDER_SHORT_CALL_ID ] , {
 "Short Call ID" , "rsvp.sender.short_call_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_MAPNB ] , {
 "MAPnb" , "rsvp.diffserv.mapnb" , FT_UINT8 , BASE_DEC , NULL , 0x0 , MAPNB_DESCRIPTION , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_MAP ] , {
 "MAP" , "rsvp.diffserv.map" , FT_NONE , BASE_NONE , NULL , 0x0 , MAP_DESCRIPTION , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_MAP_EXP ] , {
 "EXP" , "rsvp.diffserv.map.exp" , FT_UINT8 , BASE_DEC , NULL , 0x0 , EXP_DESCRIPTION , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID ] , {
 PHBID_DESCRIPTION , "rsvp.diffserv.phbid" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_DSCP ] , {
 PHBID_DSCP_DESCRIPTION , "rsvp.diffserv.phbid.dscp" , FT_UINT16 , BASE_DEC , NULL , PHBID_DSCP_MASK , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_CODE ] , {
 PHBID_CODE_DESCRIPTION , "rsvp.diffserv.phbid.code" , FT_UINT16 , BASE_DEC , NULL , PHBID_CODE_MASK , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_BIT14 ] , {
 PHBID_BIT14_DESCRIPTION , "rsvp.diffserv.phbid.bit14" , FT_UINT16 , BASE_DEC , VALS ( phbid_bit14_vals ) , PHBID_BIT14_MASK , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_BIT15 ] , {
 PHBID_BIT15_DESCRIPTION , "rsvp.diffserv.phbid.bit15" , FT_UINT16 , BASE_DEC , VALS ( phbid_bit15_vals ) , PHBID_BIT15_MASK , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_DSTE_CLASSTYPE ] , {
 "CT" , "rsvp.dste.classtype" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_GUNI_SRC_IPV4 ] , {
 "Source TNA" , "rsvp.guni.srctna.ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_GUNI_DST_IPV4 ] , {
 "Destination TNA" , "rsvp.guni.dsttna.ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_GUNI_SRC_IPV6 ] , {
 "Source TNA" , "rsvp.guni.srctna.ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_GUNI_DST_IPV6 ] , {
 "Destination TNA" , "rsvp.guni.dsttna.ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_CALL_ID_SRC_ADDR_IPV4 ] , {
 "Source Transport Network Address" , "rsvp.callid.srcaddr.ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_CALL_ID_SRC_ADDR_IPV6 ] , {
 "Source Transport Network Address" , "rsvp.callid.srcaddr.ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_callid_srcaddr_ether , {
 "Source Transport Network Address" , "rsvp.callid.srcaddr.ether" , FT_ETHER , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_callid_srcaddr_bytes , {
 "Source Transport Network Address" , "rsvp.callid.srcaddr.bytes" , FT_ETHER , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_filter [ RSVPF_ENT_CODE ] , {
 "Enterprise Code" , "rsvp.obj_private.enterprise" , FT_UINT32 , BASE_DEC | BASE_EXT_STRING , & sminmpec_values_ext , 0x0 , "IANA Network Management Private Enterprise Code" , HFILL }
 }
 , {
 & hf_rsvp_error_flags , {
 "Flags" , "rsvp.error_flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_flags_path_state_removed , {
 "Path State Removed" , "rsvp.error_flags.path_state_removed" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_flags_not_guilty , {
 "NotGuilty" , "rsvp.error_flags.not_guilty" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_flags_in_place , {
 "InPlace" , "rsvp.error_flags.in_place" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_tlv_color_mode , {
 "Color Mode (CM)" , "rsvp.eth_tspec_tlv.color_mode" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_tlv_coupling_flag , {
 "Coupling Flag (CF)" , "rsvp.eth_tspec_tlv.coupling_flag" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_standard_contiguous_concatenation , {
 "Standard contiguous concatenation" , "rsvp.sender_tspec.standard_contiguous_concatenation" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_arbitrary_contiguous_concatenation , {
 "Arbitrary contiguous concatenation" , "rsvp.sender_tspec.arbitrary_contiguous_concatenation" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_regenerator_section , {
 "Section/Regenerator Section layer transparency" , "rsvp.sender_tspec.regenerator_section" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_multiplex_section , {
 "Line/Multiplex Section layer transparency" , "rsvp.sender_tspec.multiplex_section" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_J0_transparency , {
 "J0 transparency" , "rsvp.sender_tspec.J0_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_SOH_RSOH_DCC_transparency , {
 "SOH/RSOH DCC transparency" , "rsvp.sender_tspec.SOH_RSOH_DCC_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_LOH_MSOH_DCC_transparency , {
 "LOH/MSOH DCC transparency" , "rsvp.sender_tspec.LOH_MSOH_DCC_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_LOH_MSOH_extended_DCC_transparency , {
 "LOH/MSOH Extended DCC transparency" , "rsvp.sender_tspec.LOH_MSOH_extended_DCC_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_K1_K2_transparency , {
 "K1/K2 transparency" , "rsvp.sender_tspec.K1_K2_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_E1_transparency , {
 "E1 transparency" , "rsvp.sender_tspec.E1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_F1_transparency , {
 "F1 transparency" , "rsvp.sender_tspec.F1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_E2_transparency , {
 "E2 transparency" , "rsvp.sender_tspec.E2_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_B1_transparency , {
 "B1 transparency" , "rsvp.sender_tspec.B1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_B2_transparency , {
 "B2 transparency" , "rsvp.sender_tspec.B2_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0800 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_M0_transparency , {
 "M0 transparency" , "rsvp.sender_tspec.M0_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x1000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sender_tspec_M1_transparency , {
 "M1 transparency" , "rsvp.sender_tspec.M1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x2000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_standard_contiguous_concatenation , {
 "Standard contiguous concatenation" , "rsvp.flowspec.standard_contiguous_concatenation" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_arbitrary_contiguous_concatenation , {
 "Arbitrary contiguous concatenation" , "rsvp.flowspec.arbitrary_contiguous_concatenation" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_regenerator_section , {
 "Section/Regenerator Section layer transparency" , "rsvp.flowspec.regenerator_section" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_multiplex_section , {
 "Line/Multiplex Section layer transparency" , "rsvp.flowspec.multiplex_section" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_J0_transparency , {
 "J0 transparency" , "rsvp.flowspec.J0_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_SOH_RSOH_DCC_transparency , {
 "SOH/RSOH DCC transparency" , "rsvp.flowspec.SOH_RSOH_DCC_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_LOH_MSOH_DCC_transparency , {
 "LOH/MSOH DCC transparency" , "rsvp.flowspec.LOH_MSOH_DCC_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_LOH_MSOH_extended_DCC_transparency , {
 "LOH/MSOH Extended DCC transparency" , "rsvp.flowspec.LOH_MSOH_extended_DCC_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_K1_K2_transparency , {
 "K1/K2 transparency" , "rsvp.flowspec.K1_K2_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_E1_transparency , {
 "E1 transparency" , "rsvp.flowspec.E1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_F1_transparency , {
 "F1 transparency" , "rsvp.flowspec.F1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_E2_transparency , {
 "E2 transparency" , "rsvp.flowspec.E2_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_B1_transparency , {
 "B1 transparency" , "rsvp.flowspec.B1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_B2_transparency , {
 "B2 transparency" , "rsvp.flowspec.B2_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x0800 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_M0_transparency , {
 "M0 transparency" , "rsvp.flowspec.M0_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x1000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_M1_transparency , {
 "M1 transparency" , "rsvp.flowspec.M1_transparency" , FT_BOOLEAN , 32 , TFS ( & tfs_yes_no ) , 0x2000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_integrity_flags_handshake , {
 "Handshake" , "rsvp.integrity.flags.handshake" , FT_BOOLEAN , 8 , TFS ( & tfs_capable_not_capable ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sa_flags_local , {
 "Local protection" , "rsvp.sa.flags.local" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sa_flags_label , {
 "Label recording" , "rsvp.sa.flags.label" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sa_flags_se_style , {
 "SE style" , "rsvp.sa.flags.se_style" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sa_flags_bandwidth , {
 "Bandwidth protection" , "rsvp.sa.flags.bandwidth" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sa_flags_node , {
 "Node protection" , "rsvp.sa.flags.node" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_local_avail , {
 "Local Protection" , "rsvp.rro.flags.local_avail" , FT_BOOLEAN , 8 , TFS ( & tfs_available_not_available ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_local_in_use , {
 "Local Protection" , "rsvp.rro.flags.local_in_use" , FT_BOOLEAN , 8 , TFS ( & tfs_used_notused ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_bandwidth , {
 "Bandwidth Protection" , "rsvp.rro.flags.bandwidth" , FT_BOOLEAN , 8 , TFS ( & tfs_available_not_available ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_node , {
 "Node Protection" , "rsvp.rro.flags.node" , FT_BOOLEAN , 8 , TFS ( & tfs_available_not_available ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_node_address , {
 "Address Specifies a Node-id Address" , "rsvp.rro.flags.node_address" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_backup_tunnel_bandwidth , {
 "Backup Tunnel Has Bandwidth" , "rsvp.rro.flags.backup_tunnel_bandwidth" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_backup_tunnel_hop , {
 "Backup Tunnel Goes To" , "rsvp.rro.flags.backup_tunnel_hop" , FT_BOOLEAN , 8 , TFS ( & tfs_next_next_hop_next_hop ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rro_flags_global_label , {
 "Global label" , "rsvp.rro.flags.global_label" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_e2e , {
 "End-to-end re-routing" , "rsvp.lsp_attr.e2e" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_boundary , {
 "Boundary re-routing" , "rsvp.lsp_attr.boundary" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_segment , {
 "Segment-based re-routing" , "rsvp.lsp_attr.segment" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_integrity , {
 "LSP Integrity Required" , "rsvp.lsp_attr.integrity" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_contiguous , {
 "Contiguous LSP" , "rsvp.lsp_attr.contiguous" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_stitching , {
 "LSP stitching desired" , "rsvp.lsp_attr.stitching" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000020 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_preplanned , {
 "Pre-Planned LSP Flag" , "rsvp.lsp_attr.preplanned" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000040 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_nophp , {
 "Non-PHP behavior flag" , "rsvp.lsp_attr.nophp" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000080 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_oobmap , {
 "OOB mapping flag" , "rsvp.lsp_attr.oobmap" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000100 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_entropy , {
 "Entropy Label Capability" , "rsvp.lsp_attr.entropy" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000200 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_srlgcollect , {
 "SRLG Collection Flag" , "rsvp.lsp_attr.srlgcollect" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000400 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_costcollect , {
 "Cost Collection Flag" , "rsvp.lsp_attr.costcollect" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00000800 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_latcollect , {
 "Latency Collection Flag" , "rsvp.lsp_attr.latcollect" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00001000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attr_latvarcollect , {
 "Latency Variation Flag" , "rsvp.lsp_attr.latvarcollect" , FT_BOOLEAN , 32 , TFS ( & tfs_desired_not_desired ) , 0x00002000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_gen_uni_direction , {
 "Direction" , "rsvp.gen_uni.direction" , FT_BOOLEAN , 8 , TFS ( & tfs_gen_uni_direction ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_protection_info_flags_secondary_lsp , {
 "Secondary LSP" , "rsvp.pi.flags.secondary_lsp" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_extra_traffic , {
 "Extra Traffic" , "rsvp.pi_link.flags.extra_traffic" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_unprotected , {
 "Unprotected" , "rsvp.pi_link.flags.unprotected" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_shared , {
 "Shared" , "rsvp.pi_link.flags.shared" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_dedicated1_1 , {
 "Dedicated 1:1" , "rsvp.pi_link.flags.dedicated1_1" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_dedicated1plus1 , {
 "Dedicated 1+1" , "rsvp.pi_link.flags.dedicated1plus1" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_enhanced , {
 "Enhanced" , "rsvp.pi_link.flags.enhanced" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_extra , {
 "Extra Traffic" , "rsvp.pi_link.flags.extra" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_dedicated_1_1 , {
 "Dedicated 1:1" , "rsvp.pi_link.flags.dedicated_1_1" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_link_flags_dedicated_1plus1 , {
 "Dedicated 1+1" , "rsvp.pi_link.flags.dedicated_1plus1" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rfc4872_secondary , {
 "Secondary LSP" , "rsvp.rfc4872.secondary" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rfc4872_protecting , {
 "Protecting LSP" , "rsvp.rfc4872.protecting" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rfc4872_notification_msg , {
 "Protecting LSP" , "rsvp.rfc4872.notification_msg" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsvp_rfc4872_operational , {
 "Protecting LSP" , "rsvp.rfc4872.operational" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_lsp_flags_full_rerouting , {
 "(Full) rerouting" , "rsvp.pi_lsp.flags.full_rerouting" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_lsp_flags_rerouting_extra , {
 "Rerouting without extra-traffic" , "rsvp.pi_lsp.flags.rerouting_extra" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_lsp_flags_1_n_protection , {
 "1:N protection with extra-traffic" , "rsvp.pi_lsp.flags.1_n_protection" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_lsp_flags_1plus1_unidirectional , {
 "1+1 unidirectional protection" , "rsvp.pi_lsp.flags.1plus1_unidirectional" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_lsp_flags_1plus1_bidirectional , {
 "1+1 bidirectional protection" , "rsvp.pi_lsp.flags.1plus1_bidirectional" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_protection_info_in_place , {
 "In-Place" , "rsvp.protection_info.in_place" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_protection_info_required , {
 "Required" , "rsvp.protection_info.required" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_seg_flags_full_rerouting , {
 "(Full) rerouting" , "rsvp.pi_seg.flags.full_rerouting" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_seg_flags_rerouting_extra , {
 "Rerouting without extra-traffic" , "rsvp.pi_seg.flags.rerouting_extra" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_seg_flags_1_n_protection , {
 "1:N protection with extra-traffic" , "rsvp.pi_seg.flags.1_n_protection" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_seg_flags_1plus1_unidirectional , {
 "1+1 unidirectional protection" , "rsvp.pi_seg.flags.1plus1_unidirectional" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_rsvp_pi_seg_flags_1plus1_bidirectional , {
 "1+1 bidirectional protection" , "rsvp.pi_seg.flags.1plus1_bidirectional" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsvp_frr_flags_one2one_backup , {
 "One-to-One Backup" , "rsvp.frr.flags.one2one_backup" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_frr_flags_facility_backup , {
 "Facility Backup" , "rsvp.frr.flags.facility_backup" , FT_BOOLEAN , 8 , TFS ( & tfs_desired_not_desired ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsvp_type , {
 "Type" , "rsvp.type" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tid , {
 "Transaction ID" , "rsvp.3gpp_obj.tid" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_ie_len , {
 "Length" , "rsvp.3gpp_obj.length" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_ie_type , {
 "IE Type" , "rsvp.3gpp_obj.ie_type" , FT_UINT32 , BASE_DEC , VALS ( rsvp_3gpp_object_ie_type_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_ue_ipv4_addr , {
 "UE IPv4 address" , "rsvp.3gpp_obj.ue_ipv4_addr" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_ue_ipv6_addr , {
 "UE IPv6 address" , "rsvp.3gpp_obj.ue_ipv6_addr" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_d , {
 "Direction(D)" , "rsvp.3gpp_obj.tft_d" , FT_UINT32 , BASE_DEC , VALS ( rsvp_3gpp_object_tft_d_vals ) , 0xc0000000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_ns , {
 "Non-Specific bit(NS)" , "rsvp.3gpp_obj.tft_ns" , FT_UINT32 , BASE_DEC , NULL , 0x08000000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_sr_id , {
 "SR_ID" , "rsvp.3gpp_obj.tft_sr_id" , FT_UINT32 , BASE_DEC , NULL , 0x07000000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_p , {
 "Persistency(P)" , "rsvp.3gpp_obj.tft_p" , FT_UINT32 , BASE_DEC , NULL , 0x00010000 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_opcode , {
 "TFT Operation Code" , "rsvp.3gpp_obj.tft_opcode" , FT_UINT32 , BASE_DEC , VALS ( rsvp_3gpp_obj_tft_opcode_vals ) , 0x000ff00 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_n_pkt_flt , {
 "Number of Packet filters" , "rsvp.3gpp_obj.tft_n_pkt_flt" , FT_UINT32 , BASE_DEC , NULL , 0x00000ff , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_flow_id , {
 "Flow Identifier" , "rsvp.3gpp_obj.flow_id" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_ev_prec , {
 "Packet filter evaluation precedence" , "rsvp.3gpp_obj.pf_ev_prec" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_len , {
 "Packet filter length" , "rsvp.3gpp_obj.pf_len" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_type , {
 "PF Type" , "rsvp.3gpp_obj.pf_type" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_cont_len , {
 "Length" , "rsvp.3gpp_obj.pf_cont_len" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_comp_type_id , {
 "PF component identifier" , "rsvp.3gpp_obj.pf_comp_type_id" , FT_UINT8 , BASE_DEC , VALS ( rsvp_3gpp_obj_pf_comp_type_id_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_src_ipv4 , {
 "IPv4 Source Address" , "rsvp.3gpp_obj.pf_src_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_dst_ipv4 , {
 "IPv4 Destination Address" , "rsvp.3gpp_obj.pf_dst_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_ipv4_mask , {
 "IPv4 Mask" , "rsvp.3gpp_obj.pf_ipv4_mask" , FT_UINT32 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_src_ipv6 , {
 "IPv6 Source Address" , "rsvp.3gpp_obj.pf_src_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_dst_ipv6 , {
 "IPv6 Destination Address" , "rsvp.3gpp_obj.pf_dst_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_ipv6_prefix_length , {
 "IPv6 Prefix length" , "rsvp.3gpp_obj.pf_ipv6_prefix_length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_prot_next , {
 "Protocol field(IPv4) or Next Header(IPv6)" , "rsvp.3gpp_obj.pf_prot_next" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_dst_port , {
 "Single Destination Port" , "rsvp.3gpp_obj.pf_dst_port" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_src_port , {
 "Single Source Port" , "rsvp.3gpp_obj.pf_src_port" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_ipsec_spi , {
 "IPsec SPI" , "rsvp.3gpp_obj.pf_ipsec_spi" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_tos_tc , {
 "Type of Service (IPv4)/Traffic Class (IPv6)" , "rsvp.3gpp_obj.pf_tos_tc" , FT_UINT8 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_flow_lbl , {
 "Flow label" , "rsvp.3gpp_obj.pf_flow_lbl" , FT_UINT24 , BASE_DEC , NULL , 0x0fffff , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_ipv6 , {
 "IPv6 Address" , "rsvp.3gpp_obj.pf_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_treatment , {
 "PF Treatment" , "rsvp.3gpp_obj.pf_treatment" , FT_UINT8 , BASE_DEC , VALS ( rsvp_3gpp_obj_pf_treatment_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_hint , {
 "PF Hint" , "rsvp.3gpp_obj.pf_hint" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_tft_qos_list_len , {
 "QoS List Length" , "rsvp.3gpp_obj.qos_list_len" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_r_qos_blob_len , {
 "R_QOS_SUB_BLOB_LEN" , "rsvp.3gpp_obj.r_qos_blob_len" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_r_qos_blob_flow_pri , {
 "FLOW_PRIORITY" , "rsvp.3gpp_obj.r_qos_blob.flow_pri" , FT_UINT8 , BASE_DEC , NULL , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_r_qos_blob_num_qos_att_set , {
 "NUM_QoS_ATTRIBUTE_SETS" , "rsvp.3gpp_obj.r_qos_blob.num_qos_att_set" , FT_UINT8 , BASE_DEC , NULL , 0x0e , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_att_set_len , {
 "QoS_ATTRIBUTE_SET_LEN" , "rsvp.3gpp_obj.r_qos_blob.qos_att_set_len" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_set_id , {
 "QoS_ATTRIBUTE_SET_ID" , "rsvp.3gpp_obj.r_qos_blob.qos_attribute_set_id" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_verbose , {
 "VERBOSE" , "rsvp.3gpp_obj.r_qos_blob.verbose" , FT_BOOLEAN , 8 , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_prof_id , {
 "ProfileID" , "rsvp.3gpp_obj.r_qos_blob.prof_id" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_traff_cls , {
 "Traffic_Class" , "rsvp.3gpp_obj.r_qos_blob.traff_cls" , FT_UINT8 , BASE_DEC , VALS ( rsvp_3gpp_obj_traffic_class_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_peak_rate , {
 "Peak_Rate" , "rsvp.3gpp_obj.r_qos_blob.peak_rate" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_bucket_size , {
 "Bucket_Size" , "rsvp.3gpp_obj.r_qos_blob.bucket_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_token_rate , {
 "Token_Rate" , "rsvp.3gpp_obj.r_qos_blob.token_rate" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_max_latency , {
 "Max_Latency" , "rsvp.3gpp_obj.r_qos_blob.max_latency" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_max_loss_rte , {
 "Max_Loss_Rate" , "rsvp.3gpp_obj.r_qos_blob.max_loss_rte" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_delay_var_sensitive , {
 "Delay_Var_Sensitive" , "rsvp.3gpp_obj.r_qos_blob.delay_var_sensitive" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_attribute_reserved , {
 "Reserved" , "rsvp.3gpp_obj.r_qos_blob.reserved" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_r_qos_blob , {
 "R_QOS_SUB_BLOB" , "rsvp.3gpp_obj.r_qos_blob" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_qos_result , {
 "Result Code" , "rsvp.3gpp_obj.qos_result_code" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_lbit , {
 "L(oose) bit" , "rsvp.xro.sobj.lbit" , FT_UINT8 , BASE_DEC , VALS ( rsvp_xro_sobj_lbit_vals ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_type , {
 "Type" , "rsvp.xro.sobj.type" , FT_UINT8 , BASE_DEC , VALS ( rsvp_xro_sobj_type_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_len , {
 "Length" , "rsvp.xro.sobj.len" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_ipv4_addr , {
 "IPv4 prefix" , "rsvp.xro.sobj.ipv4.addr" , FT_IPv4 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_ipv4_prefix , {
 "Prefix Length" , "rsvp.xro.sobj.ipv4.prefix" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_ipv4_attr , {
 "Attribute" , "rsvp.xro.sobj.ipv4.attr" , FT_UINT8 , BASE_DEC , VALS ( rsvp_xro_sobj_ip_attr_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_ipv6_addr , {
 "IPv6 prefix" , "rsvp.xro.sobj.ipv6.addr" , FT_IPv6 , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_ipv6_prefix , {
 "Prefix Length" , "rsvp.xro.sobj.ipv6.prefix" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_ipv6_attr , {
 "Attribute" , "rsvp.xro.sobj.ipv6.attr" , FT_UINT8 , BASE_DEC , VALS ( rsvp_xro_sobj_ip_attr_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_srlg_id , {
 "SRLG Id" , "rsvp.xro.sobj.srlg.id" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_xro_sobj_srlg_res , {
 "Reserved" , "rsvp.xro.sobj.srlg.res" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_private_data , {
 "Data" , "rsvp.private.data" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_numtlvs , {
 "Num TLVs" , "rsvp.juniper.tlvs" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_padlength , {
 "Padlength" , "rsvp.juniper.padlength" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_type , {
 "Juniper type" , "rsvp.juniper.type" , FT_UINT8 , BASE_HEX , VALS ( rsvp_juniper_attr_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_length , {
 "Juniper length" , "rsvp.juniper.length" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_attrib_cos , {
 "Cos" , "rsvp.juniper.attrib.cos" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_attrib_metric1 , {
 "Metric 1" , "rsvp.juniper.attrib.metric1" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_attrib_metric2 , {
 "Metric 2" , "rsvp.juniper.attrib.metric2" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_attrib_ccc_status , {
 "CCC Status" , "rsvp.juniper.attrib.ccc_status" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_attrib_path , {
 "Path type" , "rsvp.juniper.attrib.path" , FT_UINT16 , BASE_HEX , VALS ( rsvp_juniper_path_attr_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_attrib_unknown , {
 "Unknown" , "rsvp.juniper.attrib.unknown" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_pad , {
 "Pad" , "rsvp.juniper.pad" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_juniper_unknown , {
 "Unknown" , "rsvp.juniper.unknown" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_unknown_data , {
 "Data" , "rsvp.unknown.data" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_loose_hop , {
 "Hop" , "rsvp.loose_hop" , FT_BOOLEAN , 8 , TFS ( & tfs_loose_strict_hop ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_data_length , {
 "Data length" , "rsvp.data_length" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_flags , {
 "Flags" , "rsvp.session.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_destination_address , {
 "Destination address" , "rsvp.session.destination_address" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_protocol , {
 "Protocol" , "rsvp.session.protocol" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_destination_port , {
 "Destination port" , "rsvp.session.destination_port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_dscp , {
 "DSCP" , "rsvp.session.dscp" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & dscp_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_extended_ipv4_address , {
 "Extended IPv4 Address" , "rsvp.session.extended_ipv4_address" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_data , {
 "Data" , "rsvp.session.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_length , {
 "Length" , "rsvp.ifid_tlv.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_ipv4_address , {
 "IPv4 address" , "rsvp.ifid_tlv.ipv4_address" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_ipv6_address , {
 "IPv6 address" , "rsvp.ifid_tlv.ipv6_address" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlvinterface_id , {
 "Interface-ID" , "rsvp.ifid_tlv.interface_id" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_label , {
 "Label" , "rsvp.ifid_tlv.label" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_node_id , {
 "Node ID" , "rsvp.ifid_tlv.node_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_area , {
 "Area" , "rsvp.ifid_tlv.area" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_autonomous_system , {
 "Autonomous System" , "rsvp.ifid_tlv.autonomous_system" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_error_string , {
 "Error String" , "rsvp.ifid_tlv.error_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_data , {
 "Data" , "rsvp.ifid_tlv.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ifid_tlv_padding , {
 "Padding" , "rsvp.ifid_tlv.padding" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hop_neighbor_address_ipv4 , {
 "Neighbor address" , "rsvp.hop.neighbor_address_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hop_logical_interface , {
 "Logical interface" , "rsvp.hop.logical_interface" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hop_neighbor_address_ipv6 , {
 "Neighbor address" , "rsvp.neighbor_address_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hop_data , {
 "Data" , "rsvp.hop.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_time_values_data , {
 "Data" , "rsvp.time_values.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_error_node_ipv4 , {
 "Error node" , "rsvp.error.error_node_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_error_node_ipv6 , {
 "Error node" , "rsvp.error.error_node_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_data , {
 "Data" , "rsvp.error.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_error_error_code , {
 "Error code" , "rsvp.error.error_code" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsvp_error_codes_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_scope_ipv4_address , {
 "IPv4 Address" , "rsvp.scope.ipv4_address" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_scope_ipv6_address , {
 "IPv6 Address" , "rsvp.scope.ipv6_address" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_scope_data , {
 "Data" , "rsvp.scope.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_style_flags , {
 "Flags" , "rsvp.style.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_style_style , {
 "Style" , "rsvp.style.style" , FT_UINT24 , BASE_HEX , VALS ( style_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_style_data , {
 "Data" , "rsvp.style.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_confirm_receiver_address_ipv4 , {
 "Receiver address" , "rsvp.confirm.receiver_address_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_confirm_receiver_address_ipv6 , {
 "Receiver address" , "rsvp.confirm.receiver_address_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_confirm_data , {
 "Data" , "rsvp.confirm.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_template_filter_source_address_ipv6 , {
 "Source address" , "rsvp.template_filter.source_address_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_template_filter_source_port , {
 "Source port" , "rsvp.template_filter.source_port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_template_filter_data , {
 "Data" , "rsvp.template_filter.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_length , {
 "Length" , "rsvp.eth_tspec.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_profile , {
 "Profile" , "rsvp.eth_tspec.profile" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_index , {
 "Index" , "rsvp.eth_tspec.index" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_reserved , {
 "Reserved" , "rsvp.eth_tspec.reserved" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_el2cp , {
 "EL2CP" , "rsvp.eth_tspec.el2cp" , FT_UINT8 , BASE_DEC , VALS ( el2cp_val_str ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_il2cp , {
 "IL2CP" , "rsvp.eth_tspec.il2cp" , FT_UINT8 , BASE_DEC , VALS ( il2cp_val_str ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_cir , {
 "CIR" , "rsvp.eth_tspec.cir" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_cbs , {
 "CBS" , "rsvp.eth_tspec.cbs" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_eir , {
 "EIR" , "rsvp.eth_tspec.eir" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_eth_tspec_ebs , {
 "EBS" , "rsvp.eth_tspec.ebs" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_message_format_version , {
 "Message format version" , "rsvp.tspec.message_format_version" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_service_header , {
 "Service header" , "rsvp.tspec.service_header" , FT_UINT8 , BASE_DEC , VALS ( qos_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_token_bucket_rate , {
 "Token bucket rate" , "rsvp.tspec.token_bucket_rate" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_token_bucket_size , {
 "Token bucket size" , "rsvp.tspec.token_bucket_size" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_peak_data_rate , {
 "Peak data rate" , "rsvp.tspec.peak_data_rate" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_hint , {
 "Hint" , "rsvp.tspec.hint" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_compression_factor , {
 "Compression Factor" , "rsvp.tspec.compression_factor" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_signal_type_sonet , {
 "Signal Type" , "rsvp.tspec.signal_type" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & gmpls_sonet_signal_type_str_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_requested_concatenation , {
 "Requested Concatenation (RCC)" , "rsvp.tspec.requested_concatenation" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_number_of_contiguous_components , {
 "Number of Contiguous Components (NCC)" , "rsvp.tspec.number_of_contiguous_components" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_number_of_virtual_components , {
 "Number of Virtual Components (NVC)" , "rsvp.tspec.number_of_virtual_components" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_multiplier , {
 "Multiplier (MT)" , "rsvp.tspec.multiplier" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_transparency , {
 "Transparency (T)" , "rsvp.tspec.transparency" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_profile , {
 "Profile (P)" , "rsvp.tspec.profile" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_signal_type_g709 , {
 "Signal Type" , "rsvp.tspec.signal_type" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gmpls_g709_signal_type_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_number_of_multiplexed_components , {
 "Number of Multiplexed Components (NMC)" , "rsvp.number_of_multiplexed_components" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_mtu , {
 "MTU" , "rsvp.tspec.mtu" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_tspec_data , {
 "Data" , "rsvp.tspec.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_message_format_version , {
 "Message format version" , "rsvp.flowspec.message_format_version" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_service_header , {
 "Service header" , "rsvp.flowspec.service_header" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & intsrv_services_str_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_token_bucket_rate , {
 "Token bucket rate" , "rsvp.flowspec.token_bucket_rate" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_token_bucket_size , {
 "Token bucket size" , "rsvp.flowspec.token_bucket_size" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_peak_data_rate , {
 "Peak data rate" , "rsvp.flowspec.peak_data_rate" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_rate , {
 "Rate" , "rsvp.flowspec.rate" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_slack_term , {
 "Slack term" , "rsvp.flowspec.slack_term" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_signal_type_sonet , {
 "Signal Type" , "rsvp.flowspec.signal_type" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & gmpls_sonet_signal_type_str_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_requested_concatenation , {
 "Requested Concatenation (RCC)" , "rsvp.flowspec.requested_concatenation" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_number_of_contiguous_components , {
 "Number of Contiguous Components (NCC)" , "rsvp.flowspec.number_of_contiguous_components" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_number_of_virtual_components , {
 "Number of Virtual Components (NVC)" , "rsvp.flowspec.number_of_virtual_components" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_multiplier , {
 "Multiplier (MT)" , "rsvp.flowspec.multiplier" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_transparency , {
 "Transparency (T)" , "rsvp.flowspec.transparency" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_profile , {
 "Profile (P)" , "rsvp.flowspec.profile" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_signal_type_g709 , {
 "Signal Type" , "rsvp.flowspec.signal_type" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gmpls_g709_signal_type_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_number_of_multiplexed_components , {
 "Number of Multiplexed Components (NMC)" , "rsvp.flowspec.number_of_multiplexed_components" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flowspec_mtu , {
 "MTU" , "rsvp.flowspec.mtu" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_message_format_version , {
 "Message format version" , "rsvp.adspec.message_format_version" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_service_header , {
 "Service header" , "rsvp.adspec.service_header" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & intsrv_services_str_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_integrity_flags , {
 "Flags" , "rsvp.integrity.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_integrity_key_identifier , {
 "Key Identifier" , "rsvp.integrity.key_identifier" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_integrity_sequence_number , {
 "Sequence Number" , "rsvp.integrity.sequence_number" , FT_UINT64 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_integrity_hash , {
 "Hash" , "rsvp.integrity.hash" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_policy_data , {
 "Data" , "rsvp.policy.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_l3pid , {
 "L3PID" , "rsvp.label_request.l3pid" , FT_UINT16 , BASE_HEX , VALS ( etype_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_min_vpi , {
 "Min VPI" , "rsvp.label_request.min_vpi" , FT_UINT16 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_min_vci , {
 "Min VCI" , "rsvp.label_request.min_vci" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_max_vpi , {
 "Max VPI" , "rsvp.label_request.max_vpi" , FT_UINT16 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_max_vci , {
 "Max VCI" , "rsvp.label_request.max_vci" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_lsp_encoding_type , {
 "LSP Encoding Type" , "rsvp.label_request.lsp_encoding_type" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gmpls_lsp_enc_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_switching_type , {
 "Switching Type" , "rsvp.label_request.switching_type" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gmpls_switching_type_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_g_pid , {
 "G-PID" , "rsvp.label_request.g_pid" , FT_UINT16 , BASE_HEX | BASE_RANGE_STRING , RVALS ( gmpls_gpid_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_data , {
 "Data" , "rsvp.label_request.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_label , {
 "Label" , "rsvp.label.label" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_generalized_label , {
 "Generalized Label" , "rsvp.label.generalized_label" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_generalized_label_evpl_vlad_id , {
 "VLAN ID" , "rsvp.label.generalized_label_evpl_vlad_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_data , {
 "Data" , "rsvp.label.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_set_action , {
 "Action" , "rsvp.label_set.action" , FT_UINT8 , BASE_DEC , VALS ( action_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_exclude_any , {
 "Exclude-Any" , "rsvp.session_attribute.exclude_any" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_include_any , {
 "Include-Any" , "rsvp.session_attribute.include_any" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_include_all , {
 "Include-All" , "rsvp.session_attribute.include_all" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_setup_priority , {
 "Setup priority" , "rsvp.session_attribute.setup_priority" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_hold_priority , {
 "Hold priority" , "rsvp.session_attribute.hold_priority" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_flags , {
 "Flags" , "rsvp.session_attribute.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_name_length , {
 "Name length" , "rsvp.session_attribute.name_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_name , {
 "Name" , "rsvp.session_attribute.name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_session_attribute_data , {
 "Data" , "rsvp.session_attribute.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_length , {
 "Length" , "rsvp.ero_rro_subobjects.length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_ipv4_hop , {
 "IPv4 hop" , "rsvp.ero_rro_subobjects.ipv4_hop" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_prefix_length , {
 "Prefix length" , "rsvp.ero_rro_subobjects.prefix_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_flags , {
 "Flags" , "rsvp.ero_rro_subobjects.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_ipv6_hop , {
 "IPv6 hop" , "rsvp.ero_rro_subobjects.ipv6_hop" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_label , {
 "Label" , "rsvp.ero_rro_subobjects.label" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_router_id , {
 "Router-ID" , "rsvp.ero_rro_subobjects.router_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_interface_id , {
 "Interface-ID" , "rsvp.ero_rro_subobjects.interface_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_path_key , {
 "Path Key" , "rsvp.ero_rro_subobjects.path_key" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_pce_id_ipv4 , {
 "PCE-ID" , "rsvp.ero_rro_subobjects.pce_id_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_pce_id_ipv6 , {
 "PCE-ID" , "rsvp.ero_rro_subobjects.pce_id_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_private_length , {
 "Length" , "rsvp.ero_rro_subobjects.private_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_subobjects_private_data , {
 "Data" , "rsvp.ero_rro_subobjects.private_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_explicit_route_data , {
 "Data" , "rsvp.explicit_route.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_record_route_data , {
 "Data" , "rsvp.record_route.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_exclude_route_data , {
 "Data" , "rsvp.exclude_route.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_flags , {
 "Flags" , "rsvp.message_id.flags" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_epoch , {
 "Epoch" , "rsvp.message_id.epoch" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_message_id , {
 "Message-ID" , "rsvp.message_id.message_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_data , {
 "Data" , "rsvp.message_id.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_ack_flags , {
 "Flags" , "rsvp.message_id_ack.flags" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_ack_epoch , {
 "Epoch" , "rsvp.message_id_ack.epoch" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_ack_message_id , {
 "Message-ID" , "rsvp.message_id_ack.message_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_ack_data , {
 "Data" , "rsvp.message_id_ack.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_list_flags , {
 "Flags" , "rsvp.message_id_list.flags" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_list_epoch , {
 "Epoch" , "rsvp.message_id_list.epoch" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_list_message_id , {
 "Message-ID" , "rsvp.message_id_list.message_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_id_list_data , {
 "Data" , "rsvp.message_id_list.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hello_source_instance , {
 "Source Instance" , "rsvp.hello.source_instance" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hello_destination_instance , {
 "Destination Instance" , "rsvp.hello.destination_instance" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_dclass_dscp , {
 "DSCP" , "rsvp.dclass.dscp" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & dscp_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_dclass_data , {
 "Data" , "rsvp.dclass.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_admin_status_bits , {
 "Admin Status" , "rsvp.admin_status.bits" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_admin_status_data , {
 "Data" , "rsvp.admin_status.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attributes_tlv , {
 "LSP attributes TLV" , "rsvp.lsp_attributes_tlv" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_attributes_tlv_data , {
 "Data" , "rsvp.lsp_attributes_tlv.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_type , {
 "Association type" , "rsvp.association.type" , FT_UINT16 , BASE_DEC , VALS ( association_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_id , {
 "Association ID" , "rsvp.association.id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_source_ipv4 , {
 "Association source" , "rsvp.association.source_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_source_ipv6 , {
 "Association source" , "rsvp.association.source_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_routing_area_id , {
 "Routing Area ID" , "rsvp.association.routing_area_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_node_id , {
 "Node ID" , "rsvp.association.node_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_padding , {
 "Padding" , "rsvp.association.padding" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_association_data , {
 "Data" , "rsvp.association.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_length , {
 "Length" , "rsvp.lsp_tunnel_if_id.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_component_link_identifier , {
 "Component link identifier" , "rsvp.lsp_tunnel_if_id.component_link_identifier" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_component_link_identifier_ipv4 , {
 "Component link identifier" , "rsvp.lsp_tunnel_if_id.component_link_identifier_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_lsp_encoding_type , {
 "LSP Encoding Type" , "rsvp.lsp_tunnel_if_id.lsp_encoding_type" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gmpls_lsp_enc_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_switching_type , {
 "Switching Type" , "rsvp.lsp_tunnel_if_id.switching_type" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gmpls_switching_type_rvals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_signal_type , {
 "Signal Type" , "rsvp.lsp_tunnel_if_id.signal_type" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & gmpls_sonet_signal_type_str_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_connection_id , {
 "Sub Interface/Connection ID" , "rsvp.lsp_tunnel_if_id.connection_id" , FT_UINT64 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_sc_pc_id , {
 "SC PC ID" , "rsvp.lsp_tunnel_if_id.sc_pc_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_sc_pc_scn_address , {
 "SC PC SCN Address" , "rsvp.lsp_tunnel_if_id.sc_pc_scn_address" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_router_id , {
 "Router ID" , "rsvp.lsp_tunnel_if_id.router_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_interface_id , {
 "Interface ID" , "rsvp.lsp_tunnel_if_id.interface_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_ipv4_interface_address , {
 "IPv4 interface address" , "rsvp.lsp_tunnel_if_id.ipv4_interface_address" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_target_igp_instance , {
 "Target IGP instance" , "rsvp.lsp_tunnel_if_id.target_igp_instance" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_action , {
 "Action" , "rsvp.lsp_tunnel_if_id.action" , FT_UINT8 , BASE_DEC , VALS ( lsp_tunnel_if_id_action_str ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_ipv6_interface_address , {
 "IPv6 interface address" , "rsvp.lsp_tunnel_if_id.ipv6_interface_address" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_lsp_tunnel_if_id_data , {
 "Data" , "rsvp.lsp_tunnel_if_id.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_notify_request_notify_node_address_ipv4 , {
 "Notify node address" , "rsvp.notify_request.notify_node_address_ipv4" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_notify_request_notify_node_address_ipv6 , {
 "Notify node address" , "rsvp.notify_request.notify_node_address_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_notify_request_data , {
 "Data" , "rsvp.notify_request.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_id_data , {
 "Data" , "rsvp.call_id.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_id_address_type , {
 "Address type" , "rsvp.call_id.address_type" , FT_UINT8 , BASE_DEC , VALS ( address_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_id_reserved , {
 "Reserved" , "rsvp.call_id.reserved" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_id_international_segment , {
 "International Segment" , "rsvp.call_id.international_segment" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_id_national_segment , {
 "National Segment" , "rsvp.call_id.national_segment" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_id_local_identifier , {
 "Local Identifier" , "rsvp.call_id.local_identifier" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_restart_cap_data , {
 "Data" , "rsvp.restart_cap.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_protection_info_link_flags , {
 "Link Flags" , "rsvp.protection_info.link_flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_protection_info_data , {
 "Data" , "rsvp.protection_info.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_setup_priority , {
 "Setup Priority" , "rsvp.fast_reroute.setup_priority" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_hold_priority , {
 "Hold Priority" , "rsvp.fast_reroute.hold_priority" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_hop_limit , {
 "Hop Limit" , "rsvp.fast_reroute.hop_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_flags , {
 "Flags" , "rsvp.fast_reroute.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_bandwidth , {
 "Bandwidth" , "rsvp.fast_reroute.bandwidth" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_include_any , {
 "Include-Any" , "rsvp.fast_reroute.include_any" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_exclude_any , {
 "Exclude-Any" , "rsvp.fast_reroute.exclude_any" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_include_all , {
 "Include-All" , "rsvp.fast_reroute.include_all" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_fast_reroute_data , {
 "Data" , "rsvp.fast_reroute.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_detour_data , {
 "Data" , "rsvp.detour.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_diffserv_data , {
 "Data" , "rsvp.diffserv.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_diffserv_aware_te_data , {
 "Data" , "rsvp.diffserv_aware_te.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_version , {
 "RSVP Version" , "rsvp.version" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_flags , {
 "Flags" , "rsvp.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_rsvp_sending_ttl , {
 "Sending TTL" , "rsvp.sending_ttl" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_length , {
 "Message length" , "rsvp.message_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_length , {
 "Length" , "rsvp.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_extended_tunnel_id , {
 "Extended Tunnel ID" , "rsvp.extended_tunnel_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_extended_tunnel_ipv6 , {
 "Extended Tunnel ID" , "rsvp.extended_tunnel_id_ipv6" , FT_IPv6 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_extended_tunnel , {
 "Extended Tunnel" , "rsvp.extended_tunnel" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_refresh_interval , {
 "Refresh interval" , "rsvp.refresh_interval" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_minimum_policed_unit , {
 "Minimum policed unit [m]" , "rsvp.minimum_policed_unit" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_maximum_packet_size , {
 "Maximum packet size [M]" , "rsvp.maximum_packet_size" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_hf_rsvp_adspec_break_bit , {
 "Break bit" , "rsvp.adspec.break_bit" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_request_m , {
 "M (Merge in Data Plane)" , "rsvp.label_request.m" , FT_BOOLEAN , 8 , TFS ( & tfs_can_cannot ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsvp_dlci_length , {
 "DLCI Length" , "rsvp.label_request.dlci_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_min_dlci , {
 "Min DLCI" , "rsvp.label_request.min_dlci" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_max_dlci , {
 "Max DLCI" , "rsvp.label_request.max_dlci" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ero_rro_autonomous_system , {
 "Autonomous System" , "rsvp.ero_rro_subobjects.autonomous_system" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_nsap_length , {
 "NSAP Length" , "rsvp.nsap_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_gen_uni_data , {
 "Data" , "rsvp.gen_uni.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_gen_uni_logical_port_id , {
 "Logical Port ID" , "rsvp.gen_uni.logical_port_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_gen_uni_service_level , {
 "Service Level" , "rsvp.gen_uni.service_level" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_restart_cap_restart_time , {
 "Restart Time" , "rsvp.restart_cap.restart_time" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_restart_cap_recovery_time , {
 "Recovery Time" , "rsvp.restart_cap.recovery_time" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_detour_plr_id , {
 "PLR ID" , "rsvp.detour.plr_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_detour_avoid_node_id , {
 "Avoid Node ID" , "rsvp.detour.avoid_node_id" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_message_checksum , {
 "Message Checksum" , "rsvp.message_checksum" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_call_attributes_endpont_id , {
 "Endpoint ID" , "rsvp.call_attributes.endpoint_id" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_isis_area_id , {
 "IS-IS Area Identifier" , "rsvp.isis_area_id" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_type , {
 "Adspec Type" , "rsvp.adspec.type" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & adspec_params_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_len , {
 "Length" , "rsvp.adspec.len" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_uint , {
 "Adspec uint" , "rsvp.adspec.uint" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_float , {
 "Adspec float" , "rsvp.adspec.float" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_adspec_bytes , {
 "Adspec bytes" , "rsvp.adspec.bytes" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_wavelength_freq , {
 "Freq" , "rsvp.wavelength.freq" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_wavelength_grid , {
 "Grid" , "rsvp.wavelength.grid" , FT_UINT8 , BASE_DEC , VALS ( lambda_grid_vals ) , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_wavelength_channel_spacing , {
 "Channel Spacing" , "rsvp.wavelength.channel_spacing" , FT_UINT8 , BASE_DEC , NULL , 0x1E , NULL , HFILL }
 }
 , {
 & hf_rsvp_wavelength_n , {
 "n" , "rsvp.wavelength.n" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_wavelength_wavelength , {
 "Wavelength" , "rsvp.wavelength.wavelength" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sonet_s , {
 "S" , "rsvp.sonet.s" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sonet_u , {
 "U" , "rsvp.sonet.u" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sonet_k , {
 "K" , "rsvp.sonet.k" , FT_UINT8 , BASE_DEC , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_rsvp_sonet_l , {
 "L" , "rsvp.sonet.l" , FT_UINT8 , BASE_DEC , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_sonet_m , {
 "M" , "rsvp.sonet.m" , FT_UINT8 , BASE_DEC , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_rsvp_g709_t3 , {
 "t3" , "rsvp.g709.t3" , FT_UINT16 , BASE_DEC , NULL , 0x03F0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_g709_t2 , {
 "t2" , "rsvp.g709.t2" , FT_UINT8 , BASE_DEC , NULL , 0x0E , NULL , HFILL }
 }
 , {
 & hf_rsvp_g709_t1 , {
 "t1" , "rsvp.g709.t1" , FT_UINT8 , BASE_DEC , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_set_type , {
 "Label type" , "rsvp.label_set.type" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_label_set_subchannel , {
 "Subchannel" , "rsvp.label_set.subchannel" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_nsap_address , {
 "NSAP address" , "rsvp.nsap_address" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_class_diversity , {
 "Diversity" , "rsvp.class_diversity" , FT_UINT8 , BASE_DEC , VALS ( ouni_guni_diversity_str ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_egress_label_type , {
 "Label type" , "rsvp.egress.label_type" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_egress_label , {
 "Label" , "rsvp.egress.label" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_source_transport_network_addr , {
 "Source Transport Network addr" , "rsvp.source_transport_network_addr" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_ie_data , {
 "IE Data" , "rsvp.ie_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_dst_port_range , {
 "Destination Port range" , "rsvp.3gpp_obj.pf_dst_port_range" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsvp_3gpp_obj_pf_src_port_range , {
 "Source Port range" , "rsvp.3gpp_obj.pf_src_port_range" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_rsvp_invalid_length , {
 "rsvp.invalid_length" , PI_MALFORMED , PI_ERROR , "Invalid length" , EXPFILL }
 }
 , {
 & ei_rsvp_packet_filter_component , {
 "rsvp.packet_filter_component" , PI_UNDECODED , PI_WARN , "Not dissected Packet filter component" , EXPFILL }
 }
 , {
 & ei_rsvp_bundle_component_msg , {
 "rsvp.bundle_component_msg" , PI_UNDECODED , PI_WARN , "Bundle Component Messages Not Dissected" , EXPFILL }
 }
 , {
 & ei_rsvp_parameter , {
 "rsvp.parameter.unknown" , PI_PROTOCOL , PI_WARN , "Unknown parameter" , EXPFILL }
 }
 , {
 & ei_rsvp_adspec_type , {
 "rsvp.adspec.type.unknown" , PI_PROTOCOL , PI_WARN , "Unknown type" , EXPFILL }
 }
 , {
 & ei_rsvp_call_id_address_type , {
 "rsvp.call_id.address_type.unknown" , PI_PROTOCOL , PI_WARN , "Unknown Transport Network type" , EXPFILL }
 }
 , {
 & ei_rsvp_session_type , {
 "rsvp.session_type.unknown" , PI_PROTOCOL , PI_WARN , "Unknown session type" , EXPFILL }
 }
 , }
 ;
 expert_module_t * expert_rsvp ;
 gint * ett_tree [ TT_MAX ] ;
 for ( i = 0 ;
 i < TT_MAX ;
 i ++ ) {
 ett_treelist [ i ] = - 1 ;
 ett_tree [ i ] = & ( ett_treelist [ i ] ) ;
 }
 proto_rsvp = proto_register_protocol ( "Resource ReserVation Protocol (RSVP)" , "RSVP" , "rsvp" ) ;
 proto_rsvp_e2e1 = proto_register_protocol ( "Resource ReserVation Protocol (RSVP-E2EI)" , "RSVP-E2EI" , "rsvp-e2ei" ) ;
 proto_register_field_array ( proto_rsvp , rsvpf_info , array_length ( rsvpf_info ) ) ;
 proto_register_subtree_array ( ett_tree , array_length ( ett_tree ) ) ;
 expert_rsvp = expert_register_protocol ( proto_rsvp ) ;
 expert_register_field_array ( expert_rsvp , ei , array_length ( ei ) ) ;
 register_rsvp_prefs ( ) ;
 register_init_routine ( & rsvp_init_protocol ) ;
 register_cleanup_routine ( & rsvp_cleanup_protocol ) ;
 register_conversation_table ( proto_rsvp , TRUE , rsvp_conversation_packet , rsvp_hostlist_packet ) ;
 }