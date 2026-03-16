static CLEAR_MARKS_PROC ( aos_clear_marks ) {
 aos_state_t * const pptr = vptr ;
 r_clear_attrs ( & pptr -> blocks , l_mark ) ;
 }