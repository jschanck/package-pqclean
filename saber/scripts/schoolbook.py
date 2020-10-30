p = print

def load(v, off, k):
  for i in range(k):
    p("{}{}={}[{}];".format(v,i,v,i+off))

def mul(a, an, b, bn, first):
  for i in range(a+b, a+b+an+bn-1):
    for j in range(a, min(a+an, i+1)):
      if i-j < b or i-j > b+bn-1: continue
      src = "c[{}]".format(i) if (j==a or i-j==b+bn-1) else "t0"
      dest = "c[{}]".format(i) if (j == a+an-1 or i-j == b) else "t0"
      if first[i]:
        p("{}=mul(a{}, b{});".format(dest, j-a, i-j-b))
      else:
        p("{}=mac(a{}, b{}, {});".format(dest, j-a, i-j-b, src))
      first[i] = 0
  return first

def mul16_772(acc=0):
  if acc: p("static void schoolbook16x16_acc(__m256i *c, const __m256i *a, const __m256i *b) {")
  else: p("static void schoolbook16x16(__m256i *c, const __m256i *a, const __m256i *b) {")
  p("__m256i a0,a1,a2,a3,a4,a5,a6;")
  p("__m256i b0,b1,b2,b3,b4,b5,b6;")
  p("__m256i t0;")
  first = [1-acc]*33

  load("a", 0, 7)
  load("b", 0, 7)
  first = mul(0,  7,  0, 7, first)
  load("b", 7, 7)
  first = mul(0,  7,  7, 7, first)
  load("b", 14, 2)
  first = mul(0,  7, 14, 2, first)

  load("a", 7, 7)
  first = mul(7,  7, 14, 2, first)
  load("b", 7, 7)
  first = mul(7,  7,  7, 7, first)
  load("b", 0, 7)
  first = mul(7,  7,  0, 7, first)

  load("a", 14, 2)
  first = mul(14, 2,  0, 7, first)
  load("b", 7, 7)
  first = mul(14, 2,  7, 7, first)
  load("b", 14, 2)
  first = mul(14, 2, 14, 2, first)

  if not acc: p("c[31] = _mm256_setzero_si256();")
  p("}")

def mul16_4444(acc=0):
  if acc: p("static void schoolbook16x16_acc(__m256i *c, const __m256i *a, const __m256i *b) {")
  else: p("static void schoolbook16x16(__m256i *c, const __m256i *a, const __m256i *b) {")
  p("__m256i a0,a1,a2,a3;")
  p("__m256i b0,b1,b2,b3;")
  p("__m256i t0;")
  first = [1-acc]*32

  load("a", 0, 4)
  load("b", 0, 4)
  first = mul(0, 4, 0, 4, first)
  load("b", 4, 4)
  first = mul(0, 4, 4, 4, first)
  load("b", 8, 4)
  first = mul(0, 4, 8, 4, first)
  load("b", 12, 4)
  first = mul(0, 4, 12, 4, first)

  load("a", 4, 4)
  first = mul(4, 4, 12, 4, first)
  load("b", 8, 4)
  first = mul(4, 4, 8, 4, first)
  load("b", 4, 4)
  first = mul(4, 4, 4, 4, first)
  load("b", 0, 4)
  first = mul(4, 4, 0, 4, first)

  load("a", 8, 4)
  first = mul(8, 4, 0, 4, first)
  load("b", 4, 4)
  first = mul(8, 4, 4, 4, first)
  load("b", 8, 4)
  first = mul(8, 4, 8, 4, first)
  load("b", 12, 4)
  first = mul(8, 4, 12, 4, first)

  load("a", 12, 4)
  first = mul(12, 4, 12, 4, first)
  load("b", 8, 4)
  first = mul(12, 4, 8, 4, first)
  load("b", 4, 4)
  first = mul(12, 4, 4, 4, first)
  load("b", 0, 4)
  first = mul(12, 4, 0, 4, first)

  if not acc: p("c[31] = _mm256_setzero_si256();")
  p("}")

if __name__=="__main__":
  p("/* 16 word parallel multiply */")
  p("#define mul(a, b)     _mm256_mullo_epi16((a), (b))")
  p("/* 16 word parallel multiply and accumulate */")
  p("#define mac(a, b, c)  _mm256_add_epi16(_mm256_mullo_epi16((a), (b)), (c))")
  p()
  mul16_4444(acc=0);
  p()
  mul16_4444(acc=1);
  p()
