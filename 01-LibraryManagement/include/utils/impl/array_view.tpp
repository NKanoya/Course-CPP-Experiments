namespace Utils {

    template<class T>
    ArrayView<T> makeArrayView(std::vector<T> &vector) {
        return ArrayView<T>{vector};
    }

    template<class T, std::size_t arraySize>
    ArrayView<T> makeArrayView(std::array<T, arraySize> &array) {
        return ArrayView<T>{array};
    }

    template<class T>
    ArrayView<T> makeArrayView(T *beginPointer, std::size_t size) {
        return ArrayView<T>(beginPointer, size);
    }

    template<class T>
    ArrayView<const T> makeArrayViewConst(const std::vector<T> &vector) {
        return ArrayView<T>{vector};
    }

    template<class T, std::size_t arraySize>
    ArrayView<const T> makeArrayViewConst(const std::array<T, arraySize> &array) {
        return ArrayView<T>{array};
    }

    template<class T>
    ArrayView<const T> makeArrayViewConst(const T *beginPointer, std::size_t size) {
        return ArrayView<T>(beginPointer, size);
    }

    template<class T>
    void ArrayView<T>::rebind(std::vector<T> &vector) {
        Impl::ArrayViewImpl<T>::p_begin = &vector[0];
        Impl::ArrayViewImpl<T>::p_end = Impl::ArrayViewImpl<T>::p_begin + vector.size();
    }

    template<class T>
    template<std::size_t arraySize>
    void ArrayView<T>::rebind(std::array<T, arraySize> &array) {
        Impl::ArrayViewImpl<T>::p_begin = &array[0];
        Impl::ArrayViewImpl<T>::p_end = Impl::ArrayViewImpl<T>::p_begin + arraySize;
    }

    template<class T>
    void ArrayView<T>::rebind(T *beginPointer, std::size_t  arraySize) {
        Impl::ArrayViewImpl<T>::p_begin = beginPointer;
        Impl::ArrayViewImpl<T>::p_end = Impl::ArrayViewImpl<T>::p_begin +  arraySize;
    }



    // class ArrayView<const T>

    template<class T>
    void ArrayView<const T>::rebind(const std::vector<T> &vector) {
        Impl::ArrayViewImpl<T>::p_begin = &vector[0];
        Impl::ArrayViewImpl<T>::p_end = Impl::ArrayViewImpl<T>::p_begin + vector.size();
    }

    template<class T>
    template<std::size_t arraySize>
    void ArrayView<const T>::rebind(const std::array<T, arraySize> &array) {
        Impl::ArrayViewImpl<T>::p_begin = &array[0];
        Impl::ArrayViewImpl<T>::p_end = Impl::ArrayViewImpl<T>::p_begin +  arraySize;
    }

    template<class T>
    void ArrayView<const T>::rebind(const T *beginPointer, std::size_t  arraySize) {
        Impl::ArrayViewImpl<T>::p_begin = beginPointer;
        Impl::ArrayViewImpl<T>::p_end = Impl::ArrayViewImpl<T>::p_begin +  arraySize;
    }

}

