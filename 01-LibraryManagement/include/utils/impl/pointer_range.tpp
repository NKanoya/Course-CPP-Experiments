namespace Utils {

    template<class T>
    PointerRange<T> PointerRange<T>::makePointerRange(std::vector<T> &vector) {
        return {vector};
    }

    template<class T>
    template<std::size_t arraySize>
    Utils::PointerRange<T> Utils::PointerRange<T>::makePointerRange(std::array<T, arraySize> &array) {
        return {array};
    }

    template<class T>
    PointerRange<T> PointerRange<T>::makePointerRange(T *array, std::size_t size) {
        return PointerRange<T>(array, size);
    }

}

