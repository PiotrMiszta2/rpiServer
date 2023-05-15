#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "messages_micro.h"
#include "messages_micro_req.h"
void message_check_()
{
  MessageS* message = message_create(MESSAGE_TYPE_REQ, NULL, 0);
  assert_true(message_check(message));
  free(message);
}

void message_micro_req_check()
{
  MessageMicroReqS* req = message_micro_req_create(MESSAGE_MICRO_REQ_TYPE_LD1, MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO);
  MessageS* s = message_create_micro_req_create(req);
  MessageCharS* toSend = message_create_char(s);
  uint32_t paySize;
  memcpy(&paySize, toSend->msg, sizeof(uint32_t));
  assert_int_equal(paySize, sizeof(MessageMicroReqS));
}

int main(void)
{
  const struct CMUnitTest tests[] = {
    unit_test(message_check_),
    unit_test(message_micro_req_check),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
