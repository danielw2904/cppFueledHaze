// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <iostream>     // std::cout

using namespace Rcpp;

#define NA_INTEGER64 LLONG_MIN


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
    //std::cout << (isna ? 0 : temp_) << "\n";
    ret[i] = (isna ? 0 : temp_);
    //::cout << ret[i] << "\n";
  }
return ret;
}

void pprint(std::vector<long long> x){
  int i, n = x.size();
  for(i = 0; i<n; i++){
    std::cout << x[i] << std::endl;
  };
}

//[[Rcpp::export]]
void getRes(SEXP x){
  pprint(toStdInt(x));
}


/*** R
library(bit64)
x <- "9007199254740993"
x <- as.integer64(x)
as.numeric(x)
x <- c(x + c(1:10))
x <- as.integer64(c(x, NA))
x

getRes(x)

getRes(as.integer64(1123))

getRes(1) # Does not work. Requires integer64  

  
***/
