#ifndef PDBOT_TODOSTORAGE_H_
#define PDBOT_TODOSTORAGE_H_
#pragma once

#include <unordered_map>

#include "Todo.pb.h"
#include "todo_storage/IdGenerator.h"

using TodoVector = std::vector<Todo>;

class TodoStorage final {
 private:
  using Storage = std::unordered_map<uint32_t, std::string>;
  using IdGenerator = IdGenerator<uint32_t>;

 public:
  TodoStorage(IdGenerator id_generator_, TodoVector todos);

  TodoStorage();

  void AddTodo(std::string name);
  void DeleteTodo(uint32_t id);

  TodoVector GetAll() const;

 private:
  IdGenerator id_generator_;
  Storage storage_;
};

#endif  // PDBOT_TODOSTORAGE_H_
