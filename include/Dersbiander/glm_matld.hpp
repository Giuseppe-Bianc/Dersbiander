#pragma once
#define GLM_FORCE_INTRINSICS
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_WIN32
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_FORCE_PURE
#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_CXX20
#define GLM_FORCE_UNRESTRICTED_GENTYPE
#define GLM_FORCE_PRECISION_HIGHP_DOUBLE
#define GLM_FORCE_PRECISION_HIGHP_FLOAT
#define GLM_FORCE_PRECISION_HIGHP_INT
#define GLM_FORCE_PRECISION_HIGHP_UINT

#include "disableWarn.hpp"
// clang-format off
DISABLE_WARNINGS_PUSH(
        4005 4201 4459 4514 4625 4626 4820
        6244 6285 6385 6386 26409 26415 26418
        26429 26432 26437 26438 26440 26446 26447
        26450 26451 26455 26457 26459 26460 26461
        26467 26472 26473 26474 26475 26481 26482
        26485 26490 26491 26493 26494 26495 26496
        26497 26498 26800 26814 26818 26826)

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/fast_square_root.hpp> // fastNormalize
// clang-format on
#include "casts.hpp"
// Restore warning levels.
DISABLE_WARNINGS_POP()
namespace glm {
    using lowp_ldvec1 = vec<1, long double, lowp>;
    using lowp_ldvec2 = vec<2, long double, lowp>;
    using lowp_ldvec3 = vec<3, long double, lowp>;
    using lowp_ldvec4 = vec<4, long double, lowp>;

    using mediump_ldvec1 = vec<1, long double, mediump>;
    using mediump_ldvec2 = vec<2, long double, mediump>;
    using mediump_ldvec3 = vec<3, long double, mediump>;
    using mediump_ldvec4 = vec<4, long double, mediump>;

    using highp_ldvec1 = vec<1, long double, highp>;
    using highp_ldvec2 = vec<2, long double, highp>;
    using highp_ldvec3 = vec<3, long double, highp>;
    using highp_ldvec4 = vec<4, long double, highp>;

    using ldvec1 = vec<1, long double, defaultp>;
    using ldvec2 = vec<2, long double, defaultp>;
    using ldvec3 = vec<3, long double, defaultp>;
    using ldvec4 = vec<4, long double, defaultp>;

    using lowp_ldmat2 = mat<2, 2, long double, lowp>;
    using lowp_ldmat3 = mat<3, 3, long double, lowp>;
    using lowp_ldmat4 = mat<4, 4, long double, lowp>;

    using mediump_ldmat2 = mat<2, 2, long double, mediump>;
    using mediump_ldmat3 = mat<3, 3, long double, mediump>;
    using mediump_ldmat4 = mat<4, 4, long double, mediump>;

    using highp_ldmat2 = mat<2, 2, long double, highp>;
    using highp_ldmat3 = mat<3, 3, long double, highp>;
    using highp_ldmat4 = mat<4, 4, long double, highp>;

    using ldmat2 = mat<2, 2, long double, defaultp>;
    using ldmat3 = mat<3, 3, long double, defaultp>;
    using ldmat4 = mat<4, 4, long double, defaultp>;
    using lowp_ldmat2x2 = mat<2, 2, long double, lowp>;
    using lowp_ldmat2x3 = mat<2, 3, long double, lowp>;
    using lowp_ldmat2x4 = mat<2, 4, long double, lowp>;
    using lowp_ldmat3x2 = mat<3, 2, long double, lowp>;
    using lowp_ldmat3x3 = mat<3, 3, long double, lowp>;
    using lowp_ldmat3x4 = mat<3, 4, long double, lowp>;
    using lowp_ldmat4x2 = mat<4, 2, long double, lowp>;
    using lowp_ldmat4x3 = mat<4, 3, long double, lowp>;
    using lowp_ldmat4x4 = mat<4, 4, long double, lowp>;

    using mediump_ldmat2x2 = mat<2, 2, long double, mediump>;
    using mediump_ldmat2x3 = mat<2, 3, long double, mediump>;
    using mediump_ldmat2x4 = mat<2, 4, long double, mediump>;
    using mediump_ldmat3x2 = mat<3, 2, long double, mediump>;
    using mediump_ldmat3x3 = mat<3, 3, long double, mediump>;
    using mediump_ldmat3x4 = mat<3, 4, long double, mediump>;
    using mediump_ldmat4x2 = mat<4, 2, long double, mediump>;
    using mediump_ldmat4x3 = mat<4, 3, long double, mediump>;
    using mediump_ldmat4x4 = mat<4, 4, long double, mediump>;

    using highp_ldmat2x2 = mat<2, 2, long double, highp>;
    using highp_ldmat2x3 = mat<2, 3, long double, highp>;
    using highp_ldmat2x4 = mat<2, 4, long double, highp>;
    using highp_ldmat3x2 = mat<3, 2, long double, highp>;
    using highp_ldmat3x3 = mat<3, 3, long double, highp>;
    using highp_ldmat3x4 = mat<3, 4, long double, highp>;
    using highp_ldmat4x2 = mat<4, 2, long double, highp>;
    using highp_ldmat4x3 = mat<4, 3, long double, highp>;
    using highp_ldmat4x4 = mat<4, 4, long double, highp>;

    using ldmat2x2 = mat<2, 2, long double, defaultp>;
    using ldmat3x2 = mat<3, 2, long double, defaultp>;
    using ldmat4x2 = mat<4, 2, long double, defaultp>;
    using ldmat2x3 = mat<2, 3, long double, defaultp>;
    using ldmat3x3 = mat<3, 3, long double, defaultp>;
    using ldmat4x3 = mat<4, 3, long double, defaultp>;
    using ldmat2x4 = mat<2, 4, long double, defaultp>;
    using ldmat3x4 = mat<3, 4, long double, defaultp>;
    using ldmat4x4 = mat<4, 4, long double, defaultp>;
}  // namespace glm
