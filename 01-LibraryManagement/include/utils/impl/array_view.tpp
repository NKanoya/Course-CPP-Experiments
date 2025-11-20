namespace Utils {

    template<class T>
    ArrayView<T> makeArrayView(std::vector<T> &vector) {
        return ArrayView<T>{vector};
    }

    template<class T, std::size_t arraySize>
    Utils::ArrayView<T> makeArrayView(std::array<T, arraySize> &array) {
        return ArrayView<T>{array};
    }

    template<class T>
    ArrayView<T> makeArrayView(T *beginPointer, std::size_t size) {
        return ArrayView<T>(beginPointer, size);
    }

    template<class T>
    void ArrayView<T>::rebind(std::vector<T> &vector) {
        p_begin = &vector[0];
        p_end = p_begin + vector.size();
    }

    template<class T>
    template<std::size_t length>
    void ArrayView<T>::rebind(std::array<T, length> &array) {
        p_begin = &array[0];
        p_end = p_begin + length;
    }

    template<class T>
    void ArrayView<T>::rebind(T *beginPointer, std::size_t length) {
        p_begin = beginPointer;
        p_end = p_begin + length;
    }

}

