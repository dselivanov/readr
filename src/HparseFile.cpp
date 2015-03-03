#include "HCollector.h"
#include "HStreamFile.h"
#include "HStreamString.h"
#include "HTokenizerDelimited.h"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
void readFile(std::string path) {
  StreamFile source(path);

  char c;
  while((c = source.get()) != EOF)
    Rcout << c;
}

// [[Rcpp::export]]
void readString(CharacterVector x) {
  StreamString source(x);

  char c;
  while((c = source.get()) != EOF)
    Rcout << c;
}

// [[Rcpp::export]]
std::vector<std::string> tokenizeString(CharacterVector x) {
  StreamString source(x);
  TokenizerDelimited csv(',');

  std::vector<std::string> out;

  while(source.peek() != EOF) {
    Token t = csv.nextToken(&source);
    out.push_back(t.asString(source));
  }

  return out;
}

// [[Rcpp::export]]
NumericVector parseNumbers(CharacterVector x) {
  StreamString source(x);
  TokenizerDelimited csv(',');
  DoubleCollector out;

  out.resize(100);

  int i = 0;
  while(source.peek() != EOF && i < 100) {
    Token t = csv.nextToken(&source);
    out.setValue(i++, t);
  }

  return out.vector();
}

