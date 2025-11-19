namespace Utils {

    template<class T>
    PointerRange<T> makePointerRange(std::vector<T> &vector) {
        return PointerRange<T>{vector};
    }

    template<class T, std::size_t arraySize>
    Utils::PointerRange<T> makePointerRange(std::array<T, arraySize> &array) {
        return PointerRange<T>{array};
    }

    template<class T>
    PointerRange<T> makePointerRange(T *array, std::size_t size) {
        return PointerRange<T>(array, size);
    }

}

