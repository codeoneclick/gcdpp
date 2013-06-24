//
//  gcdpp_impl.cpp
//
//  Created by Sergey Sergeev on 6/12/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include "gcdpp_impl.h"

std::shared_ptr<gcdpp::gcdpp_impl> gcdpp::gcdpp_impl::instance(void)
{
    static std::once_flag flag;
    static std::shared_ptr<gcdpp_impl> instance_ = nullptr;
    std::call_once(flag, []()
                   {
                       instance_ = std::make_shared<gcdpp_impl>();
                   });
    return instance_;
}


gcdpp::gcdpp_impl::gcdpp_impl(void)
{
    m_mainQueue = std::make_shared<gcdpp_t_main_queue>(GCDPP_DISPATCH_QUEUE_PRIORITY_MAIN_STR);
    m_poolQueue[gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_LOW] = std::make_shared<gcdpp_t_queue>(GCDPP_DISPATCH_QUEUE_PRIORITY_LOW_STR);
    m_poolQueue[gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_DEFAULT] = std::make_shared<gcdpp_t_queue>(GCDPP_DISPATCH_QUEUE_PRIORITY_DEFAULT_STR);
    m_poolQueue[gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH] = std::make_shared<gcdpp_t_queue>(GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH_STR);
}

gcdpp::gcdpp_impl::~gcdpp_impl(void)
{
    
}

std::shared_ptr<gcdpp::gcdpp_t_queue> gcdpp::gcdpp_impl::gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY _priority)
{
    assert(m_poolQueue[_priority] != nullptr);
    return m_poolQueue[_priority];
}
 
std::shared_ptr<gcdpp::gcdpp_t_main_queue> gcdpp::gcdpp_impl::gcdpp_dispatch_get_main_queue(void)
{
    assert(m_mainQueue != nullptr);
    return m_mainQueue;
}
