//
// Created on 2025/11/18.
//

#ifndef LIBRARYMANAGEMENT_DATA_STRUCT_HPP
#define LIBRARYMANAGEMENT_DATA_STRUCT_HPP

#include <vector>
#include <array>
#include <string>
#include <stdexcept>
#include <iostream>

#include "array_view.hpp"

namespace Utils {

    struct DoMainKeyExist {
        template<class Array>
        inline bool operator()(const Array &arr) const {
            return !arr[0].empty();
        }
    };

    /**
     * @brief @c InfoEntry : a class managing structured data with enum-based keys
     *
     * <p>This structure encapsulates a standard array to guarantee continuous memory storage
     * for its values, offering significant efficiency gains in I/O and performance-critical
     * scenarios due to memory locality.</p>
     *
     * <p>It acts as a high-performance alternative to maps or structs where keys are guaranteed
     * to be compile-time constants.</p>
     *
     * @tparam T_ Type of elements
     * @tparam EnumClass_ An enum class of @c keys. It should include a @c KEY_COUNT member at
     * the end to sign the count of keys
     * @tparam ValidChecker_ A @c bool(Array) functor to check if the structured data is valid.
     * Default value: @c DoMainKeyExist which will call the @c empty() method of the first element
     * (index 0, seen as the main key)
     *
     * <p>The @b requirement of the template param @c EnumClass_ includes:</p>
     *
     * <ul>
     * <li>it should includes a member @c KEY_COUNT at the end, signing the count of the keys</li>
     * <li>besides @c KEY_COUNT , it should include at least 1 more keys</li>
     * </ul>
     *
     * <p>The first key will be considered as the @b main key. If the value of first Key is empty or invalid, the whole
     * entry will be identified as invalid.</p>
     *
     * <p>By default, the template will use the functor @c DoMainKeyExist to call @c empty() of the first element and return
     * its opposite value, that is to check if the main key is valid indicating if the whole entry is valid.</p>
     */
    template <class T_,
              class EnumClass_,
              class ValidChecker_ = DoMainKeyExist >
    class InfoEntry {
    public:

        /**
         * @brief @c ::Key : Alias of the enum class, which defines keys
         */
        using Key = EnumClass_;

        /**
         * @brief @c KEYCOUNT : A constant recording the count of the keys
         */
        static constexpr std::size_t KEYCOUNT = static_cast<std::size_t>(Key::KEY_COUNT);

        /**
         * @brief @c checker : A static const member, the instance of the functor @c ValidChecker_
         *
         * Used for checking if the structured data is valid.
         */
        static const ValidChecker_ checker;

        /**
         * @brief @c ::UseCopyTag & @c ::UseMoveTag : The tag types use to call different version of overloaded constructors,
         * determining whether the constructor @b copys or @b moves the received elements to its internal array.
         */
        struct UseCopyTag {};
        struct UseMoveTag {};

        // the class requires the number of keys (except for `KEY_COUNT`) should be at least 1
        static_assert(KEYCOUNT > 0, "The number of key should be at least 1!");
    private:

        // the internal array
        std::array<T_, static_cast<std::size_t>(Key::KEY_COUNT)> m_arr;

    public:

        /**
         * @b The default constructor of @c InfoEntry , constructing an empty (invalid) entry
         */
        InfoEntry() : m_arr() {}


        /**
         * @brief Receive a range of array to construct the entry
         *
         * @param ArrayView The pointer range of the space of array
         *
         * @note The contructor will use copy semantics, that is to copy the elements from the ranges to
         * the entry
         *
         * @see <code>IntroEntry(ArrayView&lt;T_>, UseCopyTag)</code> & <code>IntroEntry(ArrayView&lt;T_>, UseMoveTag)</code>
         */
        explicit InfoEntry(ArrayView<T_> ArrayView);

        /**
         * @brief Receive a range of array to construct the entry, explicitly using @b copy semantics
         *
         * @param ArrayView The pointer range of the space of array
         * @param useCopy The object inner struct of @c ::UseCopyTag . Use @c ::UseCopyTag{} to construct an empty
         * object
         *
         * @note The contructor will use copy semantics, that is to copy the elements from the ranges to
         * the entry
         *
         * <p>The second param requires an random object of inner struct type @c ::UseCopyTag (An empty one @c ::UseCopyTag{} is OK)
         * , only used for matching this version of overloaded constructors</p>
         *
         * <p>This version of constructor does the same as the constructors with no tags <code>IntroEntry(ArrayView&lt;T_>)</code></p>
         *
         * @see If avoiding copying is expected, use <code>IntroEntry(ArrayView&lt;T_>, UseMoveTag)</code>
         */
        InfoEntry(ArrayView<T_> ArrayView, UseCopyTag useCopy);

        /**
         * @brief Receive a range of array to construct the entry, explicitly using @b move semantics
         *
         * @param ArrayView The pointer range of the space of array
         * @param useMove The object inner struct of @c ::UseMoveTag . Use @c ::UseMoveTag{} to construct an empty
         * object
         *
         * @note The contructor will use move semantics, that is to move the elements from the ranges to
         * the entry, compared with the constructor using copy semantics.
         *
         * <p>The second param requires an random object of inner struct type @c ::UseMoveTag (An empty one @c ::UseMoveTag{} is OK)
         * , only used for matching this version of overloaded constructors</p>
         *
         * @see use <code>IntroEntry(ArrayView&lt;T_>, UseCopyTag)</code> or default <code>IntroEntry(ArrayView&lt;T_>)</code>
         * constructor when the data needs to be copied to the entry.
         */
        InfoEntry(ArrayView<T_> ArrayView, UseMoveTag useMove);

        /**
         * @brief use @c ::Key as index to access the elements
         * @param key the key from enum class @c ::Key
         * @return the reference of the elements
         */
        inline T_& operator[](Key key) noexcept;

        /**
         * @brief use @c ::Key as index to access the elements in a const context
         * @param key the key from enum class @c ::Key
         * @return the constant reference of the elements
         */
        inline const T_& operator[](Key key) const noexcept;

        /**
         * @brief use @c ::Key as index to access the elements, with bound checking
         * @param key the key from enum class @c ::Key
         * @note if the index is out of range, the method will throw @c std::out_of_range
         * @return the reference of the elements
         */
        T_& at(Key key);

        /**
         * @brief use @c ::Key as index to access the elements in a const context, with bound checking
         * @param key the key from enum class @c ::Key
         * @note if the index is out of range, the method will throw @c std::out_of_range
         * @return the constant reference of the elements
         */
        const T_& at(Key key) const;

        /**
         * @brief To get the owing continuous memory block of the internal array
         *
         * Use this interface to access the elements with numeric index (via pointer movement)
         *
         * @return A pointer range, including the @c first and @c end pointers
         */
        inline ArrayView<T_> getRange();

        /**
         * @brief To get the owing continuous memory block of the internal array
         *
         * Use this interface to access the elements with numeric index (via pointer movement)
         *
         * @return A pointer range, including the @c first and @c end pointers
         */
        inline ArrayView<const T_> getRange() const;

        /**
         * @brief Checks the validity of the object.
         *
         * This method delegates the validity check to an internal functor, @c ValidChecker .
         * By default, an object is considered valid if the main key's value (at index 0)
         * is not empty.
         *
         * @return True if the object is valid; otherwise, false.
         */
        inline bool valid() const {
            return checker(m_arr);
        }

        /**
         * @brief A type conversion methods to @c bool , returns the validity of the object.
         *
         * This method delegates the validity check to an internal functor, @c ValidChecker .
         * By default, an object is considered valid if the main key's value (at index 0)
         * is not empty.
         *
         * @return True if the object is valid; otherwise, false.
         *
         * @see @c valid()
         */
        inline operator bool() const {
            return checker(m_arr);
        }
    };

}

#include "impl/array_view.tpp"

#include "impl/info_entry.tpp"



#endif //LIBRARYMANAGEMENT_DATA_STRUCT_HPP
