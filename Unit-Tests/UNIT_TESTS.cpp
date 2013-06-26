//
//  UNIT_TESTS_h
//  gcdpp-run
//
//  Created by Sergey Sergeev on 6/24/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#ifndef UNIT_TESTS_h
#define UNIT_TESTS_h

#include "gtest/gtest.h"
#include "gcdppLib.h"

TEST(gcdppLib, Dispatch_01)
{
    std::function<void(int, float, std::string)> function = [](int a, float b, const std::string& c)
    {
        EXPECT_TRUE(a == 1 && b == 2.0f && c == "Hello World");
    };
    gcdpp::impl::DispatchAsync<int, float, std::string>(gcdpp::queue::GetGlobalQueue(gcdpp::queue::GCDPP_DISPATCH_QUEUE_PRIORITY_LOW), function, 1, 2.0f, "Hello World");
}

class Clazz
{
    
public:
    
    std::string m_value;
    
    void Foo(int a, float b, const std::string& c)
    {
        std::cout<<a<<b<<c<<std::endl;
    };
};

TEST(gcdppLib, Dispatch_02)
{
    std::shared_ptr<Clazz> clazz = std::make_shared<Clazz>();
    clazz->m_value = "Hello World";
    
    std::function<void(std::shared_ptr<Clazz> )> function = [](std::shared_ptr<Clazz> clazz)
    {
        EXPECT_TRUE(clazz->m_value == "Hello World");
    };
    gcdpp::impl::DispatchAsync<std::shared_ptr<Clazz>>(gcdpp::queue::GetGlobalQueue(gcdpp::queue::GCDPP_DISPATCH_QUEUE_PRIORITY_LOW), function, clazz);
}

TEST(gcdppLib, Dispatch_03)
{
    std::function<void(void)> function = [](void)
    {
        EXPECT_TRUE(true);
    };
    gcdpp::impl::DispatchAsync(gcdpp::queue::GetGlobalQueue(gcdpp::queue::GCDPP_DISPATCH_QUEUE_PRIORITY_LOW), function);
}

TEST(gcdppLib, Dispatch_04)
{
    std::function<void(std::string)> function = [](const std::string& a)
    {
        std::function<void(std::string)> function = [](const std::string& a)
        {
            EXPECT_TRUE(a == "Hello World");
        };
        std::string b = a;
        b.append(" World");
        gcdpp::impl::DispatchAsync<std::string>(gcdpp::queue::GetMainQueue(), function, b);
    };
    gcdpp::impl::DispatchAsync<std::string>(gcdpp::queue::GetGlobalQueue(gcdpp::queue::GCDPP_DISPATCH_QUEUE_PRIORITY_LOW), function, "Hello");
}

typedef std::function<void(void)> task_t;

TEST(gcdppLib, Dispatch_05)
{
    std::shared_ptr<Clazz> clazz = std::make_shared<Clazz>();
    task_t task = std::bind(&Clazz::Foo, clazz, 1, 2.0f, "Hello World");
    gcdpp::impl::DispatchAsync(gcdpp::queue::GetGlobalQueue(gcdpp::queue::GCDPP_DISPATCH_QUEUE_PRIORITY_LOW), task);
}

#endif
