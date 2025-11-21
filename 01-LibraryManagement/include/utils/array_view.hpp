//
// Created on 2025/11/21.
//

#ifndef LIBRARYMANAGEMENT_ARRAY_VIEW_HPP
#define LIBRARYMANAGEMENT_ARRAY_VIEW_HPP

#include <vector>
#include <string>

namespace Utils {

    // -----------------------------------------------------------------------------
    // ARRAYVIEW_IMPL - THE INTERNAL BASE FOR ARRAYVIEW-RELATED CLASSES
    // -----------------------------------------------------------------------------

    /**
     * @brief Utility namespace for internal implementation details.
     */
    namespace Impl {

        /**
         * @brief Internal implementation base class for ArrayView.
         *
         * <p>This struct serves as the common base for both @c ArrayView&lt;T> and <code>ArrayView&lt;const T></code>. </p>
         *
         * <p>It carries the core pointer data and provides all read-only access methods
         * which are independent of the view's mutability, ensuring code reuse.</p>
         *
         * @tparam T The element type, which may be @b const-qualified (e.g., @c int or <code>const int</code> ).
         */
        template<class T>
        struct ArrayViewImpl {

            /** @brief The underlying element type, equivalent to the template parameter T. */
            using ValueType = T;

            /** @brief Pointer to the beginning of the memory range. */
            ValueType *p_begin;

            /** @brief Pointer to the beginning of the memory range. */
            ValueType *p_end;

            /**
             * @brief Constructs the base view with explicit begin and end pointers.
             * @param p_begin Pointer to the start of the view.
             * @param p_end Pointer to the end of the view (one past the last element).
             */
            ArrayViewImpl(ValueType* p_begin, ValueType* p_end) : p_begin(p_begin), p_end(p_end) {}

            /**
             * @brief Gets the number of elements in the view.
             * @return @c std::ptrdiff_t The size (length) of the view.
             */
            inline std::ptrdiff_t size() const noexcept {
                return p_end - p_begin;
            }

            /**
             * @brief Gets a const pointer to the beginning of the view (const access).
             *
             * <p>The method is to match the interface of containers template from standard library.</p>
             *
             * @note The 'const' in the return type prevents mutation even if ValueType is non-const.
             *
             * @return const @c ValueType* A constant pointer to the first element.
             */
            inline const ValueType *begin() const noexcept {
                return p_begin;
            }

            /**
             * @brief Gets a const pointer to one past the end of the view (const access).
             *
             * <p>The method is to match the interface of containers template from standard library.</p>
             *
             * @return const @c ValueType* A constant pointer to the end position.
             */
            inline const ValueType *end() const noexcept {
                return p_end;
            }

            /**
             * @brief Accesses an element by index (const access).
             * @param index The index of the element to access.
             * @return <code>const ValueType&</code> A constant reference to the element.
             */
            inline const ValueType &operator[](std::size_t index) const {
                return *(p_begin + index);
            }

            /**
             * @brief Checks if the view is empty.
             * @return bool True if the view contains no elements.
             */
            inline bool empty() const noexcept {
                return p_begin == p_end;
            }
        };

    }

    // -----------------------------------------------------------------------------
    // ARRAYVIEW - MUTABLE (NON-CONST) VERSION
    // -----------------------------------------------------------------------------

    /**
     * @brief Represents a non-owning, @b mutable view of a contiguous memory range.
     *
     * <p>ArrayView stores a pair of pointers (begin and one-past-the-end)
     * to describe a continuous memory block. It is designed to provide read-write
     * access to the underlying data. It inherits read-only access from ArrayViewImpl.</p>
     *
     * @tparam T The non-const type of elements within the range (e.g., int).
     */
    template<class T>
    struct ArrayView : public Impl::ArrayViewImpl<T> {

        /** @brief Alias for the underlying element type. */
        using ValueType = Impl::ArrayViewImpl<T>::ValueType;

        /**
         * @brief Constructs a view from a @c std::vector (non-const).
         * @param vector The vector whose memory is viewed.
         */
        explicit ArrayView(std::vector<T> &vector) : Impl::ArrayViewImpl<T>(&vector[0], &vector[0] + vector.size()) {}

        /**
         * @brief Constructs a view from a @c std::array (non-const).
         * @tparam size The size of the array.
         * @param array The array whose memory is viewed.
         */
        template<std::size_t size>
        explicit ArrayView(std::array<T, size> &array) : Impl::ArrayViewImpl<T>(&array[0], &array[0] + size) {}

        /**
         * @brief Constructs a view from a raw pointer and size.
         * @param beginPointer Pointer to the start of the C-style array.
         * @param size The number of elements in the array.
         */
        explicit ArrayView(T *beginPointer, std::size_t size) : Impl::ArrayViewImpl<T>(beginPointer, beginPointer + size) {}

        /**
         * @brief Gets a non-const pointer to the beginning of the view.
         * @return @c ValueType* A mutable pointer to the first element.
         */
        inline ValueType *begin() noexcept {
            return Impl::ArrayViewImpl<T>::p_begin;
        }

        /**
         * @brief Gets a non-const pointer to one past the end of the view.
         * @return @c ValueType* A mutable pointer to the end position.
         */
        inline ValueType *end() noexcept {
            return Impl::ArrayViewImpl<T>::p_end;
        }

        /**
         * @brief Accesses an element by index (non-const access).
         * @return ValueType& A mutable reference to the element.
         */
        inline ValueType &operator[](std::size_t index)  {
            return *(Impl::ArrayViewImpl<T>::p_begin + index);
        }

        /**
         * @brief Rebinds the view to a new non-const std::vector.
         * @param vector The new vector to view.
         */
        void rebind(std::vector<T> &vector);

        /**
         * @brief Rebinds the view to a new non-const std::array.
         * @tparam length The size of the array.
         * @param array The new array to view.
         */
        template<std::size_t arraySize>
        void rebind(std::array<T, arraySize> &array);

        /**
         * @brief Rebinds the view to a new non-const raw pointer range.
         * @param beginPointer Pointer to the start of the new range.
         * @param length The length of the new range.
         */
        void rebind(T *beginPointer, std::size_t  arraySize);
    };


    // -----------------------------------------------------------------------------
    // ARRAYVIEW - CONST (READ-ONLY) VERSION (Partial Specialization)
    // -----------------------------------------------------------------------------

    /**
     * @brief Represents a non-owning, @b read-only view of a contiguous memory range.
     *
     * This partial specialization is used when the view is known to be immutable.
     * Its constructors and rebind methods are restricted to accepting const sources.
     *
     * @tparam T The non-const type of elements (e.g., int, but the view is const int).
     */
    template<class T>
    struct ArrayView<const T> : public Impl::ArrayViewImpl<const T> {

        /** @brief Alias for the underlying element type (which is const T). */
        using ValueType = Impl::ArrayViewImpl<const T>::ValueType;

        /**
         * @brief Conversion Constructor for Safe Conversion.Implicit conversion from @c ArrayView&lt;T>
         * to <code>ArrayView&lt;const T></code> .
         *
         * @param other the object of @c ArrayView&lt;T>
         */
        ArrayView(const ArrayView<T>& other) : Impl::ArrayViewImpl<const T>(other.p_begin, other.p_end) {}

        /**
         * @brief Constructs a view from a std::vector (const).
         * @param vector The constant vector whose memory is viewed.
         */
        explicit ArrayView(const std::vector<T> &vector)
            : Impl::ArrayViewImpl<const T>(&vector[0], &vector[0] + vector.size()) {}

        /**
         * @brief Constructs a view from a std::array (const).
         * @tparam size The size of the array.
         * @param array The constant array whose memory is viewed.
         */
        template<std::size_t arraySize>
        explicit ArrayView(const std::array<T, arraySize> &array)
            : Impl::ArrayViewImpl<const T>(&array[0], &array[0] + arraySize) {}

        /**
         * @brief Constructs a view from a const raw pointer and size.
         * @param beginPointer Constant pointer to the start of the C-style array.
         * @param size The number of elements in the array.
         */
        explicit ArrayView(const T *beginPointer, std::size_t size)
            : Impl::ArrayViewImpl<const T>(beginPointer, beginPointer + size) {}

        /**
         * @brief Rebinds the view to a new <code>const std::vector</code> .
         * @param vector The new constant vector to view.
         */
        void rebind(const std::vector<T> &vector);

        /**
          * @brief Rebinds the view to a new <code>const std::array</code> .
          * @tparam length The size of the array.
          * @param array The new constant array to view.
          */
        template<std::size_t arraySize>
        void rebind(const std::array<T, arraySize> &array);

        /**
         * @brief Rebinds the view to a new const raw pointer range.
         * @param beginPointer Constant pointer to the start of the new range.
         * @param length The length of the new range.
         */
        void rebind(const T * beginPointer, std::size_t  arraySize);
    };

    /**
     * @brief Alias for the read-only version of ArrayView (ArrayView<const T>).
     *
     * This alias should be used by default whenever data modification is NOT required.
     *
     * <p>It provides clear semantic intent (read-only) and allows for seamless interoperability,
     * as a mutable @c ArrayView<T> can be implicitly converted and passed to any function
     * expecting an @c ArrayViewConst<T> .</p>
     *
     * <h3>Usage Recommendation:</h3>
     * <ul>
     * <li><b>Default Choice:</b> Use @c ArrayViewConst<T> in function parameters unless mutation is necessary.</li>
     * <li><b>Mutability Required:</b> Only use @c ArrayView<T> when the function explicitly needs to write to the underlying memory.</li>
     * </ul>
     *
     * <h3>Const Restriction:</h3>
     * This alias strictly enforces read-only access. Direct assignment from an @c ArrayViewConst<T>
     * back to an @c ArrayView<T> is disallowed by the C++ type system, ensuring
     * that @b const-correctness is always preserved.
     *
     * @tparam T The non-const type of the elements (e.g., int).
     */
    template<class T>
    using ArrayViewConst = ArrayView<const T>;


    // -----------------------------------------------------------------------------
    // FACTORY FUNCTIONS (makeArrayView)
    // -----------------------------------------------------------------------------

    /**
     * @brief Factory function to create a mutable ArrayView from a std::vector.
     * @tparam T The element type.
     * @param vector The vector to view.
     * @return ArrayView<T> A mutable view of the vector.
     */
    template<class T>
    ArrayView<T> makeArrayView(std::vector<T> &vector);

    /**
     * @brief Factory function to create a mutable ArrayView from a std::array.
     * @tparam T The element type.
     * @tparam arraySize The size of the array.
     * @param array The array to view.
     * @return ArrayView<T> A mutable view of the array.
     */
    template<class T, std::size_t arraySize>
    ArrayView<T> makeArrayView(std::array<T, arraySize> &array);

    /**
     * @brief Factory function to create a mutable ArrayView from a raw pointer range.
     * @tparam T The element type.
     * @param array Pointer to the start of the range.
     * @param size The size of the range.
     * @return ArrayView<T> A mutable view of the range.
     */
    template<class T>
    ArrayView<T> makeArrayView(T *array, std::size_t size);


    // -----------------------------------------------------------------------------
    // FACTORY FUNCTIONS (makeArrayView - Const Overloads)
    // -----------------------------------------------------------------------------

    /**
     * @brief Factory function to create a const ArrayView from a constant std::vector.
     * @tparam T The element type.
     * @param vector The constant vector to view.
     * @return ArrayView<const T> A constant view of the vector.
     */
    template<class T>
    ArrayView<const T> makeArrayViewConst(const std::vector<T> &vector);

    /**
     * @brief Factory function to create a const ArrayView from a constant std::array.
     * @tparam T The element type.
     * @tparam arraySize The size of the array.
     * @param array The constant array to view.
     * @return ArrayView<const T> A constant view of the array.
     */
    template<class T, std::size_t arraySize>
    ArrayView<const T> makeArrayViewConst(const std::array<T, arraySize> &array);

    /**
     * @brief Factory function to create a const ArrayView from a constant raw pointer range.
     * @tparam T The element type.
     * @param array Constant pointer to the start of the range.
     * @param size The size of the range.
     * @return ArrayView<const T> A constant view of the range.
     */
    template<class T>
    ArrayView<const T> makeArrayViewConst(const T *array, std::size_t size);


}

#endif //LIBRARYMANAGEMENT_ARRAY_VIEW_HPP
