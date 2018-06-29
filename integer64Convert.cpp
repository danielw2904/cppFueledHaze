// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <iostream>     // std::cout

using namespace Rcpp;

#define NA_INTEGER64 LLONG_MIN


std::vector<long long> toStdInt(SEXP x_){
  if(!Rf_inherits(x_, "integer64")){
    warning("Converting to 'long long'");
    std::vector<long long> retAlt = as<std::vector<long long> >(x_);
    return retAlt;
  }
  long long i, n = LENGTH(x_);
  long long * x = (long long *) REAL(x_);
  std::vector<long long> ret(n);
  long long temp_;
  long long * temp = &temp_;
  for(i=0; i<n; i++){
    bool isna = (long long)x[i] == NA_INTEGER64;
    *temp  = (long long) x[i];
    //std::cout << (isna ? 0 : temp_) << "\n";
    ret[i] = (isna ? 0 : temp_);
    //::cout << ret[i] << "\n";
  }
return ret;
}

template<typename T>
void pprint(std::vector<T> x){
  int i, n = x.size();
  for(i = 0; i<n; i++){
    std::cout << x[i] << std::endl;
  };
}

//[[Rcpp::export]]
void getRes(SEXP x){
  pprint(toStdInt(x));
}

int64_t* rec(SEXP x){
  int64_t * res = reinterpret_cast<int64_t*>(REAL(x));
  return res;
}

std::vector<int64_t> Val(SEXP x){
  if(!Rf_inherits(x, "integer64")){
    warning("Converting to 'long long'");
    std::vector<int64_t> retAlt = as<std::vector<int64_t> >(x);
    return retAlt;
  };
  size_t i, n = LENGTH(x);
  std::vector<int64_t> res(n);
  for(i=0; i<n; i++){
  res[i] = rec(x)[i] == NA_INTEGER64 ? 0 : rec(x)[i];
  };
  return res;
}

template<typename T>
NumericVector toNum(std::vector<T> res){
  NumericVector out = wrap(res);
  return out;
}

//[[Rcpp::export]]
void getVal(SEXP x){
  pprint( Val(x) );
}



/*** R
library(bit64)
x <- "9007199254740993"
x <- as.integer64(x)
as.numeric(x)
x <- c(x + c(1:10000))
x <- as.integer64(c(x, NA))
x

library(microbenchmark)
resb <- microbenchmark(
getRes(x), times = 30
)
valb <- microbenchmark(
getVal(x), times = 30
)

getRes(as.integer64(1123))
getRes(as.integer64(2.5))
getRes(1) # Just converting to long long with warning  

  
***/
