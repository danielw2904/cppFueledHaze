// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <memory>
// swapping ostringstream objects
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>

using namespace Rcpp;

#define NA_INTEGER64 LLONG_MIN


//[[Rcpp::export]]
std::vector<int64_t> toStdVec(SEXP x){
  std::vector<int64_t> y;
  y = as<std::vector<int64_t> >(x);
  for(auto i = y.begin(); i!=y.end(); ++i){
    std::cout << *i << std::endl;
  }
  return(y);
}


//[[Rcpp::export]]
long long toStdInt2(SEXP x){
  long long * y = (long long *) REAL(x);
  std::cout << *y << std::endl;
  return *y;
}

std::vector<int64_t> endres;

//[[Rcpp::export]]
std::vector<long long> toStdInt(SEXP x_){
  std::vector<long long> y;
  long long i, n = LENGTH(x_);
  long long * x = (long long *) REAL(x_);
  std::vector<long long> ret(n);
  long long temp_;
  long long * temp = &temp_;
  for(i=0; i<n; i++){
    bool isna = (long long)x[i] == NA_INTEGER64;
    *temp  = (long long) x[i];
    std::cout << (isna ? 0 : temp_) << "\n";
    ret[i] = (isna ? 0 : temp_);
    std::cout << ret[i] << "\n";
  }
return ret;
}

//[[Rcpp::export]]
void getRes(std::vector<int64_t> x){
  endres = x;
  int n = endres.size();
  for(int i=0; i<n; i++){
    std::cout << endres[i] << std::endl;
  }
}



/*** R
library(bit64)
x <- "1007199254740950000"
x <- as.integer64(x)
as.numeric(x)
x <- c(x + c(1:10))
x <- c(x, NA)
x
toStdVec(x)
z <- toStdInt2(x)

toStdInt(1)
out <- toStdInt(x)

y <- c(123, 456, 789)
toStdVec(y)
toStdVec2(y)

***/
