#include "Event.h"

QueueHandle_t EventQueue::_queue = nullptr;

void EventQueue::init() {
  if (_queue == nullptr) {
    _queue = xQueueCreate(SIZE, sizeof(Event));
  }
}

bool EventQueue::post(const Event& e) {
  if (_queue == nullptr) {
    init();
  }

  return xQueueSend(_queue, &e, 0) == pdTRUE;
}

bool EventQueue::postFromISR(const Event& e) {
  if (_queue == nullptr) {
    return false;
  }

  BaseType_t higherPriorityTaskWoken = pdFALSE;
  bool result = xQueueSendFromISR(_queue, &e, &higherPriorityTaskWoken) == pdTRUE;

  if (higherPriorityTaskWoken) {
    portYIELD_FROM_ISR();
  }

  return result;
}

bool EventQueue::poll(Event& out) {
  if (_queue == nullptr) {
    init();
  }

  return xQueueReceive(_queue, &out, 0) == pdTRUE;
}
