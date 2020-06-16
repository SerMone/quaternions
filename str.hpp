#ifndef STR_HPP
#define STR_HPP
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>


template< typename T >
typename std::iterator_traits< T >::value_type
identity(typename std::iterator_traits< T >::value_type v) {
  return v;
}

template< typename T > using IdentityType = decltype(identity< T >);

template< class ForwardIterator,
          typename StrType1 = const char *,
          typename StrType2 = const char *,
          typename StrType3 = const char *,
          typename Transform = IdentityType< ForwardIterator > >
std::string join(ForwardIterator first,
                 ForwardIterator last,
                 StrType1 &&sep = ",",
                 StrType2 &&open = "[",
                 StrType3 &&close = "]",
                 Transform tr = identity< ForwardIterator >) {

  std::stringstream ss;

  ss << std::forward< StrType2 >(open);

  if (first != last) {

    ss << tr(*first);

    ++first;
  }

  for (; first != last; ++first)
    ss << std::forward< StrType1 >(sep) << tr(*first);

  ss << std::forward< StrType3 >(close);

  return ss.str();
}

#endif /* STR_HPP */


