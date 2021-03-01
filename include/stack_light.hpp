// Copyright 2020 arsenykhoIod <arsenykholod@yandex.ru>

#ifndef TEMPLATE_STACK_LIGHT_HPP
#define TEMPLATE_STACK_LIGHT_HPP

template <typename T>
class stack_light
{
 public:
  stack_light();
  //конструктор копироания -запрещён
  stack_light(const stack_light& s) = delete;
  //конструктор перемещения
  stack_light(stack_light&& s) noexcept;
  //оператор копирования запрещен
  void operator=(const stack_light& s) = delete;
  //оператор перемещения
  void operator=(stack_light&& s) noexcept;
  const T& head() const;
  void push(const T& value);
  void push(T&& value);
  void pop();
  ~stack_light();

 private:
  struct node
  {
    T body;
    node* previous;
    explicit node(const T& elem)
        : body(elem)
    {}
    explicit node(T&& elem)
        : body(std::move(elem))
    {}
  } *current;
};

template <typename T>
stack_light<T>::stack_light()
    : current(nullptr)
{}

template <typename T>
stack_light<T>::stack_light(stack_light&& s) noexcept
    : current(std::move(s.current))
{
  //иначе возможна утечка памяти
  s.current = nullptr;
}

template <typename T>
const T& stack_light<T>::head() const {
  if (!current) throw std::runtime_error("No elements in stack");
  return current->body;
}

template <typename T>
void stack_light<T>::push(const T& value) {
  node* tmp_pointer = new node(value);
  tmp_pointer->previous = current;
  current = tmp_pointer;
}

template <typename T>
void stack_light<T>::push(T&& value) {
  node* tmp_pointer = new node(std::move(value));//move разрывает связь между
  //именем и значением
  tmp_pointer->previous = current;
  current = tmp_pointer;
}

template <typename T>
void stack_light<T>::pop() {
  if (current) {
    node* tmp_pointer = current->previous;
    delete current;
    current = tmp_pointer;
  }
}

template <typename T>
stack_light<T>::~stack_light() {
  if (current){
    while (current->previous){
      node* tmp_pointer = current;
      current = current->previous;
      delete tmp_pointer;
    }
    delete current;
  }
}

template <typename T>
void stack_light<T>::operator=(stack_light&& s) noexcept{
  current = std::move(s.current);
  s.current = nullptr;
}

#endif  // TEMPLATE_STACK_LIGHT_HPP
