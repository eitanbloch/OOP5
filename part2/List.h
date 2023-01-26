//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_LIST_H
#define OOP5_LIST_H



template<typename... TT>
struct List {};

template<typename T, typename... TT>
struct List<T, TT...> {
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = 1 + sizeof...(TT);
};

template<>
struct List<> {
    constexpr static int size = 0;
};

template<typename T, typename U>
struct PrependList {};

template<typename T, typename... TT>
struct PrependList<T, List<TT...>> {
    typedef List<T, TT...> list;
};

template<typename T>
struct PrependList<T, List<>> {
    typedef List<T> list;
};

template<int N, typename T>
struct GetAtIndex {};

template<int N, typename T, typename... TT>
struct GetAtIndex<N, List<T, TT...>> {
    typedef typename GetAtIndex<N - 1, List<TT...>>::value value;
};

template<typename T, typename... TT>
struct GetAtIndex<0, List<T, TT...>> {
    typedef T value;
};


template<int N, typename V, typename T>
struct SetAtIndex {};

template<int N, typename V, typename T, typename... TT>
struct SetAtIndex<N, V, List<T, TT...>> {
    typedef typename PrependList<T, typename SetAtIndex<N - 1, V, List<TT...>>::list>::list list;
};

template<typename V, typename T, typename... TT>
struct SetAtIndex<0, V, List<T, TT...>> {
    typedef typename PrependList<V, List<TT...>>::list list;
};


#endif //OOP5_LIST_H
