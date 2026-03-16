static struct bitmap * find_objects ( struct rev_info * revs , struct object_list * roots , struct bitmap * seen ) {
 struct bitmap * base = NULL ;
 int needs_walk = 0 ;
 struct object_list * not_mapped = NULL ;
 while ( roots ) {
 struct object * object = roots -> item ;
 roots = roots -> next ;
 if ( object -> type == OBJ_COMMIT ) {
 khiter_t pos = kh_get_sha1 ( bitmap_git . bitmaps , object -> oid . hash ) ;
 if ( pos < kh_end ( bitmap_git . bitmaps ) ) {
 struct stored_bitmap * st = kh_value ( bitmap_git . bitmaps , pos ) ;
 struct ewah_bitmap * or_with = lookup_stored_bitmap ( st ) ;
 if ( base == NULL ) base = ewah_to_bitmap ( or_with ) ;
 else bitmap_or_ewah ( base , or_with ) ;
 object -> flags |= SEEN ;
 continue ;
 }
 }
 object_list_insert ( object , & not_mapped ) ;
 }
 if ( not_mapped == NULL ) return base ;
 roots = not_mapped ;
 while ( roots ) {
 struct object * object = roots -> item ;
 int pos ;
 roots = roots -> next ;
 pos = bitmap_position ( object -> oid . hash ) ;
 if ( pos < 0 || base == NULL || ! bitmap_get ( base , pos ) ) {
 object -> flags &= ~ UNINTERESTING ;
 add_pending_object ( revs , object , "" ) ;
 needs_walk = 1 ;
 }
 else {
 object -> flags |= SEEN ;
 }
 }
 if ( needs_walk ) {
 struct include_data incdata ;
 if ( base == NULL ) base = bitmap_new ( ) ;
 incdata . base = base ;
 incdata . seen = seen ;
 revs -> include_check = should_include ;
 revs -> include_check_data = & incdata ;
 if ( prepare_revision_walk ( revs ) ) die ( "revision walk setup failed" ) ;
 traverse_commit_list ( revs , show_commit , show_object , base ) ;
 }
 return base ;
 }