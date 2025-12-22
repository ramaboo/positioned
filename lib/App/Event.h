#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <stdint.h>

enum class EventType : uint8_t {
  None = 0,
  BackwardPressed,
  BackwardReleased,
  ForwardPressed,
  ForwardReleased,
  StartStopPressed,
  StartStopReleased,
  EncoderPressed,
  EncoderReleased,
  EncoderTurn,
  SwitchBackward,
  SwitchForward,
  SwitchOff,
};

struct Event {
  EventType type = EventType::None;
  uint32_t value = 0;
  constexpr Event(EventType t = EventType::None, uint32_t v = 0) : type(t), value(v) {}
};

class EventQueue {
 public:
  static bool post(const Event& e);
  static bool postFromISR(const Event& e);
  static bool poll(Event& out);
  static void init();

 private:
  static const uint32_t SIZE = 16;
  static QueueHandle_t _queue;
};
