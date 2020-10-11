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

vec2_t B2 = 
  { &R[2], &R[3], &R[4],
    &D[4], &D[5], &D[6],
    &L[6], &L[7], &L[0],
    &U[0], &U[1], &U[2] };

vec2_t L2 = 
  { &B[2], &B[3], &B[4],
    &D[6], &D[7], &D[0],
    &F[6], &F[7], &F[0],
    &U[6], &U[7], &U[0] };

vec2_t U2 = 
  { &L[0], &L[1], &L[2],
    &F[0], &F[1], &F[2],
    &R[0], &R[1], &R[2],
    &B[0], &B[1], &B[2] };

vec2_t D2 = 
  { &L[4], &L[5], &L[6],
    &B[4], &B[5], &B[6],
    &R[4], &R[5], &R[6],
    &F[4], &F[5], &F[6] };

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

//////////////////////////////////////////////// 48
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

void moo(char name)
{ /* yea messy stuff */
  switch (name) {
  case 'F':
    Rotate2(F2);
    Rotate(F);
    break;
  case 'R':
    Rotate2(R2);
    Rotate(R);
    break;
  case 'B':
    Rotate2(B2);
    Rotate(B);
    break;
  case 'L':
    Rotate2(L2);
    Rotate(L);
    break;
  case 'U':
    Rotate2(U2);
    Rotate(U);
    break;
  case 'D':
    Rotate2(D2);
    Rotate(D);
    break;
  default:
    std::cout << "bOom";
    break; }}

bool ORIG()
{ /* T H A T S */
  static vec_t ORIG_F(SIZ, 'G'); // Green
  static vec_t ORIG_R(SIZ, 'R'); // Red
  static vec_t ORIG_U(SIZ, 'W'); // White
  static vec_t ORIG_B(SIZ, 'B'); // Blue
  static vec_t ORIG_L(SIZ, 'O'); // Orange
  static vec_t ORIG_D(SIZ, 'Y'); // Yellow

  return ((F == ORIG_F) &&
          (R == ORIG_R) &&
          (U == ORIG_U) &&
          (B == ORIG_B) &&
          (L == ORIG_L) &&
          (D == ORIG_D)); }

int conseq(std::string &str)
{ /* Yea1 */
  for(int cont = 1; ; ++cont) {
    for(char c: str) {
      moo(c); }
    if( ORIG()) {
      return cont; }}}

int main(int argc, char *argv[])
{ /* https://rubiks-cu.be/ */
  std::ostream_iterator<char> oi(std::cout, " ");
  std::string str("BLUFF");
  std::cout << conseq(str);
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
//
//             +---+---+---+
//             | 4 | 5 | 6 |   
//             +---+---+---+
//             | 3 | U | 7 |
//             +---+---+---+
//             | 2 | 1 | 0 |
// +---+---+---+---+---+---+---+---+---+
// | 0 | 1 | 2 | 0 | 1 | 2 | 0 | 1 | 2 |
// +---+---+---+---+---+---+---+---+---+
// | 7 | R | 3 | 7 | B | 3 | 7 | L | 3 |
// +---+---+---+---+---+---+---+---+---+
// | 6 | 5 | 4 | 6 | 5 | 4 | 6 | 5 | 4 |
// +---+---+---+---+---+---+---+---+---+
//             | 4 | 5 | 6 |
//             +---+---+---+
//             | 3 | D | 7 |
//             +---+---+---+
//             | 2 | 1 | 0 |
//             +---+---+---+     
//                         +---+---+---+
//                         | 2 | 3 | 4 |
//                         +---+---+---+
//                         | 1 | U | 5 |
//                         +---+---+---+
//                         | 0 | 7 | 6 |
//             +---+---+---+---+---+---+---+---+---+
//             | 0 | 1 | 2 | 0 | 1 | 2 | 0 | 1 | 2 |
//             +---+---+---+---+---+---+---+---+---+
//             | 7 | B | 3 | 7 | L | 3 | 7 | F | 3 |
//             +---+---+---+---+---+---+---+---+---+
//             | 6 | 5 | 4 | 6 | 5 | 4 | 6 | 5 | 4 |
//             +---+---+---+---+---+---+---+---+---+
//                         | 6 | 7 | 0 |
//                         +---+---+---+
//                         | 5 | D | 1 |
//                         +---+---+---+
//                         | 4 | 3 | 2 |
//                         +---+---+---+
//
//             +---+---+---+
//             | 4 | 5 | 6 |
//             +---+---+---+
//             | 3 | B | 7 |
//             +---+---+---+
//             | 2 | 1 | 0 |
// +---+---+---+---+---+---+---+---+---+
// | 6 | 7 | 0 | 0 | 1 | 2 | 2 | 3 | 4 |
// +---+---+---+---+---+---+---+---+---+
// | 5 | L | 1 | 7 | U | 3 | 1 | R | 5 |
// +---+---+---+---+---+---+---+---+---+
// | 4 | 3 | 2 | 6 | 5 | 4 | 0 | 7 | 6 |
// +---+---+---+---+---+---+---+---+---+
//             | 0 | 1 | 2 |
//             +---+---+---+
//             | 7 | F | 3 |
//             +---+---+---+
//             | 6 | 5 | 4 |
//             +---+---+---+
//             +---+---+---+
//             | 0 | 1 | 2 |   
//             +---+---+---+
//             | 7 | F | 3 |
//             +---+---+---+
//             | 6 | 5 | 4 |
// +---+---+---+---+---+---+---+---+---+
// | 2 | 3 | 4 | 0 | 1 | 2 | 6 | 7 | 0 |
// +---+---+---+---+---+---+---+---+---+
// | 1 | L | 5 | 7 | D | 3 | 5 | R | 1 |
// +---+---+---+---+---+---+---+---+---+
// | 0 | 7 | 6 | 6 | 5 | 4 | 4 | 3 | 2 |
// +---+---+---+---+---+---+---+---+---+
//             | 4 | 5 | 6 |
//             +---+---+---+
//             | 3 | B | 7 |
//             +---+---+---+
//             | 2 | 1 | 0 |
//             +---+---+---+     
//
