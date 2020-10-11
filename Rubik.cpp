/*-*-c++-*-*////////////////////////////////////
#include <iostream>
#include <forward_list>
#include <cstring>
#define CYCL 4
////____>>>>````,,,,''''rrrr----____<<<<$$$$....
struct coupe {
  char c; // string character
  int  n; // c conseq counter
  coupe(char c=0, int n=0): c(c), n(n) {}
};
/////// ***  _______ %%%% =====  >>>>> (`      ^
typedef std::forward_list<coupe> stack_t;
//////////////////////// Remove Cycles *********
char *Rc(char* s)
{ // [Staät]
  stack_t ls = {coupe()}; // sentinel
  do {
    // imp: s
    char c = *s;
    int  n = 1;
    while( *++s == c ){ ++n; }
    n %= CYCL; // discard cycles
    // mod: s
    // out: n, c
    if( !n ){ continue; } // avoid n=0 entries
    coupe &last = ls.front(); // LIFO
    if( c == last.c ){ // merge
      n = (n + last.n)% CYCL;
      if( !n ){ // dzero
        ls.pop_front();
        continue;
      }
      last.n = n;
    } else {
      ls.emplace_front(c, n);
    }    
  } while( *s );
  /* imp: s, ls */
  for( auto &cp: ls ){
    char c = cp.c;
    int n = cp.n;
    while( n-- ){ *--s = c; }
  }
  /* out: s */
  ls.clear();
  return s;
}
bool ckch(char ch) // character check
{
  switch (ch) {
  case 'B':
  case 'D':
  case 'F':
  case 'L':
  case 'R':
  case 'U':
    return true;
  default:
    return false;
  }
}
bool ckstr(char *str) // check string
{
  for(; ckch(*str); ++str)
    ;
  return !*str;
}
///////////////////////////////////////// part 2
#include <algorithm>
////----\\\\____****""""````||||$$$$>>>>    ::::
////----''''____""""====````,,,,>>>>----////....
////====,,,,````>>>>    ::::''''____))))((((;;;;
#include <iterator>
////////////////////////////////////////////////
////////////////////////////////////////////////
#include <vector>
#define range(V) V.begin(), V.end()
#define dump(V, IT) std::copy(range(V), IT); puts("")
typedef std::vector<char> vec_t;
#define SIZ 8
vec_t F(SIZ, 'G'); // Green
vec_t R(SIZ, 'R'); // Red
vec_t U(SIZ, 'W'); // White
vec_t B(SIZ, 'B'); // Blue
vec_t L(SIZ, 'O'); // Orange
vec_t D(SIZ, 'Y'); // Yellow
#define SIZ2 12
typedef std::vector<char*> vec2_t;
vec2_t F2 = 
  { &L[2], &L[3], &L[4],
    &D[0], &D[1], &D[2],
    &R[6], &R[7], &R[0],
    &U[4], &U[5], &U[6] };

vec2_t R2 = 
  { &F[2], &F[3], &F[4],
    &D[2], &D[3], &D[4],
    &B[6], &B[7], &B[0],
    &U[2], &U[3], &U[4] };

void Rotate2(vec2_t &p)
{ /* Y - this looks like a coordinate system */
  static int n = 3;
  static vec_t buf(n);
  for(int i = 0; i < n; ++i) {
    buf[i] = *p[i]; }
  for(int i = n; i < SIZ2; ++i) {
    *p[i - n] = *p[i]; }
  for(int i = 0; i < n; ++i) {
    *p[SIZ2 - n + i] = buf[i]; }}

void Rotate(vec_t &p)
{ /* Ok! */
  static int n = 2;
  static vec_t buf(n);
  for(int i = 0; i < n; ++i) {
    buf[i] = p[SIZ - n + i]; }
  for(int i = SIZ- 1; i >=2; --i) {
    p[i] = p[i- n]; }
  for(int i = 0; i < n; ++i) {
    p[i] = buf[i]; }}

//////////////////////////////////////////////////////// 56
#include <map>
std::map<char,vec_t*> face =
  {{'F', &F},
   {'R', &R},
   {'U', &U},
   {'B', &B},
   {'L', &L},
   {'D', &D}};

std::map<char,char> clr =
  {{'F', 'G'},
   {'R', 'R'},
   {'U', 'W'},
   {'B', 'B'},
   {'L', 'O'},
   {'D', 'Y'}};

void dump_face(char name)
{ /**/
  vec_t vec = *face[name];
  char colour = clr[name];
  char Clr[] = {vec[0], vec[1], vec[2],
                vec[7], colour, vec[3],
                vec[6], vec[5], vec[4]};
  for ( int j = 0 ; j <= SIZ ; ++ j ) {
    if(j%3==0){puts("");}//whatz?
    std::cout << Clr[j] << ' '; }
  puts(""); }

void dump_all()
{ /**/
  static std::string names = "FRUBLD";
  for(char c: names) {
    dump_face(c);
    std::cout << c << '\n'; }}

int main(int argc, char *argv[])
{ /* https://rubiks-cu.be/ */
  std::ostream_iterator<char> oi(std::cout, " ");
  Rotate2(F2);
  Rotate(F);
  dump_all();
  Rotate2(R2);
  Rotate(R);
  dump_all();
  puts("ay");
}
/////////////////////////////////////////// log:
//             +---+---+---+
//             | 0 | 1 | 2 |   
//             +---+---+---+
//             | 7 | U | 3 |
//             +---+---+---+
//             | 6 | 5 | 4 |
// +---+---+---+---+---+---+---+---+---+
// | 0 | 1 | 2 | 0 | 1 | 2 | 0 | 1 | 2 |
// +---+---+---+---+---+---+---+---+---+
// | 7 | L | 3 | 7 | F | 3 | 7 | R | 3 |
// +---+---+---+---+---+---+---+---+---+
// | 6 | 5 | 4 | 6 | 5 | 4 | 6 | 5 | 4 |
// +---+---+---+---+---+---+---+---+---+
//             | 0 | 1 | 2 |
//             +---+---+---+
//             | 7 | D | 3 |
//             +---+---+---+
//             | 6 | 5 | 4 |
//             +---+---+---+     
//
//             +---+---+---+
//             | 6 | 7 | 0 |   
//             +---+---+---+
//             | 5 | U | 1 |
//             +---+---+---+
//             | 4 | 3 | 2 |
// +---+---+---+---+---+---+---+---+---+
// | 0 | 1 | 2 | 0 | 1 | 2 | 0 | 1 | 2 |
// +---+---+---+---+---+---+---+---+---+
// | 7 | F | 3 | 7 | R | 3 | 7 | B | 3 |
// +---+---+---+---+---+---+---+---+---+
// | 6 | 5 | 4 | 6 | 5 | 4 | 6 | 5 | 4 |
// +---+---+---+---+---+---+---+---+---+
//             | 2 | 3 | 4 |
//             +---+---+---+
//             | 1 | D | 5 |
//             +---+---+---+
//             | 0 | 7 | 6 |
//             +---+---+---+     
