#pragma once

#if defined(__clang__)
// Clang/LLVM
#define ATTR_ALIGNED(n) __attribute__((aligned(n)))
#define ATTR_ALLOCATE(segname) __attribute__((section(segname)))
#define ATTR_ALLOCATOR __attribute__((allocator))
#define ATTR_APPDOMAIN __attribute__((annotate("appdomain")))
#define ATTR_COLD __attribute__((cold))
#define ATTR_CODE_SEG(segname) __attribute__((section(segname)))
#define ATTR_DEPRECATED(msg) [[deprecated(msg)]]
#define ATTR_DLLIMPORT __attribute__((dllimport))
#define ATTR_DLLEXPORT __attribute__((dllexport))
#define ATTR_EMPTY_BASES __attribute__((__empty_bases__))
#define ATTR_FORMAT(fmt, args) __attribute__((format(printf, fmt, args)))
#define ATTR_HOT __attribute__((hot))
#define ATTR_JITINTRINSIC __attribute__((jitintrinsic))
#define ATTR_NAKED __attribute__((naked))
#define ATTR_NOALIAS __attribute__((__may_alias__))
#define ATTR_NOINLINE __attribute__((noinline))
#define ATTR_NODISCARD [[nodiscard]]
#define ATTR_NORETURN __attribute__((noreturn))
#define ATTR_NOTHROW noexcept
#define ATTR_NO_SANITIZE_ADDRESS __attribute__((no_sanitize("address")))
#define ATTR_NOVTABLE
#define ATTR_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#define ATTR_PACKED __attribute__((packed))
#define ATTR_PURE __attribute__((pure))
#define ATTR_PROCESS
#define ATTR_PROPERTY(getFunc, putFunc) M
#define ATTR_RESTRICT __restrict__
#define ATTR_SAFEBUFFERS
#define ATTR_SELECTANY
#define ATTR_SPECTRE_NOMITIGATION
#define ATTR_THREAD __thread
#define ATTR_UUID(guid)
#define ATTR_UNUSED __attribute__((unused))
#define ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#elif defined(__GNUC__) || defined(__GNUG__)
// GCC
#define ATTR_ALIGNED(n) __attribute__((aligned(n)))
#define ATTR_ALLOCATE(segname) __attribute__((section(segname)))
#define ATTR_ALLOCATOR __attribute__((allocator))
#define ATTR_APPDOMAIN __attribute__((annotate("appdomain")))
#define ATTR_CODE_SEG(segname) __attribute__((section(segname)))
#define ATTR_COLD __attribute__((cold))
#define ATTR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#define ATTR_DLLIMPORT __attribute__((dllimport))
#define ATTR_DLLEXPORT __attribute__((dllexport))
#define ATTR_EMPTY_BASES __declspec(empty_bases)
#define ATTR_FORMAT(fmt, args) __attribute__((format(printf, fmt, args)))
#define ATTR_HOT __attribute__((hot))
#define ATTR_JITINTRINSIC __declspec(jitintrinsic)
#define ATTR_MAY_ALIAS __attribute__((may_alias))
#define ATTR_NAKED __attribute__((naked))
#define ATTR_NOALIAS __attribute__((__may_alias__))
#define ATTR_NOINLINE __attribute__((noinline))
#define ATTR_NODISCARD __attribute__((warn_unused_result))
#define ATTR_NO_RETURN __attribute__((noreturn))
#define ATTR_NO_SANITIZE_ADDRESS __attribute__((no_sanitize("address")))
#define ATTR_NOTHROW noexcept
#define ATTR_NOVTABLE __declspec(novtable)
#define ATTR_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#define ATTR_PACKED __attribute__((packed))
#define ATTR_PROCESS
#define ATTR_PROPERTY(getFunc, putFunc) __declspec(property(get = getFunc, put = putFunc))
#define ATTR_RESTRICT __restrict__
#define ATTR_SAFEBUFFERS
#define ATTR_SELECTANY __declspec(selectany)
#define ATTR_SPECTRE_NOMITIGATION
#define ATTR_THREAD __thread
#define ATTR_UNSED __attribute__((unused))
#define ATTR_UUID(guid) __declspec(uuid(guid))
#define ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#elif defined(_MSC_VER)
// MSVC
#define ATTR_ALIGNED(n) __declspec(align(n))
#define ATTR_ALLOCATE(segname) __declspec(allocate(segname))
#define ATTR_ALLOCATOR __declspec(allocator)
#define ATTR_APPDOMAIN __declspec(appdomain)
#define ATTR_CODE_SEG(segname) __declspec(code_seg(segname))
#define ATTR_COLD __declspec(cold)
#define ATTR_DEPRECATED(msg) __declspec(deprecated(msg))
#define ATTR_DLLIMPORT __declspec(dllimport)
#define ATTR_DLLEXPORT __declspec(dllexport)
#define ATTR_EMPTY_BASES __declspec(empty_bases)
#define ATTR_FORMAT(fmt, args) __format_string(fmt, args)
#define ATTR_HOT __declspec(noinline)
#define ATTR_JITINTRINSIC __declspec(jitintrinsic)
#define ATTR_MAY_ALIAS __declspec(noalias)
#define ATTR_NOALIAS __declspec(noalias)
#define ATTR_NOINLINE __declspec(noinline)
#define ATTR_NAKED __declspec(naked)
#define ATTR_NODISCARD _Check_return_
#define ATTR_NO_RETURN __declspec(noreturn)
#define ATTR_NO_SANITIZE_ADDRESS __declspec(no_sanitize_address)
#define ATTR_NOTHROW noexcept
#define ATTR_NOVTABLE __declspec(novtable)
#define ATTR_NONNULL(...)
#define ATTR_PACKED
#define ATTR_PROCESS __declspec(process)
#define ATTR_PROPERTY(getFunc, putFunc) __declspec(property(get = getFunc, put = putFunc))
#define ATTR_RESTRICT __declspec(restrict)
#define ATTR_SAFEBUFFERS __declspec(safebuffers)
#define ATTR_SELECTANY __declspec(selectany)
#define ATTR_SPECTRE_NOMITIGATION __declspec(spectre(nomitigation))
#define ATTR_THREAD __declspec(thread)
#define ATTR_UNUSED __pragma(warning(suppress : 4100 4101))
#define ATTR_UUID(guid) __declspec(uuid(guid))
#define ATTR_WARN_UNUSED_RESULT
#elif defined(__MINGW32__) || defined(__MINGW64__)
// MinGW
#define ATTR_ALIGNED(n) __attribute__((aligned(n)))
#define ATTR_ALLOCATE(segname) __attribute__((section(segname)))
#define ATTR_ALLOCATOR __attribute__((allocator))
#define ATTR_APPDOMAIN __attribute__((annotate("appdomain")))
#define ATTR_CODE_SEG(segname) __attribute__((section(segname)))
#define ATTR_COLD __attribute__((cold))
#define ATTR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#define ATTR_DLLIMPORT __attribute__((dllimport))
#define ATTR_DLLEXPORT __attribute__((dllexport))
#define ATTR_EMPTY_BASES
#define ATTR_FORMAT(fmt, args) __attribute__((format(printf, fmt, args)))
#define ATTR_HOT __attribute__((hot))
#define ATTR_JITINTRINSIC
#define ATTR_MAY_ALIAS __attribute__((may_alias))
#define ATTR_NAKED __attribute__((naked))
#define ATTR_NOALIAS __attribute__((__may_alias__))
#define ATTR_NOINLINE __attribute__((noinline))
#define ATTR_NODISCARD __attribute__((warn_unused_result))
#define ATTR_NO_RETURN __attribute__((noreturn))
#define ATTR_NOTHROW noexcept
#define ATTR_NO_SANITIZE_ADDRESS
#define ATTR_NO_SANITIZE_THREAD
#define ATTR_NOVTABLE
#define ATTR_NULLABLE __nullable
#define ATTR_PACKED __attribute__((packed))
#define ATTR_PROCESS
#define ATTR_PROPERTY(getFunc, putFunc)
#define ATTR_RESTRICT __restrict__
#define ATTR_SAFEBUFFERS
#define ATTR_SELECTANY
#define ATTR_SPECTRE_NOMITIGATION
#define ATTR_THREAD __thread
#define ATTR_UNUSED __attribute__((unused))
#define ATTR_UUID(guid)
#define ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))

#else
// Unknown compiler
#define ATTR_ALIGNED(n)
#define ATTR_ALLOCATE(segname)
#define ATTR_ALLOCATOR
#define ATTR_APPDOMAIN
#define ATTR_COLD
#define ATTR_DEPRECATED(msg)
#define ATTR_DLLIMPORT
#define ATTR_DLLEXPORT
#define ATTR_EMPTY_BASES
#define ATTR_FORMAT(fmt, args)
#define ATTR_HOT
#define ATTR_JITINTRINSIC
#define ATTR_MAY_ALIAS
#define ATTR_NAKED
#define ATTR_NOALIAS
#define ATTR_NOINLINE
#define ATTR_NODISCARD
#define ATTR_NORETURN
#define ATTR_NOTHROW
#define ATTR_NO_SANITIZE_ADDRESS
#define ATTR_NOVTABLE
#define ATTR_NONNULL(...)
#define ATTR_PACKED
#define ATTR_PROCESS
#define ATTR_PROPERTY(getFunc, putFunc)
#define ATTR_RESTRICT
#define ATTR_SAFEBUFFERS
#define ATTR_SELECTANY
#define ATTR_SPECTRE_NOMITIGATION
#define ATTR_THREAD
#define ATTR_UUID(guid)
#define ATTR_UNUSED
#define ATTR_WARN_UNUSED_RESULT
#endif
