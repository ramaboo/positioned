#pragma once
#include <stdint.h>

enum class EventType : uint8_t {
  None = 0,
  BackPressed,
  BackReleased,
  ControlPressed,
  ControlReleased,
  ForwardPressed,
  ForwardReleased,
  EncoderPressed,
  EncoderReleased,
  EncoderTurn
};

struct Event {
  EventType type = EventType::None;
  uint32_t value = 0;
  constexpr Event(EventType t = EventType::None, uint32_t v = 0) : type(t), value(v) {}
};

class EventQueue {
public:
  static bool post(const Event& e);
  static bool poll(Event& out);

private:
  static const uint32_t SIZE = 16;
  static Event _buffer[];
  static volatile uint32_t _head;
  static volatile uint32_t _tail;
};
