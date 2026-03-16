static inline void gen_stack_update(DisasContext *s, int addend)

{


    if (CODE64(s)) {

        gen_op_addq_ESP_im(addend);

    } else


    if (s->ss32) {

        gen_op_addl_ESP_im(addend);

    } else {

        gen_op_addw_ESP_im(addend);

    }

}
