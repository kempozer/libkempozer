---
permalink: style_guidelines.html
title: Code Style Guidelines
---

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
* include a `typedef` following the struct declaration with the struct identifier converted to __Pascal Case excluding the trailing t__.
  * Example:
    ```c
    struct kmz_my_struct_t {
    };
    typedef struct kmz_my_struct_t KmzMyStruct;
    ```

### Constructors

All exposed struct constructors __must__:

* follow all [method style conventions](#methods).
* be prefixed with `from_` immediately following the common method prefix.
* return the type by __value__.

### Methods

All exposed struct methods __must__:

* be named using snake casing.
* be prefixed with the `typedef` identifier of the struct followed by `__`.
  * Example:
    ```c
    int KmzMyStruct__get_var(KmzMyStruct * me);
    ```
* have a first parameter of `<struct> me` or `<struct> * me`.

### Constants

All exposed struct constants __must__:

* be declared with the modifier `static const`.
* be named using upper snake casing.
* be prefixed with the `typedef` identifier of the struct followed by `__`.
  * Example:
    ```c
    static const int KmzMyStruct__MY_CONSTANT = 0;
    ```
