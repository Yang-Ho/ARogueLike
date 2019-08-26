#ifndef UTILITIES_H
#define UTILITIES_H 

template<class Container, class F>
auto erase_where(Container& c, F&& f) {
    return c.erase(std::remove_if(c.begin(),
                                  c.end(),
                                  std::forward<F>(f)),
                   c.end());
}

#endif /* UTILITIES_H */
//  [Last modified: 2019 08 16 at 11:53:06 MDT]
