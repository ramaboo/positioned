#include "Event.h"

Event EventQueue::_buffer[EventQueue::SIZE];
volatile uint32_t EventQueue::_head = 0;
volatile uint32_t EventQueue::_tail = 0;

bool EventQueue::post(const Event& e) {
  uint32_t next = (_head + 1) % SIZE;
  if (next == _tail) return false; // full
  _buffer[_head] = e;
  _head = next;
  return true;
}

bool EventQueue::poll(Event& out) {
  if (_head == _tail) return false; // empty
  out = _buffer[_tail];
  _tail = (_tail + 1) % SIZE;
  return true;
}
