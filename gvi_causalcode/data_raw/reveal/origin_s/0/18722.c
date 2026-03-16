void dissect_zcl_appl_idt_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 proto_tree * sub_tree ;
 guint64 value64 ;
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_APPL_IDT_BASIC_IDENT : value64 = tvb_get_letoh56 ( tvb , * offset ) ;
 sub_tree = proto_tree_add_subtree_format ( tree , tvb , * offset , 8 , ett_zbee_zcl_appl_idt_basic , NULL , "Basic Identification: 0x%" G_GINT64_MODIFIER "x" , value64 ) ;
 proto_tree_add_item ( sub_tree , hf_zbee_zcl_appl_idt_company_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( sub_tree , hf_zbee_zcl_appl_idt_brand_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( sub_tree , hf_zbee_zcl_appl_idt_prod_type_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( sub_tree , hf_zbee_zcl_appl_idt_ceced_spec_ver , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_APPL_IDT_COMPANY_ID : proto_tree_add_item ( tree , hf_zbee_zcl_appl_idt_company_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_APPL_IDT_BRAND_ID : proto_tree_add_item ( tree , hf_zbee_zcl_appl_idt_brand_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_APPL_IDT_PROD_TYPE_NAME : proto_tree_add_item ( tree , hf_zbee_zcl_appl_idt_string_len , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_idt_prod_type_name , tvb , * offset , 2 , ENC_BIG_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_APPL_IDT_PROD_TYPE_ID : proto_tree_add_item ( tree , hf_zbee_zcl_appl_idt_prod_type_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_APPL_IDT_CECED_SPEC_VER : proto_tree_add_item ( tree , hf_zbee_zcl_appl_idt_ceced_spec_ver , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }