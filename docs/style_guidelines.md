---
permalink: style-guidelines.html
title: Code Style Guidelines
---

{% include shared.html %}
{% include menu.html %}

# Style guidelines

### Source files

All source files __must__:

* use a tab of 4 spaces.
* use Unix line endings.
* be prefixed with `kmz_`.

### Structs

All exposed structs __must__:

* be named using snake casing.
* be suffixed with `_t`.
* be prefixed with `kmz_`.
* include the opening parenthesis (`{`) on the same line as the struct identifier.
* include a `typedef` following the struct declaration with the struct identifier converted to __Pascal Case excluding the trailing t__.
* use the doxygen `@const` tag on fields that are read-only.
* prefix non-public fields with `_`.
  * Example:
    ```c
    struct kmz_my_struct_t {
        /** @const */
        int _var;
    };
    typedef struct kmz_my_struct_t KmzMyStruct;
    ```
* provide a __macro constructor__ if the struct represents a value type.
  * Example:
    ```c
    struct kmz_my_value_struct_t {
        int var_1, var_2;
    };
    typedef struct kmz_my_value_struct_t KmzMyValueStruct;
    
    #define my_value_struct(var_1, var_2) (MyValueStruct) {var_1,var_2}
    ```

### Constructors

All exposed struct constructors __must__:

* follow all [method naming conventions](#methods).
* be prefixed with `from_` immediately following the common method prefix.
* return `<struct>` or `<struct> *`.
  * Example:
    ```c
    KmzMyStruct * KmzMyStruct__from_int(int var) {
        KmzMyStruct * me = malloc(sizeof(KmzMyStruct));
        return me;
    }
    ```

### Methods

All exposed struct methods __must__:

* be __declared in a header__ and __defined in a source file__.
* be named using snake casing.
* be prefixed with the `typedef` identifier of the struct followed by `__`.
* have a first parameter of `<struct> me` or `<struct> * me`.
  * Example:
    ```c
    int KmzMyStruct__get_var(KmzMyStruct * me);
    ```
* include the opening parenthesis (`{`) on the same line as the method identifier in the source file.
  * Example:
    ```c
    int KmzMyStruct__get_var(KmzMyStruct * me) {
        return me->_var;
    }
    ```

### Constants

All exposed struct constants __must__:

* be declared with the modifier `static const`.
* be named using upper snake casing.
* be prefixed with the `typedef` identifier of the struct followed by `__`.
  * Example:
    ```c
    static const int KmzMyStruct__MY_CONSTANT = 0;
    ```
    
### Macros

All exposed macros that are designed to be used in code __must__:

* be named using lower snake casing.
* be defined as a function macro.
* be prefixed with `kmz__`.
  * Example:
    ```c
    #define kmz__my_macro(arg1)
    ```
* define a name for any varargs expected.
  * Example:
    ```c
    #define kmz_my_vararg_macro(args...)
    ```
