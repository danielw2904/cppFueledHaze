// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::interfaces(r, cpp)]]
#include <Rcpp.h>
#include <sstream>
//#include <clickhouse/client.h>
//#include "result.h"
using namespace Rcpp;
using namespace std;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//


// // [[Rcpp::export]]
// int t_o(SEXP x) {
//   int y, z;
//   y = TYPEOF(x);
//   z = Rf_inherits(x, "integer64") ? 13 : y;
//   return z;
// }

// // [[Rcpp::export]]
// bool Is_NA(SEXP val) {
//   IntegerVector::stored_type cv = as<IntegerVector::stored_type>(val);
//   bool a;
//   a = IntegerVector::is_na(cv);
//   return a;
// }
// 
// // [[Rcpp::export]]
// void p_a(SEXP a) {
//   CharacterVector cv = as<CharacterVector>(a);
//   for(size_t i=0; i<cv.length(); i++){
//     bool istna = CharacterVector::is_na(cv[i]);
//     Rcout << istna << "\n";
//     stringstream str;
//     str << cv[i];
//     int64_t x;
//     str >> x;
//     Rcout << x << "\n";
//   }
// }
// 
// template<typename CT, typename RT, typename VT>
// void toColumn(SEXP v, std::shared_ptr<CT> col, std::shared_ptr<ColumnUInt8> nullCol,
//               std::function<VT(typename RT::stored_type)> convertFn) {
//   RT cv = as<RT>(v);
//   if(nullCol) {
//     for(typename RT::stored_type e : cv) {
//       bool isNA = RT::is_na(e);
//       col->Append(isNA ? 0 : convertFn(e));
//       nullCol->Append(isNA);
//     }
//   } else {
//     for(typename RT::stored_type e : cv) {
//       if(RT::is_na(e)) {
//         stop("cannot write NA into a non-nullable column of type "+
//           col->Type()->GetName());
//       }
//       col->Append(convertFn(e));
//     }
//   }
// }
// 
// 
// toColumn<CT, IntegerVector, VT>(v, col, nullCol,
//                                 [](IntegerVector::stored_type x) {return x;});
// break;
// }
// void s_t(IntegerVector x){
//   int typ = TYPEOF(x);
//   [](IntegerVector::stored_type typ){return typ;};
// }
// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation.
//


  
// void toCol(SEXP v, std::shared_ptr<int64_t> col){
//   IntegerVector cv = as<IntegerVector>(v);
//       for(IntegerVector::stored_type e : cv) {
//           bool isNA = IntegerVector::is_na(e);
//           cout << (isNA ? 0 : std::function<int64_t(IntegerVector::stored_type)>[](IntegerVector::stored_type e) {return e;});
// }
//[[Rcpp::export]]
std::vector<int64_t> toStdVec(SEXP x){
  std::vector<int64_t> y;
  y = as<std::vector<int64_t> >(x);
  for(auto i = y.begin(); i!=y.end(); ++i){
    cout << *i << endl;
  }
  return(y);
}

//[[Rcpp::export]]      
void tType(SEXP v){
  cout << typeid(v).name() << endl;
  //NumericVector cv = as<NumericVector>(v);
  //print(cv);
  std::vector<int64_t> cc = toStdVec(v);
  for(size_t i=0; i<cc.size() ; i++) {
    bool isNA = NumericVector::is_na(cc[i]);
    cout << (isNA ? 99 : cc[i]) << endl;
  }
}


/*** R
library(bit64)
x <- "9007199254740993"
x <- as.integer64(x)
X <- c(x, x, x)
Y <- c(1,2,3)
tType(Y)
tType(x)
# p_a(X)
# 
# Is_NA(x)
# 
# t_o(x)
# s_t(x)
# y <- "whatevs"
# t_o(y)
# 
# z <- 2L
# t_o(z)
*/
