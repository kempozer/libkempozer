#ifndef kmz_numerics_h
#define kmz_numerics_h

// region Types:
typedef float kmz_percent;
typedef uint8_t kmz_channel;

enum kmz_bool_t {
    KMZ_FALSE = 0,
    KMZ_TRUE = 1,
};
typedef enum kmz_bool_t KmzBool;
// endregion;

// region Helpers:

#define kmz__between(val, in_min, ex_max) val >= in_min && val < ex_max
#define kmz__clamp(val, min, max) val < min ? min : (val > max ? max : val)
// endregion;

#endif /* kmz_numerics_h */
