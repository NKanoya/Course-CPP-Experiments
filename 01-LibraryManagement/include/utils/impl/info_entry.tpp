namespace Utils {

    // static member
    template<class T_, class EnumClass_, class ValidChecker_>
    const ValidChecker_ InfoEntry<T_, EnumClass_, ValidChecker_>::checker = {};

    template<class T_, class EnumClass_, class ValidChecker_>
    InfoEntry<T_, EnumClass_, ValidChecker_>::
    InfoEntry(ArrayViewConst<T_> ArrayView) {
        // use copy mode
        if(ArrayView.size() != KEYCOUNT) {
            m_arr[0] = "";      // construct an invalid object
            return;
        }

        // copy the elements to inner array
        for(int i = 0; i < KEYCOUNT; ++i) {
            m_arr[i] = ArrayView.p_begin[i];
        }
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    InfoEntry<T_, EnumClass_, ValidChecker_>::
    InfoEntry(ArrayViewConst<T_> ArrayView, InfoEntry::UseCopyTag useCopy)
            : InfoEntry(ArrayView) {}

    template<class T_, class EnumClass_, class ValidChecker_>
    InfoEntry<T_, EnumClass_, ValidChecker_>::
    InfoEntry(ArrayView<T_> ArrayView, InfoEntry::UseMoveTag useMove) {
        // use copy mode
        if(ArrayView.size() != KEYCOUNT) {
            m_arr[0] = "";      // construct an invalid object
            return;
        }

        // move the elements to inner array
        for(int i = 0; i < KEYCOUNT; ++i) {
            m_arr[i] = std::move(ArrayView.p_begin[i]);

            std::cout << ArrayView.p_begin[i];
        }
    }



    template <class T_, class EnumClass_, class ValidChecker_>
    inline T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
    operator[](InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) noexcept {
        return m_arr[static_cast<std::size_t>(key)];
    }

    template <class T_, class EnumClass_, class ValidChecker_>
    inline const T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
    operator[](InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) const noexcept {
        return m_arr[static_cast<std::size_t>(key)];
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
    at(InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) {
        auto index = static_cast<std::size_t>(key);
        if(key >= Key::KEY_COUNT) {
            if(key == Key::KEY_COUNT) {
                // use Key::KEY_COUNT as key
                throw std::out_of_range("Out of range! DO NOT use Key::KEY_COUNT as key!");
            }
            throw std::out_of_range("Out of range! Invalid Key!");
        }
        return m_arr[index];
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    const T_& InfoEntry<T_, EnumClass_, ValidChecker_>::
    at(InfoEntry<T_, EnumClass_, ValidChecker_>::Key key) const {
        auto index = static_cast<std::size_t>(key);
        if(key >= Key::KEY_COUNT) {
            if(key == Key::KEY_COUNT) {
                // use Key::KEY_COUNT as key
                throw std::out_of_range("Out of range! DO NOT use Key::KEY_COUNT as key!");
            }
            throw std::out_of_range("Out of range! Invalid Key!");
        }
        return m_arr[index];
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    inline ArrayView<T_> InfoEntry<T_, EnumClass_, ValidChecker_>::
    getRange() {
        return ArrayView<T_>(m_arr);
    }

    template<class T_, class EnumClass_, class ValidChecker_>
    inline ArrayViewConst<T_> InfoEntry<T_, EnumClass_, ValidChecker_>::
    getRange() const {
        return ArrayView<const T_>(m_arr);
    }

}

