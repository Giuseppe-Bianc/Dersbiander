#pragma once

#include "format.hpp" // NOLINT(*-include-cleaner)
#include "glm_matld.hpp" // NOLINT(*-include-cleaner)

// #define PRETTY_PRINT

#define GLMP_FUN_QUAL GLM_FUNC_QUALIFIER
namespace glmp {
    namespace detail {

        static inline constexpr const char *LabelTrue = "true";
        static inline constexpr const char *LabelFalse = "false";

        template <typename T> struct TypePrefix {
            static constexpr char const *value = "";
        };

        template <> struct TypePrefix<float> {
            static constexpr char const *value = "";
        };

        template <> struct TypePrefix<double> {
            static constexpr char const *value = "d";
        };
        template <> struct TypePrefix<long double> {
            static constexpr char const *value = "ld";
        };

        template <> struct TypePrefix<bool> {
            static constexpr char const *value = "b";
        };

        template <> struct TypePrefix<uint8_t> {
            static constexpr char const *value = "u8";
        };

        template <> struct TypePrefix<int8_t> {
            static constexpr char const *value = "i8";
        };

        template <> struct TypePrefix<uint16_t> {
            static constexpr char const *value = "u16";
        };

        template <> struct TypePrefix<int16_t> {
            static constexpr char const *value = "i16";
        };

        template <> struct TypePrefix<uint32_t> {
            static constexpr char const *value = "u";
        };

        template <> struct TypePrefix<int32_t> {
            static constexpr char const *value = "i";
        };

        template <> struct TypePrefix<uint64_t> {
            static constexpr char const *value = "u64";
        };

        template <> struct TypePrefix<int64_t> {
            static constexpr char const *value = "i64";
        };

        template <typename T> struct prefix {
            static constexpr char const *value() { return TypePrefix<T>::value; }
        };

        template <typename matType> struct compute_to_string {};

        template <glm::qualifier Q> struct compute_to_string<glm::vec<1, bool, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<1, bool, Q> const &x) {
                return FORMAT("bvec1({})", x[0] ? detail::LabelTrue : detail::LabelFalse);
            }
        };

        template <glm::qualifier Q> struct compute_to_string<glm::vec<2, bool, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<2, bool, Q> const &x) {
                return FORMAT("bvec2({}, {})", x[0] ? detail::LabelTrue : detail::LabelFalse,
                                x[1] ? detail::LabelTrue : detail::LabelFalse);
            }
        };

        template <glm::qualifier Q> struct compute_to_string<glm::vec<3, bool, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<3, bool, Q> const &x) {
                return FORMAT("bvec3({}, {}, {})", x[0] ? detail::LabelTrue : detail::LabelFalse,
                                x[1] ? detail::LabelTrue : detail::LabelFalse, x[2] ? detail::LabelTrue : detail::LabelFalse);
            }
        };

        template <glm::qualifier Q> struct compute_to_string<glm::vec<4, bool, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<4, bool, Q> const &x) {
                return FORMAT("bvec4({}, {}, {}, {})", x[0] ? detail::LabelTrue : detail::LabelFalse,
                                x[1] ? detail::LabelTrue : detail::LabelFalse, x[2] ? detail::LabelTrue : detail::LabelFalse,
                                x[3] ? detail::LabelTrue : detail::LabelFalse);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::vec<1, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<1, T, Q> const &x) {
                return FORMAT("{}vec1({})", prefix<T>::value(), x[0]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::vec<2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<2, T, Q> const &x) {
                return FORMAT("{}vec2({}, {})", prefix<T>::value(), x[0], x[1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::vec<3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<3, T, Q> const &x) {
                return FORMAT("{}vec3({}, {}, {})", prefix<T>::value(), x[0], x[1], x[2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::vec<4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::vec<4, T, Q> const &x) {
                return FORMAT("{}vec4({}, {}, {}, {})", prefix<T>::value(), x[0], x[1], x[2], x[3]);
            }
        };
#ifdef PRETTY_PRINT
        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<2, 2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<2, 2, T, Q> const &x) {
                return FORMAT("{}mat2x2(({},{}),\n ({},{})) ", prefix<T>::value(), x[0][0], x[0][1], x[1][0], x[1][1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<2, 3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<2, 3, T, Q> const &x) {
                return FORMAT("{}mat2x3(({}, {}, {}),\n ({}, {}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[1][0],
                                x[1][1], x[1][2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<2, 4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<2, 4, T, Q> const &x) {
                return FORMAT("{}mat2x4(({}, {}, {}, {}),\n ({}, {}, {}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[0][2],
                                x[0][3], x[1][0], x[1][1], x[1][2], x[1][3]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<3, 2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<3, 2, T, Q> const &x) {
                return FORMAT("{}mat3x2(({}, {}),\n ({}, {}),\n ({}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[1][0],
                                x[1][1], x[2][0], x[2][1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<3, 3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<3, 3, T, Q> const &x) {
                return FORMAT("{}mat3x3(({}, {}, {}),\n ({}, {}, {}),\n ({}, {}, {}))", prefix<T>::value(), x[0][0], x[0][1],
                                x[0][2], x[1][0], x[1][1], x[1][2], x[2][0], x[2][1], x[2][2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<3, 4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<3, 4, T, Q> const &x) {
                return FORMAT("{}mat3x4(({}, {}, {}, {}),\n ({}, {}, {}, {}),\n ({}, "
                                "{}, {}, {}))",
                                prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3],
                                x[2][0], x[2][1], x[2][2], x[2][3]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<4, 2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<4, 2, T, Q> const &x) {
                return FORMAT("{}mat4x2(({}, {}),\n ({}, {}),\n ({}, {}),\n ({}, {}))", prefix<T>::value(), x[0][0], x[0][1],
                                x[1][0], x[1][1], x[2][0], x[2][1], x[3][0], x[3][1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<4, 3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<4, 3, T, Q> const &x) {
                return FORMAT("{}mat4x3(({}, {}, {}),\n ({}, {}, {}),\n ({}, {}, {}),\n "
                                "({}, {}, {}))",
                                prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[1][0], x[1][1], x[1][2], x[2][0], x[2][1],
                                x[2][2], x[3][0], x[3][1], x[3][2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<4, 4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<4, 4, T, Q> const &x) {
                return FORMAT("{}mat4x4(({}, {}, {}, {}),\n ({}, {}, {}, {}),\n ({}, {}, {}, "
                                "{}),\n ({}, {}, {}, {}))",
                                prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3],
                                x[2][0], x[2][1], x[2][2], x[2][3], x[3][0], x[3][1], x[3][2], x[3][3]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::qua<T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::qua<T, Q> const &q) {  // NOLINT(*-identifier-length)
                return FORMAT("{}quat({}, [{}, {}, {}])", prefix<T>::value(), q.w, q.x, q.y, q.z);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::tdualquat<T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::tdualquat<T, Q> const &x) {
                return FORMAT("{}dualquat(({}, [{}, {}, {}]),\n ({}, [{}, {}, {}]))", prefix<T>::value(), x.real.w, x.real.x,
                                x.real.y, x.real.z, x.dual.w, x.dual.x, x.dual.y, x.dual.z);
            }
        };
#else
        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<2, 2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<2, 2, T, Q> const &x) {
                return FORMAT("{}mat2x2(({},{}), ({},{})) ", prefix<T>::value(), x[0][0], x[0][1], x[1][0], x[1][1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<2, 3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<2, 3, T, Q> const &x) {
                return FORMAT("{}mat2x3(({}, {}, {}), ({}, {}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[1][0],
                                x[1][1], x[1][2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<2, 4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<2, 4, T, Q> const &x) {
                return FORMAT("{}mat2x4(({}, {}, {}, {}), ({}, {}, {}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[0][2],
                                x[0][3], x[1][0], x[1][1], x[1][2], x[1][3]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<3, 2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<3, 2, T, Q> const &x) {
                return FORMAT("{}mat3x2(({}, {}), ({}, {}), ({}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[1][0], x[1][1],
                                x[2][0], x[2][1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<3, 3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<3, 3, T, Q> const &x) {
                return FORMAT("{}mat3x3(({}, {}, {}), ({}, {}, {}), ({}, {}, {}))", prefix<T>::value(), x[0][0], x[0][1],
                                x[0][2], x[1][0], x[1][1], x[1][2], x[2][0], x[2][1], x[2][2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<3, 4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<3, 4, T, Q> const &x) {
                return FORMAT("{}mat3x4(({}, {}, {}, {}), ({}, {}, {}, {}), ({}, "
                                "{}, {}, {}))",
                                prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3],
                                x[2][0], x[2][1], x[2][2], x[2][3]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<4, 2, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<4, 2, T, Q> const &x) {
                return FORMAT("{}mat4x2(({}, {}), ({}, {}), ({}, {}), ({}, {}))", prefix<T>::value(), x[0][0], x[0][1], x[1][0],
                                x[1][1], x[2][0], x[2][1], x[3][0], x[3][1]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<4, 3, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<4, 3, T, Q> const &x) {
                return FORMAT("{}mat4x3(({}, {}, {}), ({}, {}, {}), ({}, {}, {}), "
                                "({}, {}, {}))",
                                prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[1][0], x[1][1], x[1][2], x[2][0], x[2][1],
                                x[2][2], x[3][0], x[3][1], x[3][2]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::mat<4, 4, T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::mat<4, 4, T, Q> const &x) {
                return FORMAT("{}mat4x4(({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, "
                                "{}), ({}, {}, {}, {}))",
                                prefix<T>::value(), x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3],
                                x[2][0], x[2][1], x[2][2], x[2][3], x[3][0], x[3][1], x[3][2], x[3][3]);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::qua<T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::qua<T, Q> const &q) {  // NOLINT(*-identifier-length)
                return FORMAT("{}quat({}, [{}, {}, {}])", prefix<T>::value(), q.w, q.x, q.y, q.z);
            }
        };

        template <typename T, glm::qualifier Q> struct compute_to_string<glm::tdualquat<T, Q> > {
            [[nodiscard]] GLMP_FUN_QUAL static std::string call(glm::tdualquat<T, Q> const &x) {
                return FORMAT("{}dualquat(({}, [{}, {}, {}]), ({}, [{}, {}, {}]))", prefix<T>::value(), x.real.w, x.real.x,
                                x.real.y, x.real.z, x.dual.w, x.dual.x, x.dual.y, x.dual.z);
            }
        };
#endif  // PRETY_PRINT

    }  // namespace detail

    template <class matType> [[nodiscard]] GLMP_FUN_QUAL std::string to_string(matType const &x) {
        return detail::compute_to_string<matType>::call(x);
    }
}  // namespace glmp
