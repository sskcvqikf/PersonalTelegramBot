#ifndef PDBOT_DELETETODOJSONHANDLER_H_
#define PDBOT_DELETETODOJSONHANDLER_H_
#pragma once

#include "handlers/JsonHandler.h"
#include "todo_storage/TodoStorage.h"

class DeleteTodoJsonHandler : public JsonHandler {
 public:
  explicit DeleteTodoJsonHandler(TodoStorage& storage_) noexcept;
  Json Handle(const Json& json) override;

 private:
  TodoStorage& storage_;
};

#endif  // PDBOT_DELETETODOJSONHANDLER_H_
