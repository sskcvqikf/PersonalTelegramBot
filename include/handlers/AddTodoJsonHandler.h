#ifndef PDBOT_ADDTODOJSONHANDLER_H_
#define PDBOT_ADDTODOJSONHANDLER_H_
#pragma once

#include "handlers/JsonHandler.h"
#include "todo_storage/TodoStorage.h"

class AddTodoJsonHandler : public JsonHandler {
 public:
  explicit AddTodoJsonHandler(TodoStorage& storage);
  Json Handle(const Json& request) override;

 private:
  TodoStorage& storage_;
};

#endif  // PDBOT_ADDTODOJSONHANDLER_H_
