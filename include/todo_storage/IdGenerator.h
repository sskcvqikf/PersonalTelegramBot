#ifndef PDBOT_IDGENERATOR_H_
#define PDBOT_IDGENERATOR_H_
#pragma once

#include <type_traits>

template <typename Id>
class IdGenerator {
 private:
  static_assert(std::is_integral_v<Id>, "Id must be an integral type");

 public:
  IdGenerator() noexcept : IdGenerator({}) {}

  explicit IdGenerator(Id start) noexcept : last_id_(start) {}

  Id GetNextId() { return last_id_++; }

 private:
  Id last_id_;
};

#endif  // PDBOT_IDGENERATOR_H_
