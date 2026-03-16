static inline void *alloc_code_gen_buffer(void)

{

    void *buf = static_code_gen_buffer;


    if (cross_256mb(buf, tcg_ctx.code_gen_buffer_size)) {

        buf = split_cross_256mb(buf, tcg_ctx.code_gen_buffer_size);

    }


    map_exec(buf, tcg_ctx.code_gen_buffer_size);

    return buf;

}
