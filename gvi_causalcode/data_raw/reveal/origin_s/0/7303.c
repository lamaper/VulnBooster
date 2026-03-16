static tvbuff_t * ber_tvb_new_subset_length ( tvbuff_t * tvb , const gint backing_offset , const gint backing_length ) {
 gint length_remaining ;
 length_remaining = tvb_reported_length_remaining ( tvb , backing_offset ) ;
 return tvb_new_subset_length ( tvb , backing_offset , ( length_remaining > backing_length ) ? backing_length : length_remaining ) ;
 }