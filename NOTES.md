File for notetaking while making my custom layer for 4coder

# Articles
- [Customization layer, getting started](https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_])

# Editor errors
Red squiggly lines appear, but if it compiles, don't touch it. :D

# Notes
- For better updating, make a copy of `custom/4coder_default_bindings.cpp` (called `custom_layer.cpp` in the rest of the file) and edit that copy. 

## Building the custom layer in Linux
build.sh (if using this exact command, the file shall be placed in code/)
    #!/bin/bash
    custom/bin/buildsuper_x64-linux.sh custom_layer.cpp $@

## Entry point
The entry point for the custom layer is the `custom_layer_init` function in `custom_layer.cpp` 

## Key bindings
The `custom_layer_init` function calls `setup_default_mapping` which will define the default bindings of 4coder with the bindings from `4coder_default_map.cpp`.  
It's possible to overwrite that file or create a new one

### Key maps overview
4coder groups key bindings into key maps.
Keymap -> Allows us to have multiple sets of keys that will be active or inactive depending on the context

#### Default keymaps
keys_global: bindings for operation not related to the editing of the file (opening the file browser, closing a file...)   
keys_file: bindings for the editing of the file
keys_code: bindings that only apply to code editing (indentation, auto-completion, listing types...)

### Key codes
They are used to reference a key.   
The list of key codes are in `custom/generated/4coder_event_codes.h` 

## Physical keys
Now 4coder uses keyboard layout independent key codes, which means when a key code is "referenced" in a specific mode, it's referenced to that physical position of the key.
It's an option wich can be activated in config.4coder by changing the value of `bind_by_physical_key` to true.



