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

## Using code to overwrite key bindings
If what we want to do is overwrite some bindings in code, select a key map using the `SelectMap` function and passing the key map id we wish to use, and then bind a key combination using Bind and passing it the command we want to bind and the keys to use to call the command separated by commas. Do this after calling `setup_default_mapping`.  

Basically [`4coder_default_map.cpp`](code/custom/4coder_default_map.cpp)
Also, we need to remove the code that reads `bindings.4coder` file in `4coder_default_framework.cpp` in the `default_4coder_initialize` function, otherwise, it will overwrite the changes.
To remove it, just `#if 0` 

`code_map_id` inherits from `file_map_id`, which inherits from `global_map_id`   
That means that all `global_map_id` bindings are avilable in `file_map_id`, and all `file_map_id` bindings and those inherited from `global_map_id` are avilable in `code_map_id`   
It also means that if `setup_default_mapping` defines a binding in `code_map_id` and we want to use the same key combination in `file_map_id` or `global_map_id` it wouldn't work. We would need to comment the `code_map_id` binding in `setup_default_mapping`  

We can't set the same key binding for two different functions. For that we'll need to create a custom command. But we can set two different bindings to the same function

### Special bindings
BindTextInput -> to set which function should be called when text is inserted
BindMouse, BindMouseRelease -> to bind commands to mouse buttons
BindMouseWheel -> to bind commands to the mouse wheel rotation
BindMouseMove -> to bind commands to mouse movements
BindCore -> to bind non key events, such as a function to call on application startup or exit

## Bindings from scratch
If we wanted to redefine all the bindings, we can do the same as in [the previous section](#using-code-to-overwrite-key-bindings) but we have to remove the calls to `setup_default_mapping` and `setup_essential_mapping`. For this, we need to setup some bindings that are neccesary for 4coder to work correctly.   

I've made some changes to `custom_layer.cpp` and now can only open, list the commands and kill the current buffer and switch buffer (and close). There is no need for the code to ne in `custom_layer_init.cpp` function body, it just has to be after `SelectMapping`

## Defining new key maps
To define a new set of key maps, we onlu need to define a new id for each one of them using `vars_save_string_lit`. This function can be called after including `4coder_default_include.cpp`.

Example:
    String_ID map_id = vars_save_string_lit("name_for_a_map_id");

## Inheriting a key map
Selected key maps can inherit another key map, simply done by `ParentMap`
    SelectMap(file_map_id);
    ...
    ParentMap(global_map_id);

This will make all bindings from the global key map available in the file key map.   
Any binding from the child key map will overwrite it's parent.
Also, we need to call `SelectMap` on the parent map before being able to inherit it, because `SelectMap` is what actually creates the map

## Using key maps
For a key to be active, we need to attach it to a buffer. 
When `view_input_handler` hook receives an input (in the file `4coder_default_hooks.cpp`), it will retrieve the current key map associated to the current buffer, and search it for a command corresponding to the key pressed.   
It's possible to change the current key map attached to a buffer with the function `set_current_mapid`

