#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
 
 
void test1()
{
  assert_int_equal(1, 1);
}
 
int main(void)
{
  const UnitTest tests[] = {
    unit_test(test1),
  };
 
  return run_tests(tests);
}
