static hb_blob_t * _hb_face_for_data_reference_table ( hb_face_t * face HB_UNUSED , hb_tag_t tag , void * user_data ) {
 hb_face_for_data_closure_t * data = ( hb_face_for_data_closure_t * ) user_data ;
 if ( tag == HB_TAG_NONE ) return hb_blob_reference ( data -> blob ) ;
 const OT : : OpenTypeFontFile & ot_file = * OT : : Sanitizer < OT : : OpenTypeFontFile > : : lock_instance ( data -> blob ) ;
 const OT : : OpenTypeFontFace & ot_face = ot_file . get_face ( data -> index ) ;
 const OT : : OpenTypeTable & table = ot_face . get_table_by_tag ( tag ) ;
 hb_blob_t * blob = hb_blob_create_sub_blob ( data -> blob , table . offset , table . length ) ;
 return blob ;
 }