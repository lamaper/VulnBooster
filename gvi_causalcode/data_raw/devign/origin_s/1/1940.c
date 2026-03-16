static inline bool use_goto_tb(DisasContext *s, int n, uint64_t dest)

{

     

    if (s->base.singlestep_enabled || s->ss_active || (s->base.tb->cflags & CF_LAST_IO)) {

        return false;

    }


     

    if ((s->base.tb->pc & TARGET_PAGE_MASK) != (dest & TARGET_PAGE_MASK)) {

        return false;

    }




    return true;

}
