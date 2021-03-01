// Copyright 2020 arsenykhoIod <arsenykholod@yandex.ru>

#include <gtest/gtest.h>
#include "stack_light.hpp"
#include "stack.hpp"

TEST(stack_light, push_lvalue) {
  int a = 23;
  int b = 17;
  stack_light<int> stack1;
  stack1.push(b);
  EXPECT_EQ(stack1.head(), b);
  stack1.push(a);
  EXPECT_EQ(stack1.head(), a);
}

TEST(stack_light, push_rvalue) {
  double ex1 = 9.8;
  double ex2 = 9.9;

  double ex3 = ex2;
  stack_light<double> stack1;
  stack1.push(ex1);
  EXPECT_EQ(stack1.head(), ex1);
  stack1.push(std::move(ex2));
  EXPECT_EQ(stack1.head(), ex3);
}

TEST(stack_light, pop) {
  char a = 'a';
  stack_light<char> stack1;
  stack1.pop();
  stack1.push(a);
  EXPECT_EQ(stack1.head(), 'a');
  stack1.push('u');
  EXPECT_EQ(stack1.head(), 'u');
  stack1.pop();
  EXPECT_EQ(stack1.head(), 'a');
}

TEST(stack_light, head_catch) {
  double e = 2.89;
  stack_light<double> stack1;
  EXPECT_THROW( stack1.head(), std::runtime_error);
  stack1.push(e);
  stack1.pop();
  EXPECT_THROW( stack1.head(), std::runtime_error);
}
//через перемещение
TEST(stack_light, move_constructible) {
  int i = 293;
  stack_light<int> stack1;
  stack1.push(i);
  stack_light<int> stack2(std::move(stack1));
  EXPECT_EQ(stack2.head(), i);
  EXPECT_EQ(std::is_move_constructible<stack_light<int>>::value,true);
}

TEST(stack_light, move_assignable) {
  char i = 'q';
  stack_light<char> stack1;
  stack1.push(i);
  stack_light<char> stack2;
  stack2 = std::move(stack1);
  EXPECT_EQ(stack2.head(), i);
  EXPECT_EQ(std::is_move_assignable<stack_light<char>>::value,true);
}
//через копирование
TEST(stack_light, copy_prohibited) {
  //проверяет на возможность присваивания копированием
  EXPECT_EQ(std::is_copy_assignable<stack_light<char>>::value, false);
  //проверяет на возможность создания объекта из копии другого объекта
  EXPECT_EQ(std::is_copy_constructible<stack_light<char>>::value,false);
}

struct example2 {
  int int_ex;
  char char_ex;
  bool operator==(const example2& ex) const { // needed for EXPECT_EQ
    if ((ex.char_ex == char_ex)&&(ex.int_ex == int_ex)) return true;
    else return false;
  }
  example2(const int& i, const char& c)
      : int_ex(i)
      , char_ex(c)
  {}
  example2(const example2& ex) = delete;
  example2(example2&& ex) noexcept
      : int_ex(ex.int_ex)
      , char_ex(ex.char_ex)
  {}
};

TEST(stack, push) {
  stack<int> stack2;
  stack2.push(18);
  EXPECT_EQ(stack2.head(), 18);
}

TEST(stack, head_catch) {
  stack<double> stack2;
  EXPECT_THROW(stack2.head(), std::runtime_error);
}

TEST(stack, push_emplace) {
  stack<example2> stack2;
  int i1 = 1;
  char c1 = 'a';
  stack2.push_emplace(i1, c1);
  EXPECT_EQ(stack2.head(), example2(i1, c1));

  int i2 = 2;
  char c2 = 'b';
  stack2.push_emplace(std::move(i2), std::move(c2));
  EXPECT_EQ(stack2.head(), example2(2, 'b'));

  int i3 = 3;
  char c3 = 'c';
  stack2.push_emplace(std::move(i3), c3);
  EXPECT_EQ(stack2.head(), example2(3, c3));
}

TEST(stack, pop) {
  stack<example2> stack2;
  example2 e1(0, '0');
  example2 e2(5, '5');
  example2 e3(0, '0');
  stack2.push(std::move(e1));
  stack2.push(std::move(e2));
  stack2.pop();
  EXPECT_EQ(stack2.head(), e3);
  stack2.pop();
  EXPECT_THROW(stack2.head(), std::runtime_error);
}

TEST(stack, move_constructible) {
  int i = 10;
  stack<int> stack1;
  stack1.push(std::move(i));
  stack<int> stack2(std::move(stack1));
  EXPECT_EQ(stack2.head(), 10);
  EXPECT_EQ(std::is_move_constructible<stack<int>>::value,true);
}

TEST(stack, move_assignable) {
  char c = 'q';
  stack<char> stack1;
  stack1.push(std::move(c));
  stack<char> stack2;
  stack2 = std::move(stack1);
  EXPECT_EQ(stack2.head(), 'q');
  EXPECT_EQ(std::is_move_assignable<stack<char>>::value,true);
}

TEST(stack, copy_prohibited) {
  EXPECT_EQ(std::is_copy_assignable<stack<char>>::value, false);
  EXPECT_EQ(std::is_copy_constructible<stack<char>>::value,false);
}