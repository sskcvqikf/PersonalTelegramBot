#ifndef PDBOT_GETALLTODOJSONHANDLER_H_
#define PDBOT_GETALLTODOJSONHANDLER_H_
#pragma once

#include "handlers/JsonHandler.h"
#include "todo_storage/TodoStorage.h"

class GetAllTodoJsonHandler : public JsonHandler {
 public:
  explicit GetAllTodoJsonHandler(TodoStorage& storage);
  Json Handle(const Json& json) override;

 private:
  TodoStorage& storage_;
};

#endif  // PDBOT_GETALLTODOJSONHANDLER_H_
