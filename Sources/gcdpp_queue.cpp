//
//  thread_concurrency_queue.cpp
//
//  Created by Sergey Sergeev on 6/12/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include "gcdpp_queue.h"
#include "gcdpp_task.h"

gcdpp::gcdpp_t_main_queue::gcdpp_t_main_queue(const std::string& _guid) :
m_guid(_guid)
{
    
}

gcdpp::gcdpp_t_main_queue::~gcdpp_t_main_queue(void)
{
    
}

void gcdpp::gcdpp_t_main_queue::append_task(std::shared_ptr<gcdpp_t_i_task> _task)
{
    m_queue.push(_task);
}

void gcdpp::gcdpp_t_main_queue::_Update(void)
{
    while(!m_queue.empty())
    {
        std::shared_ptr<gcdpp_t_i_task> task_ =  m_queue.front();
        m_queue.pop();
        task_->execute();
    }
}

gcdpp::gcdpp_t_queue::gcdpp_t_queue(const std::string& _guid) :
gcdpp_t_main_queue(_guid),
m_running(1),
m_thread(&gcdpp_t_queue::_Thread, this)
{
    
}

gcdpp::gcdpp_t_queue::~gcdpp_t_queue(void)
{
    m_running = 0;
    m_thread.join();
}

void gcdpp::gcdpp_t_queue::append_task(std::shared_ptr<gcdpp_t_i_task> _task)
{
    m_mutex.lock();
    m_queue.push(_task);
    m_mutex.unlock();
}

void gcdpp::gcdpp_t_queue::_Thread(void)
{
    while (m_running)
    {
        if(!m_queue.empty())
        {
            m_mutex.lock();
            std::shared_ptr<gcdpp_t_i_task> task_ =  m_queue.front();
            m_queue.pop();
            m_mutex.unlock();
            task_->execute();
        }
        else
        {
            std::this_thread::yield();
        }
    }
}