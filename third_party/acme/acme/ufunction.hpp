// ufunction v1.0
//
// unique_function - a std::function replacement with two notable features
// 1. not copyable (you can capture unique_ptr)
// 2. noexcept move constructible
//
// MIT License:
// Copyright(c) 2020 Borislav Stanimirov
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files(the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions :
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
#pragma once

#include <functional>
#include <type_traits>

namespace acme
{

template <typename F>
class ufunction : private std::function<F>
{
    using function = std::function<F>;
public:
    ufunction() noexcept = default;

    ufunction(std::nullptr_t) noexcept : function(nullptr) {}
    ufunction& operator=(std::nullptr_t) noexcept { function::operator=(nullptr); return *this; }

    ufunction(const ufunction&) = delete;
    ufunction operator=(const ufunction&) = delete;

    ufunction(ufunction&&) noexcept = default;
    ufunction& operator=(ufunction&&) noexcept = default;

    template <typename FO>
    ufunction(FO&& f) noexcept : function(copy_wrapper<FO>{std::move(f)}) {}

    template <typename FO>
    ufunction& operator=(FO&& f) noexcept
    {
        function::operator=(copy_wrapper<FO>{std::move(f)});
        return *this;
    }

    using function::operator bool;
    using function::operator();
private:
    template <typename FO>
    struct copy_wrapper
    {
        static_assert(!std::is_const_v<FO>, "Cannot bind to a const function");

        FO func_object;
        copy_wrapper(FO&& f) : func_object(std::move(f)) {}

        // should never get to any of the following two
        // but we need them to compile
        copy_wrapper(const copy_wrapper& other) : func_object(const_cast<FO&&>(other.func_object)) { throw 0; }
        copy_wrapper& operator=(const copy_wrapper&) { throw 0; }

        // not `= default` so we can force noexcept
        copy_wrapper(copy_wrapper&& other) noexcept : func_object(std::move(other.func_object)) {}
        copy_wrapper& operator=(copy_wrapper&& other) noexcept
        {
            func_object = std::move(other.func_object);
            return *this;
        }

        template <typename... Args>
        auto operator()(Args&&... args) { return func_object(std::forward<Args>(args)...); }
    };
};

}
