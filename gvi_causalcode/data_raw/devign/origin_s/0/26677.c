static inline void temp_save(TCGContext *s, TCGTemp *ts,

                             TCGRegSet allocated_regs)

{


     

    if (!ts->indirect_base) {

         

        tcg_debug_assert(ts->val_type == TEMP_VAL_MEM || ts->fixed_reg);

        return;

    }


    temp_sync(s, ts, allocated_regs);

    temp_dead(s, ts);

}
