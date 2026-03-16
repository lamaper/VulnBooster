void init_get_bits(GetBitContext *s,

                   UINT8 *buffer, int buffer_size)

{

    s->buffer= buffer;

    s->size= buffer_size;

    s->buffer_end= buffer + buffer_size;


    s->index=0;


    s->buffer_ptr = buffer;

    s->bit_count = 16;

    s->cache = 0;


    s->buffer_ptr = (uint32_t*)buffer;

    s->bit_count = 32;

    s->cache0 = 0;

    s->cache1 = 0;


    {

        OPEN_READER(re, s)

        UPDATE_CACHE(re, s)

 

        CLOSE_READER(re, s)

    }


    s->cache1 = 0;


}
