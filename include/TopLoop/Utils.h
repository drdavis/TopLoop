/** @file  Utils.h
 *  @brief TL::Utils class header
 *
 *  Utility functions for TopLoop
 *
 *  @author Douglas Davis < douglas.davis@cern.ch >
 */

#ifndef TL_Utils_h
#define TL_Utils_h

// C++
#include <iostream>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <vector>

// boost
// #include <boost/range/combine.hpp>

//#define TeV 0.000001
//#define GeV 0.001

namespace TL {
  // default is MeV to other
  const double TeV = 1.0e-6;
  const double GeV = 1.0e-3;

  // for variables specifically already in GeV
  const double GeVtoTeV = 1.0e-3;
  
  enum STATUS {
    Good,
    Fail
  };
}

namespace TL {
  // boost::combine isn't available on ATLAS provided Boost versions
  // Lame.
  /*
    template<class... containers>
    auto zip(containers&... conts) -> decltype(boost::combine(conts...));
  */
  
  auto string_split(const std::string &s, char delim, std::vector<std::string> &elems)
    ->  std::vector<std::string>& ;
  auto string_split(const std::string &s, char delim)
    -> std::vector<std::string>;

  template <typename Arg, typename... Args>
  void TopPrint(std::ostream& out, Arg&& arg, Args&&... args);

  template <typename Arg, typename... Args>
  void Info(Arg&& arg, Args&&... args);

  template <typename Arg, typename... Args>
  void Warning(Arg&& arg, Args&&... args);

  template <typename Arg, typename... Args>
  void Fatal(Arg&& arg, Args&&... args);

}

// boost::combine isn't available on ATLAS provided Boost versions
// Lame.
/*
  template<class... containers>
  inline auto TL::zip(containers&... conts) -> decltype(boost::combine(conts...)) {
  return boost::combine(conts...);
  }
*/

inline auto TL::string_split(const std::string &s, char delim, std::vector<std::string> &elems)
  -> std::vector<std::string>& {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.emplace_back(item);
  }
  return elems;
}

inline auto TL::string_split(const std::string &s, char delim)
  -> std::vector<std::string> {
  std::vector<std::string> elems;
  string_split(s, delim, elems);
  return elems;
}

template <typename Arg, typename... Args>
inline void TL::TopPrint(std::ostream& out, Arg&& arg, Args&&... args) {
  out << "TopLoop:\t" << std::forward<Arg>(arg);
  using expander = int[];
  (void)expander{0, (void(out << ' ' << std::forward<Args>(args)),0)...};
  out << std::endl;
}

template<typename Arg, typename... Args>
inline void TL::Info(Arg&& arg, Args&&... args) {
  TopPrint(std::cout,"INFO\t",arg,"\t",args...);
}

template<typename Arg, typename... Args>
inline void TL::Warning(Arg&& arg, Args&&... args) {
  TopPrint(std::cout,"WARNING\t",arg,"\t",args...);
}

template<typename Arg, typename... Args>
inline void TL::Fatal(Arg&& arg, Args&&... args) {
  TopPrint(std::cerr,"FATAL\t",arg,"\t",args...);
  std::exit(EXIT_FAILURE);
}

#endif
