/*
4coder_default_bidings.cpp - Supplies the default bindings used for default 4coder behavior.
*/

// TOP

#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.cpp"

// NOTE(allen): Users can declare their own managed IDs here.

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

void
custom_layer_init(Application_Links *app){
    Thread_Context *tctx = get_thread_context(app);
    
    // NOTE(allen): setup for default framework
    default_framework_init(app);
    
    // NOTE(allen): default hooks and command maps
    set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
#if OS_MAC
    setup_mac_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#else
    //NOTE(AD): setup_default_mapping is implemented in 4coder_default_map  
    setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#endif
	setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);

    // NOTE(AD): CUSTOM MAPPING BEGIN
    MappingScope();
    SelectMapping(&framework_mapping);
    SelectMap(global_map_id);
    Bind(kill_buffer, KeyCode_K, KeyCode_Control); // assign Ctrl+K to kill buffer
    Bind(change_active_panel, KeyCode_O, KeyCode_Control, KeyCode_Alt); /// assign Ctrl+Alt+o to switch buffer
    // With this example, there will be two ways to kill buffer, the way it's 
    // programmed in setup_default_mapping and this one, they both work
    // CUSTOM MAPPING END
}

#endif //FCODER_DEFAULT_BINDINGS

// BOTTOM

