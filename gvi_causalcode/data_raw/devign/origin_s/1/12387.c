static int line_in_init (HWVoiceIn *hw, struct audsettings *as)

{

    SpiceVoiceIn *in = container_of (hw, SpiceVoiceIn, hw);

    struct audsettings settings;


    settings.freq       = spice_server_get_best_record_rate(NULL);


    settings.freq       = SPICE_INTERFACE_RECORD_FREQ;


    settings.nchannels  = SPICE_INTERFACE_RECORD_CHAN;

    settings.fmt        = AUD_FMT_S16;

    settings.endianness = AUDIO_HOST_ENDIANNESS;



    audio_pcm_init_info (&hw->info, &settings);

    hw->samples = LINE_IN_SAMPLES;

    in->active = 0;



    in->sin.base.sif = &record_sif.base;

    qemu_spice_add_interface (&in->sin.base);


    spice_server_set_record_rate(&in->sin, settings.freq);


    return 0;

}
