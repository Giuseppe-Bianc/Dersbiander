#pragma once
#include "Log.hpp"
#include "disableWarn.hpp"
#include "format.hpp"
#include "headers.hpp"

// On GCC < 4.8, the following define is often missing. Since
// this library only uses sleep_for, this should be safe
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 5 && __GNUC_MINOR__ < 8
#define _GLIBCXX_USE_NANOSLEEP
#endif

inline static constexpr long double MICROSENCONDSFACTOR = 1000.0L;
inline static constexpr long double MILLISENCONDSFACTOR = 1'000'000.0L;
inline static constexpr long double SENCONDSFACTOR = 1'000'000'000.0L;
inline static constexpr long MFACTOR = 100;

DISABLE_WARNINGS_PUSH(6005 26447 26455 26496)

// OLINTBEGIN(*-include-cleaner)
class Timer {  // NOLINT(*-special-member-functions)
protected:
    /// This is a typedef to make clocks easier to use
    using clock = std::chrono::high_resolution_clock;  // NOLINT(*-include-cleaner)
    using times = std::tuple<long double, long double, long double, long double, std::string, std::string, std::string,
                             std::string>;

    /// This typedef is for points in time
    using time_point = std::chrono::time_point<clock>;  // NOLINT(*-include-cleaner)

    /// This is the type of a printing function, you can make your own
    using time_print_t = std::function<std::string(std::string, std::string)>;  // NOLINT(*-include-cleaner)

    /// This is the title of the timer
    std::string title_;

    /// This is the function that is used to format most of the timing message
    time_print_t time_print_;

    /// This is the starting point (when the timer was created)
    time_point start_;

    /// This is the number of times cycles (print divides by this number)
    std::size_t cycles{1};

public:
    /// Standard print function, this one is set by default
    // NOLINTBEGIN
    static const std::string Simple(const std::string &title, const std::string &time) { return FORMAT("{}: {}", title, time); }

    static const std::string Big(const std::string &title, const std::string &time) {
        return FORMAT("-----------------------------------------\n| {} | Time = {}\n-----------------------------------------",
                        title, time);
    }
    // NOLINTEND

    /// Standard constructor, can set title and print function
    explicit Timer(const std::string &title = "Timer", const time_print_t &time_print = Simple)
      : title_(title), time_print_(time_print), start_(clock::now()) {}

    Timer(const Timer &other) = delete;              // Delete copy constructor
    Timer &operator=(const Timer &other) = delete;   // Delete copy assignment operator
    Timer(const Timer &&other) = delete;             // Delete move constructor
    Timer &operator=(const Timer &&other) = delete;  // Delete move assignment operator

    /// Time a function by running it multiple times. Target time is the len to target.
    [[nodiscard]] std::string time_it(const std::function<void()> &f,
                                      long double target_time = 1) {  // NOLINT(*-identifier-length)
        const time_point start = start_;
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.InnerPointer)
        [[maybe_unused]] auto total_time = C_LD(NAN);

        start_ = clock::now();
        std::size_t n = 0;  // NOLINT(*-identifier-length)
        do {                // NOLINT(*-avoid-do-while)
            f();
            std::chrono::duration<long double> elapsed = clock::now() - start_;
            total_time = elapsed.count();
        } while(n++ < MFACTOR && total_time < target_time);

        std::string out = FORMAT("{} for {} tries", make_time_str(total_time / static_cast<long double>(n)), std::to_string(n));
        start_ = start;
        return out;
    }

    [[nodiscard]] inline long double make_time() const noexcept {
        const std::chrono::duration<long double, std::nano> elapsed = clock::now() - start_;
        return elapsed.count();
    }

    // NOLINTBEGIN
    [[nodiscard]] static times make_named_times(long double time) {  // NOLINT(*-identifier-length)
        const auto &secondsTime = time / SENCONDSFACTOR;
        const auto &millisTime = time / MILLISENCONDSFACTOR;
        const auto &microTime = time / MICROSENCONDSFACTOR;
        return {secondsTime, millisTime, microTime, time, "s", "ms", "us", "ns"};
    }
    // NOLINTEND

    [[nodiscard]] times multi_time() const { return make_named_times(make_time()); }

    [[nodiscard]] static std::pair<long double, std::string> make_named_time(long double time) {
        const auto &[ld1, ld2, ld3, ld4, str1, str2, str3, str4] = make_named_times(time);
        // Accessing values
        if(ld1 > 1) [[likely]] {  // seconds
            return {ld1, str1};
        } else if(ld2 > 1) [[likely]] {  // milli
            return {ld2, str2};
        } else if(ld3 > 1) [[likely]] {  // micro
            return {ld3, str3};
        } else [[unlikely]] {
            return {ld4, str4};
        }
    }

    /// This formats the numerical value for the time string
    [[nodiscard]] inline std::string make_time_str() const {  // NOLINT(modernize-use-nodiscard)
        const long double time = make_time() / static_cast<long double>(cycles);
        return make_time_str(time);
    }

    // LCOV_EXCL_START
    /// This prints out a time string from a time
    [[nodiscard]] static inline std::string make_time_str(long double time) {  // NOLINT(modernize-use-nodiscard)
        const auto &[titme, stime] = make_named_time(time);
        return FORMAT("{:.f} {}", titme, stime);
    }
    // LCOV_EXCL_STOP

    /// This is the main function, it creates a string
    [[nodiscard]] inline std::string to_string() const noexcept {
        return std::invoke(time_print_, title_, make_time_str());
    }  // NOLINT(modernize-use-nodiscard)

    /// Division sets the number of cycles to divide by (no graphical change)
    Timer &operator/(std::size_t val) noexcept {
        cycles = val;
        return *this;
    }
};

/// This class prints out the time upon destruction
class AutoTimer : public Timer {
public:
    /// Reimplementing the constructor is required in GCC 4.7
    explicit AutoTimer(const std::string &title = "Timer", const time_print_t &time_print = Simple) : Timer(title, time_print) {}

    // GCC 4.7 does not support using inheriting constructors.
    AutoTimer(const AutoTimer &other) = delete;              // Delete copy constructor
    AutoTimer &operator=(const AutoTimer &other) = delete;   // Delete copy assignment operator
    AutoTimer(const AutoTimer &&other) = delete;             // Delete move constructor
    AutoTimer &operator=(const AutoTimer &&other) = delete;  // Delete move assignment operator

    /// This destructor prints the string
    ~AutoTimer() { LINFO(to_string()); }
};

template <> struct fmt::formatter<Timer> : formatter<std::string_view> { // NOLINT(*-include-cleaner)
    template <typename FormatContext> auto format(const Timer &timer, FormatContext &ctx) {
        return formatter<std::string_view>::format(timer.to_string(), ctx);
    }
};
// OLINTEND
DISABLE_WARNINGS_POP()
