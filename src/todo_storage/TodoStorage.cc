#include "todo_storage/TodoStorage.h"

TodoStorage::TodoStorage(IdGenerator id_generator_, TodoVector todos)
    : id_generator_(std::move(id_generator_)) {
  for (auto& i : todos) {
    storage_.insert({i.id(), i.task()});
  }
}

TodoStorage::TodoStorage() : TodoStorage({}, {}) {}

void TodoStorage::AddTodo(std::string name) {
  storage_.insert({id_generator_.GetNextId(), std::move(name)});
}

void TodoStorage::DeleteTodo(uint32_t id) {
  if (auto found = storage_.find(id); found != storage_.end()) {
    storage_.erase(found);
  }
}

TodoVector TodoStorage::GetAll() const {
  TodoVector ret;
  ret.reserve(storage_.size());
  for (const auto& i : storage_) {
    Todo todo;
    todo.set_allocated_task(std::make_unique<std::string>(i.second).release());
    todo.set_id(i.first);
    ret.push_back(std::move(todo));
  }
  return ret;
}
