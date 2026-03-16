hb_blob_t * hb_face_reference_blob ( hb_face_t * face ) {
 return face -> reference_table ( HB_TAG_NONE ) ;
 }