// Copyright 2020 arsenykhoIod <arsenykholod@yandex.ru>


#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP

template <typename T>
class stack {
 public:
  stack();
  stack(const stack& s) = delete;
  stack(stack&& s) noexcept;
  void operator=(const stack& s) = delete;
  void operator=(stack&& s) noexcept;

  template <typename ... Args>
  void push_emplace(Args&&... value);

  void push(T&& value);
  const T& head() const;
  ~stack();
  void pop();

  private:
  struct node
  {
    T body;
    node* previous;
    template <typename ... Args>
    explicit node(Args&&... args)
        : body(std::forward<Args>(args)...)
    {}
    explicit node(T&& elem)
        : body(std::move(elem))
    {}
  } *element;
};

template <typename T>
stack<T>::stack()
    : element(nullptr)
{}

template <typename T>
const T& stack<T>::head() const {
  if (!element) throw std::runtime_error("No elements in stack");
  return element->body;
}
template <typename T>
void stack<T>::push(T&& value) {
  node* tmp_pointer = new node(std::move(value));
  tmp_pointer->previous = element;
  element = tmp_pointer;
}

template <typename T>
//множечный шаблон (...)
template <typename... Args>
void stack<T>::push_emplace(Args&&... value)
{
  node* tmp_pointer = new node(std::forward<Args>(value)...);
  tmp_pointer->previous = element;
  element = tmp_pointer;
}
template <typename T>
void stack<T>::pop() {
  if (element) {
    node* tmp_pointer = element->previous;
    delete element;
    element = tmp_pointer;
  }
}

template <typename T>
stack<T>::~stack() {
  if (element){
    while (element->previous){
      node* tmp_pointer = element;
      element = element->previous;
      delete tmp_pointer;
    }
    delete element;
  }
}

template <typename T>
stack<T>::stack(stack&& s) noexcept
    : element(s.element)
{
  s.element = nullptr;
}

template <typename T>
void stack<T>::operator=(stack&& s) noexcept {
  element = std::move(s.element);
  s.element = nullptr;
}

#endif  // TEMPLATE_STACK_HPP
